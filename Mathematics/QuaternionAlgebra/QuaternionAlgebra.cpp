#include "QuaternionAlgebra.h"
#include <math.h>
#include <memory>

#ifndef _MATH_DEFINES_DEFINED
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD M_PI/180.0
#endif
#ifndef RAD2DEG
#define RAD2DEG 180.0/M_PI
#endif


bool qIsEquald(const double* a, const double* b)
{
	return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]);
}

double* qNegated(double* q)
{
	q[0] = -q[0];
	q[1] = -q[1];
	q[2] = -q[2];
	q[3] = -q[3];
	return q;
}
double* qNegated(double* q, const double* q0)
{
	q[0] = -q0[0];
	q[1] = -q0[1];
	q[2] = -q0[2];
	q[3] = -q0[3];
	return q;
}

double* qIdentityd(double* q)
{
	q[0] = 1.0;
	q[1] = q[2] = q[3] = 0.0;
	return q;
}

double* qCopyd(double* dst, const double* src)
{
	memcpy(dst, src, sizeof(double)*4);
	return dst;
}

// |q|^2
double qNormSquaredd(const double* q)
{
	return q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
}

// |q|
double qNormd(const double* q)
{
	return sqrt(qNormSquaredd(q));
}

// q = q / |q|
double* qNormalized(double* q)
{
	return qDivScalard(q, qNormd(q));
}

// q2 = q1 / |q1|
double* qNormalized(const double* q1, double* q2)
{
	return qDivScalard(q2, q1, qNormd(q1));
}


// q = q^(-1)
double* qInvertd(double* q)
{
	double n = qNormSquaredd(q);
	q[0] = q[0]/n;
	q[1] = -q[1]/n;
	q[2] = -q[2]/n;
	q[3] = -q[3]/n;

	return q;
}

// q2 = q1^(-1)
double* qInvertd(const double* q1, double* q2)
{
	double n = qNormSquaredd(q1);
	q2[0] = q1[0]/n;
	q2[1] = -q1[1]/n;
	q2[2] = -q1[2]/n;
	q2[3] = -q1[3]/n;

	return q2;
}

// q1 += q2
double* qAddd(double* q1, const double* q2)
{
	q1[0] += q2[0];
	q1[1] += q2[1];
	q1[2] += q2[2];
	q1[3] += q2[3];

	return q1;
}

// q1 = q2 + q3
double* qAddd(double* q1, const double* q2, const double* q3)
{
	q1[0] = q2[0] + q3[0];
	q1[1] = q2[1] + q3[1];
	q1[2] = q2[2] + q3[2];
	q1[3] = q2[3] + q3[3];

	return q1;
}

// q1 -= q2
double* qSubd(double* q1, const double* q2)
{
	q1[0] -= q2[0];
	q1[1] -= q2[1];
	q1[2] -= q2[2];
	q1[3] -= q2[3];
	
	return q1;
}

// q1 = q2 - q3
double* qSubd(double* q1, const double* q2, const double* q3)
{
	q1[0] = q2[0] - q3[0];
	q1[1] = q2[1] - q3[1];
	q1[2] = q2[2] - q3[2];
	q1[3] = q2[3] - q3[3];

	return q1;
}

// q1 *= q2
double* qMuld(double* q1, const double* q2)
{
	double qtemp[4];
	memcpy(qtemp, q1, sizeof(double)*4);

	q1[0] = qtemp[0]*q2[0] - qtemp[1]*q2[1] - qtemp[2]*q2[2] - qtemp[3]*q2[3];
	q1[1] = qtemp[1]*q2[0] + qtemp[0]*q2[1] - qtemp[3]*q2[2] + qtemp[2]*q2[3];
	q1[2] = qtemp[2]*q2[0] + qtemp[3]*q2[1] + qtemp[0]*q2[2] - qtemp[1]*q2[3];
	q1[3] = qtemp[3]*q2[0] - qtemp[2]*q2[1] + qtemp[1]*q2[2] + qtemp[0]*q2[3];

	return q1;
}

