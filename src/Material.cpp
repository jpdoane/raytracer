#include "Material.h"

bool Flat::scatter( const Hit& /*hit*/, Ray& /*scat*/, Color& albedo ) const
{
    albedo=alb;
    return false;
}

bool Diffuse::scatter( const Hit& hit, Ray& scat, Color& albedo ) const 
{
    scat = Ray(hit.point, hit.point + hit.normal + rnd.randn3());
    // scat = Ray(hit.point, hit.point + hit.normal + rnd.rand_in_sphere());
    albedo=alb;
    return true;
}

bool Reflective::scatter( const Hit& hit, Ray& scat, Color& albedo ) const 
{
    scat.origin = hit.point;
    albedo=alb;

    if(fuzz==0)
    {
        scat.direction = hit.ray.direction - 2*dot(hit.normal,hit.ray.direction)*hit.normal;
        return true;
    }
    else
    {
        do
        {
            scat.direction = hit.ray.direction - 2*dot(hit.normal,hit.ray.direction)*hit.normal + rnd.randn3(fuzz);
        } while (dot(scat.direction,hit.normal)<0); //make sure scattered ray doesn't go inside ball
        return true;
    }
        
}


bool ColorizeNormal::scatter( const Hit& hit, Ray& /*scat*/, Color& albedo ) const
{
    albedo = normalizedVecToColor(hit.normal);
    return false;
}

