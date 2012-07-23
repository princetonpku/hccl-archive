#include "double2.h"
#include <cmath>

double2::double2()
    : x(0), y(0)
{
}

double2::double2(double _x, double _y)
    : x(_x), y(_y)
{
}

double2::~double2()
{
}

double2& double2::operator+=(const double2 &f)
{
    x+=f.x;
    y+=f.y;
    return *this;
}

double2& double2::operator-=(const double2 &f)
{
    x-=f.x;
    y-=f.y;
    return *this;
}

double2& double2::operator*=(const double2 &f)
{
    x*=f.x;
    y*=f.y;
    return *this;
}

double2& double2::operator/=(const double2 &f)
{
    x/=f.x;
    y/=f.y;
    return *this;
}

double2& double2::operator+=(double s)
{
    x+=s;
    y+=s;
    return *this;
}

double2& double2::operator-=(double s)
{
    x-=s;
    y-=s;
    return *this;
}

double2& double2::operator*=(double s)
{
    x*=s;
    y*=s;
    return *this;
}

double2& double2::operator/=(double s)
{
    x/=s;
    y/=s;
    return *this;
}

double2 double2::operator+(const double2 &f)
{
    return double2(x+f.x, y+f.y);
}

double2 double2::operator-(const double2 &f)
{
    return double2(x-f.x, y-f.y);
}

double2 double2::operator*(const double2 &f)
{
    return double2(x*f.x, y*f.y);
}

double2 double2::operator/(const double2 &f)
{
    return double2(x/f.x, y/f.y);
}

double2 double2::operator+(double s)
{
    return double2(x+s, y+s);
}

double2 double2::operator-(double s)
{
    return double2(x-s, y-s);
}

double2 double2::operator*(double s)
{
    return double2(x*s, y*s);
}

double2 double2::operator/(double s)
{
    return double2(x/s, y/s);
}

double2 operator+(double s, const double2 &f)
{
    return double2(s+f.x, s+f.y);
}

double2 operator-(double s, const double2 &f)
{
    return double2(s-f.x, s-f.y);
}

double2 operator*(double s, const double2 &f)
{
    return double2(s*f.x, s*f.y);
}

double2 operator/(double s, const double2 &f)
{
    return double2(s/f.x, s/f.y);
}

double dot(const double2 &f1, const double2 &f2)
{
    return (f1.x*f2.x + f1.y*f2.y);
}

double length(const double2 &f)
{
    return sqrt(f.x*f.x + f.y*f.y);
}
