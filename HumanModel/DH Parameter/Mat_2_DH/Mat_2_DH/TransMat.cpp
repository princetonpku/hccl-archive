#include "TransMat.h"

// zero matrix initialization
TransMat::TransMat()
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			TransMatrix[i][j]=0;
		}
	}
}

// determines transformation matrix from 3 euler angles and 3 translational factors (in X-Y-Z order)
void TransMat::Euler2TransXYZ (const double a1,const double a2,const double a3,const double d1,const double d2,const double d3)
{
	RotMat X, Y, Z, XYZ;
	X.MakeRotMat_X(a1);
	Y.MakeRotMat_Y(a2);
	Z.MakeRotMat_Z(a3);
	XYZ = Z*Y*X;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			TransMatrix[i][j] = XYZ.RotMatrix[i][j];
		}
	}
	TransMatrix[0][3] = d1;
	TransMatrix[1][3] = d2;
	TransMatrix[2][3] = d3;
	TransMatrix[3][3] = 1;
}