#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <limits.h>
#include <stdio.h>
#include "Vector.h"
#include "ObjectMaterial.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Light.h"

static float SCENE_ERROR = 0.5;

class BoundingBox;

class Object {

	protected :
		int obj_id;
		Vector obj_pos;
		ObjectMaterial obj_mat;

	public:
		Object();
		~Object();
		Object(Vector &v);
		int getID() const;
		Vector getPosition() const;
		ObjectMaterial getMaterial() const;
		void setPosition(const Vector &pos);
		void setMaterial(ObjectMaterial &om);
		virtual bool getRayIntersection(const Ray &r, Vector& x_point) = 0;
		virtual bool getBoundingBoxIntersection(const BoundingBox &b, Vector& x_point) = 0;
		virtual Vector getNormal(Vector &int_pt) = 0;
};

class Sphere: public Object {

	private:
		float radius;

	public:
		Sphere(Vector c, float r);
        ~Sphere();
		Vector getNormal(Vector &int_pt);
		bool getRayIntersection(const Ray &ray, Vector& x_point);
        bool getBoundingBoxIntersection(const BoundingBox& b, Vector& x_point);
		float getRadius() const;
};

class Plane: public Object {

	private:
		Vector normal;   // normal vector
        float dist;     // distance along normal to origin

	public:
		Plane(Vector n, float d);
        ~Plane();
		Vector getNormal();
        Vector getNormal(Vector& x);
        // Return if the ray intersects the plane
		bool getRayIntersection(const Ray &ray, Vector& x_point);
        bool getBoundingBoxIntersection(const BoundingBox& b, Vector& x_point);
		float getDistance() const;
};
#endif