// q1 = q2 * q3
double* qMuld(double* q1, const double* q2, const double* q3)
{
	q1[0] = q2[0]*q3[0] - q2[1]*q3[1] - q2[2]*q3[2] - q2[3]*q3[3];
	q1[1] = q2[1]*q3[0] + q2[0]*q3[1] - q2[3]*q3[2] + q2[2]*q3[3];
	q1[2] = q2[2]*q3[0] + q2[3]*q3[1] + q2[0]*q3[2] - q2[1]*q3[3];
	q1[3] = q2[3]*q3[0] - q2[2]*q3[1] + q2[1]*q3[2] + q2[0]*q3[3];

	return q1;
}


// // inline CQuaternion operator*(const CQuaternion& q, const VECTOR& v)
// // {
// // 	return q*Q(0,v.x,v.y,v.z);
// // }
// // q *= v
// double* qMulVectord(double* q, const double* v)
// {
// 
// }
// 
// // q1 = q2 * v
// double* qMulVectord(double* q1, const double* q2, const double* v)
// {
// 
// }

// q *= k
double* qMulScalard(double* q, const double k)
{
	q[0] *= k;
	q[1] *= k;
	q[2] *= k;
	q[3] *= k;

	return q;
}

// q1 = q2 * k
double* qMulScalard(double* q1, const double* q2, const double k)
{
	q1[0] = q2[0]*k;
	q1[1] = q2[1]*k;
	q1[2] = q2[2]*k;
	q1[3] = q2[3]*k;

	return q1;
}

// q1 = k * q2
double* qMulScalard(double* q1, const double k, const double* q2)
{
	return qMulScalard(q1, q2, k);
}

// q1 /= q2
double* qDivd(double* q1, const double* q2)
{
	double q2inv[4];
	qInvertd(q2, q2inv);
	return qMuld(q1, q2inv);
}

// q1 = q2 / q3
double* qDivd(double* q1, const double* q2, const double* q3)
{
	double q3inv[4];
	qInvertd(q3, q3inv);
	return qMuld(q1, q2, q3inv);
}

// // q /= v
// double* qDivVectord(double* q, const double* v)
// {
// 
// }
// 
// // q1 = q2 / v
// double* qDivVectord(double* q1, const double* q2, const double* v)
// {
// 
// }
// 
// // q1 = v / q2
// double* qDivVectord(double* q1, const double* v, const double* q2)
// {
// 
// }

// q /= k
double* qDivScalard(double* q, const double k)
{
	return qMulScalard(q, 1.0/k);
}

// q1 = q2 / k
double* qDivScalard(double* q1, const double* q2, const double k)
{
	return qMulScalard(q1, q2, 1.0/k);
}

// q1 = k / q2
double* qDivScalard(double* q1, const double k, const double* q2)
{
	double q2inv[4];
	qInvertd(q2, q2inv);
	return qMulScalard(q1, k, q2inv);
}

// convert axis-angle representation to quaternion (Map from so(3) --> SO(3))
double* qExpd(const double* a, double* q)
{
	double m = a[1]*a[1] + a[2]*a[2] + a[3]*a[3];

	if(m == 0)
		qIdentityd(q);
	else
	{
		m = sqrt(m);
		double sm = sin(a[0]*0.5)/m;
		q[0] = cos(a[0]*0.5);
		q[1] = a[1]*sm;
		q[2] = a[2]*sm;
		q[3] = a[3]*sm;

		qNormalized(q);				// Do I have to normalize q here?
	}

	return q;
}

