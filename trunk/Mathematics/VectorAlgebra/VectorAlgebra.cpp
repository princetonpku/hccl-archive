#include "VectorAlgebra.h"
#include <math.h>
#include <memory>


// a == b
bool vIsEqual3f(const float* a, const float* b)
{
	return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2]);
}


float vDot3f(const float* a, const float* b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

float* vCross3f(const float* a, const float* b, float* c)
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];

	return c;
}

float vNormSquared3f(const float* x)
{
	return vDot3f(x, x);
}

float vNorm3f(const float* x)
{
	return sqrt(vNormSquared3f(x));
}

float* vNormalize3f( float* x )
{
	return vDivScalar3f(x, vNorm3f(x));
}

// a = b
float* vCopy3f(float* a, const float* b)
{
	memcpy(a, b, sizeof(float)*3);
	return a;
}

// a = (b, b, b)
float* vAssign3f(float* a, const float b)
{
	a[0] = b;
	a[1] = b;
	a[2] = b;
	return a;
}

// x = -x;
float* vNegate3f(float* x)
{
	x[0] = -x[0];
	x[1] = -x[1];
	x[2] = -x[2];

	return x;
}

// c = a + b
float* vAdd3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
	return c;
}

// a += b
float* vAdd3f(float* a, const float* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	return a;
}

// x += a
float* vAddScalar3f(float* x, const float& a)
{
	x[0] += a;	x[1] += a;	x[2] += a;
	return x;
}

// x = a+k
float* vAddScalar3f(float* x, const float* a, const float& k)
{
	x[0] = a[0] + k;
	x[1] = a[1] + k;
	x[2] = a[2] + k;
	return x;
}

// c = a - b
float* vSub3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
	return c;
}

// a -= b
float* vSub3f(float* a, const float* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	return a;
}

// x -= a
float* vSubScalar3f(float* x, const float& a)
{
	x[0] -= a;	x[1] -= a;	x[2] -= a;
	return x;
}

// x = a-k
float* vSubScalar3f(float* x, const float* a, const float& k)
{
	x[0] = a[0] - k;
	x[1] = a[1] - k;
	x[2] = a[2] - k;
	return x;
}

// a *= b (element-wise multiplication)
float* vMul3f(float* a, const float* b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	return a;
}

// c = a * b (element-wise multiplication)
float* vMul3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];
	return c;
}

// x *= a
float* vMulScalar3f(float* x, const float& a)
{
	x[0] *= a;	x[1] *= a;	x[2] *= a;
	return x;
}

// x = a*k
float* vMulScalar3f(float* x, const float* a, const float& k)
{
	x[0] = a[0]*k;
	x[1] = a[1]*k;
	x[2] = a[2]*k;

	return x;
}

// a /= b (element-wise division)
float* vDiv3f(float* a, const float* b)
{
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	return a;
}

// c = a / b (element-wise division)
float* vDiv3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];
	c[2] = a[2] / b[2];
	return c;
}

// x /= a
float* vDivScalar3f(float* x, const float& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
	return x;
}

// x = a/k
float* vDivScalar3f(float* x, const float* a, const float& k)
{
	x[0] = a[0]/k;
	x[1] = a[1]/k;
	x[2] = a[2]/k;

	return x;
}




// a == b
bool vIsEqual3d(const double* a, const double* b)
{
	return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2]);
}

double vDot3d(const double* a, const double* b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

double* vCross3d(const double* a, const double* b, double* c)
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];

	return c;
}

double vNormSquared3d(const double* x)
{
	return vDot3d(x, x);
}

double vNorm3d(const double* x)
{
	return sqrt(vNormSquared3d(x));
}

double* vNormalize3d( double* x )
{
	return vDivScalar3d(x, vNorm3d(x));
}

// a = b
double* vCopy3d(double* a, const double* b)
{
	memcpy(a, b, sizeof(double)*3);
	return a;
}

// a = (b, b, b)
double* vAssign3d(double* a, const double b)
{
	a[0] = b;
	a[1] = b;
	a[2] = b;

	return a;
}

// x = -x;
double* vNegate3d(double* x)
{
	x[0] = -x[0];
	x[1] = -x[1];
	x[2] = -x[2];

	return x;
}

// c = a + b
double* vAdd3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];

	return c;
}

// a += b
double* vAdd3d(double* a, const double* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];

	return a;
}

// x += a
double* vAddScalar3d(double* x, const double& a)
{
	x[0] += a;	x[1] += a;	x[2] += a;
	return x;
}

// x = a+k
double* vAddScalar3d(double* x, const double* a, const double& k)
{
	x[0] = a[0] + k;
	x[1] = a[1] + k;
	x[2] = a[2] + k;
	return x;
}

