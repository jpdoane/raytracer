#pragma once

#include "Vec3.h"

class Ray
{
public:
    Vec3 origin;
    Vec3 direction;

    Ray() {}
    Ray(const Vec3& from, const Vec3& to): origin(from) { pointTowards(to); }

    //functions to alter direction vector
    const Vec3& pointTowards(const Vec3& to) { return direction = to-origin; }
    Vec3 pointAlongRay(float t) const { return origin + direction*t; }

    const Ray& setLength(float len) { direction.setLength(len); return *this; }
    const Ray& normalize() { return setLength(1); }

    const Ray& addToHead( const Vec3& v ) { origin += v; return *this; }
    const Ray& addToTail( const Vec3& v ) { direction += v; return *this; }

};
