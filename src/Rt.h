#pragma once

#include "Rand.h"
#include "Hit.h"
#include "Color.h"
#include "ObjectList.h"
#include "Camera.h"
#include "Image.h"

#include <pthread.h>
#include <jsoncpp/json/json.h>
#include <functional>

#define RENDER_UPDATE_INTERVAL 10  //update image every N rays

class Rt
{
    bool valid;
    unsigned int rays_per_pixel;
    unsigned int depthLimit;

    pthread_mutex_t lock; 
    bool renderActive, cancelRenderRequest;

    Image* image;
    Camera* cam;
    ObjectList* world;

    Rand rnd;

    //recursive function to get color "seen" by ray
    Color getColor(const Ray& r, const ObjectList& world, unsigned int depth = 0);

    public:

    Rt(const Json::Value& config);
    ~Rt();

    //thread-safe functions
    inline bool rendering() {pthread_mutex_lock(&lock); return renderActive; pthread_mutex_unlock(&lock); }
    inline void cancelRender() {pthread_mutex_lock(&lock); cancelRenderRequest = renderActive; pthread_mutex_unlock(&lock); }
    inline void copyImage(unsigned char* dest) { pthread_mutex_lock(&lock); image->copy_data(dest); pthread_mutex_unlock(&lock); };

    //callback to notify that updated (intermediate) image is available
    //arguments: # current aa pass, total aa passes 
    std::function<void(int,int)> imageUpdate;

    //non-threadsafe functions
    void render();
    unsigned char* getImage();
    inline bool isValid() const {return valid;}
};
