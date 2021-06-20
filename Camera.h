#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}

	virtual float getFocalLength() const = 0;
	virtual float getFStop() const = 0;
	virtual int getSamples() const = 0;
protected:
	Vector3f center; 
	Vector3f direction;
	Vector3f up;
	Vector3f horizontal;
};

class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle, float fl=1, float fs=25, int s=4);

	virtual Ray generateRay( const Vector2f& point);

	virtual float getTMin() const { 
		return 0.0f;
	}

	virtual float getFocalLength() const { return focal_length;  }
	virtual float getFStop() const { return fstop; }
	virtual int getSamples() const { return samples; };

private:
	float angle;
	float focal_length;
	float fstop;
	int samples;
};

#endif //CAMERA_H
