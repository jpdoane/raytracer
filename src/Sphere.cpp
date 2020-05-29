#include "Sphere.h"

#include <iostream>
#include <math.h>

Sphere::Sphere(const Json::Value& config_sphere)
: Object(config_sphere), valid(false)
{
    if(!Object::isValid() || config_sphere.empty())
        return;

    try
    {
        center = Vec3(config_sphere["position"]);
        radius = config_sphere["radius"].asFloat();
    }
    catch(const std::exception& e)
    {
       std::cerr << "Error parsing Sphere paramters" << std::endl;
        return;
    }

    valid = true;    
}

Sphere::~Sphere()
{
}


//return distance down ray where intersection occurs.  negative if no intersection (or behind camera)
bool Sphere::hit(const Ray& ray, Hit& hit) const
{
    //vector from sphere center to ray origin
    Vec3 oc = ray.origin - center;

    //hit distance t for sphere and ray is:
    //t*t*dot(​B​,​B​) + 2*t*dot(​B,A​-​C​) + dot(​A-C,A​-​C​) - R*R = 0

    float a = dot(ray.direction, ray.direction);
    float b_2 = dot(ray.direction, oc);  // b/2
    float c = dot(oc, oc) - radius*radius;
    float discr_4 = b_2*b_2 - a*c;  // (b^2-4ac)/4
    
    //if discr<0, no intersection.
    //If discr>0 but b>0, then camera is inside circle, just don't show 
    if(discr_4 > 0)
    {
        float sqrt_disc_plus_b_over_2 = b_2 + sqrt(discr_4); // (b + sqrt(b^2-4ac))/2
        if( sqrt_disc_plus_b_over_2 > 0 )
            return false; //smaller solution is negative, so camera is either in front of or inside the sphere, so don't record a hit

        //populate hit struct
        hit.ray = ray;
        hit.distance = -sqrt_disc_plus_b_over_2/a; //return the smaller (closer) of two solutions
        hit.point = ray.pointAlongRay(hit.distance);
        hit.normal = (hit.point - center).normalize();
        hit.material = material;
        return true;
    }
    else
        return false;

}
