#pragma once
#include "VectorAlgebra.h"

class Vector3f;
class Vector2d;
class Vector2f;

class Vector3d
{
public:
	Vector3d(void);													// zero vector
	Vector3d(double x, double y, double z);							// (x, y, z)
	Vector3d(double* xyz);											// (xyz[0], xyz[1], xyz[2])
	Vector3d(const Vector3d& v);									// copy constructor

	Vector3d(const Vector3f& v);									// typecast constructor
	Vector3d(const Vector2d& v);									// typecast constructor
	Vector3d(const Vector2f& v);									// typecast constructor
#ifdef Quaterniond
	Vector3d(const Quaterniond& q);									// typecast constructor
#endif
#ifdef Quaternionf
	Vector3d(const Quaternionf& q);									// typecast constructor
#endif

	~Vector3d(void);

	// Methods (Algebra)
public:
	// TODO: Normalize
	static double Dot(const Vector3d& a, const Vector3d& b);		// a . b
	double Dot(const Vector3d& v);									// this . v
	static Vector3d Cross(const Vector3d& a, const Vector3d& b);	// a x b
	Vector3d Cross(const Vector3d& v);								// this x v
	static double NormSquared(const Vector3d& v);					// |v|^2
	double NormSquared();											// |this|^2
	static double Norm(const Vector3d& v);							// |v|
	double Norm();													// |this|
	static Vector3d Normalize(Vector3d& v);							// v / |v|
	Vector3d Normalize(void);										// this /= |this|

	static Vector3d Add(const Vector3d& a, const Vector3d& b);		// a + b
	Vector3d Add(const Vector3d& v);								// this += v
	static Vector3d Add(const Vector3d& a, const double& k);		// a + k
	Vector3d Add(const double& k);									// this += k
	static Vector3d Sub(const Vector3d& a, const Vector3d& b);		// a - b
	Vector3d Sub(const Vector3d& v);								// this -= v
	static Vector3d Sub(const Vector3d& a, const double& k);		// a - k
	Vector3d Sub(const double& k);									// this -= k
	static Vector3d Mul(const Vector3d& a, const Vector3d& b);		// a * b (element-wise)
	Vector3d Mul(const Vector3d& v);								// this *= v (element-wise)
	static Vector3d Mul(const Vector3d& a, const double& k);		// a * k
	Vector3d Mul(const double& k);									// this *= k
	static Vector3d Div(const Vector3d& a, const Vector3d& b);		// a / b (element-wise)
	Vector3d Div(const Vector3d& v);								// this /= v (element-wise)
	static Vector3d Div(const Vector3d& a, const double& k);		// a / k
	Vector3d Div(const double& k);									// this /= k


	// Methods (Geometry)
public:
	Vector3d Rotate(const double rad, const Vector3d& axis);		// rotate this vector by given angle(rad) along the axis(must be unit)
	Vector3d Rotate(const Vector3d& axis);							// rotate this vector by given angle(norm of axis) along the axis
	Vector3d Rotate(const double* R);								// rotate this vector by multiplying the rotation matrix R (column-stacked)
	//Vector3d Rotate(const Quaterniond& q);
	Vector3d Translate(const Vector3d& dx);							// this += dx
	Vector3d Translate(const double mag, const Vector3d& dir);		// this += mag*dir

	static double Angle(const Vector3d& a, const Vector3d& b);		// get angle between two vectors
	double Angle(const Vector3d& a);								// get angle between this and a

	// Operators
public:
	Vector3d operator=(const Vector3d& v);							// assign operator

	bool operator==(const Vector3d& v);								// compare operator
	bool operator!=(const Vector3d& v);								// negative compare operator

	Vector3d operator+=(const Vector3d& v);							// unary addition operator
	Vector3d operator+=(const double& k);							// unary scalar addition operator
	Vector3d operator-=(const Vector3d& v);							// unary subtraction operator
	Vector3d operator-=(const double& k);							// unary scalar subtraction operator
	Vector3d operator*=(const Vector3d& v);							// unary multiplication operator (element-wise)
	Vector3d operator*=(const double& k);							// unary scalar multiplication operator
	Vector3d operator/=(const Vector3d& v);							// unary division operator (element-wise)
	Vector3d operator/=(const double& k);							// unary scalar division operator