// convert quaternion to axis-angle representation (Map from SO(3) --> so(3))
double* qLogd(const double* q, double* a)
{
	double qq[4];	// normalized q
	qNormalized(q, qq);

	if( qq[0] == 0 )
	{
		a[0] = 0;
		a[1] = 0.5*M_PI*qq[1];
		a[2] = 0.5*M_PI*qq[2];
		a[3] = 0.5*M_PI*qq[3];
	}
	else if( qq[0] == 1 )
	{
		a[0] = 0;
		a[1] = 0;
		a[2] = 0;
		a[3] = 0;
	}
	else
	{
		double v = sqrt(q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
		a[0] = 2*atan2(v, qq[0]);
		a[1] = qq[1]/v;
		a[2] = qq[2]/v;
		a[3] = qq[3]/v;
	}

	return a;
}

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
double* qFromMatrixd(double* q, const double* R)
{
	double tr = R[0] + R[4] + R[8];
	if( tr > 0 )
	{
		double s = 0.5 / sqrt(tr + 1.0);
		q[0] = 0.25 / s;
		q[1] = ( R[5] - R[7] ) * s;			// (R21 - R12)*s
		q[2] = ( R[6] - R[2] ) * s;			// (R02 - R20)*s
		q[3] = ( R[1] - R[3] ) * s;			// (R10 - R01)*s
	}
	else
	{
		if( R[0] > R[4] && R[0] > R[8] )	// R00 > R11 && R00 > R22
		{
			double s = 0.5 / sqrt(1.0 + R[0] - R[4] - R[8]);
			q[0] = ( R[5] - R[7] ) * s;		// (R21 - R12)*s
			q[1] = 0.25 / s;
			q[2] = ( R[3] + R[1] ) * s;		// (R01 + R10)*s
			q[3] = ( R[6] + R[2] ) * s;		// (R02 + R20)*s
		}
		else if (R[4] > R[8])
		{
			double s = 0.5 / sqrt(1.0 + R[4] - R[0] - R[8]);
			q[0] = ( R[6] - R[2] ) * s;		// (R02 - R20)*s
			q[1] = ( R[3] + R[1] ) * s;		// (R01 + R10)*s
			q[2] = 0.25 / s;
			q[3] = ( R[7] + R[5] ) * s;		// (R12 + R21)*s
		}
		else
		{
			double s = 0.5 / sqrt(1.0 + R[8] - R[0] - R[4]);
			q[0] = ( R[1] - R[3] ) * s;		// (R10 - R01)*s
			q[1] = ( R[6] + R[2] ) * s;		// (R02 + R20)*s
			q[2] = ( R[7] + R[5] ) * s;		// (R12 + R21)*s
			q[3] = 0.25f / s;
		}
	}

	return q;
}

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
double* qFromAxisAngled(double* q, const double angle, const double* axis)
{
	double a[4] = {angle, axis[0], axis[1], axis[2]};
	return qExpd(a, q);
}

double* qFromEulerd(double* q, const double a, const double b, const double c, const char* order)
{
	double ang[3] = {a, b, c};
	double qtemp[4];
	double axis[4];
	for(register int i = 0; i < 3; i++)
	{
		axis[0] = ang[i]*0.5;
		axis[1] = axis[2] = axis[3] = 0.0;
		if(order[i] == 'z' || order[i] == 'Z')
			axis[3] = 1;
		else if(order[i] == 'y' || order[i] == 'Y')
			axis[2] = 1;
		else if(order[i] == 'x' || order[i] == 'X')
			axis[1] = 1;

		qExpd(axis, qtemp);
		if(i == 0)
			qCopyd(q, qtemp);
		else
			qMuld(q, qtemp);
	}

	return q;
}

// Convert quaternion to a rotation matrix
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
double* qToMatrixd(const double* q, double* R)
{
	R[0] = q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3];
	R[4] = q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3];
	R[8] = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];

	R[3] = 2*q[1]*q[2] - 2*q[0]*q[3];
	R[1] = 2*q[1]*q[2] + 2*q[0]*q[3];

	R[6] = 2*q[1]*q[3] + 2*q[0]*q[2];
	R[2] = 2*q[1]*q[3] - 2*q[0]*q[2];

	R[7] = 2*q[2]*q[3] - 2*q[0]*q[1];
	R[5] = 2*q[2]*q[3] + 2*q[0]*q[1];

	return R;
}



