#include "Camera.h"
#include <vector>
#include <iostream>

    // example json
    // "camera": {
    //     "position": [0, 15, 15],
    //     "lookAt": [0,0,0],
    //     "up": [0,1,0],
    //     "view_distance": 8
    //     "view_width": 8
    //     "view_height": 8
    // }

Camera::Camera(const Json::Value& config)
: valid(false)
{
    if(config.empty())
        return;

    try
    {
        //camera paramters are required
        lookAt = config["lookAt"];
        camera_up = config["up"];
        view_distance  = config["view_distance"].asFloat();
        view_height  = config["view_height"].asFloat();
        view_width  = config["view_width"].asFloat();

        locateCamera(config["position"]);
    }
    catch(const std::exception& e)
    {
       std::cerr << "Error parsing Camera paramters" << std::endl;
        return;
    }
    

    valid = true;
}

void Camera::locateCamera(const Vec3& position)
{
        camera_origin = position;
        updateGeometry();
}

void Camera::locateLook(const Vec3& look)
{
        lookAt = look;
        updateGeometry();
}

void Camera::zoomCamera(float zoom)
{
        view_distance += zoom;
        updateGeometry();
}

void Camera::moveLook(float pan_right, float tilt_up)
{
        lookAt += viewU*pan_right/view_width + viewV*tilt_up/view_height;
        updateGeometry();
}

void Camera::moveCamera(float right, float up, float in)
{
    Vec3 camera_to_viewport = lookAt-camera_origin;
    camera_to_viewport.normalize();
    camera_origin += viewU*right/view_width + viewV*up/view_height + camera_to_viewport*in;
    updateGeometry();
}


void Camera::updateGeometry()
{
        Vec3 camera_to_viewport = lookAt-camera_origin;
        camera_to_viewport.setLength(view_distance);

        viewU = cross(camera_to_viewport, camera_up).setLength(view_width);    
        viewV = cross(viewU, camera_to_viewport).setLength(view_height);    

        //put origin in upper left
        viewport_origin = camera_origin + camera_to_viewport - viewU/2 - viewV/2; 
}

//return ray from camera to point in viewport.  u,v are [0,1]
Ray Camera::makeRay(float u, float v)
{    
    Ray r = Ray(camera_origin, viewport_origin + viewU*u + viewV*v);
    return r;
}
