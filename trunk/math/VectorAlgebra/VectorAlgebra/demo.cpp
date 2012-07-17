#include <stdio.h>
#include "VectorAlgebra.h"
#include <vector>
using namespace std;

int main()
{
	double v1[3] = {0.1, 0.2, 0.3};
	vector<double> v2(3, 0.0);
	v2[2] = 0.1;
	v2[1] = -0.2;
	vector<double> v3(3);

	// Cross product v3 of two vectors v1 and v2
	Cross3d(v1, &v2[0], &v3[0]);

	printf("v1 = (%lf, %lf, %lf)\n", v1[0], v1[1], v1[2]);
	printf("v2 = (%lf, %lf, %lf)\n", v2[0], v2[1], v2[2]);
	printf("v3 = v1 x v2 = (%lf, %lf, %lf)\n", v3[0], v3[1], v3[2]);

	return 0;
}