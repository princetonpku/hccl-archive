#include <stdio.h>
#include "VectorQuaternion.h"

int main(void)
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(3, 4, 5);

	Vector3d v3 = Cross(v1, v2);
	v3.Normalize();



	return 0;
}