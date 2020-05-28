#pragma once
#include <random>
#include "Vec3.h"

class Rand
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> dist_uniform_signed;
    std::uniform_real_distribution<float> dist_uniform_unsigned;
    std::normal_distribution<float> dist_normal;

    public:

    Rand() : dist_uniform_signed(-1,1), dist_uniform_unsigned(0,1), dist_normal(0,1) {}

    float uniform(float mag = 1) { return mag*dist_uniform_unsigned(generator); }
    float uniform_signed(float mag = 1) { return mag*dist_uniform_signed(generator); }
    float normal(float mag = 1) { return mag*dist_normal(generator); }

    Vec3 rand_in_cube(float rad = 1) { return Vec3(uniform_signed(rad), uniform_signed(rad),uniform_signed(rad)); }
    Vec3 rand_in_sphere(float rad = 1) { Vec3 v; do { v = rand_in_cube(rad); } while(v.length() <= rad); return v; }

};