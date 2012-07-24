#include "Vector.h"
#include <memory>
#include <math.h>
#include <algorithm>

Vector3d::Vector3d(void)
{
	memset(val, 0, sizeof(double)*3);
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

Vector3d::Vector3d(const Vector3f& v)									// typecast constructor
{
	this->val[0] = v.val[0];
	this->val[1] = v.val[1];
	this->val[2] = v.val[2];
}

Vector3d::Vector3d(const Vector2d& v)									// typecast constructor
{
	memcpy(this->val, v.val, sizeof(double)*2);
	this->val[2] = 0.0;
}

Vector3d::Vector3d(const Vector2f& v)									// typecast constructor
{
	this->val[0] = v.val[0];
	this->val[1] = v.val[1];
	this->val[2] = 0.0;
}

#ifdef Quaterniond
Vector3d::Vector3d(const Quaterniond& q)									// typecast constructor
{
	memcpy(this->val, &q.val[1], sizeof(double)*3);
}
#endif

#ifdef Quaternionf
Vector3d::Vector3d(const Quaternionf& q)									// typecast constructor
{
	this->val[0] = (double)q.val[1];
	this->val[1] = (double)q.val[2];
	this->val[2] = (double)q.val[3];
}
#endif

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
	Vector3d c;
	vCross3d(a.val, b.val, c.val);
	return c;
}

Vector3d Vector3d::Cross(const Vector3d& v)
{
	Vector3d c;
	vCross3d(this->val, v.val, c.val);
	return c;
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
	Vector3d c;
	vAdd3d(a.val, b.val, c.val);
	return c;
}

Vector3d Vector3d::Add(const Vector3d& v)
{
	vAdd3d(this->val, v.val);
	return *this;
}

Vector3d Vector3d::Add(const Vector3d& a, const double& k)
{
	Vector3d b;
	vAddScalar3d(b.val, a.val, k);
	return b;
}

Vector3d Vector3d::Add(const double& k)
{
	vAddScalar3d(this->val, k);
	return *this;
}

Vector3d Vector3d::Sub(const Vector3d& a, const Vector3d& b)
{
	Vector3d c;
	vSub3d(a.val, b.val, c.val);
	return c;
}

Vector3d Vector3d::Sub(const Vector3d& v)
{
	vSub3d(this->val, v.val);
	return *this;
}

Vector3d Vector3d::Sub(const Vector3d& a, const double& k)
{
	Vector3d b;
	vSubScalar3d(b.val, a.val, k);
	return b;
}

Vector3d Vector3d::Sub(const double& k)
{
	vSubScalar3d(this->val, k);
	return *this;
}

Vector3d Vector3d::Mul(const Vector3d& a, const Vector3d& b)
{
	Vector3d c;
	vMul3d(a.val, b.val, c.val);
	return c;
}

Vector3d Vector3d::Mul(const Vector3d& v)
{
	vMul3d(this->val, v.val);
	return *this;
}

Vector3d Vector3d::Mul(const Vector3d& a, const double& k)
{
	Vector3d b;
	vMulScalar3d(b.val, a.val, k);
	return b;
}

Vector3d Vector3d::Mul(const double& k)
{
	vMulScalar3d(this->val, k);
	return *this;
}

Vector3d Vector3d::Div(const Vector3d& a, const Vector3d& b)
{
	Vector3d c;
	vDiv3d(a.val, b.val, c.val);
	return c;
}

Vector3d Vector3d::Div(const Vector3d& v)
{
	vDiv3d(this->val, v.val);
	return *this;
}

Vector3d Vector3d::Div(const Vector3d& a, const double& k)
{
	Vector3d b;
	vDivScalar3d(b.val, a.val, k);
	return b;
}

Vector3d Vector3d::Div(const double& k)
{
	vDivScalar3d(this->val, k);
	return *this;
}

// Methods (Geometry)
Vector3d Vector3d::Rotate(const double rad, const Vector3d& axis)		// rotate this vector by given angle(rad) along the axis(must be unit)
{
	// TODO: implement rotation here

	return *this;
}

Vector3d Vector3d::Rotate( const Vector3d& axis )						// rotate this vector by given angle(norm of axis) along the axis
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

double Vector3d::Angle( const Vector3d& a, const Vector3d& b )		// get angle between two vectors
{
	double cosangle = Dot(a,b)/(Norm(a)*Norm(b));
	cosangle = std::min(1.0, std::max(-1.0 , cosangle));
	return acos(cosangle);
}

