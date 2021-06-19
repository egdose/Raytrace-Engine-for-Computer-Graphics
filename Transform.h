#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
	Transform(){assert(false);}
	Transform( const Matrix4f& m, Object3D* obj ):o(obj), m(m)
	{
		m_prime = m.inverse();
	}
	~Transform(){
	}
	virtual bool intersect( const Ray& r , Hit& h , float tmin)
	{
		Vector4f cal1 = Vector4f(r.getOrigin(), 1);
		Vector3f newOrigin = (m_prime*cal1).xyz();

		cal1 = Vector4f(r.getDirection(), 0);
		Vector3f newDirection = (m_prime*cal1).xyz();

		Ray newRay(newOrigin, newDirection);

		if (o->intersect( newRay , h , tmin))
		{
			float t = h.getT();
			Vector3f oldNormal = h.getNormal();

			Vector3f newNormal = m_prime.transposed().getSubmatrix3x3(0, 0) * oldNormal;
			newNormal.normalize();

			h.set(t, h.getMaterial(), newNormal);
			return true;
		}

		return false;
	}

 protected:
	Object3D* o; //un-transformed object	
	Matrix4f m, m_prime;
};

#endif //TRANSFORM_H
