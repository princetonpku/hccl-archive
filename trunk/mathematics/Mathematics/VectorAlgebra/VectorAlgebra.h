#ifndef VECTORALGEBRA_H
#define VECTORALGEBRA_H

float Dot3f(const float* a, const float* b);					// c = a . b
void Cross3f(const float* a, const float* b, float* c);			// c = a x b
float NormSquared3f(const float* x);							// norm(x)^2
float Norm3f(const float* x);									// norm(x)
void Normalize3f(float* x);										// x /= norm(x)
void Assign3f(float* a, const float* b);						// a = b
void Assign3f(float* a, const float b);							// a = (b, b, b)
void AddVector3f(const float* a, const float* b, float* c);		// c = a + b
void AddVector3f(float* a, const float* b);						// a += b
void SubVector3f(const float* a, const float* b, float* c);		// c = a - b
void SubVector3f(float* a, const float* b);						// a -= b
void MultiplyScalar3f(float* x, const float& a);				// x *= a
void DivideByScalar3f(float* x, const float& a);				// x /= a

double Dot3d(const double* a, const double* b);					// c = a . b
void Cross3d(const double* a, const double* b, double* c);		// c = a x b
double NormSquared3d(const double* x);							// norm(x)^2
double Norm3d(const double* x);									// norm(x)
void Normalize3d(double* x);									// x /= norm(x)
void Assign3d(double* a, const double* b);						// a = b
void Assign3d(double* a, const double b);						// a = (b, b, b)
void AddVector3d(const double* a, const double* b, double* c);	// c = a + b
void AddVector3d(double* a, const double* b);					// a += b
void SubVector3d(const double* a, const double* b, double* c);	// c = a - b
void SubVector3d(double* a, const double* b);					// a -= b
void MultiplyScalar3d(double* x, const double& a);				// x *= a
void DivideByScalar3d(double* x, const double& a);				// x /= a


// 2D version
float NormSquared2f(const float* x);							// norm(x)^2
float Norm2f(const float* x);									// norm(x)
void Normalize2f(float* x);										// x /= norm(x)
float Dot2f(const float* a, const float* b);					// c = a . b
void AddVector2f(const float* a, const float* b, float* c);		// c = a + b
void AddVector2f(float* a, const float* b);						// a += b
void SubVector2f(double* a, const double* b);					// a -= b
void DivideByScalar2f(float* x, const float& a);				// x /= a

double NormSquared2d(const double* x);							// norm(x)^2
double Norm2d(const double* x);									// norm(x)
void Normalize2d(double* x);									// x /= norm(x)
double Dot2d(const double* a, const double*b);					// c = a . b
void AddVector2d(const double* a, const double* b, double* c);	// c = a + b
void AddVector2d(double* a, const double* b);					// a += b
void SubVector2d(const double* a, const double* b, double* c);  // c = a - b
void SubVector2d(double* a, const double* b);					// a -= b
void DivideByScalar2d(double* x, const double& a);				// x /= a


#endif // VECTORALGEBRA_H