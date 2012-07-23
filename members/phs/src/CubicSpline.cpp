#include "CubicSpline.h"
#include <cmath>

CubicSpline::CubicSpline()
{
}

CubicSpline::~CubicSpline()
{
}

void CubicSpline::setPoints(const std::vector<double2> &_points)
{
    points = _points;
    TDMA();
}

double CubicSpline::evaluate(double x)
{
    if ( x < points.begin()->x || x > (points.end()-1)->x )
    {
        return -10000000;
    }

    // search parameter range
    int ii = -1;
    for (int i=0; i<points.size()-1; ++i)
    {
        if( x >= points[i].x && x <= points[i+1].x )
        {
            ii = i;
            break;
        }
    }

    return z[ii+1]/(6*h[ii])*pow(x-points[ii].x, 3) + z[ii]/(6*h[ii])*pow(points[ii+1].x-x, 3) + (points[ii+1].y/h[ii]-h[ii]/6*z[ii+1])*(x-points[ii].x) + (points[ii].y/h[ii]-h[ii]/6*z[ii])*(points[ii+1].x-x);
}

double2 CubicSpline::point(int index)
{
    if( index >= 0 && index < points.size() )
    {
        return points[index];
    }
    else
    {
        return double2(-10000000,-10000000);
    }
}

void CubicSpline::setPoint(int index, const double2 &point)
{
    if( index >= 0 && index < points.size() )
    {
        points[index] = point;
    }
}

void CubicSpline::TDMA()
{
    int n = points.size()-2; // size of linear system
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> d(n);
    h.resize(n+1);
    z.resize(n+2);


    for (int i=0; i<n+1; ++i)
    {
        h[i] = points[i+1].x - points[i].x;
    }

    // set coefficients
    for (int i=1; i<n; ++i)
    {
        a[i] = h[i];
    }
    for (int i=0; i<n; ++i)
    {
        b[i] = 2*(h[i] + h[i+1]);
    }
    for (int i=0; i<n-1; ++i)
    {
        c[i] = h[i+1];
    }
    for (int i=0; i<n; ++i)
    {
        d[i] = 6*((points[i+2].y - points[i+1].y)/h[i+1] - (points[i+1].y - points[i].y)/h[i]);
    }


    // solve
    c[0] /= b[0];
    for (int i=1; i<n-1; ++i)
    {
        c[i] /= (b[i]-c[i-1]*a[i]);
    }

    d[0] /= b[0];
    for (int i=1; i<n; ++i)
    {
        d[i] = (d[i]-d[i-1]*a[i]) / (b[i]-c[i-1]*a[i]);
    }

    z[n] = d[n-1];
    for (int i=n-2; i>=0; --i)
    {
        z[i+1] = d[i]-c[i]*z[i+2];
    }

    // natural spline
    z[0] = 0;
    z[n+1] = 0;
}

int CubicSpline::countPoints()
{
    return points.size();
}
