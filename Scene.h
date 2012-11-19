#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <stdio.h>
#include <list>
#include "Object.h"
#include "RayTracer.h"
#include "Light.h"

class RayTracer;
class Sphere;
class Light;
class Color;

class Scene {

	private:
		std::list<Object*> obj_list;
		std::list<Light> light_list;
		float width;
		float height;
		float depth;
		RayTracer *rayTracer;
		Color* col;
		void getFloatsFromColor(float*);

	public:
		Scene(); 
		~Scene();
		Scene(float h, float w, float d, RayTracer* rt);
		void setWindowSize(float h, float w);
		float getHeight();
		float getWidth();
		float getDepth();
		void addObject(Object* obj);
		void addLight(const Light& l);
		const std::list<Object*>& getObjects();
		const std::list<Light>& getLights();
		void renderScene(float** buffer);
		Color backgroundColor;
        bool checkInScene(const Vector& v);
};

#endif