	Vector3d operator-();											// unary negation operator


	// Accessors
public:
	double& operator[](int i);
	double X();
	double Y();
	double Z();

	void SetX(double nx);
	void SetY(double nx);
	void SetZ(double nx);

public:
	double val[3];
};

Vector3d operator+(const Vector3d& a, const Vector3d& b);			// binary addition operator
Vector3d operator-(const Vector3d& a, const Vector3d& b);			// binary subtraction operator
Vector3d operator*(const Vector3d& a, const Vector3d& b);			// binary multiplication operator (element-wise)
Vector3d operator*(const Vector3d& v, const double& k);				// binary scalar multiplication operator
Vector3d operator*(const double& k, const Vector3d& v);				// binary scalar multiplication operator
Vector3d operator/(const Vector3d& a, const Vector3d& b);			// binary division operator (element-wise)
Vector3d operator/(const Vector3d& v, const double& k);				// binary scalar division operator
Vector3d operator/(const double& k, const Vector3d& v);				// binary scalar division operator


class Vector3f
{
public:
	Vector3f(void);													// zero vector
	Vector3f(float x, float y, float z);							// (x, y, z)
	Vector3f(float* xyz);											// (xyz[0], xyz[1], xyz[2])
	Vector3f(const Vector3f& v);									// copy constructor

	Vector3f(const Vector3d& v);									// typecast constructor
	Vector3f(const Vector2d& v);									// typecast constructor
	Vector3f(const Vector2f& v);									// typecast constructor
#ifdef Quaterniond
	Vector3f(const Quaterniond& q);									// typecast constructor
#endif
#ifdef Quaternionf
	Vector3f(const Quaternionf& q);									// typecast constructor
#endif

	~Vector3f(void);

	// Methods (Algebra)
public:
	// TODO: Normalize
	static float Dot(const Vector3f& a, const Vector3f& b);			// a . b
	float Dot(const Vector3f& v);									// this . v
	static Vector3f Cross(const Vector3f& a, const Vector3f& b);	// a x b
	Vector3f Cross(const Vector3f& v);								// this x v
	static float NormSquared(const Vector3f& v);					// |v|^2
	float NormSquared();											// |this|^2
	static float Norm(const Vector3f& v);							// |v|
	float Norm();													// |this|
	static Vector3f Normalize(Vector3f& v);							// v / |v|
	Vector3f Normalize(void);										// this /= |this|

	static Vector3f Add(const Vector3f& a, const Vector3f& b);		// a + b
	Vector3f Add(const Vector3f& v);								// this += v
	static Vector3f Add(const Vector3f& a, const float& k);		// a + k
	Vector3f Add(const float& k);									// this += k
	static Vector3f Sub(const Vector3f& a, const Vector3f& b);		// a - b
	Vector3f Sub(const Vector3f& v);								// this -= v
	static Vector3f Sub(const Vector3f& a, const float& k);		// a - k
	Vector3f Sub(const float& k);									// this -= k
	static Vector3f Mul(const Vector3f& a, const Vector3f& b);		// a * b (element-wise)
	Vector3f Mul(const Vector3f& v);								// this *= v (element-wise)
	static Vector3f Mul(const Vector3f& a, const float& k);		// a * k
	Vector3f Mul(const float& k);									// this *= k
	static Vector3f Div(const Vector3f& a, const Vector3f& b);		// a / b (element-wise)
	Vector3f Div(const Vector3f& v);								// this /= v (element-wise)
	static Vector3f Div(const Vector3f& a, const float& k);		// a / k
	Vector3f Div(const float& k);									// this /= k


	// Methods (Geometry)
public:
	Vector3f Rotate(const float rad, const Vector3f& axis);		// rotate this vector by given angle(rad) along the axis(must be unit)
	Vector3f Rotate(const Vector3f& axis);							// rotate this vector by given angle(norm of axis) along the axis
	Vector3f Rotate(const float* R);								// rotate this vector by multiplying the rotation matrix R (column-stacked)
	//Vector3f Rotate(const Quaterniond& q);
	Vector3f Translate(const Vector3f& dx);							// this += dx
	Vector3f Translate(const float mag, const Vector3f& dir);		// this += mag*dir

