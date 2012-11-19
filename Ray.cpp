#include<iostream>
#include"Vector.h"
#include"Ray.h"
#include"Object.h"
#include"ObjectMaterial.h"

Ray::Ray(Vector &pt, Vector &dir)
{
	origin = pt;
	direction = dir;
}
Vector Ray::getDirection() const
{

	return direction;
}

Vector Ray::getOrigin() const
{
	return origin;
}

void Ray::setDirection(Vector &v)
{
	direction = v;
}

void Ray::setOrigin(Vector &v)
{
	origin = v;
}
