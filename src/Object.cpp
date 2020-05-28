#include "Object.h"
#include <iostream>

Object::Object(const Json::Value& config_object)
: valid(false), material(NULL)
{
    if(config_object.empty())
        return;

    try
    {
        std::string material_type = config_object["material"].asString();
        Color col(config_object["color"]);

        if(material_type.compare("flat")==0)
        {   
            material = new Flat(col);
        }
        else if(material_type.compare("diffuse")==0)
        {   
            material = new Diffuse(col);
        }
        else if(material_type.compare("reflective")==0)
        {   
            material = new Reflective(col);
        }
        else if(material_type.compare("colorize_normal")==0)
        {   
            material = new ColorizeNormal;
        }
        else
        {
           std::cerr << "Error:unknown material type " << material_type << std::endl;
           return;
        }
    }
    catch(const std::exception& e)
    {
       std::cerr << "Error parsing Object paramters" << std::endl;
        return;
    }

    valid = true;    
}


Object::~Object()
{
    if(material)
        delete material;
}
