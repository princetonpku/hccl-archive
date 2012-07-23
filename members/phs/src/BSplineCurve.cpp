#include "BSplineCurve.h"

BSplineCurve::BSplineCurve()
    : degree(0), points(), knots()
{
}

BSplineCurve::~BSplineCurve()
{
}

double4 BSplineCurve::evaluate(double u)
{
    if ( knots.size()<2 || u < *knots.begin() || u > *(knots.end()-1) )
    {
        return double4(0,0,0,-1);
    }

    // search parameter range
    int knotIndex = -1;
    for (int i=degree; i<knots.size()-degree; ++i)
    {
        if( u >= knots[i] && u <= knots[i+1] )
        {
            knotIndex = i;
            break;
        }
    }

    // De Boor - Cox algorithm
    std::vector<double4> deBoorCox(points.begin()+knotIndex-degree, points.begin()+knotIndex+1);
    for (int j=1; j<degree+1; ++j)
    {
        for (int i=degree; i>=j; --i)
        {
            int ii = i+knotIndex-degree;
            if ( knots[ii+degree+1-j] != knots[ii] )
            {
                double tau = (u-knots[ii])/(knots[ii+degree+1-j]-knots[ii]);
                deBoorCox[i] = (1-tau)*deBoorCox[i-1] + tau*deBoorCox[i];                
            }
        }
    }

    return deBoorCox[degree];
}

bool BSplineCurve::setKnotVector(const std::vector<double> &knotVector)
{
    // check size
    if ( knotVector.size() != degree + points.size() )
    {
        return false;
    }

    // check non-decresing
    for (int i=0; i<knotVector.size()-1; ++i)
    {
        if ( knotVector[i] > knotVector[i+1] )
        {
            return false;
        }
    }

    knots = knotVector;
    return true;
}

void BSplineCurve::buildFromControlPoints(const std::vector<double4> &controlPoints, int _degree)
{
    if ( _degree > 0 && _degree < controlPoints.size() )
    {
        degree = _degree;
        points = controlPoints;
        int n = points.size();
        
        // build default uniform knot vector
        // parameter u range : [0,1]
        knots.resize( degree+n+1 );
        for (int i=0; i<degree+1; ++i)
        {
            knots[i] = 0;
        }
        for (int i=degree+1; i<n; ++i)
        {
            knots[i] = (double)(i-degree)/(n-degree);
        }
        for (int i=n; i<n+degree+1; ++i)
        {
            knots[i] = 1;
        }
    }
}

void BSplineCurve::setControlPoint(int index, const double4 &point)
{
    if ( index >=0 && index < points.size() )
    {
        points[index] = point;
    }
}

void BSplineCurve::setKnot(int index, double knot)
{
    if ( index == 0 )
    {
        if ( knot >= knots[index+1] )
        {
            knots[index] = knots[index+1];
        }
        else
        {
            knots[index] = knot;
        }
    }
    else if ( index == knots.size()-1 )
    {
        if ( knot <= knots[index-1] )
        {
            knots[index] = knots[index-1];
        }
        else
        {
            knots[index] = knot;
        }
    }
    else if ( index >0 || index < points.size()-1 )
    {
        if ( knot <= knots[index-1] )
        {
            knots[index] = knots[index-1];
        }
        else if ( knot >= knots[index+1] )
        {
            knots[index] = knots[index+1];
        }
        else
        {
            knots[index] = knot;
        }
    }
}

std::vector<double4> BSplineCurve::controlPoints()
{
    return points;
}

std::vector<double> BSplineCurve::knotVector()
{
    return knots;
}

int BSplineCurve::countKnotVector()
{
    return knots.size();
}

int BSplineCurve::countControlPoints()
{
    return points.size();
}

double4 BSplineCurve::controlPoint(int index)
{
    if ( index >=0 && index < points.size() )
    {
        return points[index];
    }
    else
    {
        return double4(0,0,0,-1);
    }
}

double BSplineCurve::knot(int index)
{
    if ( index >=0 && index < knots.size() )
    {
        return knots[index];
    }
    else
    {
        return -100000000;
    }
}

int BSplineCurve::basisDegree()
{
    return degree;
}
