#ifndef _CUBICSPLINE_H_
#define _CUBICSPLINE_H_

#include <vector>
#include "double2.h"

class CubicSpline
{
public:
    CubicSpline();
    ~CubicSpline();

    void setPoints(const std::vector<double2> &points);
    void setPoint(int index, const double2 &point);
    double evaluate(double x);
    double2 point(int index);
    int countPoints();


private:
    std::vector<double2> points;
    std::vector<double> h;
    std::vector<double> z;
    void TDMA();
};

#endif // _CUBICSPLINE_H_
