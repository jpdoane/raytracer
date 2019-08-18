#pragma once

#include <math.h>

class Vec3
{
public:

    float e[3];

    float& x() { return e[0]; }
    float& y() { return e[1]; }
    float& z() { return e[2]; }

    const float& getx() const { return e[0]; }
    const float& gety() const { return e[1]; }
    const float& getz() const { return e[2]; }

    Vec3() { }
    Vec3(float x, float y, float z) { e[0] = x; e[1] = y; e[2] = z; }

    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0],-e[1],-e[2]); }

    inline Vec3 operator+(const Vec3 &v2) const { return Vec3(e[0]+v2.e[0],e[1]+v2.e[1],e[2]+v2.e[2]); }
    inline Vec3 operator-(const Vec3 &v2) const { return Vec3(e[0]-v2.e[0],e[1]-v2.e[1],e[2]-v2.e[2]); }
    inline Vec3 operator*(const Vec3 &v2) const { return Vec3(e[0]*v2.e[0],e[1]*v2.e[1],e[2]*v2.e[2]); }
    inline Vec3 operator/(const Vec3 &v2) const { return Vec3(e[0]/v2.e[0],e[1]/v2.e[1],e[2]/v2.e[2]); }

    inline const Vec3& operator+=(const Vec3 &v2) { e[0]+=v2.e[0]; e[1]+=v2.e[1]; e[2]+=v2.e[2]; return *this; }
    inline const Vec3& operator-=(const Vec3 &v2) { e[0]-=v2.e[0]; e[1]-=v2.e[1]; e[2]-=v2.e[2]; return *this; }
    inline const Vec3& operator*=(const Vec3 &v2) { e[0]*=v2.e[0]; e[1]*=v2.e[1]; e[2]*=v2.e[2]; return *this; }
    inline const Vec3& operator/=(const Vec3 &v2) { e[0]/=v2.e[0]; e[1]/=v2.e[1]; e[2]/=v2.e[2]; return *this; }
    inline const Vec3& operator*=(float t) { e[0]*=t; e[1]*=t; e[2]*=t; return *this; }
    inline const Vec3& operator/=(float t) { e[0]/=t; e[1]/=t; e[2]/=t; return *this; }

    inline Vec3 operator+(float t) const { return Vec3(e[0]+t,e[1]+t,e[2]+t); }
    inline Vec3 operator-(float t) const { return Vec3(e[0]-t,e[1]-t,e[2]-t); }
    inline Vec3 operator*(float t) const { return Vec3(e[0]*t,e[1]*t,e[2]*t); }
    inline Vec3 operator/(float t) const { return Vec3(e[0]/t,e[1]/t,e[2]/t); }

    inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }                                                        

    const Vec3& setLength(float len) { return (*this) *= (len/length()); }
    const Vec3& normalize() { return setLength(1); }
};

inline Vec3 operator*(float t, const Vec3 &v1) { return Vec3(v1.e[0]*t,v1.e[1]*t,v1.e[2]*t); }
inline float dot(const Vec3 &v1, const Vec3 &v2)  { return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2]; }
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)  { return Vec3( v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1],
                                                            -(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0]),
                                                            v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]); }

