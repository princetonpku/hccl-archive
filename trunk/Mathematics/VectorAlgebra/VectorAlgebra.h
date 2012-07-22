#ifndef VECTORALGEBRA_H
#define VECTORALGEBRA_H

// 3D version
bool vIsEqual3f(const float* a, const float* b);					// a == b
float vDot3f(const float* a, const float* b);						// c = a . b
float* vCross3f(const float* a, const float* b, float* c);			// c = a x b
float vNormSquared3f(const float* x);								// norm(x)^2
float vNorm3f(const float* x);										// norm(x)
float* vNormalize3f(float* x);										// x /= norm(x)
float* vCopy3f(float* a, const float* b);							// a = b
float* vAssign3f(float* a, const float b);							// a = (b, b, b)
float* vNegate3f(float* x);											// x = -x;
float* vAdd3f(const float* a, const float* b, float* c);			// c = a + b
float* vAdd3f(float* a, const float* b);							// a += b
float* vSub3f(const float* a, const float* b, float* c);			// c = a - b
float* vSub3f(float* a, const float* b);							// a -= b
float* vMul3f(float* a, const float* b);							// a *= b (element-wise multiplication)
float* vMul3f(const float* a, const float* b, float* c);			// c = a * b (element-wise multiplication)
float* vDiv3f(float* a, const float* b);							// a /= b (element-wise division)
float* vDiv3f(const float* a, const float* b, float* c);			// c = a / b (element-wise division)
float* vMulScalar3f(float* x, const float& a);						// x *= a
float* vMulScalar3f(float* x, const float* a, const float& k);		// x = a*k
float* vDivScalar3f(float* x, const float& a);						// x /= a
float* vDivScalar3f(float* x, const float* a, const float& k);		// x = a/k


bool vIsEqual3d(const double* a, const double* b);					// a == b
double vDot3d(const double* a, const double* b);					// c = a . b
double* vCross3d(const double* a, const double* b, double* c);		// c = a x b
double vNormSquared3d(const double* x);								// norm(x)^2
double vNorm3d(const double* x);									// norm(x)
double* vNormalize3d(double* x);									// x /= norm(x)
double* vCopy3d(double* a, const double* b);						// a = b
double* vAssign3d(double* a, const double b);						// a = (b, b, b)
double* vNegate3d(double* x);										// x = -x;
double* vAdd3d(const double* a, const double* b, double* c);		// c = a + b
double* vAdd3d(double* a, const double* b);							// a += b
double* vSub3d(const double* a, const double* b, double* c);		// c = a - b
double* vSub3d(double* a, const double* b);							// a -= b
double* vMul3d(double* a, const double* b);							// a *= b (element-wise multiplication)
double* vMul3d(const double* a, const double* b, double* c);		// c = a * b (element-wise multiplication)
double* vMulScalar3d(double* x, const double& a);					// x *= a
double* vMulScalar3d(double* x, const double* a, const double& k);	// x = a*k
double* vDiv3d(double* a, const double* b);							// a /= b (element-wise division)
double* vDiv3d(const double* a, const double* b, double* c);		// c = a / b (element-wise division)
double* vDivScalar3d(double* x, const double& a);					// x /= a
double* vDivScalar3d(double* x, const double* a, const double& k);	// x = a/k


// 2D version
bool vIsEqual2f(const float* a, const float* b);					// a == b
float vDot2f(const float* a, const float* b);						// c = a . b
float vCross2f(const float* a, const float* b);						// c = a x b
float vNormSquared2f(const float* x);								// norm(x)^2
float vNorm2f(const float* x);										// norm(x)
float* vNormalize2f(float* x);										// x /= norm(x)
float* vCopy2f(float* a, const float* b);							// a = b
float* vAssign2f(float* a, const float b);							// a = (b, b, b)
float* vNegate2f(float* x);											// x = -x
float* vAdd2f(const float* a, const float* b, float* c);			// c = a + b
float* vAdd2f(float* a, const float* b);							// a += b
float* vSub2f(const float* a, const float* b, float* c);			// c = a - b
float* vSub2f(float* a, const float* b);							// a -= b
float* vMul2f(float* a, const float* b);							// a *= b (element-wise multiplication)
float* vMul2f(const float* a, const float* b, float* c);			// c = a * b (element-wise multiplication)
float* vDiv2f(float* a, const float* b);							// a /= b (element-wise division)
float* vDiv2f(const float* a, const float* b, float* c);			// c = a / b (element-wise division)
float* vMulScalar2f(float* x, const float& a);						// x *= a
float* vMulScalar2f(float* x, const float* a, const float& k);		// x = a*k
float* vDivScalar2f(float* x, const float& a);						// x /= a
float* vDivScalar2f(float* x, const float* a, const float& k);		// x = a/k



bool vIsEqual2d(const double* a, const double* b);					// a == b
double vNormSquared2d(const double* x);								// norm(x)^2
double vNorm2d(const double* x);									// norm(x)
double* vNormalize2d(double* x);									// x /= norm(x)
double vDot2d(const double* a, const double*b);						// c = a . b
double vCross2d(const double* a, const double* b);					// c = a x b
double* vCopy2d(double* a, const double* b);						// a = b
double* vAssign2d(double* a, const double b);						// a = (b, b, b)
double* vNegate2d(double* x);										// x = -x
double* vAdd2d(const double* a, const double* b, double* c);		// c = a + b
double* vAdd2d(double* a, const double* b);							// a += b
double* vSub2d(double* a, const double* b);							// a -= b
double* vSub2d(const double* a, const double* b, double* c);		// c = a - b
double* vMul2d(double* a, const double* b);							// a *= b (element-wise multiplication)
double* vMul2d(const double* a, const double* b, double* c);		// c = a * b (element-wise multiplication)
double* vDiv2d(double* a, const double* b);							// a /= b (element-wise division)
double* vDiv2d(const double* a, const double* b, double* c);		// c = a / b (element-wise division)
double* vMulScalar2d(double* x, const double& a);					// x *= a
double* vMulScalar2d(double* x, const double* a, const double& k);	// x = a*k
double* vDivScalar2d(double* x, const double& a);					// x /= a
double* vDivScalar2d(double* x, const double* a, const double& k);	// x = a/k

#endif // VECTORALGEBRA_H