//////////////////////////////////////////////////////////////////////////
// float
//////////////////////////////////////////////////////////////////////////

bool qIsEqualf(const float* a, const float* b)
{
	return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]);
}

float* qNegatef(float* q)
{
	q[0] = -q[0];
	q[1] = -q[1];
	q[2] = -q[2];
	q[3] = -q[3];
	return q;
}
float* qNegatef(float* q, const float* q0)
{
	q[0] = -q0[0];
	q[1] = -q0[1];
	q[2] = -q0[2];
	q[3] = -q0[3];
	return q;
}

float* qIdentityf(float* q)
{
	q[0] = 1.0;
	q[1] = q[2] = q[3] = 0.0;
	return q;
}

float* qCopyf(float* dst, const float* src)
{
	memcpy(dst, src, sizeof(float)*4);
	return dst;
}

// |q|^2
float qNormSquaredf(const float* q)
{
	return q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
}

// |q|
float qNormf(const float* q)
{
	return sqrt(qNormSquaredf(q));
}

// q = q / |q|
float* qNormalizef(float* q)
{
	return qDivScalarf(q, qNormf(q));
}

// q2 = q1 / |q1|
float* qNormalizef(const float* q1, float* q2)
{
	return qDivScalarf(q2, q1, qNormf(q1));
}


// q = q^(-1)
float* qInvertf(float* q)
{
	float n = qNormSquaredf(q);
	q[0] = q[0]/n;
	q[1] = -q[1]/n;
	q[2] = -q[2]/n;
	q[3] = -q[3]/n;

	return q;
}

// q2 = q1^(-1)
float* qInvertf(const float* q1, float* q2)
{
	float n = qNormSquaredf(q1);
	q2[0] = q1[0]/n;
	q2[1] = -q1[1]/n;
	q2[2] = -q1[2]/n;
	q2[3] = -q1[3]/n;

	return q2;
}

// q1 += q2
float* qAddf(float* q1, const float* q2)
{
	q1[0] += q2[0];
	q1[1] += q2[1];
	q1[2] += q2[2];
	q1[3] += q2[3];

	return q1;
}

// q1 = q2 + q3
float* qAddf(float* q1, const float* q2, const float* q3)
{
	q1[0] = q2[0] + q3[0];
	q1[1] = q2[1] + q3[1];
	q1[2] = q2[2] + q3[2];
	q1[3] = q2[3] + q3[3];

	return q1;
}

// q1 -= q2
float* qSubf(float* q1, const float* q2)
{
	q1[0] -= q2[0];
	q1[1] -= q2[1];
	q1[2] -= q2[2];
	q1[3] -= q2[3];

	return q1;
}

// q1 = q2 - q3
float* qSubf(float* q1, const float* q2, const float* q3)
{
	q1[0] = q2[0] - q3[0];
	q1[1] = q2[1] - q3[1];
	q1[2] = q2[2] - q3[2];
	q1[3] = q2[3] - q3[3];

	return q1;
}

// q1 *= q2
float* qMulf(float* q1, const float* q2)
{
	float qtemp[4];
	memcpy(qtemp, q1, sizeof(float)*4);

	q1[0] = qtemp[0]*q2[0] - qtemp[1]*q2[1] - qtemp[2]*q2[2] - qtemp[3]*q2[3];
	q1[1] = qtemp[1]*q2[0] + qtemp[0]*q2[1] - qtemp[3]*q2[2] + qtemp[2]*q2[3];
	q1[2] = qtemp[2]*q2[0] + qtemp[3]*q2[1] + qtemp[0]*q2[2] - qtemp[1]*q2[3];
	q1[3] = qtemp[3]*q2[0] - qtemp[2]*q2[1] + qtemp[1]*q2[2] + qtemp[0]*q2[3];

	return q1;
}

