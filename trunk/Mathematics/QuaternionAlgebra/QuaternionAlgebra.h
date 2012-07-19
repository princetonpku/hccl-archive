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

#endif // QUATERNIONALGEBRA_H