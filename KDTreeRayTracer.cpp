#include <iostream>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stack>

#include "Vector.h"
#include "Ray.h"
#include "Object.h"
#include "ObjectMaterial.h"
#include "KDTreeRayTracer.h"
#include "Scene.h"
#include "Light.h"

KDTreeRayTracer::KDTreeRayTracer() :
	tree_depth(3)
{
	
}

KDTreeRayTracer::~KDTreeRayTracer()
{
}

/* We use a uniform grid to build the KD-Tree */
bool KDTreeRayTracer::buildKDTree()
{
	// create root BoundingBox
	Vector* orig = new Vector(0, 0, 0);
	tree_root = new BoundingBox(*orig, scene.getWidth(), 
			scene.getHeight(), scene.getDepth());
	tree_root->box_depth = 0;
	std::list<Object*> ol = scene.getObjects();
	std::list<Object*>::iterator it;
	for (it = ol.begin(); it != ol.end(); it++)
		tree_root->objs.push_back(*it);

	// create stack for traversal while building
	std::stack<BoundingBox*> box_stack;
	box_stack.push(tree_root);

	// build tree
	BoundingBox* cur_box;
	while (!box_stack.empty()) {
		cur_box = box_stack.top();
		box_stack.pop();
		
		if (cur_box->box_depth == tree_depth) // we reached the leaf
			continue;
		else {
			BoundingBox* l_child = new BoundingBox();
			BoundingBox* r_child = new BoundingBox();
			assert(cur_box->split(cur_box->findMaxDimension(), 
					*l_child, *r_child));
			cur_box->l_child = l_child;
			cur_box->r_child = r_child;
			box_stack.push(l_child);
			box_stack.push(r_child);
		}
	}
	fprintf(stderr, "Finished building tree\n");
	return true;
}

void KDTreeRayTracer::setScene(Scene &sc)
{
	scene = sc;
	buildKDTree();
}

float KDTreeRayTracer::findNearestObject(const Ray &r , Object*& nearObj)
{
	Vector ray_entry, ray_exit;
	float near_dist = INT_MAX;
	std::stack<BoundingBox*> box_stack;

	// push root on to stack
	box_stack.push(tree_root);

	while (!box_stack.empty()) {
		BoundingBox* cur_box = box_stack.top();
		box_stack.pop();

		// check if we are at a leaf node
		if (cur_box->box_depth == tree_depth) {
			// there are objects in leaf node
			if (cur_box->objs.size() > 0) { 
				std::list<Object*>::iterator it;
				for (it=cur_box->objs.begin(); it != 
						cur_box->objs.end(); it++) {
					Vector pt;
                    // if the ray doesn't intersect, continue
                    if(!(*it)->getRayIntersection(r, pt))
						continue;
                    // if the ray intersects outside the scene, continue
                    if (!scene.checkInScene(pt))
                        continue;
					float obj_dist = pt.length(r.getOrigin());
					if(obj_dist < near_dist)
					{
						near_dist = obj_dist;
						nearObj = *it;
					}
				}
				if (near_dist < INT_MAX) // we hit an object
					return near_dist;
			} else
				continue;
		} else { // we aren't at a leaf node yet
			if (cur_box->l_child->containsPoint(r.getOrigin())) {
				// ray origin is in l_child
				if (cur_box->r_child->intersectsRay(r))
					box_stack.push(cur_box->r_child);
				box_stack.push(cur_box->l_child);
			} else { // ray origin in r_child
				if (cur_box->l_child->intersectsRay(r))
					box_stack.push(cur_box->l_child);
				box_stack.push(cur_box->r_child);
			}				
		}
				
	}
	return near_dist;
}

