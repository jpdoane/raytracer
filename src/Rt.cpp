#include "Rt.h" 

#include "Vec3.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include "Material.h"

#include <iostream> 


Rt::Rt(const Json::Value& config)
:valid(false), image(NULL), cam(NULL), world(NULL)
{
    //parse config
    try
    {   
        Json::Value render = config["render"];

        aa = render.get("raysperpixel",100).asUInt();
        depthLimit = render.get("max_depth",25).asUInt();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error parsing render paramters" << std::endl;
        return;
    }

    image = new Image(config["image"]);
    if(!image->isValid()) return;

    cam = new Camera(config["camera"]);
    if(!cam->isValid()) return;

    world = new ObjectList(config["scene"]);
    if(!world->isValid()) return;
 
    valid = true;
}

Rt::~Rt()
{
    if(image)
        delete image;
    if(cam)
        delete cam;
    if(world)
        delete world;
}

unsigned char* Rt::getImage()
{
    return image->get_data();
}

void Rt::render()
{    
    unsigned int w = image->get_width();
    unsigned int h = image->get_height();
    unsigned char* image_data = image->get_data();
    for(unsigned int px = 0; px<w; px++)
    {
        //floating point x-coord 
        float x = (float)px / w;
        for(unsigned int py = 0; py<h; py++)
        {
            //floating point y-coord, py increases down, y increases up
            float y = 1.0 - (float)py / h;
            Color pix_color(0,0,0);
            for(unsigned int naa = 0; naa<aa; naa++)
            {
                //floating point coords of antialiased subpixel
                float xaa = x + rnd.uniform_signed(.5/w);
                float yaa = y + rnd.uniform_signed(.5/h);

                //cast ray from camera to pixel
                Ray r = cam->makeRay(xaa,yaa);
                pix_color += getColor(r, *world);

            }
            pix_color /= aa; //average all antialias runs
            unsigned int px_idx = 3*(px + py*w);
            image_data[px_idx] = pix_color.r_char();
            image_data[px_idx + 1] = pix_color.g_char();
            image_data[px_idx + 2] = pix_color.b_char();
        }
    }

}

Color Rt::getColor(const Ray& r, const ObjectList& world, unsigned int depth)
{
    Color backgroundColor = WHITE;

    Hit hit;
    Color c;
    if(world.hit(r,hit))
    {
        Color albedo;
        Ray scatter;
        if(hit.material->scatter(hit, scatter, albedo) && depth < depthLimit)
        {
//            std::cout << "Hit Something!" << std::endl;
            return albedo*getColor(scatter, world, depth+1);
        }
        else
            return albedo;            
    }

    return backgroundColor;
}