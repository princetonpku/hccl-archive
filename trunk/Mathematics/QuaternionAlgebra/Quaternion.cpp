#include "Quaternion.h"
#include <memory>

Quaterniond::Quaterniond(void)													// Identity quaternion (1, 0, 0, 0)
{
	val[0] = 1;
	val[1] = val[2] = val[3] = 0;
}

Quaterniond::Quaterniond(double w, double x, double y, double z)				// (w, x, y, z)
{
	val[0] = w;
	val[1] = x;
	val[2] = y;
	val[3] = z;
}

Quaterniond::Quaterniond(double* wxyz)											// (wxyz[0], wxyz[1], wxyz[2], wxyz[3])
{
	memcpy(val, wxyz, sizeof(double)*4);
}

Quaterniond::Quaterniond(const Quaterniond& q)									// copy constructor
{
	memcpy(this->val, q.val, sizeof(double)*4);
}

// TODO: axis-angle constructor
// TODO: rotation matrix constructor
// TODO: Euler angle constructor

Quaterniond::~Quaterniond(void)
{
}

// Conversion
Quaterniond Quaterniond::FromAxisAngle(const double rad, const double axis_x, const double axis_y, const double axis_z)
{
	Quaterniond q;
	double axis[3] = {axis_x, axis_y, axis_z};
	qFromAxisAngled(q.val, rad, axis);
	return q;
}

Quaterniond Quaterniond::FromMatrix(const double* R)
{
	Quaterniond q;
	qFromMatrixd(q.val, R);
	return q;
}

Quaterniond Quaterniond::FromMatrix(const double R[3][3])
{
	Quaterniond q;
	double Rtemp[9] = {R[0][0], R[1][0], R[2][0], R[0][1], R[1][1], R[2][1], R[0][2], R[1][2], R[2][2]};
	qFromMatrixd(q.val, Rtemp);
	return q;
}

Quaterniond Quaterniond::FromEulerAngle(const double a, const double b, const double c, const char* order)
{
	Quaterniond q;
	qFromEulerd(q.val, a, b, c, order);
	return q;
}

Quaterniond Log(const Quaterniond& q)
{
	Quaterniond a;
	qLogd(q.val, a.val);
	return a;
}

Quaterniond Quaterniond::Log(void)
{
	Quaterniond a;
	qLogd(this->val, a.val);
	return a;
}

Quaterniond Exp(const Quaterniond& a)
{
	Quaterniond q;
	qExpd(a.val, q.val);
	return q;
}

Quaterniond Quaterniond::Exp(void)
{
	Quaterniond q;
	qExpd(this->val, q.val);
	return q;
}

// Methods (Algebra)
double Quaterniond::NormSquared(const Quaterniond& q)					// |q|^2
{
	return qNormSquaredd(q.val);
}

double Quaterniond::NormSquared()												// |this|^2
{
	return qNormSquaredd(this->val);
}

double Quaterniond::Norm(const Quaterniond& q)							// |q|
{
	return qNormd(q.val);
}

double Quaterniond::Norm()														// |this|
{
	return qNormd(this->val);
}

Quaterniond Quaterniond::Normalize(Quaterniond& q)						// q / |q|
{
	qNormalized(q.val);
	return q;
}

Quaterniond Quaterniond::Normalize(void)										// this /= |this|
{
	qNormalized(this->val);
	return *this;
}

Quaterniond Quaterniond::Add(const Quaterniond& a, const Quaterniond& b)	// a + b
{
	Quaterniond ret;
	qAddd(ret.val, a.val, b.val);
	return ret;
}

Quaterniond Quaterniond::Add(const Quaterniond& q)								// this += q
{
	qAddd(this->val, q.val);
	return (*this);
}

Quaterniond Quaterniond::Sub(const Quaterniond& a, const Quaterniond& b)	// a - b
{
	Quaterniond ret;
	qSubd(ret.val, a.val, b.val);
	return ret;
}

Quaterniond Quaterniond::Sub(const Quaterniond& q)								// this -= q
{
	qSubd(this->val, q.val);
	return (*this);
}

Quaterniond Quaterniond::Mul(const Quaterniond& a, const Quaterniond& b)	// a * b
{
	Quaterniond ret;
	qMuld(ret.val, a.val, b.val);
	return ret;
}

Quaterniond Quaterniond::Mul(const Quaterniond& q)								// this *= q
{
	qMuld(this->val, q.val);
	return (*this);
}

Quaterniond Quaterniond::Mul(const Quaterniond& a, const double& k)		// a * k
{
	Quaterniond ret;
	qMulScalard(ret.val, a.val, k);
	return ret;
}

