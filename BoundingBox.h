#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <list>
#include "Vector.h"
#include "Object.h"

enum Axis
{
	XAXIS,
	YAXIS,
	ZAXIS
};

class Object;

class BoundingBox
{
	public:
		BoundingBox();
		BoundingBox(const Vector& orig, float x_l, float y_l, 
			float z_l);
		~BoundingBox();

		/* Splits the object in the middle along the specified axis
		 * and updates the children */
		bool split(Axis ax, BoundingBox& lchild, BoundingBox& rchild);
		Axis findMaxDimension();
		bool containsPoint(const Vector& p);
		bool intersectsRay(const Ray& r);
	public:
		Vector lbc; // lower-bottom-corner
		// Size of the box
		float x_len;
		float y_len;
		float z_len;

		size_t box_depth;
		Axis split_axis; // axis along which the box is split next
		std::list<Object*> objs; // objects in box

		BoundingBox* l_child;
		BoundingBox* r_child;
		
};

#endif
