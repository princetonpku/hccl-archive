#ifndef QUATERNIONALGEBRA_H
#define QUATERNIONALGEBRA_H

void qIdentityd(double* q);
void qCopyd(double* dst, const double* src);

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
void qFromAxisAngled(double* q, const double angle, const double* axis);

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
void qFromMatrixd(double* q, const double* R);

// |q|^2
double qNormSquaredd(const double* q);

// |q|
double qNormd(const double* q);

// q = q / |q|
void qNormalize(double* q);

// q2 = q1 / |q1|
void qNormalize(const double* q1, double* q2);

bool qIsEquald(const double* q1, const double* q2);

// q = q^(-1)
void qInvert(double* q);
// q2 = q1^(-1)
void qInvert(const double* q1, double* q2);

// q1 += q2
void qAddd(double* q1, const double* q2);

// q1 = q2 + q3
void qAddd(double* q1, const double* q2, const double* q3);

// q1 -= q2
void qSubd(double* q1, const double* q2);

// q1 = q2 - q3
void qSubd(double* q1, const double* q2, const double* q3);

// q1 *= q2
void qMuld(double* q1, const double* q2);

// q1 = q2 * q3
void qMuld(double* q1, const double* q2, const double* q3);

// q *= v
void qMulVectord(double* q, const double* v);

// q1 = q2 * v
void qMulVectord(double* q1, const double* q2, const double* v);

// q1 = v * q2
void qMulVectord(double* q1, const double* v, const double* q2);

// q *= k
void qMulScalard(double* q, const double k);

// q1 = q2 * k
void qMulScalard(double* q1, const double* q2, const double k);
// q1 = k * q2
void qMulScalard(double* q1, const double k, const double* q2);

// q1 /= q2
void qDivd(double* q1, const double* q2);

// q1 = q2 / q3
void qDivd(double* q1, const double* q2, const double* q3);

// q /= v
void qDivVectord(double* q, const double* v);
// q1 = q2 / v
void qDivVectord(double* q1, const double* q2, const double* v);

// q1 = v / q2
void qDivVectord(double* q1, const double* v, const double* q2);

// q /= k
void qDivScalard(double* q, const double k);

// q1 = q2 / k
void qDivScalard(double* q1, const double* q2, const double k);

// q1 = k / q2
void qDivScalard(double* q1, const double k, const double* q2);

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


#endif // QUATERNIONALGEBRA_H