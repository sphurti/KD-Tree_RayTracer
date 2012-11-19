#ifndef OBJECTMATERIAL_H
#define OBJECTMATERIAL_H

#include<iostream>
#include<math.h>
#include "Vector.h"
#include "Light.h"

#define AMBIENT		0.1

class Color {
	public:
		float r;
		float g;
		float b;
		Color();
		~Color();
		Color(float, float, float);
        Color operator*(float t);
        void operator*=(float t);
        bool operator!=(const Color& rhs);
        bool operator==(const Color& rhs);
        void addColor(const Color& rhs);
		void setAmbient();
		void diffuse(float);
};

// file scope
static Color black(0.0, 0.0, 0.0);
static Color white(1.0, 1.0, 1.0);
static Color red(1.0, 0.0, 0.0);
static Color blue(0.0, 0.0, 1.0);
static Color green(0.0, 1.0, 0.0);
static Color mauve1(0.4, 0.3, 0.3);
static Color mauve2(0.45, 0.3, 0.3);

class ObjectMaterial {
	private:
		Color color;
		float diffuse;
        float specular;
		float reflection;
		float refraction;

	public:
		ObjectMaterial();
		~ObjectMaterial() {}
		Color getColor();
		float getDiffuse();
		float getSpecular();
		float getReflection();
		float getRefraction();
		void setColor(Color &c);
		void setDiffuse(float diff);
		void setSpecular(float spec);
		void setReflection(float refl);
		void setRefraction(float refr);
};

#endif
