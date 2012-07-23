#include "double4.h"
#include <cmath>

double4::double4()
    : x(0), y(0), z(0), w(0)
{
}

double4::double4(double _x, double _y, double _z, double _w)
    : x(_x), y(_y), z(_z), w(_w)
{
}

double4::~double4()
{
}

double4& double4::operator+=(const double4 &f)
{
    x+=f.x;
    y+=f.y;
    z+=f.z;
    w+=f.w;
    return *this;
}

double4& double4::operator-=(const double4 &f)
{
    x-=f.x;
    y-=f.y;
    z-=f.z;
    w-=f.w;
    return *this;
}

double4& double4::operator*=(const double4 &f)
{
    x*=f.x;
    y*=f.y;
    z*=f.z;
    w*=f.w;
    return *this;
}

double4& double4::operator/=(const double4 &f)
{
    x/=f.x;
    y/=f.y;
    z/=f.z;
    w/=f.w;
    return *this;
}

double4& double4::operator+=(double s)
{
    x+=s;
    y+=s;
    z+=s;
    w+=s;
    return *this;
}

double4& double4::operator-=(double s)
{
    x-=s;
    y-=s;
    z-=s;
    w-=s;
    return *this;
}

double4& double4::operator*=(double s)
{
    x*=s;
    y*=s;
    z*=s;
    w*=s;
    return *this;
}

double4& double4::operator/=(double s)
{
    x/=s;
    y/=s;
    z/=s;
    w/=s;
    return *this;
}

double4 double4::operator+(const double4 &f)
{
    return double4(x+f.x, y+f.y, z+f.z, w+f.w);
}

double4 double4::operator-(const double4 &f)
{
    return double4(x-f.x, y-f.y, z-f.z, w-f.w);
}

double4 double4::operator*(const double4 &f)
{
    return double4(x*f.x, y*f.y, z*f.z, w*f.w);
}

double4 double4::operator/(const double4 &f)
{
    return double4(x/f.x, y/f.y, z/f.z, w/f.w);
}

double4 double4::operator+(double s)
{
    return double4(x+s, y+s, z+s, w+s);
}

double4 double4::operator-(double s)
{
    return double4(x-s, y-s, z-s, w-s);
}

double4 double4::operator*(double s)
{
    return double4(x*s, y*s, z*s, w*s);
}

double4 double4::operator/(double s)
{
    return double4(x/s, y/s, z/s, w/s);
}

double4 operator+(double s, const double4 &f)
{
    return double4(s+f.x, s+f.y, s+f.z, s+f.w);
}

double4 operator-(double s, const double4 &f)
{
    return double4(s-f.x, s-f.y, s-f.z, s-f.w);
}

double4 operator*(double s, const double4 &f)
{
    return double4(s*f.x, s*f.y, s*f.z, s*f.w);
}

double4 operator/(double s, const double4 &f)
{
    return double4(s/f.x, s/f.y, s/f.z, s/f.w);
}

double dot(const double4 &f1, const double4 &f2)
{
    return (f1.x*f2.x + f1.y*f2.y + f1.z*f2.z + f1.w+f2.w);
}

double length(const double4 &f)
{
    return sqrt(f.x*f.x + f.y*f.y + f.z*f.z + f.w+f.w);
}