// q1 = q2 * q3
float* qMulf(float* q1, const float* q2, const float* q3)
{
	q1[0] = q2[0]*q3[0] - q2[1]*q3[1] - q2[2]*q3[2] - q2[3]*q3[3];
	q1[1] = q2[1]*q3[0] + q2[0]*q3[1] - q2[3]*q3[2] + q2[2]*q3[3];
	q1[2] = q2[2]*q3[0] + q2[3]*q3[1] + q2[0]*q3[2] - q2[1]*q3[3];
	q1[3] = q2[3]*q3[0] - q2[2]*q3[1] + q2[1]*q3[2] + q2[0]*q3[3];

	return q1;
}


// // inline CQuaternion operator*(const CQuaternion& q, const VECTOR& v)
// // {
// // 	return q*Q(0,v.x,v.y,v.z);
// // }
// // q *= v
// float* qMulVectorf(float* q, const float* v)
// {
// 
// }
// 
// // q1 = q2 * v
// float* qMulVectorf(float* q1, const float* q2, const float* v)
// {
// 
// }

// q *= k
float* qMulScalarf(float* q, const float k)
{
	q[0] *= k;
	q[1] *= k;
	q[2] *= k;
	q[3] *= k;

	return q;
}

// q1 = q2 * k
float* qMulScalarf(float* q1, const float* q2, const float k)
{
	q1[0] = q2[0]*k;
	q1[1] = q2[1]*k;
	q1[2] = q2[2]*k;
	q1[3] = q2[3]*k;

	return q1;
}

// q1 = k * q2
float* qMulScalarf(float* q1, const float k, const float* q2)
{
	return qMulScalarf(q1, q2, k);
}

// q1 /= q2
float* qDivf(float* q1, const float* q2)
{
	float q2inv[4];
	qInvertf(q2, q2inv);
	return qMulf(q1, q2inv);
}

// q1 = q2 / q3
float* qDivf(float* q1, const float* q2, const float* q3)
{
	float q3inv[4];
	qInvertf(q3, q3inv);
	return qMulf(q1, q2, q3inv);
}

// // q /= v
// float* qDivVectorf(float* q, const float* v)
// {
// 
// }
// 
// // q1 = q2 / v
// float* qDivVectorf(float* q1, const float* q2, const float* v)
// {
// 
// }
// 
// // q1 = v / q2
// float* qDivVectorf(float* q1, const float* v, const float* q2)
// {
// 
// }

// q /= k
float* qDivScalarf(float* q, const float k)
{
	return qMulScalarf(q, 1.f/k);
}

// q1 = q2 / k
float* qDivScalarf(float* q1, const float* q2, const float k)
{
	return qMulScalarf(q1, q2, 1.f/k);
}

// q1 = k / q2
float* qDivScalarf(float* q1, const float k, const float* q2)
{
	float q2inv[4];
	qInvertf(q2, q2inv);
	return qMulScalarf(q1, k, q2inv);
}

// convert axis-angle representation to quaternion (Map from so(3) --> SO(3))
float* qExpf(const float* a, float* q)
{
	float m = a[1]*a[1] + a[2]*a[2] + a[3]*a[3];

	if(m == 0)
		qIdentityf(q);
	else
	{
		m = sqrt(m);
		float sm = sin(a[0]*0.5f)/m;
		q[0] = cos(a[0]*0.5f);
		q[1] = a[1]*sm;
		q[2] = a[2]*sm;
		q[3] = a[3]*sm;

		qNormalizef(q);				// Do I have to normalize q here?
	}

	return q;
}

