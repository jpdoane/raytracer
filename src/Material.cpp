#include "Material.h"

bool Flat::scatter( const Hit& /*hit*/, Ray& /*scat*/, Color& albedo ) const
{
    albedo=alb;
    return false;
}

bool Diffuse::scatter( const Hit& hit, Ray& scat, Color& albedo ) const 
{
    scat = Ray(hit.point, hit.point + hit.normal + rnd.rand_in_sphere());
    albedo=alb;
    return true;
}

bool Reflective::scatter( const Hit& hit, Ray& scat, Color& albedo ) const 
{
    scat.origin = hit.point;
    scat.direction = hit.ray.direction - 2*dot(hit.normal,hit.ray.direction)*hit.normal;
    albedo=alb;
    return true;
}


bool ColorizeNormal::scatter( const Hit& hit, Ray& /*scat*/, Color& albedo ) const
{
    albedo = normalizedVecToColor(hit.normal);
    return false;
}

