#pragma once

#include "Rand.h"
#include "Hit.h"
#include "Color.h"
#include "ObjectList.h"
#include "Camera.h"
#include "Image.h"

#include <jsoncpp/json/json.h>
#include <functional>

class Rt
{
    bool valid;
    unsigned int aa;
    unsigned int depthLimit;

    Image* image;
    Camera* cam;
    ObjectList* world;

    Rand rnd;

    public:

    Rt(const Json::Value& config);
    ~Rt();

    void render();
    std::function<bool(void)> updateImageCallback;

    Color getColor(const Ray& r, const ObjectList& world, unsigned int depth = 0);

    unsigned char* getImage();

    inline bool isValid() const {return valid;}
};
