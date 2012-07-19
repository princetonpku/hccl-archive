#include <stdio.h>
#include "VectorAlgebra.h"
#include <vector>
using namespace std;

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// 3D case example
	//////////////////////////////////////////////////////////////////////////

	// Declare vectors
	double v1[3] = {0.1, 0.2, 0.3};
	vector<double> v2(3, 0.0);
	v2[2] = 0.1;
	v2[1] = -0.2;
	
	// Cross product v3 of two vectors v1 and v2
	vector<double> v3(3);	
	vCross3d(v1, &v2[0], &v3[0]);

	// Dot product of two vectors v1 and v2
	double dot_product = vDot3d(v1, v2.data());

	// Norm of the vectors
	double n1 = vNorm3d(v1);
	double n2 = vNorm3d(&v2[0]);
	double n3 = vNorm3d(&v3[0]);

	printf("v1 = (%lf, %lf, %lf)\t|v1| = %lf\n", v1[0], v1[1], v1[2], n1);
	printf("v2 = (%lf, %lf, %lf)\t|v2| = %lf\n", v2[0], v2[1], v2[2], n2);
	printf("v1 x v2 = (%lf, %lf, %lf)\t|v1 x v2| = %lf\n", v3[0], v3[1], v3[2], n3);
	printf("v1 * v2 = %lf\n", dot_product);	
	




	//////////////////////////////////////////////////////////////////////////
	// 2D case example
	//////////////////////////////////////////////////////////////////////////

	double v4[2] = {0.5, -0.2};
	double v5[2] = {1.2, 0.3};

	double dot_product2d = vDot2d(v4, v5);
	printf("v4 * v5 = %lf\n", dot_product2d);	

	return 0;
}