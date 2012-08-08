
#include <iostream>
#include "DH_Conversion.h"
#define PI 3.141592654

void main ()
{
	//validation Transformation matrix -> DH Parameter
	TransMat transmatrix1;
	transmatrix1.TransMatrix[0][0] = 0.707106781186548;
	transmatrix1.TransMatrix[0][1] = -0.353553390593274;
	transmatrix1.TransMatrix[0][2] = 0.612372435695794;
	transmatrix1.TransMatrix[0][3] = 3.53553390593274;
	transmatrix1.TransMatrix[1][0] = 0.707106781186547;
	transmatrix1.TransMatrix[1][1] = 0.353553390593274;
	transmatrix1.TransMatrix[1][2] = -0.612372435695795;
	transmatrix1.TransMatrix[1][3] = 3.53553390593274;
	transmatrix1.TransMatrix[2][0] = 0;
	transmatrix1.TransMatrix[2][1] = 0.866025403784439;
	transmatrix1.TransMatrix[2][2] = 0.5;
	transmatrix1.TransMatrix[2][3] = 5;
	transmatrix1.TransMatrix[3][0] = 0;
	transmatrix1.TransMatrix[3][1] = 0;
	transmatrix1.TransMatrix[3][2] = 0;
	transmatrix1.TransMatrix[3][3] = 1;

	DH_Param result;
	result = ConvertDH2Param(transmatrix1);
	std::cout<< result.theta << " " << result.alpha << " " << result.a << " " << result.d << std::endl;

	//validation Euler -> Transformation matrix
	TransMat transmatrix2;
	transmatrix2.Euler2TransXYZ(PI/4, PI/2, PI/3, 2.0, 3.0, 4.0);
	std::cout<<transmatrix2.TransMatrix[0][0]<<" "<<transmatrix2.TransMatrix[0][1]<<" "<<transmatrix2.TransMatrix[0][2]<<" "<<transmatrix2.TransMatrix[0][3]<<std::endl;
	std::cout<<transmatrix2.TransMatrix[1][0]<<" "<<transmatrix2.TransMatrix[1][1]<<" "<<transmatrix2.TransMatrix[1][2]<<" "<<transmatrix2.TransMatrix[1][3]<<std::endl;
	std::cout<<transmatrix2.TransMatrix[2][0]<<" "<<transmatrix2.TransMatrix[2][1]<<" "<<transmatrix2.TransMatrix[2][2]<<" "<<transmatrix2.TransMatrix[2][3]<<std::endl;
	std::cout<<transmatrix2.TransMatrix[3][0]<<" "<<transmatrix2.TransMatrix[3][1]<<" "<<transmatrix2.TransMatrix[3][2]<<" "<<transmatrix2.TransMatrix[3][3]<<std::endl;

}