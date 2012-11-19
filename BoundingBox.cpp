#include <stdio.h>
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	l_child = NULL;
	r_child = NULL;
}

BoundingBox::BoundingBox(const Vector& orig, float x_l, float y_l, 
		float z_l) :
	lbc(orig),
	x_len(x_l),
	y_len(y_l),
	z_len(z_l)
{	
	BoundingBox();
}

BoundingBox::~BoundingBox()
{
}

bool BoundingBox::split(Axis ax, BoundingBox& l_child, BoundingBox& r_child) {

	// set lbcs for children
	l_child.lbc = lbc;
	r_child.lbc = lbc;

	// set dimensions for children
	l_child.x_len = x_len;
	l_child.y_len = y_len;
	l_child.z_len = z_len;
	r_child.x_len = x_len;
	r_child.y_len = y_len;
	r_child.z_len = z_len;

	switch(ax) {
		case XAXIS: 
			r_child.lbc.x = (lbc.x + x_len) / 2;
			r_child.x_len = x_len / 2;
			l_child.x_len = x_len / 2;
			break;
		case YAXIS: 
			r_child.lbc.y = (lbc.y + y_len) / 2;
			r_child.y_len = y_len / 2;
			l_child.y_len = y_len / 2;
			break;
		case ZAXIS: 
			r_child.lbc.z = (lbc.z + z_len) / 2;
			r_child.z_len = z_len / 2;
			l_child.z_len = z_len / 2;
			break;
	}

	// set tree_depth for children
	l_child.box_depth = box_depth + 1;
	r_child.box_depth = box_depth + 1;
	
	// set objects appropriately
	std::list<Object*>::iterator it;
    Vector x_point;
	for (it = objs.begin(); it != objs.end(); it++) {
		if ((*it)->getBoundingBoxIntersection(l_child, x_point))
			l_child.objs.push_back(*it);
		if ((*it)->getBoundingBoxIntersection(r_child, x_point))
			r_child.objs.push_back(*it);
	}
	
	// set this split_axis
	split_axis = ax;
	return true;
}

Axis BoundingBox::findMaxDimension() {
	if (x_len > y_len) {
		if (x_len > z_len)
			return XAXIS;
	} else {
		if (y_len > z_len)
			return YAXIS;
	}
	return ZAXIS;
}

bool BoundingBox::containsPoint(const Vector& p)
{
	// box low end
	float b_low_x = lbc.x;
	float b_low_y = lbc.y;
	float b_low_z = lbc.z;

	// box high end
	float b_high_x = lbc.x + x_len;
	float b_high_y = lbc.y + y_len;
	float b_high_z = lbc.z + z_len;

	if (p.x >= b_low_x && p.x <= b_high_x &&
			p.y >= b_low_y && p.y <= b_high_y &&
			p.z >= b_low_z && p.z <= b_high_z)
		return true;
	return false;
}

bool BoundingBox::intersectsRay(const Ray& r)
{
	// box low end
	float b_low_x = lbc.x;
	float b_low_y = lbc.y;
	float b_low_z = lbc.z;

	// box high end
	float b_high_x = lbc.x + x_len;
	float b_high_y = lbc.y + y_len;
	float b_high_z = lbc.z + z_len;

	float t_near = INT_MIN;
	float t_far = INT_MAX;
	float t1, t2;

	Vector r_o = r.getOrigin();
	Vector r_d = r.getDirection();

	if (r_d.x == 0) { // ray parallel to x plane
		if (r_o.x < b_low_x || r_o.x > b_high_x)
			return false;
	} else {
		t1 = (b_low_x - r_o.x) / r_d.x;	
		t2 = (b_high_x - r_o.x) / r_d.x;
		if (t1 > t2) { // swap
			t1 = t1 - t2;
			t2 = t2 + t1;
			t1 = t2 - t1;
		}
		if (t1 > t_near) t_near = t1;
		if (t2 < t_far) t_far = t2;
		if (t_near > t_far) return false;
		if (t_far < 0) return false;
	}

	if (r_d.y == 0) { // ray parallel to x plane
		if (r_o.y < b_low_y || r_o.y > b_high_y)
			return false;
	} else {
		t1 = (b_low_y - r_o.y) / r_d.y;	
		t2 = (b_high_y - r_o.y) / r_d.y;
		if (t1 > t2) { // swap
			t1 = t1 - t2;
			t2 = t2 + t1;
			t1 = t2 - t1;
		}
		if (t1 > t_near) t_near = t1;
		if (t2 < t_far) t_far = t2;
		if (t_near > t_far) return false;
		if (t_far < 0) return false;
	}

	if (r_d.z == 0) { // ray parallel to x plane
		if (r_o.z < b_low_z || r_o.z > b_high_z)
			return false;
	} else {
		t1 = (b_low_z - r_o.z) / r_d.z;	
		t2 = (b_high_z - r_o.z) / r_d.z;
		if (t1 > t2) { // swap
			t1 = t1 - t2;
			t2 = t2 + t1;
			t1 = t2 - t1;
		}
		if (t1 > t_near) t_near = t1;
		if (t2 < t_far) t_far = t2;
		if (t_near > t_far) return false;
		if (t_far < 0) return false;
	}

	return true;
}
