// L-BFGS-B.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "lbfgsb.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ap::real_1d_array x;
	ap::integer_1d_array nbd;
	ap::real_1d_array lbd, ubd;
	x.setbounds(1, 10);
	nbd.setbounds(1, 10);
	lbd.setbounds(1, 10);
	ubd.setbounds(1, 10);
	for(int i = 1; i <= 10; i++)
	{
		x(i) = 100.0*rand()/RAND_MAX;
		nbd(i) = 0;
		lbd(i) = 0.0;
		ubd(i) = 0.0;
	}
	int info = 0;
	lbfgsbminimize(10, 7, x, 0.001, 0.001, 0.001, 100, nbd, lbd, ubd, info);

	for(int i = 0; i < 10; i++)
	std::cout << x(i) << std::endl;

	return 0;
}

