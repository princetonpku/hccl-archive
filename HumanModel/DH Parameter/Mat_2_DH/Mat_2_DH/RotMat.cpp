#include "RotMat.h"
#include <math.h>

// zero matrix initialization
RotMat::RotMat()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			RotMatrix[i][j]=0;
		}
	}
}

// matrix multiplication
RotMat RotMat::operator* (const RotMat& b)
{
	RotMat c;

	for(int i=0;i< 3;i++)
	{
		for(int j=0;j< 3;j++)
		{
			c.RotMatrix[i][j] = 0;
			for(int k=0;k< 3;k++)
			{
				c.RotMatrix[i][j] = c.RotMatrix[i][j] + RotMatrix[i][k] * b.RotMatrix[k][j];
			}
		} 
	} 
	return c;
}


RotMat& RotMat::operator= (const RotMat& b)
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			RotMatrix[i][j] = b.RotMatrix[i][j];
		}
	}
	return *this;
}

// rotation matrix - x axis
void RotMat::MakeRotMat_X (const double& a)
{
	RotMatrix[0][0] = 1;
	RotMatrix[1][1] = cos(a);
	RotMatrix[1][2] = -sin(a);
	RotMatrix[2][1] = sin(a);
	RotMatrix[2][2] = cos(a);
}
// rotation matrix - y axis
void RotMat::MakeRotMat_Y (const double& a)
{
	RotMatrix[0][0] = cos(a);
	RotMatrix[0][2] = sin(a);
	RotMatrix[1][1] = 1;
	RotMatrix[2][0] = -sin(a);
	RotMatrix[2][2] = cos(a);
}
// rotation matrix - z axis
void RotMat::MakeRotMat_Z (const double& a)
{
	RotMatrix[0][0] = cos(a);
	RotMatrix[0][1] = -sin(a);
	RotMatrix[1][0] = sin(a);
	RotMatrix[1][1] = cos(a);
	RotMatrix[2][2] = 1;
}