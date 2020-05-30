#include "Rt.h" 

#include "Vec3.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include "Material.h"

#include <iostream> 
#include <string.h>

Rt::Rt(const Json::Value& config)
:valid(false), renderActive(false), cancelRenderRequest(false), image(NULL), cam(NULL), world(NULL)
{
    pthread_mutex_init(&lock,NULL);

    //parse config
    try
    {   
        Json::Value render = config["render"];

        rays_per_pixel = render.get("raysperpixel",100).asUInt();
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
    pthread_mutex_lock(&lock);
    cancelRenderRequest = false;
    renderActive = true;    
    unsigned int w = image->get_width();
    unsigned int h = image->get_height();
    pthread_mutex_unlock(&lock);

    Color* temp_image = new Color[w*h];
    memset(temp_image,0,w*h*sizeof(Color));
    unsigned int naa;
    float scale_data,scale_update;
    bool exitloop = false;
    for(naa = 0; naa<rays_per_pixel; naa++)
    {
        scale_data = (float) naa/(naa+1);
        scale_update = 1.0f/(naa+1);

        for(unsigned int px = 0; px<w; px++)
        {
            //floating point x-coord 
            float x = (float)px / w;
            for(unsigned int py = 0; py<h; py++)
            {
                //floating point y-coord, py increases down, y increases up
                float y = 1.0 - (float)py / h;

                //floating point coords of antialiased subpixel
                float xaa = x + rnd.uniform_signed(.5/w);
                float yaa = y + rnd.uniform_signed(.5/h);

                //cast ray from camera to pixel
                Ray r = cam->makeRay(xaa,yaa);
                // temp_image[px + py*w] = getColor(r, *world);
                // temp_image[px + py*w] += getColor(r, *world)/aa;
                temp_image[px + py*w] = temp_image[px + py*w]*scale_data + getColor(r, *world)*scale_update;
            }
        }

        //every RENDER_UPDATE_INTERVAL loops, update image with partial aa result
        if( (naa+1) % RENDER_UPDATE_INTERVAL == 0 )
        {
            pthread_mutex_lock(&lock);
            image->copyFromColorArray(temp_image);
            pthread_mutex_unlock(&lock);
            if(imageUpdate) imageUpdate(naa+1, rays_per_pixel); //notify of new image
        }

        //check to see if render has been cancelled
        pthread_mutex_lock(&lock);
        exitloop = cancelRenderRequest;
        pthread_mutex_unlock(&lock);
        if(exitloop) break; 
    }

    if(!exitloop)
    {
        pthread_mutex_lock(&lock);
        image->copyFromColorArray(temp_image);
        pthread_mutex_unlock(&lock);
        if(imageUpdate) imageUpdate(rays_per_pixel, rays_per_pixel);
    }

    delete[] temp_image;

    pthread_mutex_lock(&lock);
    cancelRenderRequest = false;
    renderActive = false;
    pthread_mutex_unlock(&lock);    
}

//recursive function to get color "seen" by ray
Color Rt::getColor(const Ray& r, const ObjectList& world, unsigned int depth)
{
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

    return world.backgroundColor;
}