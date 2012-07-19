#include "Quaternion.h"
#include <typeinfo.h>

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
	double axis[3] = {axis_x, axis_y, axis_z};
	qFromAxisAngled(this->val, rad, axis);
	return *this;
}

Quaterniond Quaterniond::FromMatrix(const double* R)
{
	qFromMatrixd(this->val, R);
	return *this;
}

Quaterniond Quaterniond::FromEulerAngle(const double a, const double b, const double c, const char* order)
{
	qFromEulerd(this->val, a, b, c, order);
	return *this;
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