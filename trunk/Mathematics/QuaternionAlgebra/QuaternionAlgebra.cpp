#include "QuaternionAlgebra.h"
#include <math.h>
#include <typeinfo.h>

#ifndef _MATH_DEFINES_DEFINED
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD M_PI/180.0
#endif
#ifndef RAD2DEG
#define RAD2DEG 180.0/M_PI
#endif


void qIdentityd(double* q)
{
	q[0] = 1.0;
	q[1] = q[2] = q[3] = 0.0;
}

void qCopyd(double* dst, const double* src)
{
	memcpy(dst, src, sizeof(double)*4);
}

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
void qFromAxisAngled(double* q, const double angle, const double* axis)
{
	double m = axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2];

	if(m == 0)
		qIdentityd(q);
	else
	{
		m = sqrt(m);
		double sm = sin(angle*0.5)/m;
		q[0] = cos(angle*0.5);
		q[1] = axis[0]*sm;
		q[2] = axis[1]*sm;
		q[3] = axis[2]*sm;

		// Do I have to normalize q here?
	}
}

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
void qFromMatrixd(double* q, const double* R)
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
void qNormalize(double* q)
{
	qDivScalard(q, qNormd(q));
}

// q2 = q1 / |q1|
void qNormalize(const double* q1, double* q2)
{
	qDivScalard(q2, q1, qNormd(q1));
}

bool qIsEquald(const double* q1, const double* q2)
{
	return ( q1[0] == q2[0] && q1[1] == q2[1] && q1[2] == q2[2] && q1[3] == q2[3] );
}

// q = q^(-1)
void qInvert(double* q)
{
	double n = qNormSquaredd(q);
	q[0] = q[0]/n;
	q[1] = -q[1]/n;
	q[2] = -q[2]/n;
	q[3] = -q[3]/n;
}

// q2 = q1^(-1)
void qInvert(const double* q1, double* q2)
{

}

// q1 += q2
void qAddd(double* q1, const double* q2)
{

}

// q1 = q2 + q3
void qAddd(double* q1, const double* q2, const double* q3)
{

}

// q1 -= q2
void qSubd(double* q1, const double* q2)
{

}

// q1 = q2 - q3
void qSubd(double* q1, const double* q2, const double* q3)
{

}

// // binary quaternion multiplication operator
// inline CQuaternion operator*(const CQuaternion& q1, const CQuaternion& q2)
// {
// 	CQuaternion temp;
// 	temp.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
// 	temp.x = q1.x*q2.w + q1.w*q2.x - q1.z*q2.y + q1.y*q2.z;
// 	temp.y = q1.y*q2.w + q1.z*q2.x + q1.w*q2.y - q1.x*q2.z;
// 	temp.z = q1.z*q2.w - q1.y*q2.x + q1.x*q2.y + q1.w*q2.z;
// 	return temp;
// }
// q1 *= q2
void qMuld(double* q1, const double* q2)
{

}

// q1 = q2 * q3
void qMuld(double* q1, const double* q2, const double* q3)
{

}


// inline CQuaternion operator*(const CQuaternion& q, const VECTOR& v)
// {
// 	return q*Q(0,v.x,v.y,v.z);
// }
// q *= v
void qMulVectord(double* q, const double* v)
{

}

// q1 = q2 * v
void qMulVectord(double* q1, const double* q2, const double* v)
{

}

// q *= k
void qMulScalard(double* q, const double k)
{

}

// q1 = q2 * k
void qMulScalard(double* q1, const double* q2, const double k)
{

}

// q1 = k * q2
void qMulScalard(double* q1, const double k, const double* q2)
{

}

// // binary quaternion division operator
// inline CQuaternion operator/(const CQuaternion& q1, const CQuaternion& q2)
// {
// 	return (q1 * !q2);		// !q2 == quaternion inversion of q2
// }
// 
// q1 /= q2
void qDivd(double* q1, const double* q2)
{

}