Quaterniond Quaterniond::Mul(const double& k)									// this *= k
{
	qMulScalard(this->val, k);
	return (*this);
}

Quaterniond Quaterniond::Div(const Quaterniond& a, const Quaterniond& b)	// a / b
{
	Quaterniond ret;
	qDivd(ret.val, a.val, b.val);
	return ret;
}

Quaterniond Quaterniond::Div(const Quaterniond& q)								// this /= q
{
	qDivd(this->val, q.val);
	return (*this);
}

Quaterniond Quaterniond::Div(const Quaterniond& a, const double& k)		// a / k
{
	Quaterniond ret;
	qDivScalard(ret.val, a.val, k);
	return ret;
}

Quaterniond Quaterniond::Div(const double& k)									// this /= k
{
	qDivScalard(this->val, k);
	return (*this);
}

// Operators
Quaterniond Quaterniond::operator=(const Quaterniond& v)						// assign operator
{
	qCopyd(this->val, v.val);
	return *this;
}

bool Quaterniond::operator==(const Quaterniond& v)								// compare operator
{
	return qIsEquald(this->val, v.val);
}

bool Quaterniond::operator!=(const Quaterniond& v)								// negative compare operator
{
	return !qIsEquald(this->val, v.val);
}

Quaterniond Quaterniond::operator+=(const Quaterniond& v)						// unary addition operator
{
	qAddd(this->val, v.val);
	return *this;
}

Quaterniond Quaterniond::operator-=(const Quaterniond& v)						// unary subtraction operator
{
	qSubd(this->val, v.val);
	return *this;
}

Quaterniond Quaterniond::operator*=(const Quaterniond& v)						// unary multiplication operator (element-wise)
{
	qMuld(this->val, v.val);
	return *this;
}

Quaterniond Quaterniond::operator*=(const double& k)							// unary scalar multiplication operator
{
	qMulScalard(this->val, k);
	return *this;
}

Quaterniond Quaterniond::operator/=(const Quaterniond& v)						// unary division operator (element-wise)
{
	qDivd(this->val, v.val);
	return *this;
}

Quaterniond Quaterniond::operator/=(const double& k)							// unary scalar division operator
{
	qDivScalard(this->val, k);
	return *this;
}

Quaterniond Quaterniond::operator-()											// unary negation operator
{
	Quaterniond temp(*this);
	qNegated(temp.val);
	return temp;
}

Quaterniond operator+(const Quaterniond& a, const Quaterniond& b)		// binary addition operator
{
	Quaterniond qtemp;
	qAddd(qtemp.val, a.val, b.val);
	return qtemp;
}

Quaterniond operator-(const Quaterniond& a, const Quaterniond& b)		// binary subtraction operator
{
	Quaterniond qtemp;
	qSubd(qtemp.val, a.val, b.val);
	return qtemp;
}

Quaterniond operator*(const Quaterniond& a, const Quaterniond& b)		// binary multiplication operator (element-wise)
{
	Quaterniond qtemp;
	qMuld(qtemp.val, a.val, b.val);
	return qtemp;
}

Quaterniond operator*(const Quaterniond& q, const double& k)			// binary scalar multiplication operator
{
	Quaterniond qtemp(q);
	return (qtemp*=k);
}

Quaterniond operator*(const double& k, const Quaterniond& q)			// binary scalar multiplication operator
{
	Quaterniond qtemp(q);
	return (qtemp*=k);
}

Quaterniond operator/(const Quaterniond& a, const Quaterniond& b)		// binary division operator (element-wise)
{
	Quaterniond qtemp(a);
	return (qtemp*=!b);
}

Quaterniond operator/(const Quaterniond& q, const double& k)			// binary scalar division operator
{
	Quaterniond qtemp(q);
	return (qtemp/=k);
}

Quaterniond operator/(const double& k, const Quaterniond& q)			// binary scalar division operator
{
	Quaterniond qtemp(!q);
	qMulScalard(qtemp.val, k);
	return qtemp;
}

Quaterniond operator!(const Quaterniond& q)							// unary inversion operator
{
	Quaterniond qtemp;
	qInvertd(q.val, qtemp.val);
	return qtemp;
}

// Accessors
double& Quaterniond::operator[](int i){ return val[i]; }
double* Quaterniond::GetData(){ return val; }
double Quaterniond::W(){ return val[0]; }
double Quaterniond::X(){ return val[1]; }
double Quaterniond::Y(){ return val[2]; }
double Quaterniond::Z(){ return val[3]; }

void Quaterniond::SetW(double nw) { val[0] = nw; }
void Quaterniond::SetX(double nx) { val[1] = nx; }
void Quaterniond::SetY(double ny) { val[2] = ny; }
void Quaterniond::SetZ(double nz) { val[3] = nz; }


