#ifndef _MUSCLEFORCE_H_
#define _MUSCLEFORCE_H_

#include "CubicSpline.h"

class Muscle
{
public:
    Muscle();
    ~Muscle();

	void setParameters(double MaxForce, double OptLength, double MaxVelocity);
	void setMaxForce(double MaxForce);
	void setOptLength(double OptLength);
	void setMaxVelocity(double MaxVelocity);

	double getForce0(double ActLevel);
	double getForce1(double ActLevel, double Length, double Velocity);

private:
	double _MaxForce;
	double _OptLength;
	double _MaxVelocity;

	CubicSpline AFLCurve;
	CubicSpline PFLCurve;
	CubicSpline FVCurve;
};

#endif // _MUSCLEFORCE_H_