#include <stdlib.h>
#include <stdio.h>
#include <list>
#include "Vector.h"
#include "Ray.h"
#include "Object.h"
#include "ObjectMaterial.h"
#include "RayTracer.h"
#include "Light.h"

Scene::Scene()
{
}

Scene::Scene(float w, float h, float d, RayTracer* rt):
	width(w),
	height(h),
	depth(d),
	rayTracer(rt)
{
	// Allocate Color array to hold colors returned by raytracer
	col = (Color*)malloc(sizeof(Color) * height * width);

    // ground plane
    Plane* p1 = new Plane(Vector(0, 1, 0), 0);
	ObjectMaterial* p1_om = new ObjectMaterial();
	p1_om->setColor(blue);
    p1_om->setReflection(0.1);
	p1->setMaterial(*p1_om);
	addObject(p1);

    // wall plane
    Plane* p2 = new Plane(Vector(0, 0, -1), depth);
	ObjectMaterial* p2_om = new ObjectMaterial();
	p2_om->setColor(mauve2);
//    p2_om->setReflection(0.3);
	p2->setMaterial(*p2_om);
	addObject(p2);

    // right wall plane
    Plane* p3 = new Plane(Vector(-1, 0, 0), width-1);
	ObjectMaterial* p3_om = new ObjectMaterial();
	p3_om->setColor(white);
    p3_om->setReflection(0.3);
	p3->setMaterial(*p3_om);
	addObject(p3);
 
    // roof plane
    Plane* p5 = new Plane(Vector(0, -1, 0), height);
	ObjectMaterial* p5_om = new ObjectMaterial();
	p5_om->setColor(blue);
    p3_om->setReflection(0.3);
	p5->setMaterial(*p5_om);
	addObject(p5);

    // left wall plane
    Plane* p4 = new Plane(Vector(1, 0, 0), 0);
	ObjectMaterial* p4_om = new ObjectMaterial();
	p4_om->setColor(white);
//    p4_om->setReflection(0.3);
	p4->setMaterial(*p4_om);
	addObject(p4);


	// Add a sphere to scene
	Sphere* s = new Sphere(Vector(350, 80, 340), 80);
	ObjectMaterial* om = new ObjectMaterial();
	om->setColor(red);
    om->setReflection(0.8);
	s->setMaterial(*om);
	addObject(s);

    //Sphere s1(Vector(340, 340, 340),100.0);
    Sphere* s1 = new Sphere(Vector(175, 140, 160),130.0);
    ObjectMaterial* om1 = new ObjectMaterial();
    om1->setColor(green);
    om1->setReflection(0.8);
    om1->setSpecular(0.9);
    s1->setMaterial(*om1);
    addObject(s1);

	Light l1(Vector(50, 50, -600));
	addLight(l1);
}

Scene::~Scene()
{
    free(col);
}

float Scene::getHeight()
{
	return height;
}

float Scene::getWidth()
{
	return width;
}

float Scene::getDepth()
{
	return depth;
}

const std::list<Object*>& Scene::getObjects()
{
	return obj_list;
}

void Scene::addObject(Object* o)
{
	obj_list.push_front(o);
}

void Scene::addLight(const Light &l)
{
        light_list.push_front(l);
}

const std::list<Light>& Scene::getLights()
{
        return light_list;
}

void Scene::getFloatsFromColor(float* b)
{
	int ctr = 0;
	for (int i=0; i<height * width; i++) {
		b[ctr++] = col[i].r;
		b[ctr++] = col[i].g;
		b[ctr++] = col[i].b;
	}
}

void Scene::renderScene(float** buffer)
{
	for (int i=0; i<height * width; i++) {
        /* Create a ray with origin as the point on the screen. For the simple
           ray-tracer, we can use the "eye" as the ray-origin, but the KDTree
           tracer requires the origin of a ray to be in the root BoundingBox
           so set direction as (screen_point - eye) and origin as screen_point
        */
		float ro_x = width / 2; 
		float ro_y = height / 2;
        float ro_z = -500.0;
		Vector* eye = new Vector(ro_x, ro_y, ro_z);
        Vector* screen_point = new Vector(i % (int)width, i / (int)width, 0.0);
		Vector* direction = new Vector(*screen_point - *eye);
        direction->normalise();
		Ray* ray = new Ray(*screen_point, *direction);
		// Call rayTrace for (i,j)
		col[i] = rayTracer->rayTrace(*ray, (float)0);
	}
	getFloatsFromColor(*buffer);
}

bool Scene::checkInScene(const Vector& v)
{
    if (v.x < 0 - SCENE_ERROR || v.x > width + SCENE_ERROR)
        return false;
    if (v.y < 0 - SCENE_ERROR || v.y > height + SCENE_ERROR)
        return false;
    if (v.z < 0 - SCENE_ERROR || v.z > depth + SCENE_ERROR)
        return false;
    return true;
}
