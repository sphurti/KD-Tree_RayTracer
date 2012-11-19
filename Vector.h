#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<math.h>

class Vector{

	private:

	public:
		float x,y,z;
		Vector() {}
		~Vector() {}
		Vector(float xc, float yc, float zc);
		Vector(const Vector &v);
		float dot_product(const Vector &v);
		Vector cross_product(const Vector &v);
		Vector unit_vector();
		Vector operator+(const Vector &v1);
		Vector operator-(const Vector &v1);
		Vector operator*(float t);
		void operator=(const Vector &v1);
		bool operator==(const Vector &v1);
		float magnitude();
		void  normalise();
		float length(const Vector &v1);
};

#endif
