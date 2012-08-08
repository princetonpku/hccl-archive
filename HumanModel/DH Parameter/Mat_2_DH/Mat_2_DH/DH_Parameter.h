#pragma once

class DH_Param
{
public:
	DH_Param();
	DH_Param (double angle1, double angle2, double distance1, double distance2)
		: theta(angle1), alpha(angle2), d(distance1), a(distance2) {}


// 4 D-H parameters
	double theta;
	double alpha;
	double d;
	double a;


	DH_Param& operator= (const DH_Param& b);
};