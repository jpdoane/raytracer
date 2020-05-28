#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
    bool valid;
    Vec3 center;
    float radius;

    Sphere(const Json::Value& config_sphere);
    ~Sphere();
    virtual bool hit(const Ray& ray, Hit& hit) const;

    inline bool isValid() const {return valid;}
};