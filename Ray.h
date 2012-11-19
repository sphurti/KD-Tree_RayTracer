#ifndef RAY_H
#define RAY_H

#include<iostream>
#include "Vector.h"

class Ray {
	private:
		Vector origin;
		Vector direction;

	public:
		Ray(Vector &pt, Vector &dir);
		Vector getDirection() const;
		void setDirection(Vector &v_dir);
		Vector getOrigin() const;
		void setOrigin(Vector &v_pt);
};

#endif