// c = a - b
double* vSub3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];

	return c;
}

// a -= b
double* vSub3d(double* a, const double* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];

	return a;
}

// x -= a
double* vSubScalar3d(double* x, const double& a)
{
	x[0] -= a;	x[1] -= a;	x[2] -= a;
	return x;
}

// x = a-k
double* vSubScalar3d(double* x, const double* a, const double& k)
{
	x[0] = a[0] - k;
	x[1] = a[1] - k;
	x[2] = a[2] - k;
	return x;
}

// a *= b (element-wise multiplication)
double* vMul3d(double* a, const double* b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];

	return a;
}

// c = a * b (element-wise multiplication)
double* vMul3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];

	return c;
}

// x *= a
double* vMulScalar3d(double* x, const double& a)
{
	x[0] *= a;	x[1] *= a;	x[2] *= a;
	return x;
}

// x = a*k
double* vMulScalar3d(double* x, const double* a, const double& k)
{
	x[0] = a[0]*k;
	x[1] = a[1]*k;
	x[2] = a[2]*k;

	return x;
}

// a /= b (element-wise division)
double* vDiv3d(double* a, const double* b)
{
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	return a;
}

// c = a / b (element-wise division)
double* vDiv3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];
	c[2] = a[2] / b[2];
	return c;
}

// x /= a
double* vDivScalar3d(double* x, const double& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
	return x;
}

// x = a/k
double* vDivScalar3d(double* x, const double* a, const double& k)
{
	x[0] = a[0]/k;
	x[1] = a[1]/k;
	x[2] = a[2]/k;

	return x;
}

// c = a + b
int* vAdd3i(const int* a, const int* b, int* c)
{
	c[0]=a[0]+b[0];
	c[1]=a[1]+b[1];
	c[2]=a[2]+b[2];

	return c;
}

// a += b
int* vAdd3i(int* a, const int* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];

	return a;
}

c = a - b
int* vSub3i(const int* a, const int* b, int* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];

	return c;
}

a -= b
int* vSub3i(int* a, const int* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];

	return a;
}

a *= b
int* vMul3i(int* a, const int* b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];

	return a;
}

c = a * b
int* vMul3i(const int* a, const int* b, int* c)
{
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];

	return c;
}

a /= b
int* vDiv3i(int* a, const int* b)
{
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];

	return a;
}

c = a / b
int* vDiv3i(const int* a, const int* b, int* c)
{
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];
	c[2] = a[2] / b[2];

	return c;
}

a %= b
int* vMod3i(int* a, const int* b)
{
	a[0] %= b[0];
	a[1] %= b[1];
	a[2] %= b[2];

	return a;
}

c = a % b
int* vMod3i(const int* a, const int* b, int* c)
{
	c[0] = a[0] % b[0];
	c[1] = a[1] % b[1];
	c[2] = a[2] % b[2];

	return c;
}

x += a
int* vAddScalar3i(int* x, const int& a)
{
	x[0] += a;
	x[1] += a;
	x[2] += a;

	return x;
}

x = a + k
int* vAddScalar3i(int* x, const int* a, const int& k)
{
	x[0] = a[0] + k;
	x[1] = a[1] + k;
	x[2] = a[2] + k;

	return x;
}

x -= a
int* vSubScalar3i(int* x, const int& a)
{
	x[0] -= a;
	x[1] -= a;
	x[2] -= a;
	return x;
}

x = a - k
int* vSubScalar3i(int* x, const int* a, const int& k)
{
	x[0] = a[0] - k;
	x[1] = a[1] - k;
	x[2] = a[2] - k;

	return x;
}

x *= a
int* vMulScalar3i(int* x, const int& a)
{
	x[0] *= a;
	x[1] *= a;
	x[2] *= a;

	return x;
}

x = a * k
int* vMulScalar3i(int* x, const int* a, const int& k)
{
	x[0] = a[0] * k;
	x[1] = a[1] * k;
	x[2] = a[2] * k;

	return x;
}

x /= a
int* vDivScalar3i(int* x, const int& a)
{
	x[0] /= k;
	x[1] /= k;
	x[2] /= k;

	return x;
}

x = a / k
int* vDivScalar3i(int* x, const int* a, const int& k)
{
	x[0] = a[0] / k;
	x[1] = a[1] / k;
	x[2] = a[2] / k;

	return x;
}

x %= a
int* vModScalar3i(int* x, const int& a)
{
	x[0] %= k;
	x[1] %= k;
	x[2] %= k;

	return x;
}

x = a % k
int* vModScalar3i(int* x, const int* a, const int& k)
{
	x[0] = a[0] % k;
	x[1] = a[1] % k;
	x[2] = a[2] % k;

	return x;
}

