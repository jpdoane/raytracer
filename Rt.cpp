#include "Rt.h" 

#include "Vec3.h"
#include "Ray.h"
#include "Color.h"
#include "Camera.h"
#include "Sphere.h"
#include "Material.h"

#include <stdlib.h> 

Rt::Rt(int w, int h)
: w(w), h(h)
{
    image_data = new unsigned char[h*w*3];
    depthLimit = 25;	
}

Rt::~Rt()
{
    delete[] image_data;
}

unsigned char* Rt::getImage()
{
    return image_data;
}

void Rt::render()
{
    unsigned int Naa = 100;

    Camera cam(Vec3(0,0,8), Vec3(0,0,0), Vec3(0,1,0), 1, 8, 6);

    HittableList world;
    world.emplace_back(new Sphere(Vec3(0,0,-3), 8, Diffuse(RED)));
    world.emplace_back(new Sphere(Vec3(0,-1e4-10,0), 1e4, Diffuse(GREY)));
    
    for(unsigned int px = 0; px<w; px++)
    {
        //floating point x-coord 
        float x = (float)px / w;
        for(unsigned int py = 0; py<h; py++)
        {
            //floating point y-coord, py increases down, y increases up
            float y = 1.0 - (float)py / h;
            Color pix_color(0,0,0);
            for(unsigned int naa = 0; naa<Naa; naa++)
            {
                //floating point coords of antialiased subpixel
                float xaa = x + rnd.uniform_signed(.5/w);
                float yaa = y + rnd.uniform_signed(.5/h);

                //cast ray from camera to pixel
                Ray r = cam.makeRay(xaa,yaa);
                pix_color += getColor(r, world);

            }
            pix_color /= Naa; //average all antialias runs
            unsigned int px_idx = 3*(px + py*w);
            image_data[px_idx] = pix_color.r_char();
            image_data[px_idx + 1] = pix_color.g_char();
            image_data[px_idx + 2] = pix_color.b_char();
        }
    }

}

Color Rt::getColor(const Ray& r, const Hittable& world, unsigned int depth)
{
    Color backgroundColor = WHITE;

    Hit hit;
    Color c;
    if(world.hit(r,hit))
    {
        Color albedo;
        Ray scatter;
        if(hit.material->scatter(hit, scatter, albedo) && depth < depthLimit)
            return albedo*getColor(scatter, world, depth+1);
        else
            return albedo;            
    }

    return backgroundColor;
}