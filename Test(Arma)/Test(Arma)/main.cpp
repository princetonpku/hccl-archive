////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// As a courtesy, the Armadillo package contains pre-compiled 32 bit versions of LAPACK and BLAS for Windows,
// $(ARMADILLO_DIR)\examples\lib_win32
//
// as well as MSVC project files to compile the example programs. 
// 
// If you're getting messages such as "use of LAPACK needs to be enabled", manually modify "$(ARMADILLO_DIR)/include/armadillo_bits/config.hpp" to enable the use of LAPACK.
// 
// If you're using a 64 bit system (such as Windows 7), dedicated 64 bit versions of LAPACK and BLAS are considerably faster.
//
// If you don't have 64 bit BLAS, it's better to define ARMA_DONT_USE_BLAS before including the Armadillo header, ie.:
// #define ARMA_DONT_USE_BLAS
// #include <armadillo>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <algorithm>
#include <numeric>

#define ARMA_DONT_USE_BLAS
#include <armadillo>

using namespace arma;

int main()
{	
	mat a = 3*mat().eye(5,5);
	a.print("a = ");

	std::iota(a.colptr(1), a.colptr(2), 1);
	a.print("a = ");

	mat b = a.submat(1,1,3,3);
	b.print("b = ");

	std::iota(b.begin(), b.end(), 10);
	b.print("b = ");

	a.print("a = ");
	a.submat(1,1,3,3) = b;
	a.print("a = ");

	inv(a).print("inv(a) = "); // this function needs LAPACK : manually modify "$(ARMADILLO_DIR)/include/armadillo_bits/config.hpp"

	return 0;
} 