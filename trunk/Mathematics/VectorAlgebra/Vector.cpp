#include "Vector.h"
#include <typeinfo.h>

Vector3d::Vector3d(void)
{
}

Vector3d::Vector3d(double x, double y, double z)							// (x, y, z)
{
	val[0] = x;	val[1] = y;	val[2] = z;
}

Vector3d::Vector3d(double* xyz)											// (xyz[0], xyz[1], xyz[2])
{
	memcpy(val, xyz, sizeof(double)*3);
}

Vector3d::Vector3d(const Vector3d& v)									// copy constructor
{
	memcpy(this->val, v.val, sizeof(double)*3);
}

Vector3d::~Vector3d(void)
{
}

// Methods (Algebra)

double Vector3d::Dot( const Vector3d& a, const Vector3d& b )
{
	return vDot3d(a.val, b.val);
}

double Vector3d::Dot( const Vector3d& v )
{
	return vDot3d(this->val, v.val);
}

Vector3d Vector3d::Cross(const Vector3d& a, const Vector3d& b)
{
	double c[3];
	return vCross3d(a.val, b.val, c);
}

double Vector3d::NormSquared(const Vector3d& v)
{
	return vNormSquared3d(v.val);
}

double Vector3d::NormSquared()
{
	return vNormSquared3d(this->val);
}

double Vector3d::Norm(const Vector3d& v)
{
	return vNorm3d(v.val);
}

double Vector3d::Norm()
{
	return vNorm3d(this->val);
}

Vector3d Vector3d::Normalize(Vector3d& v)
{
	vNormalize3d(v.val);
	return v;
}

Vector3d Vector3d::Normalize(void)
{
	vNormalize3d(this->val);
	return *this;
}

Vector3d Vector3d::Add(const Vector3d& a, const Vector3d& b)
{
	double c[3];
	return vAdd3d(a.val, b.val, c);
}

Vector3d Vector3d::Add(const Vector3d& v)
{
	return vAdd3d(this->val, v.val);
}

Vector3d Vector3d::Sub(const Vector3d& a, const Vector3d& b)
{
	double c[3];
	return vSub3d(a.val, b.val, c);
}

Vector3d Vector3d::Sub(const Vector3d& v)
{
	return vSub3d(this->val, v.val);
}

Vector3d Vector3d::Mul(const Vector3d& a, const Vector3d& b)
{
	double c[3];
	return vMul3d(a.val, b.val, c);
}

Vector3d Vector3d::Mul(const Vector3d& v)
{
	return vMul3d(this->val, v.val);
}

Vector3d Vector3d::Mul(const Vector3d& a, const double& k)
{
	double x[3];
	return vMulScalar3d(x, a.val, k);
}

Vector3d Vector3d::Mul(const double& k)
{
	return vMulScalar3d(this->val, k);
}

Vector3d Vector3d::Div(const Vector3d& a, const Vector3d& b)
{
	double c[3];
	return vDiv3d(a.val, b.val, c);
}

Vector3d Vector3d::Div(const Vector3d& v)
{
	return vDiv3d(this->val, v.val);
}

Vector3d Vector3d::Div(const Vector3d& a, const double& k)
{
	double x[3];
	return vDivScalar3d(x, a.val, k);
}

Vector3d Vector3d::Div(const double& k)
{
	return vDivScalar3d(this->val, k);
}

// Methods (Geometry)
Vector3d Vector3d::Rotate(const double rad, const Vector3d& axis)		// rotate this vector by given angle(rad) along the axis(must be unit)
{
	// TODO: implement rotation here

	return *this;
}

Vector3d Vector3d::Rotate(const double* R)								// rotate this vector by multiplying the rotation matrix R (column-stacked)
{
	Vector3d temp(*this);
	this->val[0] = R[0]*temp[0] + R[3]*temp[1] + R[6]*temp[2];
	this->val[0] = R[1]*temp[0] + R[4]*temp[1] + R[7]*temp[2];
	this->val[0] = R[2]*temp[0] + R[5]*temp[1] + R[8]*temp[2];
	return *this;
}

//Vector3d Vector3d::Rotate(const Quaterniond& q);
Vector3d Vector3d::Translate(const Vector3d& dx)							// this += dx
{
	vAdd3d(this->val, dx.val);
	return *this;
}

Vector3d Vector3d::Translate(const double mag, const Vector3d& dir)			// this += mag*dir
{
	double dval[3];
	vAdd3d(this->val, vMulScalar3d(dval, dir.val, mag));
	return *this;
}

// Operators
Vector3d Vector3d::operator=(const Vector3d& v)								// assign operator
{
	vCopy3d(this->val, v.val);
	return *this;
}

bool Vector3d::operator==(const Vector3d& v)								// compare operator
{
	return vIsEqual3d(this->val, v.val);
}
bool Vector3d::operator!=(const Vector3d& v)								// negative compare operator
{
	return !vIsEqual3d(this->val, v.val);
}

Vector3d Vector3d::operator+=(const Vector3d& v)							// unary addition operator
{
	vAdd3d(this->val, v.val);
	return *this;
}
Vector3d Vector3d::operator-=(const Vector3d& v)							// unary subtraction operator
{
	vSub3d(this->val, v.val);
	return *this;
}
Vector3d Vector3d::operator*=(const Vector3d& v)							// unary multiplication operator (element-wise)
{
	vMul3d(this->val, v.val);
	return *this;
}
Vector3d Vector3d::operator*=(const double& k)								// unary scalar multiplication operator
{
	vMulScalar3d(this->val, k);
	return *this;
}
Vector3d Vector3d::operator/=(const Vector3d& v)							// unary division operator (element-wise)
{
	vDiv3d(this->val, v.val);
	return *this;
}
Vector3d Vector3d::operator/=(const double& k)								// unary scalar division operator
{
	vDivScalar3d(this->val, k);
	return *this;
}

Vector3d Vector3d::operator-()												// unary negation operator
{
	Vector3d temp(*this);
	vNegate3d(temp.val);
	return temp;
}

// Accessors
double& Vector3d::operator[](int i){ return val[i]; }
double Vector3d::X(){ return val[0]; }
double Vector3d::Y(){ return val[1]; }
double Vector3d::Z(){ return val[2]; }

void Vector3d::SetX(double nx) { val[0] = nx; }
void Vector3d::SetY(double ny) { val[1] = ny; }
void Vector3d::SetZ(double nz) { val[2] = nz; }