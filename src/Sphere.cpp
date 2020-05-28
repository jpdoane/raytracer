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
    hit.ray = ray;

    //hit location t for sphere and ray is:
    //t*t*dot(​B​,​B​) + 2*t*dot(​B,A​-​C​) + dot(​A-C,A​-​C​) - R*R = 0
    float a = dot(ray.direction, ray.direction);
    float b = 2*dot(ray.direction, ray.origin - center);
    Vec3 oc = ray.origin - center;
    float c = dot(oc, oc) - radius*radius;

    float discr = b*b - 4*a*c;
    //if discr<0, no intersection.
    //If discr>0 but b>0, then camera is inside circle, just don't show 
    if(discr > 0)
    {
        float sqrt_disc_plus_b = b + sqrt(discr);
        if( sqrt_disc_plus_b > 0 )
            return false; //smaller solution is negative, so camera is either in front of or inside the sphere, so don't record a hit

        //populate hit struct
        hit.t = -sqrt_disc_plus_b/(2*a); //return the smaller (closer) of two solutions
        hit.point = ray.pointAlongRay(hit.t);
        hit.normal = (hit.point - center).normalize();
        hit.material = material;
        return true;
    }
    else
        return false;
}