// convert quaternion to axis-angle representation (Map from SO(3) --> so(3))
float* qLogf(const float* q, float* a)
{
	float qq[4];	// normalized q
	qNormalizef(q, qq);

	if( qq[0] == 0 )
	{
		a[0] = 0.f;
		a[1] = 0.5f*M_PI*qq[1];
		a[2] = 0.5f*M_PI*qq[2];
		a[3] = 0.5f*M_PI*qq[3];
	}
	else if( qq[0] == 1 )
	{
		a[0] = 0;
		a[1] = 0;
		a[2] = 0;
		a[3] = 0;
	}
	else
	{
		float v = sqrt(q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
		a[0] = 2*atan2(v, qq[0]);
		a[1] = qq[1]/v;
		a[2] = qq[2]/v;
		a[3] = qq[3]/v;
	}

	return a;
}

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
float* qFromMatrixf(float* q, const float* R)
{
	float tr = R[0] + R[4] + R[8];
	if( tr > 0 )
	{
		float s = 0.5 / sqrt(tr + 1.f);
		q[0] = 0.25 / s;
		q[1] = ( R[5] - R[7] ) * s;			// (R21 - R12)*s
		q[2] = ( R[6] - R[2] ) * s;			// (R02 - R20)*s
		q[3] = ( R[1] - R[3] ) * s;			// (R10 - R01)*s
	}
	else
	{
		if( R[0] > R[4] && R[0] > R[8] )	// R00 > R11 && R00 > R22
		{
			float s = 0.5 / sqrt(1.0 + R[0] - R[4] - R[8]);
			q[0] = ( R[5] - R[7] ) * s;		// (R21 - R12)*s
			q[1] = 0.25 / s;
			q[2] = ( R[3] + R[1] ) * s;		// (R01 + R10)*s
			q[3] = ( R[6] + R[2] ) * s;		// (R02 + R20)*s
		}
		else if (R[4] > R[8])
		{
			float s = 0.5 / sqrt(1.0 + R[4] - R[0] - R[8]);
			q[0] = ( R[6] - R[2] ) * s;		// (R02 - R20)*s
			q[1] = ( R[3] + R[1] ) * s;		// (R01 + R10)*s
			q[2] = 0.25 / s;
			q[3] = ( R[7] + R[5] ) * s;		// (R12 + R21)*s
		}
		else
		{
			float s = 0.5 / sqrt(1.0 + R[8] - R[0] - R[4]);
			q[0] = ( R[1] - R[3] ) * s;		// (R10 - R01)*s
			q[1] = ( R[6] + R[2] ) * s;		// (R02 + R20)*s
			q[2] = ( R[7] + R[5] ) * s;		// (R12 + R21)*s
			q[3] = 0.25f / s;
		}
	}

	return q;
}

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
float* qFromAxisAnglef(float* q, const float angle, const float* axis)
{
	float a[4] = {angle, axis[0], axis[1], axis[2]};
	return qExpf(a, q);
}

float* qFromEulerf(float* q, const float a, const float b, const float c, const char* order)
{
	float ang[3] = {a, b, c};
	float qtemp[4];
	float axis[4];
	for(register int i = 0; i < 3; i++)
	{
		axis[0] = ang[i]*0.5;
		axis[1] = axis[2] = axis[3] = 0.0;
		if(order[i] == 'z' || order[i] == 'Z')
			axis[3] = 1;
		else if(order[i] == 'y' || order[i] == 'Y')
			axis[2] = 1;
		else if(order[i] == 'x' || order[i] == 'X')
			axis[1] = 1;

		qExpf(axis, qtemp);
		if(i == 0)
			qCopyf(q, qtemp);
		else
			qMulf(q, qtemp);
	}

	return q;
}

// Convert quaternion to a rotation matrix
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
float* qToMatrixf(const float* q, float* R)
{
	R[0] = q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3];
	R[4] = q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3];
	R[8] = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];

	R[3] = 2*q[1]*q[2] - 2*q[0]*q[3];
	R[1] = 2*q[1]*q[2] + 2*q[0]*q[3];

	R[6] = 2*q[1]*q[3] + 2*q[0]*q[2];
	R[2] = 2*q[1]*q[3] - 2*q[0]*q[2];

	R[7] = 2*q[2]*q[3] - 2*q[0]*q[1];
	R[5] = 2*q[2]*q[3] + 2*q[0]*q[1];

	return R;
}