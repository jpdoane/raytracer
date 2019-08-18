#include "Camera.h"

Camera::Camera(Vec3 location, Vec3 lookAt, Vec3 up, float view_distance, float view_width, float view_height)
: camera_origin(location)
{   
    Vec3 camera_to_viewport = lookAt-camera_origin;
    camera_to_viewport.setLength(view_distance);

    viewU = cross(camera_to_viewport, up).setLength(view_width);    
    viewV = cross(viewU, camera_to_viewport).setLength(view_height);    
    //viewV = cross(camera_to_viewport,viewU).setLength(view_height);    

    //put origin in upper left
    viewport_origin = camera_origin + camera_to_viewport - viewU/2 - viewV/2; 
}

//return ray from camera to point in viewport.  u,v are [0,1]
Ray Camera::makeRay(float u, float v)
{    
    Ray r = Ray(camera_origin, viewport_origin + viewU*u + viewV*v);
    return r;
}
