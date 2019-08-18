#pragma once
#include "Color.h"
#include "Hit.h"
#include "Rand.h"

struct Hit;

class Material
{
    protected:
    Color alb;

    public:
    Material(Color albedo): alb(albedo) {}
    virtual ~Material() {}

    virtual bool scatter( const Hit& /*hit*/, Ray& /*scat*/, Color& albedo ) const = 0;
    virtual Material* clone_new() const = 0;
};

class Flat: public Material
{
    Flat(Color albedo): Material(albedo) {}
    virtual bool scatter( const Hit& /*hit*/, Ray& /*scat*/, Color& albedo ) const;
    virtual Flat* clone_new() const { return new Flat(*this); };
};


class Diffuse : public Material
{
    mutable Rand rnd;

    public:
    Diffuse(Color albedo): Material(albedo) {}

    virtual bool scatter( const Hit& hit, Ray& scat, Color& albedo ) const;
    virtual Diffuse* clone_new() const { return new Diffuse(*this); };
};

class ColorizeNormal : public Material
{
    public:
    ColorizeNormal(): Material(Color()) {}

    virtual bool scatter( const Hit& hit, Ray& scat, Color& albedo ) const;
    virtual ColorizeNormal* clone_new() const { return new ColorizeNormal(*this); };
};