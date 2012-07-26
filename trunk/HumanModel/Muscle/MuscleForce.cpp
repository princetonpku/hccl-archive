#include "MuscleForce.h"

Muscle::Muscle()
:_MaxForce(0), _OptLength(0), _MaxVelocity(0)
{
	std::vector<double2> FLPoints;
	FLPoints.push_back(double2(-5.307692,0.012188));
	FLPoints.push_back(double2(-4.307692, 0.021899));
	FLPoints.push_back(double2(-1.923077, 0.036466));
	FLPoints.push_back(double2(-0.884615, 0.052493));
	FLPoints.push_back(double2(-0.269231, 0.075312));
	FLPoints.push_back(double2(0.230769, 0.114158));
	FLPoints.push_back(double2(0.461538, 0.157859));
	FLPoints.push_back(double2(0.52725, 0.226667));
	FLPoints.push_back(double2(0.62875, 0.636667));
	FLPoints.push_back(double2(0.71875, 0.856667));
	FLPoints.push_back(double2(0.86125, 0.95));
	FLPoints.push_back(double2(1.045, 0.993333));
	FLPoints.push_back(double2(1.2175, 0.77));
	FLPoints.push_back(double2(1.43875, 0.246667));
	FLPoints.push_back(double2(1.5, 0.193821));
	FLPoints.push_back(double2(1.615385, 0.133252));
	FLPoints.push_back(double2(2, 0.072683));
	FLPoints.push_back(double2(2.961538, 0.044417));
	FLPoints.push_back(double2(3.692308, 0.036341));
	FLPoints.push_back(double2(5.461538, 0.021899));
	FLPoints.push_back(double2(9.901902, 0.007332));
	FLCurve.setPoints(FLPoints);

	std::vector<double2> FVPoints;
	FVPoints.push_back(double2(-1, 0));
	FVPoints.push_back(double2(-0.95, 0.010417));
	FVPoints.push_back(double2(-0.9, 0.021739));
	FVPoints.push_back(double2(-0.85, 0.034091));
	FVPoints.push_back(double2(-0.8, 0.047619));
	FVPoints.push_back(double2(-0.75, 0.0625));
	FVPoints.push_back(double2(-0.7, 0.078947));
	FVPoints.push_back(double2(-0.65, 0.097222));
	FVPoints.push_back(double2(-0.6, 0.117647));
	FVPoints.push_back(double2(-0.55, 0.140625));
	FVPoints.push_back(double2(-0.5, 0.166667));
	FVPoints.push_back(double2(-0.45, 0.196429));
	FVPoints.push_back(double2(-0.4, 0.230769));
	FVPoints.push_back(double2(-0.35, 0.270833));
	FVPoints.push_back(double2(-0.3, 0.318182));
	FVPoints.push_back(double2(-0.25, 0.375));
	FVPoints.push_back(double2(-0.2, 0.444444));
	FVPoints.push_back(double2(-0.15, 0.53125));
	FVPoints.push_back(double2(-0.1, 0.642857));
	FVPoints.push_back(double2(-0.05, 0.791667));
	FVPoints.push_back(double2(0, 1));
	FVPoints.push_back(double2(0.05, 1.482014));
	FVPoints.push_back(double2(0.1, 1.601571));
	FVPoints.push_back(double2(0.15, 1.655791));
	FVPoints.push_back(double2(0.2, 1.686739));
	FVPoints.push_back(double2(0.25, 1.706751));
	FVPoints.push_back(double2(0.3, 1.720753));
	FVPoints.push_back(double2(0.35, 1.731099));
	FVPoints.push_back(double2(0.4, 1.739055));
	FVPoints.push_back(double2(0.45, 1.745365));
	FVPoints.push_back(double2(0.5, 1.75049));
	FVPoints.push_back(double2(0.55, 1.754736));
	FVPoints.push_back(double2(0.6, 1.758312));
	FVPoints.push_back(double2(0.65, 1.761364));
	FVPoints.push_back(double2(0.7, 1.763999));
	FVPoints.push_back(double2(0.75, 1.766298));
	FVPoints.push_back(double2(0.8, 1.768321));
	FVPoints.push_back(double2(0.85, 1.770115));
	FVPoints.push_back(double2(0.9, 1.771717));
	FVPoints.push_back(double2(0.95, 1.773155));
	FVPoints.push_back(double2(1, 1.774455));
	FVCurve.setPoints(FVPoints);
}

Muscle::~Muscle()
{
}

void Muscle::setParameters(double f, double l, double v)
{
	_MaxForce = f;
	_OptLength = l;
	_MaxVelocity = v;
}

double Muscle::getForce0(double a)
{
	if(a > 1.0)
		return -1;
	else if(a < 0.0)
		return -1;
	else
		return _MaxForce * a;
}

double Muscle::getForce1(double a, double l, double v)
{
	if(a > 1.0)
		return -1;
	else if(a < 0.0)
		return -1;
	else
	{
		if(l < 0.0)
			return -1;
		else
			return _MaxForce * a * FLCurve.evaluate(l/_OptLength) * FVCurve.evaluate(v/_MaxVelocity);
	}
}