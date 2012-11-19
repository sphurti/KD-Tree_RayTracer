CC     = g++
CFLAGS = -g -Wall
LFLAGS = -lX11 -lglut -lGL -lGLU -lXmu 
OBJS = BoundingBox.o Light.o Object.o Ray.o RayTracer.o KDTreeRayTracer.o SimpleRayTracer.o Scene.o Vector.o ObjectMaterial.o main.o

all: raytrace

raytrace: $(OBJS)
	$(CC) $(OBJS) -o raytrace $(LFLAGS)

BoundingBox.o: BoundingBox.cpp BoundingBox.h
	$(CC) $(CFLAGS) -c -o $@ $<

Light.o: Light.cpp Light.h
	$(CC) $(CFLAGS) -c -o $@ $<

Object.o: Object.cpp Object.h
	$(CC) $(CFLAGS) -c -o $@ $<

Ray.o: Ray.cpp Ray.h
	$(CC) $(CFLAGS) -c -o $@ $<

RayTracer.o: RayTracer.cpp RayTracer.h
	$(CC) $(CFLAGS) -c -o $@ $<

KDTreeRayTracer.o: KDTreeRayTracer.cpp KDTreeRayTracer.h
	$(CC) $(CFLAGS) -c -o $@ $<

SimpleRayTracer.o: SimpleRayTracer.cpp SimpleRayTracer.h
	$(CC) $(CFLAGS) -c -o $@ $<

Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) -c -o $@ $<

Vector.o: Vector.cpp Vector.h
	$(CC) $(CFLAGS) -c -o $@ $<

ObjectMaterial.o: ObjectMaterial.cpp ObjectMaterial.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f raytrace *.o

# This is GNU makefile extension to notify that roughly means: 'clean' does
# not depend on any files in order to call it.
.PHONY: clean
