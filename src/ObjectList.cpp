#include "Hit.h"
#include "Sphere.h"
#include "ObjectList.h"
#include <iostream>

ObjectList::ObjectList(const Json::Value& config_scene)
: valid(false), backgroundColor(1,1,1)
{

    // example config:
    //
    // "scene":
    // [
    //     {
    //         "type": "sphere",
    //         "position": [0, 8.1, -3],
    //         "radius": 8,
    //         "color": [1,0,0],
    //         "material": "diffuse"            
    //     },
    //     {
    //         "type": "sphere",
    //         "position": [0, -1001, 0],
    //         "radius": 1000,
    //         "color": [0.3, 0.3, 0.3],
    //         "material": "diffuse"            
    //     }
    // ]

    try
    {
        for(unsigned int no=0;no<config_scene.size();no++)
        {
            const Json::Value& obj = config_scene[no];
            if(obj["type"].compare("background")==0)
            {
                backgroundColor = Color(obj["color"]);
            }
            else if(obj["type"].compare("sphere")==0)
            {            
                emplace_back(new Sphere(obj));
            }
            else
            {
                std::cerr << "Unknown Object Type: " << obj["type"] << std::endl;
            }
            
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error Parsing scene" << std::endl;
    }
    
    valid = true;
}

bool ObjectList::hit(const Ray& ray, Hit& hit) const
{
    Hit test_hit;
    float nearest = -1;

    for (const_iterator obj = begin(); obj != end(); ++obj)
    {
        if((*obj)->hit(ray, test_hit))
        {
            if(test_hit.distance < MINIMUM_HIT_DISTANCE || test_hit.distance > MAXIMUM_HIT_DISTANCE)
            if(nearest<0 || test_hit.distance < nearest)
            {
                hit = test_hit;
                nearest = test_hit.distance;                    
            }
        }
    }
    if(nearest>0)
        return true;

    return false;            
}
