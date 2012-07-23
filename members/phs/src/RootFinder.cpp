#include "RootFinder.h"
#include <cmath>

RootFinder::RootFinder()
    : n(30), tol(1e-10), f(defaultFunction)
{
}

RootFinder::~RootFinder()
{
}

void RootFinder::setFunction(std::tr1::function<double(double)> _f)
{
    f = _f;
}

double RootFinder::findRoot(double initialValue)
{
    double x1 = initialValue;
    double x2 = (initialValue==0) ? (initialValue + 1e-5) : (1.01*initialValue);
    double x3 = initialValue;
    double epsilon = tol*abs(f(x2)-f(x1));

    for (int i=0; i<n; ++i)
    {
        if ( abs(x2-x1) <= epsilon )
        {
            break;
        }
        else
        {
            x3 = x2 - f(x2)*(x2-x1)/(f(x2)-f(x1));
            x1 = x2;
            x2 = x3;
        }
    }

    // check NaN or Indeterminate form
    return (x3!=x3) ? initialValue : x3;
}

double RootFinder::defaultFunction(double x)
{
    return x*x-4;
}

void RootFinder::setMaxIteration(int _n)
{
    if (_n>0)
    {
        n = _n;
    }
}

void RootFinder::setTolerance(double tolerance)
{
    if (tolerance > 0)
    {
        tol = tolerance;
    }
}

int RootFinder::maxIteration()
{
    return n;
}

double RootFinder::tolerance()
{
    return tol;
}