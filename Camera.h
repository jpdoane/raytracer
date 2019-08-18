#pragma once
#include "Vec3.h"
#include "Ray.h"

class Camera
{
Vec3 camera_origin, viewport_origin;
Vec3 viewU, viewV;

public:

    Camera(Vec3 location, Vec3 lookAt, Vec3 up, float view_distance, float view_width, float view_height);

    Ray makeRay(float u, float v);
};