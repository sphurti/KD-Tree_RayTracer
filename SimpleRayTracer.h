#ifndef SIMPLERAYTRACER_H
#define SIMPLERAYTRACER_H

#include "RayTracer.h"

class SimpleRayTracer : public RayTracer
{
	public:
		SimpleRayTracer();
		~SimpleRayTracer();
		void setScene(Scene &sc);
		float findNearestObject(const Ray &r, Object*& nearObj);
};

#endif
