#pragma once
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

#include <list>
#include <memory>

class Material;

struct Hit
{
    Ray ray;
    float t;
    Vec3 point;
    Vec3 normal;
    const Material* material;
};

class Hittable
{
    public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, Hit& hit) const = 0;
};

class HittableList: public Hittable, public std::list<std::unique_ptr<Hittable> >
{
    virtual bool hit(const Ray& ray, Hit& hit) const
    {
        Hit test_hit;
        float nearest = -1;

        //for (std::list<std::unique_ptr<Hittable> >::const_iterator obj = begin(); obj != end(); ++obj)
        for (const_iterator obj = begin(); obj != end(); ++obj)
        {
            if((*obj)->hit(ray, test_hit))
            {
                if(nearest<0 || test_hit.t < nearest)
                {
                    hit = test_hit;
                    nearest = test_hit.t;                    
                }
            }
        }
        if(nearest>0)
            return true;

        return false;            
    }
};