	static float Angle(const Vector3f& a, const Vector3f& b);		// get angle between two vectors
	float Angle(const Vector3f& a);								// get angle between this and a

	// Operators
public:
	Vector3f operator=(const Vector3f& v);							// assign operator

	bool operator==(const Vector3f& v);								// compare operator
	bool operator!=(const Vector3f& v);								// negative compare operator

	Vector3f operator+=(const Vector3f& v);							// unary addition operator
	Vector3f operator+=(const float& k);							// unary scalar addition operator
	Vector3f operator-=(const Vector3f& v);							// unary subtraction operator
	Vector3f operator-=(const float& k);							// unary scalar subtraction operator
	Vector3f operator*=(const Vector3f& v);							// unary multiplication operator (element-wise)
	Vector3f operator*=(const float& k);							// unary scalar multiplication operator
	Vector3f operator/=(const Vector3f& v);							// unary division operator (element-wise)
	Vector3f operator/=(const float& k);							// unary scalar division operator

	Vector3f operator-();											// unary negation operator


	// Accessors
public:
	float& operator[](int i);
	float X();
	float Y();
	float Z();

	void SetX(float nx);
	void SetY(float nx);
	void SetZ(float nx);

public:
	float val[3];
};

Vector3f operator+(const Vector3f& a, const Vector3f& b);			// binary addition operator
Vector3f operator-(const Vector3f& a, const Vector3f& b);			// binary subtraction operator
Vector3f operator*(const Vector3f& a, const Vector3f& b);			// binary multiplication operator (element-wise)
Vector3f operator*(const Vector3f& v, const float& k);				// binary scalar multiplication operator
Vector3f operator*(const float& k, const Vector3f& v);				// binary scalar multiplication operator
Vector3f operator/(const Vector3f& a, const Vector3f& b);			// binary division operator (element-wise)
Vector3f operator/(const Vector3f& v, const float& k);				// binary scalar division operator
Vector3f operator/(const float& k, const Vector3f& v);				// binary scalar division operator



class Vector2d
{
public:
	Vector2d(void);													// zero vector
	Vector2d(double x, double y);									// (x, y)
	Vector2d(double* xy);											// (xy[0], xy[1])
	Vector2d(const Vector2d& v);									// copy constructor

	Vector2d(const Vector2f& v);									// typecast constructor
	Vector2d(const Vector3d& v);									// typecast constructor
	Vector2d(const Vector3f& v);									// typecast constructor
#ifdef Quaterniond
	Vector2d(const Quaterniond& q);									// typecast constructor
#endif
#ifdef Quaternionf
	Vector2d(const Quaternionf& q);									// typecast constructor
#endif

	~Vector2d(void);

	// Methods (Algebra)
public:
	// TODO: Normalize
	static double Dot(const Vector2d& a, const Vector2d& b);		// a . b
	double Dot(const Vector2d& v);									// this . v
	static double Cross(const Vector2d& a, const Vector2d& b);		// a x b
	double Cross(const Vector2d& v);								// this x b
	static double NormSquared(const Vector2d& v);					// |v|^2
	double NormSquared();											// |this|^2
	static double Norm(const Vector2d& v);							// |v|
	double Norm();													// |this|
	static Vector2d Normalize(Vector2d& v);							// v / |v|
	Vector2d Normalize(void);										// this /= |this|

