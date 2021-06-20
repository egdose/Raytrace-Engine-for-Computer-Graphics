#include "Camera.h"

PerspectiveCamera::PerspectiveCamera(const Vector3f& center, const Vector3f& direction, const Vector3f& up, float angle, float fl, float fs, int s)
{
		this->center = Vector3f(center);
		this->direction = Vector3f(direction).normalized();
		this->horizontal = Vector3f::cross(direction, up).normalized();
		this->up = Vector3f::cross(this->horizontal, direction).normalized();
		this->angle = angle;
		this->focal_length = fl;
		this->fstop = fs;
		this->samples = s;
}

Ray PerspectiveCamera::generateRay( const Vector2f& point){
		float D = 1.0f/ tan(angle/2);

		Vector3f rayDirection = D*direction + horizontal*point[0] + up*point[1];
		Ray newRay(this->center, rayDirection.normalized());

		return newRay;
}
