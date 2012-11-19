#include "RayTracer.h"
#include <assert.h>

const int TRACE_DEPTH = 1;

RayTracer::RayTracer()
{
}

RayTracer::~RayTracer()
{
}

Color RayTracer::rayTrace(const Ray &r, float depth)
{
    bool pointVisibleToLightSource = false;
    Object *nearObj = NULL;
    float near_dist = INT_MAX;
    Color c(0.0, 0.0, 0.0);
    Color objColor;
    near_dist = findNearestObject(r, nearObj);
    if(near_dist != INT_MAX)
    {
        /* Some object has been hit */
        objColor = nearObj->getMaterial().getColor();
        assert(objColor != black);

        /* Shoot a ray from the intersection point towards all
           light sources */

        Vector int_pt = r.getOrigin() + r.getDirection() * near_dist;
        Vector normal = nearObj->getNormal(int_pt);
        normal.normalise();
        
        std::list<Light>::iterator light;
        std::list<Light> l = scene.getLights();

        float diff_color = 0.0;
        Object *nearObjLt = NULL;
        
        for( light = l.begin(); light != l.end(); light++ )
        {
            Vector dir = light->getPosition() - int_pt;
            dir.normalise();
            Ray new_ray(int_pt, dir);

            // find distance to nearest object between
            // intersection point and light source
            float near_dist_lt = INT_MAX;
            near_dist_lt = findNearestObject(new_ray, nearObjLt);
            if(!nearObjLt)
            {
                // both are unit vector so this is cos(theta)
                float dotpr = dir.dot_product(normal);
                if (dotpr > diff_color)
                    diff_color = dotpr;
                pointVisibleToLightSource = true;
            }
        }
        if (pointVisibleToLightSource)
        {
            // Add diffuse lighting
            float diff = diff_color * nearObj->getMaterial().getDiffuse();
            assert(objColor != black);
            if (diff > 0)
                objColor *= diff;
            assert(objColor != black);

            // Add specular lighting
            float spec = powf(diff_color, 20) * nearObj->getMaterial().getSpecular();
            objColor.addColor(white * spec);

            float refl = nearObj->getMaterial().getReflection();
            Color refl_color;
            if (refl > 0.0 && depth < TRACE_DEPTH)
            {
                Vector r_dir = r.getDirection();
                Vector dir = r_dir - normal * 2.0*r_dir.dot_product(normal);
                Ray* refl_ray = new Ray(int_pt, dir);
                refl_color = rayTrace(*refl_ray, depth + 1);
                objColor.addColor(refl_color * refl);
            }
            assert(objColor != black);
            return objColor;
        }
        else
        {
            objColor.setAmbient();
            assert(objColor != black);
            return objColor;
        }
    }
    return black;
}

