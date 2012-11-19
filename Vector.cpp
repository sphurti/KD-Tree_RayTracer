#include<iostream>
#include"Vector.h"
#include"Ray.h"
#include"Object.h"
#include"ObjectMaterial.h"

Vector::Vector(float xc, float yc, float zc)
{
	x = xc;
	y = yc;
	z = zc;
} 

Vector::Vector(const Vector &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

float Vector::magnitude()
{
	float mag;
	mag = x*x + y*y + z*z;
	return(sqrtf(mag));
}

float Vector::dot_product(const Vector &v)
{
	return (x*v.x + y*v.y + z*v.z);
}

Vector Vector::cross_product(const Vector &v)
{
	Vector cp;
	cp.x = y * v.z - z * v.y;
	cp.y = z * v.x - x * v.z;
	cp.z = x * v.y - y * v.x;
	return cp;
}

Vector Vector::operator+(const Vector &v)
{
	Vector sum;
	sum.x = x+v.x;
	sum.y = y+v.y;
	sum.z = z+v.z; 
	return sum;
}

Vector Vector::operator*(float t)
{
	Vector v;
	v.x = x*t;
	v.y = y*t;
	v.z = z*t;	
	return v;
}

Vector Vector::operator-(const Vector &v)
{
	Vector diff;
	diff.x = x - v.x;
	diff.y = y - v.y;
	diff.z = z - v.z;
	return diff;
}

void Vector::operator=(const Vector &v)
{
	x = v.x;
	y = v.y;
	z = v.z; 
}

bool Vector::operator==(const Vector &v)
{
	if (x == v.x && y == v.y && z == v.z)
		return true;
	return false;
}

void Vector::normalise()
{
	float mag = magnitude();
	if (mag > 0.0) {
		x = x/mag;
		y = y/mag;
		z = z/mag;
	}
}

float Vector::length(const Vector &v1)
{
	Vector v = *this - v1;
	return (v.magnitude());
}

