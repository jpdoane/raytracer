#pragma once
#include "Object.h"
#include <jsoncpp/json/json.h>

#include <list>
#include <memory>

class ObjectList: public std::list<std::unique_ptr<Object> >
{
    bool valid;

    public:
    ObjectList(const Json::Value& config_scene);
    Color backgroundColor;
    
    bool hit(const Ray& ray, Hit& hit) const;

    inline bool isValid() const {return valid;}

};