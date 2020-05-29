
#include <iostream>
#include <fstream>
#include "Rt.h"

int main(int argc, char** argv)
{
    Json::Value rtConfig;

    if(argc != 2)
    {
        std::cerr << "pass config file as parameter" << std::endl;
        return 1;
    }

    // read config file into json object
    std::ifstream configFile(argv[1]);
    if(!configFile.is_open())
    {
        std::cerr << "error opening config file " << argv[1] << std::endl;
        return 1;
    }

    configFile >> rtConfig;
    configFile.close();

    std::cout << "Rendering file " << argv[1] << std::endl;
    Rt* rt = new Rt(rtConfig);
    rt->render();
    delete rt;
    return 0;
}