// q1 = q2 / q3
void qDivd(double* q1, const double* q2, const double* q3)
{

}

// q /= v
void qDivVectord(double* q, const double* v)
{

}

// q1 = q2 / v
void qDivVectord(double* q1, const double* q2, const double* v)
{

}
// 
// // q1 = v / q2
// void qDivVectord(double* q1, const double* v, const double* q2)
// {
// 
// }

// q /= k
void qDivScalard(double* q, const double k)
{

}

// q1 = q2 / k
void qDivScalard(double* q1, const double* q2, const double k)
{

}

// q1 = k / q2
void qDivScalard(double* q1, const double k, const double* q2)
{

}

// // exponential map
// inline CQuaternion Expq(const CQuaternion& a)
// {
// 	float m = a.x*a.x + a.y*a.y + a.z*a.z;
// 
// 	if(m == 0)
// 		return Q(1, 0, 0, 0);
// 
// 	m = sqrt(m);
// 	CQuaternion temp;
// 	temp.w = cos(a.w*0.5);
// 	temp.x = a.x*sin(a.w*0.5)/m;
// 	temp.y = a.y*sin(a.w*0.5)/m;
// 	temp.z = a.z*sin(a.w*0.5)/m;
// 
// 	temp.Normalize();
// 
// 	return temp;
// }
// 
// // logarithm map
// inline CQuaternion Logq(const CQuaternion& q)
// {
// 	CQuaternion qq = q;
// 	qq.Normalize();
// 	CQuaternion temp;
// 	if( qq.w == 0 )
// 	{
// 		temp.w = 0;
// 		temp.x = 0.5*M_PI*qq.x;
// 		temp.y = 0.5*M_PI*qq.y;
// 		temp.z = 0.5*M_PI*qq.z;
// 	}
// 	else if( qq.w == 1 )
// 	{
// 		temp.w = 0.0;
// 		temp.x = 0.0;
// 		temp.y = 0.0;
// 		temp.z = 0.0;
// 	}
// 	else
// 	{
// 		float v = sqrt(q.x*q.x + q.y*q.y + q.z*q.z);
// 		temp.w = 2*atan2(v, qq.w);
// 		temp.x = qq.x/v;
// 		temp.y = qq.y/v;
// 		temp.z = qq.z/v;
// 	}
// 	return temp;
// }
// 
// inline CQuaternion ConvertFromEuler(float a, float b, float c, char* order)
// {
// 	float ang[3] = {a, b, c};
// 	CQuaternion q[3];
// 	CQuaternion axis;
// 	for(int i = 0; i < 3; i++)
// 	{
// 		axis.w = ang[i]*0.5;
// 		axis.x = 0; axis.y = 0; axis.z = 0;
// 		if(order[i] == 'z' || order[i] == 'Z')
// 			axis.z = 1;
// 		if(order[i] == 'y' || order[i] == 'Y')
// 			axis.y = 1;
// 		if(order[i] == 'x' || order[i] == 'X')
// 			axis.x = 1;
// 
// 		q[i] = Expq(axis);
// 	}
// 	return q[0]*q[1]*q[2];
// }
// 
// inline void ConvertToMatrix(CQuaternion q, float R[3][3])
// {
// 	R[0][0] = q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z;
// 	R[1][1] = q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z;
// 	R[2][2] = q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z;
// 
// 	R[0][1] = 2*q.x*q.y - 2*q.w*q.z;
// 	R[1][0] = 2*q.x*q.y + 2*q.w*q.z;
// 
// 	R[0][2] = 2*q.x*q.z + 2*q.w*q.y;
// 	R[2][0] = 2*q.x*q.z - 2*q.w*q.y;
// 
// 	R[1][2] = 2*q.y*q.z - 2*q.w*q.x;
// 	R[2][1] = 2*q.y*q.z + 2*q.w*q.x;
// }
