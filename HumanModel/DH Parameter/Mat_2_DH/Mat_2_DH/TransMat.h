#pragma once
#include "RotMat.h"

//class TransMat : public RotMat
class TransMat
{
public:
	TransMat();
	
	double TransMatrix[4][4];
	

	void Euler2TransXYZ (const double a1,const double a2,const double a3,const double d1,const double d2,const double d3); // Rotation in XYZ order combined with translation parameters to form a transformation matrix


};

