#pragma once
#include "Ray.h"
#include "Hit.h"

class Material;

class Object
{
    private:
    bool valid;

    protected:
    const Material* material;

    public:
    Object(const Json::Value& config_object);
    ~Object();

    virtual bool hit(const Ray& ray, Hit& hit) const = 0;

    inline bool isValid() const {return valid;}
};
