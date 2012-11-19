#ifndef	MATRIX_H
#define	MATRIX_H

#include<iostream>
#include<math.h>

class Matrix{

	private:
		float m[4][4];

	public:
		Matrix();
		Matrix(Matrix &m1);
		void set(Matrix &m1);
		Matrix operator+(Matrix &m1, Matrix &m2);
		Matrix operator-(Matrix &m1, Matrix &m2);
};

#endif
