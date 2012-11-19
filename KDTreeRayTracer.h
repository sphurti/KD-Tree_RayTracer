#ifndef KDTREERAYTRACER_H
#define KDTREERAYTRACER_H

#include "RayTracer.h"
#include "BoundingBox.h"

class KDTreeRayTracer : public RayTracer
{
	private:
		bool buildKDTree();
	public:
		KDTreeRayTracer();
		~KDTreeRayTracer();
		void setScene(Scene &sc);
		float findNearestObject(const Ray &r, Object*& nearObj);

		/* KD-Tree information */
		BoundingBox* tree_root;
		// how deep we want to go
		const size_t tree_depth;
};

#endif
