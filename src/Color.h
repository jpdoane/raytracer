#pragma once

#include "Vec3.h"

class Color : public Vec3
{
    public:

    Color(): Vec3() { }
    Color(float r, float g, float b): Vec3(r,g,b) { }

    Color(const Vec3& vec): Vec3(vec) { }

    float& r() { return e[0]; }
    float& g() { return e[1]; }
    float& b() { return e[2]; }

    unsigned char r_char() { return floatToChar( e[0] ); }
    unsigned char g_char() { return floatToChar( e[1] ); }
    unsigned char b_char() { return floatToChar( e[2] ); }

    unsigned char floatToChar(float val) const { return (unsigned char) (val*255); }
};

inline Color normalizedVecToColor(const Vec3& vec)
{
    return Color( (vec+1)/2 );
}


#define BLACK Color(0,0,0)
#define WHITE Color(1,1,1)
#define RED Color(1,0,0)
#define GREEN Color(0,1,0)
#define BLUE Color(0,0,1)
#define LIGHTBLUE Color(.3,.3,1)
#define LIGHTGREY Color(.7,.7,.7)
#define GREY Color(.5,.5,.5)
#define DARKGREY Color(.3,.3,.3)
