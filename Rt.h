#pragma once

#include "Rand.h"
#include "Ray.h"
#include "Hit.h"
#include "Color.h"

class Rt
{
    unsigned int w,h;
    unsigned char* image_data;
    unsigned int depthLimit;

    Rand rnd;

    public:

    Rt(int h, int w);
    ~Rt();

    void render();
    Color getColor(const Ray& r, const Hittable& world, unsigned int depth = 0);

    unsigned char* getImage();
};