//////////////////////////////////////////////////////////////////////////
// float
//////////////////////////////////////////////////////////////////////////



Quaternionf::Quaternionf(void)													// Identity quaternion (1, 0, 0, 0)
{
	val[0] = 1;
	val[1] = val[2] = val[3] = 0;
}

Quaternionf::Quaternionf(float w, float x, float y, float z)				// (w, x, y, z)
{
	val[0] = w;
	val[1] = x;
	val[2] = y;
	val[3] = z;
}

Quaternionf::Quaternionf(float* wxyz)											// (wxyz[0], wxyz[1], wxyz[2], wxyz[3])
{
	memcpy(val, wxyz, sizeof(float)*4);
}

Quaternionf::Quaternionf(const Quaternionf& q)									// copy constructor
{
	memcpy(this->val, q.val, sizeof(float)*4);
}

// TODO: axis-angle constructor
// TODO: rotation matrix constructor
// TODO: Euler angle constructor

Quaternionf::~Quaternionf(void)
{
}

// Conversion
Quaternionf Quaternionf::FromAxisAngle(const float rad, const float axis_x, const float axis_y, const float axis_z)
{
	Quaternionf q;
	float axis[3] = {axis_x, axis_y, axis_z};
	qFromAxisAnglef(q.val, rad, axis);
	return q;
}

Quaternionf Quaternionf::FromMatrix(const float* R)
{
	Quaternionf q;
	qFromMatrixf(q.val, R);
	return q;
}

Quaternionf Quaternionf::FromMatrix(const float R[3][3])
{
	Quaternionf q;
	float Rtemp[9] = {R[0][0], R[1][0], R[2][0], R[0][1], R[1][1], R[2][1], R[0][2], R[1][2], R[2][2]};
	qFromMatrixf(q.val, Rtemp);
	return q;
}

Quaternionf Quaternionf::FromEulerAngle(const float a, const float b, const float c, const char* order)
{
	Quaternionf q;
	qFromEulerf(q.val, a, b, c, order);
	return q;
}

Quaternionf Log(const Quaternionf& q)
{
	Quaternionf a;
	qLogf(q.val, a.val);
	return a;
}

Quaternionf Quaternionf::Log(void)
{
	Quaternionf a;
	qLogf(this->val, a.val);
	return a;
}

Quaternionf Exp(const Quaternionf& a)
{
	Quaternionf q;
	qExpf(a.val, q.val);
	return q;
}

Quaternionf Quaternionf::Exp(void)
{
	Quaternionf q;
	qExpf(this->val, q.val);
	return q;
}

// Methods (Algebra)
float Quaternionf::NormSquared(const Quaternionf& q)					// |q|^2
{
	return qNormSquaredf(q.val);
}

float Quaternionf::NormSquared()												// |this|^2
{
	return qNormSquaredf(this->val);
}

float Quaternionf::Norm(const Quaternionf& q)							// |q|
{
	return qNormf(q.val);
}

float Quaternionf::Norm()														// |this|
{
	return qNormf(this->val);
}

Quaternionf Quaternionf::Normalize(Quaternionf& q)						// q / |q|
{
	qNormalizef(q.val);
	return q;
}

Quaternionf Quaternionf::Normalize(void)										// this /= |this|
{
	qNormalizef(this->val);
	return *this;
}

Quaternionf Quaternionf::Add(const Quaternionf& a, const Quaternionf& b)	// a + b
{
	Quaternionf ret;
	qAddf(ret.val, a.val, b.val);
	return ret;
}

Quaternionf Quaternionf::Add(const Quaternionf& q)								// this += q
{
	qAddf(this->val, q.val);
	return (*this);
}

Quaternionf Quaternionf::Sub(const Quaternionf& a, const Quaternionf& b)	// a - b
{
	Quaternionf ret;
	qSubf(ret.val, a.val, b.val);
	return ret;
}

Quaternionf Quaternionf::Sub(const Quaternionf& q)								// this -= q
{
	qSubf(this->val, q.val);
	return (*this);
}

Quaternionf Quaternionf::Mul(const Quaternionf& a, const Quaternionf& b)	// a * b
{
	Quaternionf ret;
	qMulf(ret.val, a.val, b.val);
	return ret;
}

Quaternionf Quaternionf::Mul(const Quaternionf& q)								// this *= q
{
	qMulf(this->val, q.val);
	return (*this);
}

Quaternionf Quaternionf::Mul(const Quaternionf& a, const float& k)		// a * k
{
	Quaternionf ret;
	qMulScalarf(ret.val, a.val, k);
	return ret;
}

Quaternionf Quaternionf::Mul(const float& k)									// this *= k
{
	qMulScalarf(this->val, k);
	return (*this);
}

