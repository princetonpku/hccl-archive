#include "VectorAlgebra.h"
#include <math.h>
#include <typeinfo.h>

float vDot3f(const float* a, const float* b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void vCross3f(const float* a, const float* b, float* c)
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

float vNormSquared3f(const float* x)
{
	return vDot3f(x, x);
}

float vNorm3f(const float* x)
{
	return sqrt(vNormSquared3f(x));
}

void vNormalize3f( float* x )
{
	vDivScalar3f(x, vNorm3f(x));
}

// a = b
void vCopy3f(float* a, const float* b)
{
	memcpy(a, b, sizeof(float)*3);
}

// a = (b, b, b)
void vAssign3f(float* a, const float b)
{
	a[0] = b;
	a[1] = b;
	a[2] = b;
}

// c = a + b
void vAdd3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

// a += b
void vAdd3f(float* a, const float* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

// c = a - b
void vSub3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

// a -= b
void vSub3f(float* a, const float* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

// x *= a
void vMulScalar3f(float* x, const float& a)
{
	x[0] *= a;	x[1] *= a;	x[2] *= a;
}


// x /= a
void vDivScalar3f(float* x, const float& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
}


// a += b
void vAdd2d(double* a, const double* b)
{
	a[0] += b[0];
	a[1] += b[1];
}

// a += b
void vAdd2f(float* a, const float* b)
{
	a[0] += b[0];
	a[1] += b[1];
}






double vDot3d(const double* a, const double* b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void vCross3d(const double* a, const double* b, double* c)
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

double vNormSquared3d(const double* x)
{
	return vDot3d(x, x);
}

double vNorm3d(const double* x)
{
	return sqrt(vNormSquared3d(x));
}

void vNormalize3d( double* x )
{
	vDivScalar3d(x, vNorm3d(x));
}

// a = b
void vCopy3d(double* a, const double* b)
{
	memcpy(a, b, sizeof(double)*3);
}

// a = (b, b, b)
void vAssign3d(double* a, const double b)
{
	a[0] = b;
	a[1] = b;
	a[2] = b;
}

// c = a + b
void vAdd3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

// a += b
void vAdd3d(double* a, const double* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

// c = a - b
void vSub3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

// a -= b
void vSub3d(double* a, const double* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

// x *= a
void vMulScalar3d(double* x, const double& a)
{
	x[0] *= a;	x[1] *= a;	x[2] *= a;
}


// x /= a
void vDivScalar3d(double* x, const double& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
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