//////////////////////////////////////////////////////////////////////////
// 2D version

// a == b
bool vIsEqual2f(const float* a, const float* b)
{
	return (a[0] == b[0] && a[1] == b[1]);
}

float vNorm2f( const float* x )
{
	return sqrt(vNormSquared2f(x));
}

float vNormSquared2f( const float* x )
{
	return vDot2f(x, x);
}

float* vNormalize2f( float* x )
{
	return vDivScalar2f(x, vNorm2f(x));
}

float vDot2f(const float* a, const float* b)
{
	return a[0]*b[0] + a[1]*b[1];
}

float* vCopy2f(float* a, const float* b)
{
	memcpy(a, b, sizeof(float)*2);
	return a;
}

float* vAssign2f(float* a, const float b)
{
	a[0] = a[1] = b;
	return a;
}

// x = -x;
float* vNegate2f(float* x)
{
	x[0] = -x[0];
	x[1] = -x[1];

	return x;
}

// c = a x b
float vCross2f(const float* a, const float* b)
{
	return a[0]*b[1] - a[1]*b[0];
}

// a += b
float* vAdd2f(float* a, const float* b)
{
	a[0] += b[0];
	a[1] += b[1];
	return a;
}

// c = a + b
float* vAdd2f(const float* a, const float* b, float* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	return c;
}

// x += a
float* vAddScalar2f(float* x, const float& a)
{
	x[0] += a;	x[1] += a;
	return x;
}

// x = a+k
float* vAddScalar2f(float* x, const float* a, const float& k)
{
	x[0] = a[0] + k;
	x[1] = a[1] + k;	
	return x;
}

// a -= b
float* vSub2f(float* a, const float* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	return a;
}

// c = a - b
float* vSub2f(const float* a, const float* b, float* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	return c;
}

// x -= a
float* vSubScalar2f(float* x, const float& a)
{
	x[0] -= a;	x[1] -= a;
	return x;
}

// x = a-k
float* vSubScalar2f(float* x, const float* a, const float& k)
{
	x[0] = a[0] - k;
	x[1] = a[1] - k;	
	return x;
}

// a *= b (element-wise multiplication)
float* vMul2f(float* a, const float* b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	return a;
}

// c = a * b (element-wise multiplication)
float* vMul2f(const float* a, const float* b, float* c)
{
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	return c;
}

// x *= a
float* vMulScalar2f(float* x, const float& a)
{
	x[0] *= a;	x[1] *= a;
	return x;
}

// x = a*k
float* vMulScalar2f(float* x, const float* a, const float& k)
{
	x[0] = a[0]*k;
	x[1] = a[1]*k;

	return x;
}

// a /= b (element-wise division)
float* vDiv2f(float* a, const float* b)
{
	a[0] /= b[0];
	a[1] /= b[1];
	return a;
}

// c = a / b (element-wise division)
float* vDiv2f(const float* a, const float* b, float* c)
{
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];
	return c;
}

// x /= a
float* vDivScalar2f( float* x, const float& a )
{
	x[0] /= a;
	x[1] /= a;
	return x;
}

// x = a/k
float* vDivScalar2f(float* x, const float* a, const float& k)
{
	x[0] = a[0]/k;
	x[1] = a[1]/k;
	return x;
}



// a == b
bool vIsEqual2d(const double* a, const double* b)
{
	return (a[0] == b[0] && a[1] == b[1]);
}

double vNorm2d( const double* x )
{
	return sqrt(vNormSquared2d(x));
}

double vNormSquared2d( const double* x )
{
	return vDot2d(x, x);
}

double* vNormalize2d( double* x )
{
	return vDivScalar2d(x, vNorm2d(x));
}

double vDot2d(const double* a, const double*b)
{
	return a[0]*b[0] + a[1]*b[1];

}

// c = a x b
double vCross2d(const double* a, const double* b)
{
	return a[0]*b[1] - a[1]*b[0];
}


double* vCopy2d(double* a, const double* b)
{
	memcpy(a, b, sizeof(double)*2);
	return a;
}

double* vAssign2d(double* a, const double b)
{
	a[0] = a[1] = b;
	return a;
}

// x = -x;
double* vNegate2d(double* x)
{
	x[0] = -x[0];
	x[1] = -x[1];
	return x;
}

// a += b
double* vAdd2d(double* a, const double* b)
{
	a[0] += b[0];
	a[1] += b[1];
	return a;
}

// c = a + b
double* vAdd2d(const double* a, const double* b, double* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	return c;
}

// x += a
double* vAddScalar2d(double* x, const double& a)
{
	x[0] += a;	x[1] += a;
	return x;
}