Quaternionf Quaternionf::Div(const Quaternionf& a, const Quaternionf& b)	// a / b
{
	Quaternionf ret;
	qDivf(ret.val, a.val, b.val);
	return ret;
}

Quaternionf Quaternionf::Div(const Quaternionf& q)								// this /= q
{
	qDivf(this->val, q.val);
	return (*this);
}

Quaternionf Quaternionf::Div(const Quaternionf& a, const float& k)		// a / k
{
	Quaternionf ret;
	qDivScalarf(ret.val, a.val, k);
	return ret;
}

Quaternionf Quaternionf::Div(const float& k)									// this /= k
{
	qDivScalarf(this->val, k);
	return (*this);
}

// Operators
Quaternionf Quaternionf::operator=(const Quaternionf& v)						// assign operator
{
	qCopyf(this->val, v.val);
	return *this;
}

bool Quaternionf::operator==(const Quaternionf& v)								// compare operator
{
	return qIsEqualf(this->val, v.val);
}

bool Quaternionf::operator!=(const Quaternionf& v)								// negative compare operator
{
	return !qIsEqualf(this->val, v.val);
}

Quaternionf Quaternionf::operator+=(const Quaternionf& v)						// unary addition operator
{
	qAddf(this->val, v.val);
	return *this;
}

Quaternionf Quaternionf::operator-=(const Quaternionf& v)						// unary subtraction operator
{
	qSubf(this->val, v.val);
	return *this;
}

Quaternionf Quaternionf::operator*=(const Quaternionf& v)						// unary multiplication operator (element-wise)
{
	qMulf(this->val, v.val);
	return *this;
}

Quaternionf Quaternionf::operator*=(const float& k)							// unary scalar multiplication operator
{
	qMulScalarf(this->val, k);
	return *this;
}

Quaternionf Quaternionf::operator/=(const Quaternionf& v)						// unary division operator (element-wise)
{
	qDivf(this->val, v.val);
	return *this;
}

Quaternionf Quaternionf::operator/=(const float& k)							// unary scalar division operator
{
	qDivScalarf(this->val, k);
	return *this;
}

Quaternionf Quaternionf::operator-()											// unary negation operator
{
	Quaternionf temp(*this);
	qNegatef(temp.val);
	return temp;
}

Quaternionf operator+(const Quaternionf& a, const Quaternionf& b)		// binary addition operator
{
	Quaternionf qtemp;
	qAddf(qtemp.val, a.val, b.val);
	return qtemp;
}

Quaternionf operator-(const Quaternionf& a, const Quaternionf& b)		// binary subtraction operator
{
	Quaternionf qtemp;
	qSubf(qtemp.val, a.val, b.val);
	return qtemp;
}

Quaternionf operator*(const Quaternionf& a, const Quaternionf& b)		// binary multiplication operator (element-wise)
{
	Quaternionf qtemp;
	qMulf(qtemp.val, a.val, b.val);
	return qtemp;
}

Quaternionf operator*(const Quaternionf& q, const float& k)			// binary scalar multiplication operator
{
	Quaternionf qtemp(q);
	return (qtemp*=k);
}

Quaternionf operator*(const float& k, const Quaternionf& q)			// binary scalar multiplication operator
{
	Quaternionf qtemp(q);
	return (qtemp*=k);
}

Quaternionf operator/(const Quaternionf& a, const Quaternionf& b)		// binary division operator (element-wise)
{
	Quaternionf qtemp(a);
	return (qtemp*=!b);
}

Quaternionf operator/(const Quaternionf& q, const float& k)			// binary scalar division operator
{
	Quaternionf qtemp(q);
	return (qtemp/=k);
}

Quaternionf operator/(const float& k, const Quaternionf& q)			// binary scalar division operator
{
	Quaternionf qtemp(!q);
	qMulScalarf(qtemp.val, k);
	return qtemp;
}

Quaternionf operator!(const Quaternionf& q)							// unary inversion operator
{
	Quaternionf qtemp;
	qInvertf(q.val, qtemp.val);
	return qtemp;
}

// Accessors
float& Quaternionf::operator[](int i){ return val[i]; }
float* Quaternionf::GetData(){ return val; }
float Quaternionf::W(){ return val[0]; }
float Quaternionf::X(){ return val[1]; }
float Quaternionf::Y(){ return val[2]; }
float Quaternionf::Z(){ return val[3]; }

void Quaternionf::SetW(float nw) { val[0] = nw; }
void Quaternionf::SetX(float nx) { val[1] = nx; }
void Quaternionf::SetY(float ny) { val[2] = ny; }
void Quaternionf::SetZ(float nz) { val[3] = nz; }