#ifndef VECTORALGEBRA_H
#define VECTORALGEBRA_H

// 3D version
float vDot3f(const float* a, const float* b);				// c = a . b
float* vCross3f(const float* a, const float* b, float* c);	// c = a x b
float vNormSquared3f(const float* x);						// norm(x)^2
float vNorm3f(const float* x);								// norm(x)
float* vNormalize3f(float* x);								// x /= norm(x)
float* vCopy3f(float* a, const float* b);						// a = b
float* vAssign3f(float* a, const float b);					// a = (b, b, b)
float* vAdd3f(const float* a, const float* b, float* c);		// c = a + b
float* vAdd3f(float* a, const float* b);						// a += b
float* vSub3f(const float* a, const float* b, float* c);		// c = a - b
float* vSub3f(float* a, const float* b);						// a -= b
float* vMul3f(double* a, const double* b);					// a *= b (element-wise multiplication)
float* vMul3f(const double* a, const double* b, double* c);	// c = a * b (element-wise multiplication)
float* vMulScalar3f(float* x, const float& a);				// x *= a
float* vDivScalar3f(float* x, const float& a);				// x /= a

double vDot3d(const double* a, const double* b);			// c = a . b
double* vCross3d(const double* a, const double* b, double* c);	// c = a x b
double vNormSquared3d(const double* x);						// norm(x)^2
double vNorm3d(const double* x);							// norm(x)
double* vNormalize3d(double* x);								// x /= norm(x)
double* vCopy3d(double* a, const double* b);					// a = b
double* vAssign3d(double* a, const double b);					// a = (b, b, b)
double* vAdd3d(const double* a, const double* b, double* c);	// c = a + b
double* vAdd3d(double* a, const double* b);					// a += b
double* vSub3d(const double* a, const double* b, double* c);	// c = a - b
double* vSub3d(double* a, const double* b);					// a -= b
double* vMul3d(double* a, const double* b);					// a *= b (element-wise multiplication)
double* vMul3d(const double* a, const double* b, double* c);	// c = a * b (element-wise multiplication)
double* vMulScalar3d(double* x, const double& a);				// x *= a
double* vDivScalar3d(double* x, const double& a);				// x /= a


// 2D version
float vNormSquared2f(const float* x);						// norm(x)^2
float vNorm2f(const float* x);								// norm(x)
void vNormalize2f(float* x);								// x /= norm(x)
float vDot2f(const float* a, const float* b);				// c = a . b
void vAdd2f(const float* a, const float* b, float* c);		// c = a + b
void vAdd2f(float* a, const float* b);						// a += b
void vSub2f(double* a, const double* b);					// a -= b
void vDivScalar2f(float* x, const float& a);				// x /= a

double vNormSquared2d(const double* x);						// norm(x)^2
double vNorm2d(const double* x);							// norm(x)
void vNormalize2d(double* x);								// x /= norm(x)
double vDot2d(const double* a, const double*b);				// c = a . b
void vAdd2d(const double* a, const double* b, double* c);	// c = a + b
void vAdd2d(double* a, const double* b);					// a += b
void vSub2d(double* a, const double* b);					// a -= b
void vDivScalar2d(double* x, const double& a);				// x /= a

#endif // VECTORALGEBRA_H