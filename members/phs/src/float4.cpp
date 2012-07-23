#include "float4.h"
#include <cmath>

float4::float4()
    : x(0), y(0), z(0), w(0)
{
}

float4::float4(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
{
}

float4::~float4()
{
}

float4& float4::operator+=(const float4& f)
{
    x+=f.x;
    y+=f.y;
    z+=f.z;
    w+=f.w;
    return *this;
}

float4& float4::operator-=(const float4& f)
{
    x-=f.x;
    y-=f.y;
    z-=f.z;
    w-=f.w;
    return *this;
}

float4& float4::operator*=(const float4& f)
{
    x*=f.x;
    y*=f.y;
    z*=f.z;
    w*=f.w;
    return *this;
}

float4& float4::operator/=(const float4& f)
{
    x/=f.x;
    y/=f.y;
    z/=f.z;
    w/=f.w;
    return *this;
}

float4& float4::operator+=(float s)
{
    x+=s;
    y+=s;
    z+=s;
    w+=s;
    return *this;
}

float4& float4::operator-=(float s)
{
    x-=s;
    y-=s;
    z-=s;
    w-=s;
    return *this;
}

float4& float4::operator*=(float s)
{
    x*=s;
    y*=s;
    z*=s;
    w*=s;
    return *this;
}

float4& float4::operator/=(float s)
{
    x/=s;
    y/=s;
    z/=s;
    w/=s;
    return *this;
}

float4 float4::operator+(const float4& f)
{
    return float4(x+f.x, y+f.y, z+f.z, w+f.w);
}

float4 float4::operator-(const float4& f)
{
    return float4(x-f.x, y-f.y, z-f.z, w-f.w);
}

float4 float4::operator*(const float4& f)
{
    return float4(x*f.x, y*f.y, z*f.z, w*f.w);
}

float4 float4::operator/(const float4& f)
{
    return float4(x/f.x, y/f.y, z/f.z, w/f.w);
}

float4 float4::operator+(float s)
{
    return float4(x+s, y+s, z+s, w+s);
}

float4 float4::operator-(float s)
{
    return float4(x-s, y-s, z-s, w-s);
}

float4 float4::operator*(float s)
{
    return float4(x*s, y*s, z*s, w*s);
}

float4 float4::operator/(float s)
{
    return float4(x/s, y/s, z/s, w/s);
}

float4 operator+(float s, const float4& f)
{
    return float4(s+f.x, s+f.y, s+f.z, s+f.w);
}

float4 operator-(float s, const float4& f)
{
    return float4(s-f.x, s-f.y, s-f.z, s-f.w);
}

float4 operator*(float s, const float4& f)
{
    return float4(s*f.x, s*f.y, s*f.z, s*f.w);
}

float4 operator/(float s, const float4& f)
{
    return float4(s/f.x, s/f.y, s/f.z, s/f.w);
}

float dot(const float4& f1, const float4& f2)
{
    return (f1.x*f2.x + f1.y*f2.y + f1.z*f2.z + f1.w+f2.w);
}

float length(const float4& f)
{
    return sqrt(f.x*f.x + f.y*f.y + f.z*f.z + f.w+f.w);
}
