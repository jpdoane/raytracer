#pragma once
#include "Vec3.h"
#include "Ray.h"
#include <jsoncpp/json/json.h>

class Camera
{
bool valid;
Vec3 camera_origin, viewport_origin;
Vec3 viewU, viewV;

public:

    Camera(const Json::Value& config);
    Ray makeRay(float u, float v);

    inline bool isValid() const {return valid;}
};