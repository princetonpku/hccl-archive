#include <stdio.h>
#include "VectorQuaternion.h"
#include <iostream>

int main(void)
{
	Vector3d v1(1, 2, 3);
	Vector3d v2(3, 4, 5);

	Vector3d v3 = Cross(v1, v2);

	std::cout << "v1 = " << v1 << std::endl;
	std::cout << "v2 = " << v2 << std::endl;
	std::cout << "v3 = v1 x v2 = " << v3 << std::endl;
	v3.Normalize();
	std::cout << "v3/|v3| = " << v3 << std::endl;

	Vector3d v4;
	std::cout << "enter a new vector: ";
	std::cin >> v4;

	std::cout << "v4 = " << v4 << std::endl;

	return 0;
}