#include "Image.h"
#include <iostream>


Image::Image(const Json::Value& config)
: valid(false), data(NULL)
{
    //parse config
    try
    {   
        w = config["width"].asUInt();
        h = config["height"].asUInt();
        data = new unsigned char[h*w*3];
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error Parsing image paramters" << std::endl;
        return;
    }

    valid = true;
}

Image::~Image()
{   
    if(data)
        delete[] data;
}

void Image::copyFromColorArray(Color* col)
{
    for(unsigned int nn=0; nn<w*h; nn++)
    {
        data[nn*3] = col[nn].r_char();
        data[nn*3+1] = col[nn].g_char();
        data[nn*3+2] = col[nn].b_char();
    }
}
