#include "VectorAlgebra.h"
#include <math.h>
#include <memory>

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


// x /= a
float* vDivScalar3f(float* x, const float& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
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


//////////////////////////////////////////////////////////////////////////
// 2D version
float vNorm2f( const float* x )
{
	return sqrt(vNormSquared2f(x));
}

float vNormSquared2f( const float* x )
{
	return vDot2f(x, x);
}

void vNormalize2f( float* x )
{
	vDivScalar2f(x, vNorm2f(x));
}

float vDot2f(const float* a, const float* b)
{
	return a[0]*b[0] + a[1]*b[1];
}


// a += b
void vAdd2f(float* a, const float* b)
{
	a[0] += b[0];
	a[1] += b[1];
}

// c = a + b
void vAdd2f(const float* a, const float* b, float* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
}

// a -= b
void vSub2f(float* a, const float* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
}

// x /= a
void vDivScalar2f( float* x, const float& a )
{
	x[0] /= a;	x[1] /= a;
}






// a += b
void vAdd2d(double* a, const double* b)
{
	a[0] += b[0];
	a[1] += b[1];
}

double vNorm2d( const double* x )
{
	return sqrt(vNormSquared2d(x));
}

double vNormSquared2d( const double* x )
{
	return vDot2d(x, x);
}

void vNormalize2d( double* x )
{
	vDivScalar2d(x, vNorm2d(x));
}

double vDot2d(const double* a, const double*b)
{
	return a[0]*b[0] + a[1]*b[1];

}

// c = a + b
void vAdd2d(const double* a, const double* b, double* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
}

// a -= b
void vSub2d(double* a, const double* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
}

// x /= a
void vDivScalar2d( double* x, const double& a )
{
	x[0] /= a;	x[1] /= a;
}

