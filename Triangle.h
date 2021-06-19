#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
		///@param a b c are three vertex positions of the triangle
	
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m){
		hasTex = false;
		this->a = a;
		this->b = b;
		this->c = c;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){

		//Initializing Matrix ColumnWise
		Matrix3f M(a-b, a-c, ray.getDirection(), true);

		Vector3f B = a-ray.getOrigin();

		Vector3f X = M.inverse() * B;

		float alpha, beta, gamma, t;

		beta = X[0]; gamma = X[1]; t = X[2];
		alpha = 1-beta-gamma;

		//Intersection
		if(beta+gamma <= 1 && beta >= 0 && gamma >= 0 && t > tmin && t < hit.getT())
		{
			hit.set(t, material, (alpha*normals[0] + beta*normals[1]+  gamma*normals[2]).normalized());
			return true;
		}
		return false;
	}
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:

	Vector3f a, b, c;
};

#endif //TRIANGLE_H
