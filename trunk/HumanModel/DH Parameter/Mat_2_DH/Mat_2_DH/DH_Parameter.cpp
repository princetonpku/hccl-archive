
#include "DH_Parameter.h"

// initializes d-h parameters with 0's
DH_Param::DH_Param()
{
	theta = 0;
	alpha = 0;
	a = 0;
	d = 0;
}

DH_Param& DH_Param::operator= (const DH_Param& b)
{
	theta = b.theta;
	alpha = b.alpha;
	a = b.a;
	d = b.d;

	return *this;
}
