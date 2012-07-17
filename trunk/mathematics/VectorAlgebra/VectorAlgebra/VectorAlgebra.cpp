#include "VectorAlgebra.h"
#include <math.h>
#include <typeinfo.h>

float Dot3f(const float* a, const float* b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void Cross3f(const float* a, const float* b, float* c)
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

float NormSquared3f(const float* x)
{
	return Dot3f(x, x);
}

float Norm3f(const float* x)
{
	return sqrt(NormSquared3f(x));
}

// a = b
void Assign3f(float* a, const float* b)
{
	memcpy(a, b, sizeof(float)*3);
}

// a = (b, b, b)
void Assign3f(float* a, const float b)
{
	a[0] = b;
	a[1] = b;
	a[2] = b;
}

// c = a + b
void AddVector3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

// a += b
void AddVector3f(float* a, const float* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

// c = a - b
void SubVector3f(const float* a, const float* b, float* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

// a -= b
void SubVector3f(float* a, const float* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

// x *= a
void MultiplyScalar3f(float* x, const float& a)
{
	x[0] *= a;	x[1] *= a;	x[2] *= a;
}


// x /= a
void DivideByScalar3f(float* x, const float& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
}








double Dot3d(const double* a, const double* b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void Cross3d(const double* a, const double* b, double* c)
{
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

double NormSquared3d(const double* x)
{
	return Dot3d(x, x);
}

double Norm3d(const double* x)
{
	return sqrt(NormSquared3d(x));
}

// a = b
void Assign3d(double* a, const double* b)
{
	memcpy(a, b, sizeof(double)*3);
}

// a = (b, b, b)
void Assign3d(double* a, const double b)
{
	a[0] = b;
	a[1] = b;
	a[2] = b;
}

// c = a + b
void AddVector3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

// a += b
void AddVector3d(double* a, const double* b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

// c = a - b
void SubVector3d(const double* a, const double* b, double* c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

// a -= b
void SubVector3d(double* a, const double* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

// x *= a
void MultiplyScalar3d(double* x, const double& a)
{
	x[0] *= a;	x[1] *= a;	x[2] *= a;
}


// x /= a
void DivideByScalar3d(double* x, const double& a)
{
	x[0] /= a;	x[1] /= a;	x[2] /= a;
}


//////////////////////////////////////////////////////////////////////////
// 2D version


float Dot2f(const float* a, const float* b)
{
	return a[0]*b[0] + a[1]*b[1];
}

// a -= b
void SubVector2f(float* a, const float* b)
{
	a[0] -= b[0];
	a[1] -= b[1];
}

// c = a + b
void AddVector2f(const float* a, const float* b, float* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
}





double Dot2d(const double* a, const double*b)
{
	return a[0]*b[0] + a[1]*b[1];

}


// c = a + b
void AddVector2d(const double* a, const double* b, double* c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];

}

// a -= b
void SubVector2d(double* a, const double* b)
{
	a[0] -= b[0];
	a[1] -= b[1];

}