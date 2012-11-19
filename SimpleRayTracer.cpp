#include <iostream>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "Vector.h"
#include "Ray.h"
#include "Object.h"
#include "ObjectMaterial.h"
#include "SimpleRayTracer.h"
#include "Scene.h"
#include "Light.h"

SimpleRayTracer::SimpleRayTracer()
{
}

SimpleRayTracer::~SimpleRayTracer()
{
}

void SimpleRayTracer::setScene(Scene &sc)
{
	scene = sc;
}

float SimpleRayTracer::findNearestObject(const Ray &r , Object*& nearObj)
{
	float near_dist = INT_MAX;
	std::list<Object*>::iterator obj;
	std::list<Object*> l = scene.getObjects();
	for( obj = l.begin(); obj != l.end(); obj++ )
	{     
		Vector pt;
        // if the ray doesn't intersect, continue
        if (!(*obj)->getRayIntersection(r, pt))
			continue;
        // if the ray intersects outside the scene, continue
        if (!scene.checkInScene(pt))
            continue;
		float obj_dist = pt.length(r.getOrigin());
		if(obj_dist < near_dist)
		{
			near_dist = obj_dist;
			nearObj = *obj;
		}
	}
	return near_dist;
}

