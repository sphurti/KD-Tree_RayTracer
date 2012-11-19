#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Object.h"
#include "Ray.h"
#include "Scene.h"

class RayTracer 
{
	public:
		RayTracer();
		~RayTracer();
		virtual void setScene(Scene &sc) = 0;
		virtual float findNearestObject(const Ray &r, Object*& nearObj) = 0;
		virtual Color rayTrace(const Ray &r, float depth);

		Scene scene;
};

#endif
