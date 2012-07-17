#ifndef VECTORALGEBRA_H
#define VECTORALGEBRA_H

// TODOs
// 2d version of the followings
// vector-vector multiplication
// comments

float Dot3f(const float* a, const float* b);
void Cross3f(const float* a, const float* b, float* c);
float NormSquared3f(const float* x);
float Norm3f(const float* x);
void Assign3f(float* a, const float* b);
void Assign3f(float* a, const float b);
void AddVector3f(const float* a, const float* b, float* c);
void AddVector3f(float* a, const float* b);
void SubVector3f(const float* a, const float* b, float* c);
void SubVector3f(float* a, const float* b);
void MultiplyScalar3f(float* x, const float& a);
void DivideByScalar3f(float* x, const float& a);

double Dot3d(const double* a, const double* b);
void Cross3d(const double* a, const double* b, double* c);
double NormSquared3d(const double* x);
double Norm3d(const double* x);
void Assign3d(double* a, const double* b);
void Assign3d(double* a, const double b);
void AddVector3d(const double* a, const double* b, double* c);
void AddVector3d(double* a, const double* b);
void SubVector3d(const double* a, const double* b, double* c);
void SubVector3d(double* a, const double* b);
void MultiplyScalar3d(double* x, const double& a);
void DivideByScalar3d(double* x, const double& a);

#endif // VECTORALGEBRA_H