#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include <cassert>
#include <vector>
#include "SceneParser.h"
#include "Ray.h"
#include "Hit.h"
#include "ArgParser.h"
#include <omp.h>

class SceneParser;


class RayTracer
{
public:
	
	RayTracer()
	{
		assert( false );
	}

	RayTracer( SceneParser* scene, ArgParser* arg //more arguments as you need...
	);
	~RayTracer();
	
	Matrix3f traceRay( Ray& currentRay, float tmin, int bounces, 
										float refr_index, Hit& hit ) const;

	
private:
	SceneParser* m_scene;

	int m_maxBounces;
	Group* g;
	ArgParser* args;
};

#endif // RAY_TRACER_H
