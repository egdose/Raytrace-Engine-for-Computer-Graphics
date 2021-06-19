#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere(){ 
		//unit ball at the center
		this->centerPoint = Vector3f(0.0f, 0.0f, 0.0f);
		this->radius = 1.0f;
		this->type = 'S';
	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material){
		this->centerPoint = center;
		this->radius = radius;
		this->type = 'S';
	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		Vector3f rayOrigin = r.getOrigin() - centerPoint;

		//Using Equations
		//Week 5 Slide 13
		float a = r.getDirection().absSquared();
		float b = 2.0f * Vector3f::dot(r.getDirection(), rayOrigin);
		float c = Vector3f::dot(rayOrigin, rayOrigin) - (radius*radius);

		float deter = (b*b) - (4*a*c);

		if(deter<0) //Impossible Solution
		{
			return false;
		}

		deter = sqrt(deter);

		float t1 = ((-1)*b + deter)/(2.0f*a);
		float t2 = ((-1)*b - deter)/(2.0f*a);

		if((t1 < tmin && t2 < tmin)) //|| deter < 0) //Bound Checking
		{
			return false;
		}

		if(t1 > h.getT() && t2 > h.getT())
		{
			return false;
		}

		if (t2 >= tmin && t1 >= tmin) //If both intersections are in front
		{
			//Picking the smaller one
			float T = (t2<=t1 ? t2 : t1);
			//cout << "T: " << T << endl;

			//Gives us the normal of point of intersection
			Vector3f normal = (r.pointAtParameter(T) - centerPoint).normalized(); 

			//Updating the Hit Data Structure
			h.set(T, material, normal);
			return true;
		}
		else //Only one of the is in front
		{
			//Picking the one in front
			float T = (t2 >= tmin ? t2 : t1);
			//cout << "T: " << T << endl;

			//Gives us the normal of point of intersection
			Vector3f normal = (r.pointAtParameter(T) - centerPoint).normalized(); 

			//Updating the Hit Data Structure
			h.set(T, material, normal);
			return true;
		}

		return false;
	}

protected:
	Vector3f centerPoint;
	float radius;
};


#endif
