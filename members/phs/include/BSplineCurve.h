#ifndef _BSPLINECURVE_H_
#define _BSPLINECURVE_H_

#include <vector>
#include "double4.h"

class BSplineCurve
{
public:
    BSplineCurve();
    ~BSplineCurve();

    double4 evaluate(double u);
    void buildFromControlPoints(const std::vector<double4> &controlPoints, int degree = 3);
    bool setKnotVector(const std::vector<double> &knotVector);
    void setKnot(int index, double knot);
    void setControlPoint(int index, const double4 &point);
    double knot(int index);
    double4 controlPoint(int index);
    std::vector<double4> controlPoints();
    std::vector<double> knotVector();
    int countKnotVector();
    int countControlPoints();
    int basisDegree();

private:
    int degree; // degree = k-1
    std::vector<double4> points;
    std::vector<double> knots;
};

#endif // _BSPLINECURVE_H_