	static Vector2d Add(const Vector2d& a, const Vector2d& b);		// a + b
	Vector2d Add(const Vector2d& v);								// this += v
	static Vector2d Add(const Vector2d& a, const double& k);		// a + k
	Vector2d Add(const double& k);									// this += k
	static Vector2d Sub(const Vector2d& a, const Vector2d& b);		// a - b
	Vector2d Sub(const Vector2d& v);								// this -= v
	static Vector2d Sub(const Vector2d& a, const double& k);		// a - k
	Vector2d Sub(const double& k);									// this -= k
	static Vector2d Mul(const Vector2d& a, const Vector2d& b);		// a * b (element-wise)
	Vector2d Mul(const Vector2d& v);								// this *= v (element-wise)
	static Vector2d Mul(const Vector2d& a, const double& k);		// a * k
	Vector2d Mul(const double& k);									// this *= k
	static Vector2d Div(const Vector2d& a, const Vector2d& b);		// a / b (element-wise)
	Vector2d Div(const Vector2d& v);								// this /= v (element-wise)
	static Vector2d Div(const Vector2d& a, const double& k);		// a / k
	Vector2d Div(const double& k);									// this /= k


	// Methods (Geometry)
public:
	Vector2d Rotate(const double rad, const Vector2d& axis);		// rotate this vector by given angle(rad) along the axis(must be unit)
	Vector2d Rotate(const Vector2d& axis);							// rotate this vector by given angle(norm of axis) along the axis
	Vector2d Rotate(const double* R);								// rotate this vector by multiplying the rotation matrix R (column-stacked)
	//Vector2d Rotate(const Quaterniond& q);
	Vector2d Translate(const Vector2d& dx);							// this += dx
	Vector2d Translate(const double mag, const Vector2d& dir);		// this += mag*dir

	static double Angle(const Vector2d& a, const Vector2d& b);		// get angle between two vectors
	double Angle(const Vector2d& a);								// get angle between this and a

	// Operators
public:
	Vector2d operator=(const Vector2d& v);							// assign operator

	bool operator==(const Vector2d& v);								// compare operator
	bool operator!=(const Vector2d& v);								// negative compare operator

	Vector2d operator+=(const Vector2d& v);							// unary addition operator
	Vector2d operator+=(const double& k);							// unary scalar addition operator
	Vector2d operator-=(const Vector2d& v);							// unary subtraction operator
	Vector2d operator-=(const double& k);							// unary scalar subtraction operator
	Vector2d operator*=(const Vector2d& v);							// unary multiplication operator (element-wise)
	Vector2d operator*=(const double& k);							// unary scalar multiplication operator
	Vector2d operator/=(const Vector2d& v);							// unary division operator (element-wise)
	Vector2d operator/=(const double& k);							// unary scalar division operator

	Vector2d operator-();											// unary negation operator


	// Accessors
public:
	double& operator[](int i);
	double X();
	double Y();

	void SetX(double nx);
	void SetY(double nx);

public:
	double val[2];
};

Vector2d operator+(const Vector2d& a, const Vector2d& b);			// binary addition operator
Vector2d operator-(const Vector2d& a, const Vector2d& b);			// binary subtraction operator
Vector2d operator*(const Vector2d& a, const Vector2d& b);			// binary multiplication operator (element-wise)
Vector2d operator*(const Vector2d& v, const double& k);				// binary scalar multiplication operator
Vector2d operator*(const double& k, const Vector2d& v);				// binary scalar multiplication operator
Vector2d operator/(const Vector2d& a, const Vector2d& b);			// binary division operator (element-wise)
Vector2d operator/(const Vector2d& v, const double& k);				// binary scalar division operator
Vector2d operator/(const double& k, const Vector2d& v);				// binary scalar division operator


class Vector2f
{
public:
	Vector2f(void);													// zero vector
	Vector2f(float x, float y);									// (x, y)
	Vector2f(float* xy);											// (xy[0], xy[1])
	Vector2f(const Vector2f& v);									// copy constructor

	Vector2f(const Vector2d& v);									// typecast constructor
	Vector2f(const Vector3d& v);									// typecast constructor
	Vector2f(const Vector3f& v);									// typecast constructor
#ifdef Quaterniond
	Vector2f(const Quaterniond& q);									// typecast constructor
#endif
#ifdef Quaternionf
	Vector2f(const Quaternionf& q);									// typecast constructor
#endif

	~Vector2f(void);

