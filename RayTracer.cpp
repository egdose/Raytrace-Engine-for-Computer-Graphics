#include "RayTracer.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Group.h"
#include "Material.h"
#include "Light.h"

#define EPSILON 0.001

//IMPLEMENT THESE FUNCTIONS
//These function definitions are mere suggestions. Change them as you like.
Vector3f mirrorDirection( const Vector3f& normal, const Vector3f& incoming)
{
	//Week 7 - Slide 14
	Vector3f Reflected = incoming - 2*Vector3f::dot(normal, incoming)*normal;
	return Reflected.normalized();

	// Vector3f reflection = incoming - (2 * (Vector3f::dot(incoming,normal)) * normal);
	// return reflection.normalized();
}

bool transmittedDirection( const Vector3f& normal, const Vector3f& incoming, 
				float index_n, float index_nt, 
				Vector3f& transmitted)
{
	//Equation Given in Assignment PDF
	float cal1 = Vector3f::dot(incoming,normal);
	float cal2 = cal1 * cal1;
	float cal3 = ((index_n*index_n)*(1 - cal2))/(index_nt*index_nt);
	float cal4  = 1 - cal3;
	
	if(cal4 < 0)
		return false;

	Vector3f cal5 = normal * sqrt(cal4);
	Vector3f cal6 = cal1 * normal;
	Vector3f cal7 = incoming - cal6;
	Vector3f cal8 = (index_n * cal7)/index_nt;


	transmitted = (cal8 - cal5).normalized();
	return true;
}

RayTracer::RayTracer( SceneParser * scene, ArgParser* arg 
	//more arguments if you need...
											) :
	m_scene(scene)
{
	g=scene->getGroup();
	m_maxBounces = arg->bounces;
	args = arg;
}

RayTracer::~RayTracer()
{
}

