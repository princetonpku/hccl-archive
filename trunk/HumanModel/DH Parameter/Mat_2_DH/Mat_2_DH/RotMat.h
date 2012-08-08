#pragma once

class RotMat
{
public:
	RotMat();

	double RotMatrix[3][3];
	void MakeRotMat_X (const double& a); // basic rotation matrix in x axis
	void MakeRotMat_Y (const double& a); // basic rotation matrix in y axis
	void MakeRotMat_Z (const double& a); // basic rotation matrix in z axis

	RotMat operator* (const RotMat& b); //3X3 matrix multiplication
	RotMat& operator= (const RotMat& b);

};