	// Methods (Algebra)
public:
	// TODO: Normalize
	static float Dot(const Vector2f& a, const Vector2f& b);		// a . b
	float Dot(const Vector2f& v);									// this . v
	static float Cross(const Vector2f& a, const Vector2f& b);		// a x b
	float Cross(const Vector2f& v);								// this x b
	static float NormSquared(const Vector2f& v);					// |v|^2
	float NormSquared();											// |this|^2
	static float Norm(const Vector2f& v);							// |v|
	float Norm();													// |this|
	static Vector2f Normalize(Vector2f& v);							// v / |v|
	Vector2f Normalize(void);										// this /= |this|

	static Vector2f Add(const Vector2f& a, const Vector2f& b);		// a + b
	Vector2f Add(const Vector2f& v);								// this += v
	static Vector2f Add(const Vector2f& a, const float& k);		// a + k
	Vector2f Add(const float& k);									// this += k
	static Vector2f Sub(const Vector2f& a, const Vector2f& b);		// a - b
	Vector2f Sub(const Vector2f& v);								// this -= v
	static Vector2f Sub(const Vector2f& a, const float& k);		// a - k
	Vector2f Sub(const float& k);									// this -= k
	static Vector2f Mul(const Vector2f& a, const Vector2f& b);		// a * b (element-wise)
	Vector2f Mul(const Vector2f& v);								// this *= v (element-wise)
	static Vector2f Mul(const Vector2f& a, const float& k);		// a * k
	Vector2f Mul(const float& k);									// this *= k
	static Vector2f Div(const Vector2f& a, const Vector2f& b);		// a / b (element-wise)
	Vector2f Div(const Vector2f& v);								// this /= v (element-wise)
	static Vector2f Div(const Vector2f& a, const float& k);		// a / k
	Vector2f Div(const float& k);									// this /= k


	// Methods (Geometry)
public:
	Vector2f Rotate(const float rad, const Vector2f& axis);		// rotate this vector by given angle(rad) along the axis(must be unit)
	Vector2f Rotate(const Vector2f& axis);							// rotate this vector by given angle(norm of axis) along the axis
	Vector2f Rotate(const float* R);								// rotate this vector by multiplying the rotation matrix R (column-stacked)
	//Vector2f Rotate(const Quaterniond& q);
	Vector2f Translate(const Vector2f& dx);							// this += dx
	Vector2f Translate(const float mag, const Vector2f& dir);		// this += mag*dir

	static float Angle(const Vector2f& a, const Vector2f& b);		// get angle between two vectors
	float Angle(const Vector2f& a);								// get angle between this and a

	// Operators
public:
	Vector2f operator=(const Vector2f& v);							// assign operator

	bool operator==(const Vector2f& v);								// compare operator
	bool operator!=(const Vector2f& v);								// negative compare operator

	Vector2f operator+=(const Vector2f& v);							// unary addition operator
	Vector2f operator+=(const float& k);							// unary scalar addition operator
	Vector2f operator-=(const Vector2f& v);							// unary subtraction operator
	Vector2f operator-=(const float& k);							// unary scalar subtraction operator
	Vector2f operator*=(const Vector2f& v);							// unary multiplication operator (element-wise)
	Vector2f operator*=(const float& k);							// unary scalar multiplication operator
	Vector2f operator/=(const Vector2f& v);							// unary division operator (element-wise)
	Vector2f operator/=(const float& k);							// unary scalar division operator

	Vector2f operator-();											// unary negation operator


	// Accessors
public:
	float& operator[](int i);
	float X();
	float Y();

	void SetX(float nx);
	void SetY(float nx);

public:
	float val[2];
};

Vector2f operator+(const Vector2f& a, const Vector2f& b);			// binary addition operator
Vector2f operator-(const Vector2f& a, const Vector2f& b);			// binary subtraction operator
Vector2f operator*(const Vector2f& a, const Vector2f& b);			// binary multiplication operator (element-wise)
Vector2f operator*(const Vector2f& v, const float& k);				// binary scalar multiplication operator
Vector2f operator*(const float& k, const Vector2f& v);				// binary scalar multiplication operator
Vector2f operator/(const Vector2f& a, const Vector2f& b);			// binary division operator (element-wise)
Vector2f operator/(const Vector2f& v, const float& k);				// binary scalar division operator
Vector2f operator/(const float& k, const Vector2f& v);				// binary scalar division operator