// x = a+k
double* vAddScalar2d(double* x, const double* a, const double& k)
{
	x[0] = a[0] + k;
	x[1] = a[1] + k;	
	return x;
}

// a -= b
double* vSub2d(double* a, const double* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	return a;
}

// c = a - b
double* vSub2d(const double* a, const double* b, double* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	return c;
}

// x -= a
double* vSubScalar2d(double* x, const double& a)
{
	x[0] -= a;	x[1] -= a;
	return x;
}

// x = a-k
double* vSubScalar2d(double* x, const double* a, const double& k)
{
	x[0] = a[0] - k;
	x[1] = a[1] - k;	
	return x;
}

// a *= b (element-wise multiplication)
double* vMul2d(double* a, const double* b)
{
	a[0] *= b[0];
	a[1] *= b[1];
	return a;
}

// c = a * b (element-wise multiplication)
double* vMul2d(const double* a, const double* b, double* c)
{
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	return c;
}

// x *= a
double* vMulScalar2d(double* x, const double& a)
{
	x[0] *= a;	x[1] *= a;
	return x;
}

// x = a*k
double* vMulScalar2d(double* x, const double* a, const double& k)
{
	x[0] = a[0]*k;
	x[1] = a[1]*k;

	return x;
}

// a /= b (element-wise division)
double* vDiv2d(double* a, const double* b)
{
	a[0] /= b[0];
	a[1] /= b[1];
	return a;
}

// c = a / b (element-wise division)
double* vDiv2d(const double* a, const double* b, double* c)
{
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];
	return c;
}

// x /= a
double* vDivScalar2d( double* x, const double& a )
{
	x[0] /= a;
	x[1] /= a;
	return x;
}

// x = a/k
double* vDivScalar2d(double* x, const double* a, const double& k)
{
	x[0] = a[0]/k;
	x[1] = a[1]/k;
	return x;
}

// c = a + b
int* vAdd2i(const int* a, const int* b, int* c)
{
	c[0]=a[0]+b[0];
	c[1]=a[1]+b[1];
	
	return c;
}

// a += b
int* vAdd2i(int* a, const int* b)
{
	a[0] += b[0];
	a[1] += b[1];

	return a;
}

c = a - b
int* vSub2i(const int* a, const int* b, int* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];

	return c;
}

a -= b
int* vSub2i(int* a, const int* b)
{
	a[0] -= b[0];
	a[1] -= b[1];

	return a;
}

a *= b
int* vMul2i(int* a, const int* b)
{
	a[0] *= b[0];
	a[1] *= b[1];

	return a;
}

c = a * b
int* vMul2i(const int* a, const int* b, int* c)
{
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];

	return c;
}

a /= b
int* vDiv2i(int* a, const int* b)
{
	a[0] /= b[0];
	a[1] /= b[1];

	return a;
}

c = a / b
int* vDiv2i(const int* a, const int* b, int* c)
{
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];

	return c;
}

a %= b
int* vMod2i(int* a, const int* b)
{
	a[0] %= b[0];
	a[1] %= b[1];

	return a;
}

c = a % b
int* vMod2i(const int* a, const int* b, int* c)
{
	c[0] = a[0] % b[0];
	c[1] = a[1] % b[1];

	return c;
}

x += a
int* vAddScalar2i(int* x, const int& a)
{
	x[0] += a;
	x[1] += a;

	return x;
}

x = a + k
int* vAddScalar2i(int* x, const int* a, const int& k)
{
	x[0] = a[0] + k;
	x[1] = a[1] + k;

	return x;
}

x -= a
int* vSubScalar2i(int* x, const int& a)
{
	x[0] -= a;
	x[1] -= a;

	return x;
}

x = a - k
int* vSubScalar2i(int* x, const int* a, const int& k)
{
	x[0] = a[0] - k;
	x[1] = a[1] - k;

	return x;
}

x *= a
int* vMulScalar2i(int* x, const int& a)
{
	x[0] *= a;
	x[1] *= a;

	return x;
}

x = a * k
int* vMulScalar2i(int* x, const int* a, const int& k)
{
	x[0] = a[0] * k;
	x[1] = a[1] * k;

	return x;
}

x /= a
int* vDivScalar2i(int* x, const int& a)
{
	x[0] /= k;
	x[1] /= k;

	return x;
}

x = a / k
int* vDivScalar2i(int* x, const int* a, const int& k)
{
	x[0] = a[0] / k;
	x[1] = a[1] / k;

	return x;
}

x %= a
int* vModScalar2i(int* x, const int& a)
{
	x[0] %= k;
	x[1] %= k;

	return x;
}

x = a % k
int* vModScalar2i(int* x, const int* a, const int& k)
{
	x[0] = a[0] % k;
	x[1] = a[1] % k;

	return x;
}
