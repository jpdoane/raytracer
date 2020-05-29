#pragma once
#include "Color.h"
#include "Hit.h"
#include "Rand.h"
#include <jsoncpp/json/json.h>

struct Hit;

class Material
{
    protected:
    Color alb;

    public:
    Material(Color albedo): alb(albedo) {}
    virtual ~Material() {}

    virtual bool scatter( const Hit& /*hit*/, Ray& /*scat*/, Color& albedo ) const = 0;
};

class Flat: public Material
{
    public:
    Flat(Color albedo): Material(albedo) {}
    virtual bool scatter( const Hit& /*hit*/, Ray& /*scat*/, Color& albedo ) const;
};


class Diffuse : public Material
{
    mutable Rand rnd;

    public:
    Diffuse(Color albedo): Material(albedo) {}

    virtual bool scatter( const Hit& hit, Ray& scat, Color& albedo ) const;
};

class Reflective : public Material
{
    mutable Rand rnd;
    float fuzz;

    public:
    Reflective(Color albedo, float fuzz=0): Material(albedo), fuzz(fuzz) {}

    virtual bool scatter( const Hit& hit, Ray& scat, Color& albedo ) const;
};


class ColorizeNormal : public Material
{
    public:
    ColorizeNormal(): Material(Color()) {}

    virtual bool scatter( const Hit& hit, Ray& scat, Color& albedo ) const;
};