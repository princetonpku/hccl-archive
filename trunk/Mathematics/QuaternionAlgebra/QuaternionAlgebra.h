#ifndef QUATERNIONALGEBRA_H
#define QUATERNIONALGEBRA_H

#ifndef _MATH_DEFINES_DEFINED
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD M_PI/180.0
#endif
#ifndef RAD2DEG
#define RAD2DEG 180.0/M_PI
#endif

// a == b
bool qIsEquald(const double* a, const double* b);
double* qNegated(double* q);
double* qNegated(double* q, const double* q0);
double* qIdentityd(double* q);
double* qCopyd(double* dst, const double* src);
// |q|^2
double qNormSquaredd(const double* q);
// |q|
double qNormd(const double* q);
// q = q / |q|
double* qNormalized(double* q);
// q2 = q1 / |q1|
double* qNormalized(const double* q1, double* q2);
bool qIsEquald(const double* q1, const double* q2);
// q = q^(-1)
double* qInvertd(double* q);
// q2 = q1^(-1)
double* qInvertd(const double* q1, double* q2);
// q1 += q2
double* qAddd(double* q1, const double* q2);
// q1 = q2 + q3
double* qAddd(double* q1, const double* q2, const double* q3);
// q1 -= q2
double* qSubd(double* q1, const double* q2);
// q1 = q2 - q3
double* qSubd(double* q1, const double* q2, const double* q3);
// q1 *= q2
double* qMuld(double* q1, const double* q2);
// q1 = q2 * q3
double* qMuld(double* q1, const double* q2, const double* q3);

// // q *= v
// void qMulVectord(double* q, const double* v);
// // q1 = q2 * v
// void qMulVectord(double* q1, const double* q2, const double* v);

// q *= k
double* qMulScalard(double* q, const double k);

// q1 = q2 * k
double* qMulScalard(double* q1, const double* q2, const double k);

// q1 = k * q2
double* qMulScalard(double* q1, const double k, const double* q2);
// q1 /= q2
double* qDivd(double* q1, const double* q2);
// q1 = q2 / q3
double* qDivd(double* q1, const double* q2, const double* q3);

// // q /= v
// void qDivVectord(double* q, const double* v);
// 
// // q1 = q2 / v
// void qDivVectord(double* q1, const double* q2, const double* v);
// 
// // q1 = v / q2
// void qDivVectord(double* q1, const double* v, const double* q2);


// q /= k
double* qDivScalard(double* q, const double k);

// q1 = q2 / k
double* qDivScalard(double* q1, const double* q2, const double k);

// q1 = k / q2
double* qDivScalard(double* q1, const double k, const double* q2);

// convert axis-angle representation to quaternion (Map from so(3) --> SO(3))
double* qExpd(const double* a, double* q);

// convert quaternion to axis-angle representation (Map from SO(3) --> so(3))
double* qLogd(const double* q, double* a);

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
double* qFromMatrixd(double* q, const double* R);

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
double* qFromAxisAngled(double* q, const double angle, const double* axis);

double* qFromEulerd(double* q, const double a, const double b, const double c, const char* order);

// Convert quaternion to a rotation matrix
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
double* qToMatrixd(const double* q, double* R);


//////////////////////////////////////////////////////////////////////////
// float
//////////////////////////////////////////////////////////////////////////


// a == b
bool qIsEqualf(const float* a, const float* b);
float* qNegatef(float* q);
float* qNegatef(float* q, const float* q0);
float* qIdentityf(float* q);
float* qCopyf(float* dst, const float* src);
// |q|^2
float qNormSquaredf(const float* q);
// |q|
float qNormf(const float* q);
// q = q / |q|
float* qNormalizef(float* q);
// q2 = q1 / |q1|
float* qNormalizef(const float* q1, float* q2);
bool qIsEqualf(const float* q1, const float* q2);
// q = q^(-1)
float* qInvertf(float* q);
// q2 = q1^(-1)
float* qInvertf(const float* q1, float* q2);
// q1 += q2
float* qAddf(float* q1, const float* q2);
// q1 = q2 + q3
float* qAddf(float* q1, const float* q2, const float* q3);
// q1 -= q2
float* qSubf(float* q1, const float* q2);
// q1 = q2 - q3
float* qSubf(float* q1, const float* q2, const float* q3);
// q1 *= q2
float* qMulf(float* q1, const float* q2);
// q1 = q2 * q3
float* qMulf(float* q1, const float* q2, const float* q3);

// // q *= v
// void qMulVectorf(float* q, const float* v);
// // q1 = q2 * v
// void qMulVectorf(float* q1, const float* q2, const float* v);

// q *= k
float* qMulScalarf(float* q, const float k);

// q1 = q2 * k
float* qMulScalarf(float* q1, const float* q2, const float k);

// q1 = k * q2
float* qMulScalarf(float* q1, const float k, const float* q2);
// q1 /= q2
float* qDivf(float* q1, const float* q2);
// q1 = q2 / q3
float* qDivf(float* q1, const float* q2, const float* q3);

// // q /= v
// void qDivVectorf(float* q, const float* v);
// 
// // q1 = q2 / v
// void qDivVectorf(float* q1, const float* q2, const float* v);
// 
// // q1 = v / q2
// void qDivVectorf(float* q1, const float* v, const float* q2);


// q /= k
float* qDivScalarf(float* q, const float k);

// q1 = q2 / k
float* qDivScalarf(float* q1, const float* q2, const float k);

// q1 = k / q2
float* qDivScalarf(float* q1, const float k, const float* q2);

// convert axis-angle representation to quaternion (Map from so(3) --> SO(3))
float* qExpf(const float* a, float* q);

// convert quaternion to axis-angle representation (Map from SO(3) --> so(3))
float* qLogf(const float* q, float* a);

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
float* qFromMatrixf(float* q, const float* R);

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
float* qFromAxisAnglef(float* q, const float angle, const float* axis);

float* qFromEulerf(float* q, const float a, const float b, const float c, const char* order);

// Convert quaternion to a rotation matrix
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
float* qToMatrixf(const float* q, float* R);






#endif // QUATERNIONALGEBRA_H