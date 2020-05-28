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
        Vec3 lookAt(config["lookAt"]);
        Vec3 up(config["up"]);

        camera_origin = Vec3(config["position"]);

        float distance  = config["view_distance"].asFloat();
        float height  = config["view_height"].asFloat();
        float width  = config["view_width"].asFloat();

        Vec3 camera_to_viewport = lookAt-camera_origin;
        camera_to_viewport.setLength(distance);

        viewU = cross(camera_to_viewport, up).setLength(width);    
        viewV = cross(viewU, camera_to_viewport).setLength(height);    

        //put origin in upper left
        viewport_origin = camera_origin + camera_to_viewport - viewU/2 - viewV/2; 
    }
    catch(const std::exception& e)
    {
       std::cerr << "Error parsing Camera paramters" << std::endl;
        return;
    }
    

    valid = true;
}

//return ray from camera to point in viewport.  u,v are [0,1]
Ray Camera::makeRay(float u, float v)
{    
    Ray r = Ray(camera_origin, viewport_origin + viewU*u + viewV*v);
    return r;
}