double Vector3d::Angle( const Vector3d& a )							// get angle between this and a
{
	double cosangle = Dot(a)/(Norm()*Norm(a));
	cosangle = std::min(1.0, std::max(-1.0 , cosangle));
	return acos(cosangle);
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
Vector3d Vector3d::operator+=(const double& k)								// unary scalar addition operator
{
	vAddScalar3d(this->val, k);
	return *this;	
}
Vector3d Vector3d::operator-=(const Vector3d& v)							// unary subtraction operator
{
	vSub3d(this->val, v.val);
	return *this;
}
Vector3d Vector3d::operator-=(const double& k)								// unary scalar subtraction operator
{
	vSubScalar3d(this->val, k);
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

Vector3d operator+(const Vector3d& a, const Vector3d& b)			// binary addition operator
{
	// 	Vector3d temp;
	// 	vAdd3d(a.val, b.val, temp.val);
	// 	return temp;
	Vector3d temp(a);
	return (temp+=b);
}

Vector3d operator-(const Vector3d& a, const Vector3d& b)			// binary subtraction operator
{
	Vector3d temp(a);
	return (temp-=b);
}

Vector3d operator*(const Vector3d& a, const Vector3d& b)			// binary multiplication operator (element-wise)
{
	Vector3d temp(a);
	return (temp*=b);
}

Vector3d operator*(const Vector3d& v, const double& k)			// binary scalar multiplication operator
{
	Vector3d temp(v);
	return (temp*=k);
}

Vector3d operator*(const double& k, const Vector3d& v)			// binary scalar multiplication operator
{
	Vector3d temp(v);
	return (temp*=k);
}

Vector3d operator/(const Vector3d& a, const Vector3d& b)			// binary division operator (element-wise)
{
	Vector3d temp(a);
	return (temp/=b);
}

Vector3d operator/(const Vector3d& v, const double& k)			// binary scalar division operator
{
	Vector3d temp(v);
	return (temp/=k);
}

Vector3d operator/(const double& k, const Vector3d& v)			// binary scalar division operator
{
	Vector3d temp(v);
	return (temp/=k);
}


// Accessors
double& Vector3d::operator[](int i){ return val[i]; }
double Vector3d::X(){ return val[0]; }
double Vector3d::Y(){ return val[1]; }
double Vector3d::Z(){ return val[2]; }

void Vector3d::SetX(double nx) { val[0] = nx; }
void Vector3d::SetY(double ny) { val[1] = ny; }
void Vector3d::SetZ(double nz) { val[2] = nz; }




//////////////////////////////////////////////////////////////////////////




Vector3f::Vector3f(void)
{
	memset(val, 0, sizeof(float)*3);
}

Vector3f::Vector3f(float x, float y, float z)							// (x, y, z)
{
	val[0] = x;	val[1] = y;	val[2] = z;
}

Vector3f::Vector3f(float* xyz)											// (xyz[0], xyz[1], xyz[2])
{
	memcpy(val, xyz, sizeof(float)*3);
}

Vector3f::Vector3f(const Vector3f& v)									// copy constructor
{
	memcpy(this->val, v.val, sizeof(float)*3);
}

Vector3f::Vector3f(const Vector3d& v)									// typecast constructor
{
	this->val[0] = (float)v.val[0];
	this->val[1] = (float)v.val[1];
	this->val[2] = (float)v.val[2];
}

Vector3f::Vector3f(const Vector2d& v)									// typecast constructor
{
	this->val[0] = (float)v.val[0];
	this->val[1] = (float)v.val[1];
	this->val[2] = 0.0f;
}

Vector3f::Vector3f(const Vector2f& v)									// typecast constructor
{
	memcpy(this->val, v.val, sizeof(float)*2);
	this->val[2] = 0.0f;
}

#ifdef Quaterniond
Vector3f::Vector3f(const Quaterniond& q)									// typecast constructor
{
	this->val[0] = (float)q.val[1];
	this->val[1] = (float)q.val[2];
	this->val[2] = (float)q.val[3];
}
#endif

#ifdef Quaternionf
Vector3f::Vector3f(const Quaternionf& q)									// typecast constructor
{
	memcpy(this->val, &q.val[1], sizeof(float)*3);
}
#endif

Vector3f::~Vector3f(void)
{
}

// Methods (Algebra)

float Vector3f::Dot( const Vector3f& a, const Vector3f& b )
{
	return vDot3f(a.val, b.val);
}

float Vector3f::Dot( const Vector3f& v )
{
	return vDot3f(this->val, v.val);
}

Vector3f Vector3f::Cross(const Vector3f& a, const Vector3f& b)
{
	float c[3];
	return vCross3f(a.val, b.val, c);
}

Vector3f Vector3f::Cross(const Vector3f& v)
{
	float c[3];
	return vCross3f(this->val, v.val, c);
}

float Vector3f::NormSquared(const Vector3f& v)
{
	return vNormSquared3f(v.val);
}

float Vector3f::NormSquared()
{
	return vNormSquared3f(this->val);
}

float Vector3f::Norm(const Vector3f& v)
{
	return vNorm3f(v.val);
}

float Vector3f::Norm()
{
	return vNorm3f(this->val);
}

Vector3f Vector3f::Normalize(Vector3f& v)
{
	vNormalize3f(v.val);
	return v;
}

Vector3f Vector3f::Normalize(void)
{
	vNormalize3f(this->val);
	return *this;
}

Vector3f Vector3f::Add(const Vector3f& a, const Vector3f& b)
{
	Vector3f c;
	vAdd3f(a.val, b.val, c.val);
	return c;
}

Vector3f Vector3f::Add(const Vector3f& v)
{
	vAdd3f(this->val, v.val);
	return *this;
}

Vector3f Vector3f::Add(const Vector3f& a, const float& k)
{
	Vector3f b;
	vAddScalar3f(b.val, a.val, k);
	return b;
}

Vector3f Vector3f::Add(const float& k)
{
	vAddScalar3f(this->val, k);
	return *this;
}

Vector3f Vector3f::Sub(const Vector3f& a, const Vector3f& b)
{
	Vector3f c;
	vSub3f(a.val, b.val, c.val);
	return c;
}

Vector3f Vector3f::Sub(const Vector3f& v)
{
	vSub3f(this->val, v.val);
	return *this;
}

Vector3f Vector3f::Sub(const Vector3f& a, const float& k)
{
	Vector3f b;
	vSubScalar3f(b.val, a.val, k);
	return b;
}

Vector3f Vector3f::Sub(const float& k)
{
	vSubScalar3f(this->val, k);
	return *this;
}

Vector3f Vector3f::Mul(const Vector3f& a, const Vector3f& b)
{
	Vector3f c;
	vMul3f(a.val, b.val, c.val);
	return c;
}

Vector3f Vector3f::Mul(const Vector3f& v)
{
	vMul3f(this->val, v.val);
	return *this;
}

Vector3f Vector3f::Mul(const Vector3f& a, const float& k)
{
	Vector3f b;
	vMulScalar3f(b.val, a.val, k);
	return b;
}

Vector3f Vector3f::Mul(const float& k)
{
	vMulScalar3f(this->val, k);
	return *this;
}

Vector3f Vector3f::Div(const Vector3f& a, const Vector3f& b)
{
	Vector3f c;
	vDiv3f(a.val, b.val, c.val);
	return c;
}

Vector3f Vector3f::Div(const Vector3f& v)
{
	vDiv3f(this->val, v.val);
	return *this;
}

Vector3f Vector3f::Div(const Vector3f& a, const float& k)
{
	Vector3f b;
	vDivScalar3f(b.val, a.val, k);
	return b;
}

Vector3f Vector3f::Div(const float& k)
{
	vDivScalar3f(this->val, k);
	return *this;
}

// Methods (Geometry)
Vector3f Vector3f::Rotate(const float rad, const Vector3f& axis)		// rotate this vector by given angle(rad) along the axis(must be unit)
{
	// TODO: implement rotation here

	return *this;
}

Vector3f Vector3f::Rotate( const Vector3f& axis )						// rotate this vector by given angle(norm of axis) along the axis
{
	// TODO: implement rotation here

	return *this;
}

Vector3f Vector3f::Rotate(const float* R)								// rotate this vector by multiplying the rotation matrix R (column-stacked)
{
	Vector3f temp(*this);
	this->val[0] = R[0]*temp[0] + R[3]*temp[1] + R[6]*temp[2];
	this->val[0] = R[1]*temp[0] + R[4]*temp[1] + R[7]*temp[2];
	this->val[0] = R[2]*temp[0] + R[5]*temp[1] + R[8]*temp[2];
	return *this;
}

//Vector3f Vector3f::Rotate(const Quaterniond& q);

Vector3f Vector3f::Translate(const Vector3f& dx)							// this += dx
{
	vAdd3f(this->val, dx.val);
	return *this;
}

Vector3f Vector3f::Translate(const float mag, const Vector3f& dir)			// this += mag*dir
{
	float dval[3];
	vAdd3f(this->val, vMulScalar3f(dval, dir.val, mag));
	return *this;
}

float Vector3f::Angle( const Vector3f& a, const Vector3f& b )		// get angle between two vectors
{
	float cosangle = Dot(a,b)/(Norm(a)*Norm(b));
	cosangle = std::min(1.0f, std::max(-1.0f , cosangle));
	return acos(cosangle);
}

float Vector3f::Angle( const Vector3f& a )							// get angle between this and a
{
	float cosangle = Dot(a)/(Norm()*Norm(a));
	cosangle = std::min(1.0f, std::max(-1.0f, cosangle));
	return acos(cosangle);
}



// Operators
Vector3f Vector3f::operator=(const Vector3f& v)								// assign operator
{
	vCopy3f(this->val, v.val);
	return *this;
}

bool Vector3f::operator==(const Vector3f& v)								// compare operator
{
	return vIsEqual3f(this->val, v.val);
}
bool Vector3f::operator!=(const Vector3f& v)								// negative compare operator
{
	return !vIsEqual3f(this->val, v.val);
}

Vector3f Vector3f::operator+=(const Vector3f& v)							// unary addition operator
{
	vAdd3f(this->val, v.val);
	return *this;
}
Vector3f Vector3f::operator+=(const float& k)								// unary scalar addition operator
{
	vAddScalar3f(this->val, k);
	return *this;	
}
Vector3f Vector3f::operator-=(const Vector3f& v)							// unary subtraction operator
{
	vSub3f(this->val, v.val);
	return *this;
}
Vector3f Vector3f::operator-=(const float& k)								// unary scalar subtraction operator
{
	vSubScalar3f(this->val, k);
	return *this;	
}
Vector3f Vector3f::operator*=(const Vector3f& v)							// unary multiplication operator (element-wise)
{
	vMul3f(this->val, v.val);
	return *this;
}
Vector3f Vector3f::operator*=(const float& k)								// unary scalar multiplication operator
{
	vMulScalar3f(this->val, k);
	return *this;
}
Vector3f Vector3f::operator/=(const Vector3f& v)							// unary division operator (element-wise)
{
	vDiv3f(this->val, v.val);
	return *this;
}
Vector3f Vector3f::operator/=(const float& k)								// unary scalar division operator
{
	vDivScalar3f(this->val, k);
	return *this;
}

Vector3f Vector3f::operator-()												// unary negation operator
{
	Vector3f temp(*this);
	vNegate3f(temp.val);
	return temp;
}

Vector3f operator+(const Vector3f& a, const Vector3f& b)			// binary addition operator
{
	// 	Vector3f temp;
	// 	vAdd3f(a.val, b.val, temp.val);
	// 	return temp;
	Vector3f temp(a);
	return (temp+=b);
}

Vector3f operator-(const Vector3f& a, const Vector3f& b)			// binary subtraction operator
{
	Vector3f temp(a);
	return (temp-=b);
}

Vector3f operator*(const Vector3f& a, const Vector3f& b)			// binary multiplication operator (element-wise)
{
	Vector3f temp(a);
	return (temp*=b);
}

Vector3f operator*(const Vector3f& v, const float& k)			// binary scalar multiplication operator
{
	Vector3f temp(v);
	return (temp*=k);
}

Vector3f operator*(const float& k, const Vector3f& v)			// binary scalar multiplication operator
{
	Vector3f temp(v);
	return (temp*=k);
}

Vector3f operator/(const Vector3f& a, const Vector3f& b)			// binary division operator (element-wise)
{
	Vector3f temp(a);
	return (temp/=b);
}

Vector3f operator/(const Vector3f& v, const float& k)			// binary scalar division operator
{
	Vector3f temp(v);
	return (temp/=k);
}

Vector3f operator/(const float& k, const Vector3f& v)			// binary scalar division operator
{
	Vector3f temp(v);
	return (temp/=k);
}


// Accessors
float& Vector3f::operator[](int i){ return val[i]; }
float Vector3f::X(){ return val[0]; }
float Vector3f::Y(){ return val[1]; }
float Vector3f::Z(){ return val[2]; }

void Vector3f::SetX(float nx) { val[0] = nx; }
void Vector3f::SetY(float ny) { val[1] = ny; }
void Vector3f::SetZ(float nz) { val[2] = nz; }



//////////////////////////////////////////////////////////////////////////





Vector2d::Vector2d(void)
{
	memset(val, 0, sizeof(double)*2);
}

Vector2d::Vector2d(double x, double y)									// (x, y)
{
	val[0] = x;	val[1] = y;
}

Vector2d::Vector2d(double* xy)											// (xy[0], xy[1])
{
	memcpy(val, xy, sizeof(double)*2);
}

Vector2d::Vector2d(const Vector2d& v)									// copy constructor
{
	memcpy(this->val, v.val, sizeof(double)*2);
}

Vector2d::Vector2d(const Vector2f& v)									// typecast constructor
{
	this->val[0] = (double)v.val[0];
	this->val[1] = (double)v.val[1];
}

Vector2d::Vector2d(const Vector3d& v)									// typecast constructor
{
	memcpy(this->val, v.val, sizeof(double)*2);
}

Vector2d::Vector2d(const Vector3f& v)									// typecast constructor
{
	this->val[0] = (double)v.val[0];
	this->val[1] = (double)v.val[1];
}

#ifdef Quaterniond
Vector2d::Vector2d(const Quaterniond& q)									// typecast constructor
{
	memcpy(this->val, &q.val[1], sizeof(double)*2);
}
#endif

#ifdef Quaternionf
Vector2d::Vector2d(const Quaternionf& q)									// typecast constructor
{
	this->val[0] = (double)q.val[1];
	this->val[1] = (double)q.val[2];
}
#endif

Vector2d::~Vector2d(void)
{
}

// Methods (Algebra)

double Vector2d::Dot( const Vector2d& a, const Vector2d& b )
{
	return vDot2d(a.val, b.val);
}

double Vector2d::Dot( const Vector2d& v )
{
	return vDot2d(this->val, v.val);
}

double Vector2d::Cross(const Vector2d& a, const Vector2d& b)
{
	return vCross2d(a.val, b.val);
}

double Vector2d::Cross(const Vector2d& v)
{
	return vCross2d(this->val, v.val);
}

double Vector2d::NormSquared(const Vector2d& v)
{
	return vNormSquared2d(v.val);
}

double Vector2d::NormSquared()
{
	return vNormSquared2d(this->val);
}

double Vector2d::Norm(const Vector2d& v)
{
	return vNorm2d(v.val);
}

double Vector2d::Norm()
{
	return vNorm2d(this->val);
}

Vector2d Vector2d::Normalize(Vector2d& v)
{
	vNormalize2d(v.val);
	return v;
}

Vector2d Vector2d::Normalize(void)
{
	vNormalize2d(this->val);
	return *this;
}

Vector2d Vector2d::Add(const Vector2d& a, const Vector2d& b)
{
	Vector2d c;
	vAdd2d(a.val, b.val, c.val);
	return c;
}

Vector2d Vector2d::Add(const Vector2d& v)
{
	Vector2d c;
	vAdd2d(this->val, v.val, c.val);
	return c;
}

Vector2d Vector2d::Add(const Vector2d& a, const double& k)
{
	Vector2d b;
	vAddScalar2d(b.val, a.val, k);
	return b;
}

Vector2d Vector2d::Add(const double& k)
{
	vAddScalar2d(this->val, k);
	return *this;
}

Vector2d Vector2d::Sub(const Vector2d& a, const Vector2d& b)
{
	Vector2d c;
	vSub2d(a.val, b.val, c.val);
	return c;
}

Vector2d Vector2d::Sub(const Vector2d& v)
{
	Vector2d c;
	vSub2d(this->val, v.val, c.val);
	return c;
}

Vector2d Vector2d::Sub(const Vector2d& a, const double& k)
{
	Vector2d b;
	vSubScalar2d(b.val, a.val, k);
	return b;
}

Vector2d Vector2d::Sub(const double& k)
{
	vSubScalar2d(this->val, k);
	return *this;
}

Vector2d Vector2d::Mul(const Vector2d& a, const Vector2d& b)
{
	Vector2d c;
	vMul2d(a.val, b.val, c.val);
	return c;
}

Vector2d Vector2d::Mul(const Vector2d& v)
{
	vMul2d(this->val, v.val);
	return *this;
}

Vector2d Vector2d::Mul(const Vector2d& a, const double& k)
{
	Vector2d b;
	vMulScalar2d(b.val, a.val, k);
	return b;
}

Vector2d Vector2d::Mul(const double& k)
{
	vMulScalar2d(this->val, k);
	return *this;
}

Vector2d Vector2d::Div(const Vector2d& a, const Vector2d& b)
{
	Vector2d c;
	vDiv2d(a.val, b.val, c.val);
	return c;
}

Vector2d Vector2d::Div(const Vector2d& v)
{
	vDiv2d(this->val, v.val);
	return *this;
}

Vector2d Vector2d::Div(const Vector2d& a, const double& k)
{
	Vector2d b;
	vDivScalar2d(b.val, a.val, k);
	return b;
}

Vector2d Vector2d::Div(const double& k)
{
	vDivScalar2d(this->val, k);
	return *this;
}

// Methods (Geometry)
Vector2d Vector2d::Rotate(const double rad, const Vector2d& axis)		// rotate this vector by given angle(rad) along the axis(must be unit)
{
	// TODO: implement rotation here

	return *this;
}

Vector2d Vector2d::Rotate( const Vector2d& axis )						// rotate this vector by given angle(norm of axis) along the axis
{
	// TODO: implement rotation here

	return *this;
}

Vector2d Vector2d::Rotate(const double* R)								// rotate this vector by multiplying the rotation matrix R (column-stacked)
{
	Vector2d temp(*this);
	this->val[0] = R[0]*temp[0] + R[3]*temp[1] + R[6]*temp[2];
	this->val[0] = R[1]*temp[0] + R[4]*temp[1] + R[7]*temp[2];
	this->val[0] = R[2]*temp[0] + R[5]*temp[1] + R[8]*temp[2];
	return *this;
}

//Vector2d Vector2d::Rotate(const Quaterniond& q);

Vector2d Vector2d::Translate(const Vector2d& dx)							// this += dx
{
	return this->Add(dx);
}

Vector2d Vector2d::Translate(const double mag, const Vector2d& dir)			// this += mag*dir
{
	double dval[2];
	vAdd2d(this->val, vMulScalar2d(dval, dir.val, mag));
	return *this;
}

double Vector2d::Angle( const Vector2d& a, const Vector2d& b )		// get angle between two vectors
{
	double cosangle = Dot(a,b)/(Norm(a)*Norm(b));
	cosangle = std::min(1.0, std::max(-1.0 , cosangle));
	return acos(cosangle);
}

double Vector2d::Angle( const Vector2d& a )							// get angle between this and a
{
	double cosangle = Dot(a)/(Norm()*Norm(a));
	cosangle = std::min(1.0, std::max(-1.0 , cosangle));
	return acos(cosangle);
}



// Operators
Vector2d Vector2d::operator=(const Vector2d& v)								// assign operator
{
	vCopy2d(this->val, v.val);
	return *this;
}

bool Vector2d::operator==(const Vector2d& v)								// compare operator
{
	return vIsEqual2d(this->val, v.val);
}
bool Vector2d::operator!=(const Vector2d& v)								// negative compare operator
{
	return !vIsEqual2d(this->val, v.val);
}

Vector2d Vector2d::operator+=(const Vector2d& v)							// unary addition operator
{
	vAdd2d(this->val, v.val);
	return *this;
}
Vector2d Vector2d::operator+=(const double& k)								// unary scalar addition operator
{
	vAddScalar2d(this->val, k);
	return *this;	
}
Vector2d Vector2d::operator-=(const Vector2d& v)							// unary subtraction operator
{
	vSub2d(this->val, v.val);
	return *this;
}
Vector2d Vector2d::operator-=(const double& k)								// unary scalar subtraction operator
{
	vSubScalar2d(this->val, k);
	return *this;	
}
Vector2d Vector2d::operator*=(const Vector2d& v)							// unary multiplication operator (element-wise)
{
	vMul2d(this->val, v.val);
	return *this;
}
Vector2d Vector2d::operator*=(const double& k)								// unary scalar multiplication operator
{
	vMulScalar2d(this->val, k);
	return *this;
}
Vector2d Vector2d::operator/=(const Vector2d& v)							// unary division operator (element-wise)
{
	vDiv2d(this->val, v.val);
	return *this;
}
Vector2d Vector2d::operator/=(const double& k)								// unary scalar division operator
{
	vDivScalar2d(this->val, k);
	return *this;
}

Vector2d Vector2d::operator-()												// unary negation operator
{
	Vector2d temp(*this);
	vNegate2d(temp.val);
	return temp;
}

Vector2d operator+(const Vector2d& a, const Vector2d& b)			// binary addition operator
{
	// 	Vector2d temp;
	// 	vAdd2d(a.val, b.val, temp.val);
	// 	return temp;
	Vector2d temp(a);
	return (temp+=b);
}

Vector2d operator-(const Vector2d& a, const Vector2d& b)			// binary subtraction operator
{
	Vector2d temp(a);
	return (temp-=b);
}

Vector2d operator*(const Vector2d& a, const Vector2d& b)			// binary multiplication operator (element-wise)
{
	Vector2d temp(a);
	return (temp*=b);
}

Vector2d operator*(const Vector2d& v, const double& k)			// binary scalar multiplication operator
{
	Vector2d temp(v);
	return (temp*=k);
}

Vector2d operator*(const double& k, const Vector2d& v)			// binary scalar multiplication operator
{
	Vector2d temp(v);
	return (temp*=k);
}

Vector2d operator/(const Vector2d& a, const Vector2d& b)			// binary division operator (element-wise)
{
	Vector2d temp(a);
	return (temp/=b);
}

Vector2d operator/(const Vector2d& v, const double& k)			// binary scalar division operator
{
	Vector2d temp(v);
	return (temp/=k);
}

Vector2d operator/(const double& k, const Vector2d& v)			// binary scalar division operator
{
	Vector2d temp(v);
	return (temp/=k);
}


// Accessors
double& Vector2d::operator[](int i){ return val[i]; }
double Vector2d::X(){ return val[0]; }
double Vector2d::Y(){ return val[1]; }

void Vector2d::SetX(double nx) { val[0] = nx; }
void Vector2d::SetY(double ny) { val[1] = ny; }



//////////////////////////////////////////////////////////////////////////





Vector2f::Vector2f(void)
{
	memset(val, 0, sizeof(float)*2);
}

Vector2f::Vector2f(float x, float y)									// (x, y)
{
	val[0] = x;	val[1] = y;
}

Vector2f::Vector2f(float* xy)											// (xy[0], xy[1])
{
	memcpy(val, xy, sizeof(float)*2);
}

Vector2f::Vector2f(const Vector2f& v)									// copy constructor
{
	memcpy(this->val, v.val, sizeof(float)*2);
}

Vector2f::Vector2f(const Vector2d& v)									// typecast constructor
{
	this->val[0] = (float)v.val[0];
	this->val[1] = (float)v.val[1];
}

Vector2f::Vector2f(const Vector3d& v)									// typecast constructor
{
	this->val[0] = (float)v.val[0];
	this->val[1] = (float)v.val[1];
}

Vector2f::Vector2f(const Vector3f& v)									// typecast constructor
{
	memcpy(this->val, v.val, sizeof(float)*2);
}

#ifdef Quaterniond
Vector2f::Vector2f(const Quaterniond& q)									// typecast constructor
{
	this->val[0] = (float)q.val[1];
	this->val[1] = (float)q.val[2];
}
#endif

#ifdef Quaternionf
Vector2f::Vector2f(const Quaternionf& q)									// typecast constructor
{
	memcpy(this->val, &q.val[1], sizeof(float)*2);
}
#endif

Vector2f::~Vector2f(void)
{
}

// Methods (Algebra)

float Vector2f::Dot( const Vector2f& a, const Vector2f& b )
{
	return vDot2f(a.val, b.val);
}

float Vector2f::Dot( const Vector2f& v )
{
	return vDot2f(this->val, v.val);
}

float Vector2f::Cross(const Vector2f& a, const Vector2f& b)
{
	return vCross2f(a.val, b.val);
}

float Vector2f::Cross(const Vector2f& v)
{
	return vCross2f(this->val, v.val);
}

float Vector2f::NormSquared(const Vector2f& v)
{
	return vNormSquared2f(v.val);
}

float Vector2f::NormSquared()
{
	return vNormSquared2f(this->val);
}

float Vector2f::Norm(const Vector2f& v)
{
	return vNorm2f(v.val);
}

float Vector2f::Norm()
{
	return vNorm2f(this->val);
}

Vector2f Vector2f::Normalize(Vector2f& v)
{
	vNormalize2f(v.val);
	return v;
}

Vector2f Vector2f::Normalize(void)
{
	vNormalize2f(this->val);
	return *this;
}

Vector2f Vector2f::Add(const Vector2f& a, const Vector2f& b)
{
	Vector2f c;
	vAdd2f(a.val, b.val, c.val);
	return c;
}

Vector2f Vector2f::Add(const Vector2f& v)
{
	Vector2f c;
	vAdd2f(this->val, v.val, c.val);
	return c;
}

Vector2f Vector2f::Add(const Vector2f& a, const float& k)
{
	Vector2f b;
	vAddScalar2f(b.val, a.val, k);
	return b;
}

Vector2f Vector2f::Add(const float& k)
{
	vAddScalar2f(this->val, k);
	return *this;
}

Vector2f Vector2f::Sub(const Vector2f& a, const Vector2f& b)
{
	Vector2f c;
	vSub2f(a.val, b.val, c.val);
	return c;
}

Vector2f Vector2f::Sub(const Vector2f& v)
{
	Vector2f c;
	vSub2f(this->val, v.val, c.val);
	return c;
}

Vector2f Vector2f::Sub(const Vector2f& a, const float& k)
{
	Vector2f b;
	vSubScalar2f(b.val, a.val, k);
	return b;
}

Vector2f Vector2f::Sub(const float& k)
{
	vSubScalar2f(this->val, k);
	return *this;
}

Vector2f Vector2f::Mul(const Vector2f& a, const Vector2f& b)
{
	Vector2f c;
	vMul2f(a.val, b.val, c.val);
	return c;
}

Vector2f Vector2f::Mul(const Vector2f& v)
{
	vMul2f(this->val, v.val);
	return *this;
}

Vector2f Vector2f::Mul(const Vector2f& a, const float& k)
{
	Vector2f b;
	vMulScalar2f(b.val, a.val, k);
	return b;
}

Vector2f Vector2f::Mul(const float& k)
{
	vMulScalar2f(this->val, k);
	return *this;
}

Vector2f Vector2f::Div(const Vector2f& a, const Vector2f& b)
{
	Vector2f c;
	vDiv2f(a.val, b.val, c.val);
	return c;
}

Vector2f Vector2f::Div(const Vector2f& v)
{
	vDiv2f(this->val, v.val);
	return *this;
}

Vector2f Vector2f::Div(const Vector2f& a, const float& k)
{
	Vector2f b;
	vDivScalar2f(b.val, a.val, k);
	return b;
}

Vector2f Vector2f::Div(const float& k)
{
	vDivScalar2f(this->val, k);
	return *this;
}

// Methods (Geometry)
Vector2f Vector2f::Rotate(const float rad, const Vector2f& axis)		// rotate this vector by given angle(rad) along the axis(must be unit)
{
	// TODO: implement rotation here

	return *this;
}

Vector2f Vector2f::Rotate( const Vector2f& axis )						// rotate this vector by given angle(norm of axis) along the axis
{
	// TODO: implement rotation here

	return *this;
}

Vector2f Vector2f::Rotate(const float* R)								// rotate this vector by multiplying the rotation matrix R (column-stacked)
{
	Vector2f temp(*this);
	this->val[0] = R[0]*temp[0] + R[3]*temp[1] + R[6]*temp[2];
	this->val[0] = R[1]*temp[0] + R[4]*temp[1] + R[7]*temp[2];
	this->val[0] = R[2]*temp[0] + R[5]*temp[1] + R[8]*temp[2];
	return *this;
}

//Vector2f Vector2f::Rotate(const Quaterniond& q);

Vector2f Vector2f::Translate(const Vector2f& dx)							// this += dx
{
	return this->Add(dx);
}

Vector2f Vector2f::Translate(const float mag, const Vector2f& dir)			// this += mag*dir
{
	float dval[2];
	vAdd2f(this->val, vMulScalar2f(dval, dir.val, mag));
	return *this;
}

float Vector2f::Angle( const Vector2f& a, const Vector2f& b )		// get angle between two vectors
{
	float cosangle = Dot(a,b)/(Norm(a)*Norm(b));
	cosangle = std::min(1.0f, std::max(-1.0f, cosangle));
	return acos(cosangle);
}

float Vector2f::Angle( const Vector2f& a )							// get angle between this and a
{
	float cosangle = Dot(a)/(Norm()*Norm(a));
	cosangle = std::min(1.0f, std::max(-1.0f, cosangle));
	return acos(cosangle);
}



// Operators
Vector2f Vector2f::operator=(const Vector2f& v)								// assign operator
{
	vCopy2f(this->val, v.val);
	return *this;
}

bool Vector2f::operator==(const Vector2f& v)								// compare operator
{
	return vIsEqual2f(this->val, v.val);
}
bool Vector2f::operator!=(const Vector2f& v)								// negative compare operator
{
	return !vIsEqual2f(this->val, v.val);
}

Vector2f Vector2f::operator+=(const Vector2f& v)							// unary addition operator
{
	vAdd2f(this->val, v.val);
	return *this;
}
Vector2f Vector2f::operator+=(const float& k)								// unary scalar addition operator
{
	vAddScalar2f(this->val, k);
	return *this;	
}
Vector2f Vector2f::operator-=(const Vector2f& v)							// unary subtraction operator
{
	vSub2f(this->val, v.val);
	return *this;
}
Vector2f Vector2f::operator-=(const float& k)								// unary scalar subtraction operator
{
	vSubScalar2f(this->val, k);
	return *this;	
}
Vector2f Vector2f::operator*=(const Vector2f& v)							// unary multiplication operator (element-wise)
{
	vMul2f(this->val, v.val);
	return *this;
}
Vector2f Vector2f::operator*=(const float& k)								// unary scalar multiplication operator
{
	vMulScalar2f(this->val, k);
	return *this;
}
Vector2f Vector2f::operator/=(const Vector2f& v)							// unary division operator (element-wise)
{
	vDiv2f(this->val, v.val);
	return *this;
}
Vector2f Vector2f::operator/=(const float& k)								// unary scalar division operator
{
	vDivScalar2f(this->val, k);
	return *this;
}

Vector2f Vector2f::operator-()												// unary negation operator
{
	Vector2f temp(*this);
	vNegate2f(temp.val);
	return temp;
}

Vector2f operator+(const Vector2f& a, const Vector2f& b)			// binary addition operator
{
	// 	Vector2f temp;
	// 	vAdd2f(a.val, b.val, temp.val);
	// 	return temp;
	Vector2f temp(a);
	return (temp+=b);
}

Vector2f operator-(const Vector2f& a, const Vector2f& b)			// binary subtraction operator
{
	Vector2f temp(a);
	return (temp-=b);
}

Vector2f operator*(const Vector2f& a, const Vector2f& b)			// binary multiplication operator (element-wise)
{
	Vector2f temp(a);
	return (temp*=b);
}

Vector2f operator*(const Vector2f& v, const float& k)			// binary scalar multiplication operator
{
	Vector2f temp(v);
	return (temp*=k);
}

Vector2f operator*(const float& k, const Vector2f& v)			// binary scalar multiplication operator
{
	Vector2f temp(v);
	return (temp*=k);
}

Vector2f operator/(const Vector2f& a, const Vector2f& b)			// binary division operator (element-wise)
{
	Vector2f temp(a);
	return (temp/=b);
}

Vector2f operator/(const Vector2f& v, const float& k)			// binary scalar division operator
{
	Vector2f temp(v);
	return (temp/=k);
}

Vector2f operator/(const float& k, const Vector2f& v)			// binary scalar division operator
{
	Vector2f temp(v);
	return (temp/=k);
}


// Accessors
float& Vector2f::operator[](int i){ return val[i]; }
float Vector2f::X(){ return val[0]; }
float Vector2f::Y(){ return val[1]; }

void Vector2f::SetX(float nx) { val[0] = nx; }
void Vector2f::SetY(float ny) { val[1] = ny; }
