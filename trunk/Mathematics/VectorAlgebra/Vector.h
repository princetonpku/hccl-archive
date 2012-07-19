#pragma once
#include "VectorAlgebra.h"

class Vector3d
{
public:
	Vector3d(void);													// zero vector
	Vector3d(double x, double y, double z);							// (x, y, z)
	Vector3d(double* xyz);											// (xyz[0], xyz[1], xyz[2])
	Vector3d(const Vector3d& v);									// copy constructor
	~Vector3d(void);

	// Methods (Algebra)
public:
	// TODO: Normalize
	static double Dot(const Vector3d& a, const Vector3d& b);		// a . b
	double Dot(const Vector3d& v);									// this . v
	static Vector3d Cross(const Vector3d& a, const Vector3d& b);	// a x b
	static double NormSquared(const Vector3d& v);					// |v|^2
	double NormSquared();											// |this|^2
	static double Norm(const Vector3d& v);							// |v|
	double Norm();													// |this|
	static Vector3d Normalize(Vector3d& v);					// v / |v|
	Vector3d Normalize(void);										// this /= |this|

	static Vector3d Add(const Vector3d& a, const Vector3d& b);		// a + b
	Vector3d Add(const Vector3d& v);								// this += v
	static Vector3d Sub(const Vector3d& a, const Vector3d& b);		// a - b
	Vector3d Sub(const Vector3d& v);								// this -= v
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
	Vector3d operator-=(const Vector3d& v);							// unary subtraction operator
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
Vector3d operator*(const Vector3d& v, const double& k);			// binary scalar multiplication operator
Vector3d operator*(const double& k, const Vector3d& v);			// binary scalar multiplication operator
Vector3d operator/(const Vector3d& a, const Vector3d& b);			// binary division operator (element-wise)
Vector3d operator/(const Vector3d& v, const double& k);			// binary scalar division operator
Vector3d operator/(const double& k, const Vector3d& v);			// binary scalar division operator