Matrix3f RayTracer::traceRay( Ray& currentRay, float tmin, int bounces,
				float refr_index, Hit& hit ) const
{
	//cout << "HERE2\t";
	//Check ray intersection with Group of Objects
	Vector3f pixelColor(0.0f), depthColor(0.0f), normalColor(0.0f);
	bool toReturn = false;
	if(m_scene->getGroup()->intersect(currentRay, hit, tmin))
	{
		//cout << "Intersection Found!\n";
		float T = hit.getT();
		Vector3f ambientLight = m_scene->getAmbientLight();
		Vector3f diffShading = Vector3f(0.0f);
		Vector3f Ka = hit.getMaterial()->getDiffuseColor();
		for(register int light = 0 ; light < m_scene->getNumLights() ; ++light)
		{
			//cout << "Light: " << light << endl;
			Vector3f dirToLight; 
			Vector3f lightColor;
			float distanceToLight;
			Vector3f intersectionPoint = currentRay.pointAtParameter(T);
				m_scene->getLight(light)->getIllumination(intersectionPoint, dirToLight,
													lightColor, distanceToLight);
			

			if(args->shadows == 1)
			{
				Ray ray2(intersectionPoint, dirToLight);
				Hit hit2(distanceToLight, NULL, NULL);
				
				if(! g->intersectShadowRay(ray2, hit2, EPSILON))
					diffShading += hit.getMaterial()->Shade(currentRay, hit, dirToLight, lightColor);
			}
			else
			{
				diffShading += hit.getMaterial()->Shade(currentRay, hit, dirToLight, lightColor);
			}
		}
		
		//cout << "Calculating pixel color\n";
		// ambientLight.print();
		// Ka.print();
		// diffShading.print();
		pixelColor = ambientLight*Ka + diffShading;
		

		//cout << args << endl;

		if (T < args->depth_min)
		{
			//cout << "if (T < args->depth_min)\n";
			depthColor = Vector3f(1.0f);
		}
		else if (T > args->depth_max)
		{
			//cout << "else if (T > args->depth_max)\n";
			depthColor = Vector3f(0.0f);
		}
		else
		{
			//cout << "else\n";
			float difference = args->depth_max -  args->depth_min;
			float new_T = T - args->depth_min;
			depthColor = Vector3f(1 - new_T/difference);
		}
		
		//cout << "Calculated\n";
	}
	else
	{
		//cout << "No Intersection!\n";
		pixelColor = m_scene->getBackgroundColor(currentRay.getDirection()); //Change this later
		depthColor = Vector3f(0.0f);
		normalColor = Vector3f(0.0f);
		toReturn = true;
	}

	if (toReturn)
	{
		Matrix3f colors(pixelColor, depthColor, normalColor);
		return colors;
	}

	//Checking Reflection and Refraction
	if(bounces < m_maxBounces)
	{
		//--------------------------------------------
		//-REFLECTION---------------------------------
		//--------------------------------------------
		Vector3f reflectedColor(0.0f);
		float T = hit.getT();
		Vector3f intersectionPoint = currentRay.pointAtParameter(T);
		Ray Reflected(intersectionPoint, mirrorDirection(hit.getNormal().normalized(), currentRay.getDirection()));
		Hit recursiveHit;

		Matrix3f Reflection = traceRay(Reflected, EPSILON, bounces+1, refr_index, recursiveHit);
		Material* current = hit.getMaterial();
		if(current != nullptr)
			reflectedColor = Reflection.getCol(0)*current->getSpecularColor();
		else
			reflectedColor = Reflection.getCol(0);



		//--------------------------------------------
		//-REFRACTION---------------------------------
		//--------------------------------------------
		Vector3f refractedColor(0.0f);
		Vector3f transmitted;
		float n = refr_index;
		float nt;

		bool notTotalReflection;
		//If the angle between Ray and Normal is less than 90, means we are inside an object
		bool insideObject = (Vector3f::dot(currentRay.getDirection(), hit.getNormal().normalized()))>0;
		Vector3f normal = hit.getNormal().normalized();
		if(insideObject)
		{
			normal = normal*-1.0f;
			nt = 1.0;
		}
		else
		{
			if(hit.getMaterial() != nullptr)
				nt = hit.getMaterial()->getRefractionIndex();
			else
				nt = 1.0f;
		}
		notTotalReflection = transmittedDirection(normal, currentRay.getDirection(),
								refr_index, nt, transmitted); //We are going into the AIR so 1.0 Index

		Ray transmittedRay(intersectionPoint, transmitted);
		Hit transmittedHit;

		if(notTotalReflection)
		{
			refractedColor = (traceRay(transmittedRay, EPSILON, bounces+1, 
								nt, transmittedHit)).getCol(0);

			if(current != nullptr)
				refractedColor = refractedColor*current->getSpecularColor();

			//--------------------------------------------
			//-CALCULATING WEIGHTS------------------------
			//--------------------------------------------
			Vector3f t = transmitted;
			Vector3f d = currentRay.getDirection();
			Vector3f N = normal;

			float c;
			if(n <= nt)
			{
				c = abs(Vector3f::dot(-1.0f*d, N));
			}
			else
			{
				c = abs(Vector3f::dot(t, N));
			}

			float Ro = pow((nt-n)/(nt+n), 2);

			float R = Ro + (1-Ro) * pow(1-c, 5);

			//cout << "R: " << R << endl;

			pixelColor += + (1-R)*refractedColor + (R)*reflectedColor;

			// if(R >= 0 && R <= 1)
			// {
			// 	//ADDING REFLECTION COLOR
			// 	pixelColor += (R)*(reflectedColor);

			// 	//ADDING REFRACTION COLOR
			// 	pixelColor += (1-R)*(refractedColor);
			// }
			// else if(R>1)
			// {
			// 	//ADDING REFLECTION COLOR
			// 	pixelColor += (reflectedColor);
			// }
			// else
			// {
			// 	//ADDING REFRACTION COLOR
			// 	pixelColor += (refractedColor);
			// }
		}
		else
		{
			pixelColor += reflectedColor;
		}


	}

	normalColor = hit.getNormal();

	Matrix3f colors(pixelColor, depthColor, normalColor);

	return colors;
}
