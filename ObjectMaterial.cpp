#include<iostream>
#include"Vector.h"
#include"Ray.h"
#include"Object.h"
#include"ObjectMaterial.h"
#include "Light.h"

Color::Color()
{
	r = 0.0;
	g = 0.0;
	b = 0.0;
}

Color::~Color()
{
}

Color::Color(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
}

void Color::addColor(const Color& rhs)
{
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
}

Color Color::operator*(float t)
{
	Color c;
	c.r = r*t;
	c.g = g*t;
	c.b = b*t;	
	return c;
}

void Color::operator*=(float t)
{
	r = r*t;
	g = g*t;
	b = b*t;	
}

bool Color::operator==(const Color& rhs)
{
	if (r == rhs.r && g == rhs.g && b == rhs.b)
        return true;
    return false;
}

bool Color::operator!=(const Color& rhs)
{
	if (r == rhs.r && g == rhs.g && b == rhs.b)
        return false;
    return true;
}

void Color::setAmbient()
{
	r = AMBIENT * r;
	b = AMBIENT* b;
	g = AMBIENT * g;
}

ObjectMaterial::ObjectMaterial()
{
    reflection = 0;
    refraction = 0;
    diffuse = 0.3;
    specular = 0.5;
}

Color ObjectMaterial::getColor()
{
	return color;
}

float ObjectMaterial::getDiffuse()
{
	return diffuse;
}

float ObjectMaterial::getSpecular()
{
	return specular;
}

float ObjectMaterial::getReflection()
{
	return reflection;
}

float ObjectMaterial::getRefraction()
{
	return refraction;
}

void ObjectMaterial::setColor(Color &c)
{
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
}

void ObjectMaterial::setReflection(float refl)
{
	reflection = refl;
}

void ObjectMaterial::setRefraction(float refr)
{
	refraction = refr;
}

void ObjectMaterial::setDiffuse(float diff)
{
	diffuse = diff;
}

void ObjectMaterial::setSpecular(float spec)
{
	specular = spec;
}
