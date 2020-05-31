#pragma once
#include "Vec3.h"
#include "Ray.h"
#include <jsoncpp/json/json.h>

class Camera
{
    bool valid;
    Vec3 lookAt, camera_up, camera_origin, viewport_origin;
    float view_height,view_distance,view_width;
    Vec3 viewU, viewV;

    void updateGeometry();

public:

    Camera(const Json::Value& config);
    //absolute camera movements
    void locateCamera(const Vec3& position);
    void locateLook(const Vec3& look);

    //relative camera movements
    void zoomCamera(float zoom);
    void moveLook(float pan_right, float tilt_up);
    void moveCamera(float right, float up, float in);

    Ray makeRay(float u, float v);
    inline bool isValid() const {return valid;}
};