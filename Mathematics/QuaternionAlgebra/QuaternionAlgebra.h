#ifndef QUATERNIONALGEBRA_H
#define QUATERNIONALGEBRA_H

void qIdentityd(double* q);
void qCopyd(double* dst, const double* src);
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

// // q *= v
// void qMulVectord(double* q, const double* v);
// // q1 = q2 * v
// void qMulVectord(double* q1, const double* q2, const double* v);

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

// // q /= v
// void qDivVectord(double* q, const double* v);
// 
// // q1 = q2 / v
// void qDivVectord(double* q1, const double* q2, const double* v);
// 
// // q1 = v / q2
// void qDivVectord(double* q1, const double* v, const double* q2);


// q /= k
void qDivScalard(double* q, const double k);

// q1 = q2 / k
void qDivScalard(double* q1, const double* q2, const double k);

// q1 = k / q2
void qDivScalard(double* q1, const double k, const double* q2);

// convert axis-angle representation to quaternion (Map from so(3) --> SO(3))
void qExpd(const double* a, double* q);

// convert quaternion to axis-angle representation (Map from SO(3) --> so(3))
void qLogd(const double* q, double* a);

// Convert rotation matrix to a quaternion form.
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
void qFromMatrixd(double* q, const double* R);

// Convert axis-angle rotation to a quaternion form.
// Angle is in radian.
void qFromAxisAngled(double* q, const double angle, const double* axis);

void qFromEuler(double* q, const double a, const double b, const double c, const char* order);

// Convert quaternion to a rotation matrix
// R is 3x3 matrix, in stacked-column form. i.e. R_(i,j) = R[3*j + i]
void qToMatrix(const double* q, double* R);

#endif // QUATERNIONALGEBRA_H