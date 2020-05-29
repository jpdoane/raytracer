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

    Vec3 randn3(float rad = 1) { return Vec3(normal(rad), normal(rad),normal(rad)); }

    // Actually slower than std::normal_distribution
    //
    // Vec3 randn3_fast(float rad = 1) { return Vec3(randn_fast(rad), randn_fast(rad),randn_fast(rad)); }
    // //fast normal random numbers
    // // https://dl.acm.org/doi/pdf/10.1145/138351.138364
    // float randn_fast(float rad = 1)
    // {
    //     float u,v,x,y,Q;
    //     do{
    //         u = (float) rand() / (float) RAND_MAX;
    //         v = (float) rand() / (float) RAND_MAX;
    //         v = 1.7156f*(v-.5);
    //         x = u-0.449871f;
    //         y = abs(v)+0.386595f;
    //         Q = x*x + y*(0.19600f*y - 0.25472f*x);
    //     }
    //     while(Q>0.27597 || v*v > -4*u*u*log(u));
    //     return rad*v/u;
    // };

};