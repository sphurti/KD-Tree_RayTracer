#include <iostream>
#include <stdio.h>
#include "Vector.h"
#include "Ray.h"
#include "Object.h"
#include "ObjectMaterial.h"
#include "Light.h"

static int id_ctr = 0;

Object::Object()
{
    obj_id = id_ctr++;
}

Object::Object(Vector &v)
{
    obj_id = id_ctr++;
	obj_pos = v;
}

Object::~Object()
{
}

int Object::getID() const
{
	return obj_id;
}

Vector Object::getPosition() const
{
	return obj_pos;
}

ObjectMaterial Object::getMaterial() const
{
	return obj_mat;
}

void Object::setPosition(const Vector &pos)
{
	obj_pos = pos;
}

void Object::setMaterial(ObjectMaterial &om)
{
	obj_mat = om;
}

Sphere::Sphere(Vector c,float r):Object(c)
{
	radius = r;
}

Vector Sphere::getNormal(Vector &int_pt)
{
	Vector normal = int_pt - obj_pos;
	return normal;
}

Sphere::~Sphere()
{
}

float Sphere::getRadius() const
{
	return radius;
}

bool Sphere::getRayIntersection(const Ray &ray, Vector& x_point)
{
    Vector d = ray.getOrigin() - obj_pos;
    Vector dir = ray.getDirection();
    dir.normalise();
    float int_dist = INT_MAX;

    float b = (d.dot_product(dir))*2;
    float discriminant = (b*b) - 4*d.dot_product(d) + 4*radius*radius;

    if(discriminant > 0.0)
    {
        discriminant = sqrtf(discriminant);
        float r1 = ((b * -1) + discriminant) / 2;
        float r2 = ((b * -1) - discriminant) / 2;
        if(r1 > 0.0)
        {
            if(r2 < 0.1)
            { 
                if(r1 < int_dist)
                    int_dist = r1;
            }
            else{
                if (r2 < int_dist)
                    int_dist = r2;
            }
        }
    }
    if (int_dist < 0.1)
        return false;
    if (int_dist == INT_MAX)
        return false;
    x_point = (ray.getOrigin() + (ray.getDirection())*int_dist);
    return true;
}

/* Basically check for non-overlapping axes. If there exists at least one axis
 * where the sphere and the box don't overlap then they don't intersect */
bool Sphere::getBoundingBoxIntersection(const BoundingBox& b, Vector& x_point)
{
	// box low end
	float b_low_x = b.lbc.x;
	float b_low_y = b.lbc.y;
	float b_low_z = b.lbc.z;

	// box high end
	float b_high_x = b.lbc.x + b.x_len;
	float b_high_y = b.lbc.y + b.y_len;
	float b_high_z = b.lbc.z + b.z_len;

	// sphere low end
	float s_low_x = obj_pos.x - radius;
	float s_low_y = obj_pos.y - radius;
	float s_low_z = obj_pos.z - radius;

	// sphere high end
	float s_high_x = obj_pos.x + radius;
	float s_high_y = obj_pos.y + radius;
	float s_high_z = obj_pos.z + radius;

	if ((b_low_x - s_high_x) * (b_high_x - s_low_x) < 0)
		return true;
	if ((b_low_y - s_high_y) * (b_high_y - s_low_y) < 0)
		return true;
	if ((b_low_z - s_high_z) * (b_high_z - s_low_z) < 0)
		return true;
	return false;
}

Plane::Plane(Vector n,float d)
{
	normal = n;
    dist = d;
}

Plane::~Plane()
{
}

bool Plane::getRayIntersection(const Ray& ray, Vector& x_point)
{
    float d = normal.dot_product(ray.getDirection());
    if (d != 0) {
        float x_dist = -(normal.dot_product(ray.getOrigin()) + dist) / d;
        if (x_dist > 0.1) {
            x_point = ray.getOrigin() + ray.getDirection() * x_dist;
            return true;
        }
    }
    return false;
}

bool Plane::getBoundingBoxIntersection(const BoundingBox& b, Vector& x_point)
{
    float den = normal.x*normal.x + normal.y*normal.y + normal.z*normal.z;
    Vector v = normal * (dist / den);
    Vector point_on_plane = Vector(fabs(v.x), fabs(v.y), fabs(v.z));
    Vector ldf = b.lbc;
    Vector rdf = Vector(b.lbc.x + b.x_len, b.lbc.y, b.lbc.z);
    Vector ldb = Vector(b.lbc.x, b.lbc.y, b.lbc.z + b.z_len);
    Vector rdb = Vector(b.lbc.x + b.x_len, b.lbc.y, b.lbc.z + b.z_len);
    Vector rub = Vector(b.lbc.x + b.x_len, b.lbc.y + b.y_len, b.lbc.z + b.z_len);
    Vector ruf = Vector(b.lbc.x + b.x_len, b.lbc.y + b.y_len, b.lbc.z);
    Vector lub = Vector(b.lbc.x, b.lbc.y + b.y_len, b.lbc.z + b.z_len);
    Vector luf = Vector(b.lbc.x, b.lbc.y + b.y_len, b.lbc.z);

    // all corners need to be on the same side of the plane
    if (normal.dot_product(ldf - point_on_plane) > 0 &&
            normal.dot_product(ldb - point_on_plane) > 0 &&
            normal.dot_product(luf - point_on_plane) > 0 &&
            normal.dot_product(lub - point_on_plane) > 0 &&
            normal.dot_product(rdf - point_on_plane) > 0 &&
            normal.dot_product(rdb - point_on_plane) > 0 &&
            normal.dot_product(ruf - point_on_plane) > 0 &&
            normal.dot_product(rub - point_on_plane) > 0)
        return false;
    
    if (normal.dot_product(ldf - point_on_plane) < 0 &&
            normal.dot_product(ldb - point_on_plane) < 0 &&
            normal.dot_product(luf - point_on_plane) < 0 &&
            normal.dot_product(lub - point_on_plane) < 0 &&
            normal.dot_product(rdf - point_on_plane) < 0 &&
            normal.dot_product(rdb - point_on_plane) < 0 &&
            normal.dot_product(ruf - point_on_plane) < 0 &&
            normal.dot_product(rub - point_on_plane) < 0)
        return false;

    return true;
}

Vector Plane::getNormal()
{
	return normal;
}

Vector Plane::getNormal(Vector& x)
{
	return normal;
}

float Plane::getDistance() const
{
	return dist;
}

