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
