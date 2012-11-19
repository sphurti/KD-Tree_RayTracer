#include "RayTracer.h"
#include "SimpleRayTracer.h"
#include "KDTreeRayTracer.h"
#include <string.h>
#include <GL/glut.h>

const float WIDTH = 600.0;
const float HEIGHT = 600.0;
const float DEPTH = 600.0;

RayTracer* rayTracer;
Scene* scene;

void display()
{
	float* buffer = (float*)malloc(3 * WIDTH * HEIGHT * sizeof(float));
    scene->renderScene(&buffer);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_FLOAT, buffer);
	glFlush();
}

int main(int argc, char *argv[])
{	
	rayTracer = dynamic_cast<RayTracer*>(new KDTreeRayTracer());
//	rayTracer = dynamic_cast<RayTracer*>(new SimpleRayTracer());
	scene = new Scene(WIDTH, HEIGHT, DEPTH, rayTracer);
	rayTracer->setScene(*scene);
	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple"); 
	glutDisplayFunc(display);
	glutMainLoop();
}

