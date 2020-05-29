#pragma once

#include <float.h>
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

#define MAXIMUM_HIT_DISTANCE .00001
#define MINIMUM_HIT_DISTANCE FLT_MAX

class Material;

struct Hit
{
    Ray ray;
    float distance;
    Vec3 point;
    Vec3 normal;
    const Material* material;
};

