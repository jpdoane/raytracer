#pragma once
#include <memory>

#include "Vec3.h"
#include "Ray.h"
#include "Color.h"
#include "Material.h"
#include "Hit.h"

class Sphere : public Hittable
{
public:
    Vec3 center;
    float radius;
    const Material* material;

    Sphere(Vec3 center, float radius, const Material& material);
    ~Sphere();
    virtual bool hit(const Ray& ray, Hit& hit) const;
};