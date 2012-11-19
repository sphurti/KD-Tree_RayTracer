#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "Vector.h"
#include "Ray.h"
#include "Object.h"
#include "ObjectMaterial.h"
#include "RayTracer.h"
#include "Scene.h"

Light::Light()
{
	pos.x = 0.0;
	pos.y = 0.0;
	pos.z = 0.0;
}

Light::~Light()
{
}

Light::Light(Vector v)
{
	pos.x = v.x;
	pos.y = v.y;
	pos.z = v.z;
}

Vector Light::getPosition()
{
	return pos;
}

void Light::setPosition(Vector& v)
{
	pos.x = v.x;
        pos.y = v.y;
        pos.z = v.z;
}
