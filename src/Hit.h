#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

class Material;

struct Hit
{
    Ray ray;
    float t;
    Vec3 point;
    Vec3 normal;
    const Material* material;
};

