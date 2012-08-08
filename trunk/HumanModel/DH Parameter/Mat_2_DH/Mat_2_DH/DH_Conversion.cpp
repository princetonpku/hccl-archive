
#include "DH_Conversion.h"
#include <math.h>

// extracts dh parameters from a transformation matrix
DH_Param ConvertDH2Param (const TransMat& mat)
{
	DH_Param temp;
	temp.theta = atan2(mat.TransMatrix[1][0], mat.TransMatrix[0][0]);
	temp.alpha = atan2(mat.TransMatrix[2][1], mat.TransMatrix[2][2]);
	temp.a = sqrt(mat.TransMatrix[0][3]*mat.TransMatrix[0][3] + mat.TransMatrix[1][3]*mat.TransMatrix[1][3]);
	temp.d = mat.TransMatrix[2][3];

	return temp;
}