#pragma once
#include "../VectorAlgebra/Vector.h"
#include "QuaternionAlgebra.h"

class Quaterniond
{
public:
	Quaterniond(void);													// Identity quaternion (1, 0, 0, 0)
	Quaterniond(double w, double x, double y, double z);				// (w, x, y, z)
	Quaterniond(double* wxyz);											// (wxyz[0], wxyz[1], wxyz[2], wxyz[3])
	Quaterniond(const Quaterniond& q);									// copy constructor
	// TODO: axis-angle constructor
	// TODO: rotation matrix constructor
	// TODO: Euler angle constructor
	~Quaterniond(void);
	
// Methods (Algebra)
public:
	static double NormSquared(const Quaterniond& v);					// |q|^2
	double NormSquared();												// |this|^2
	static double Norm(const Quaterniond& v);							// |q|
	double Norm();														// |this|
	static Quaterniond Add(const Quaterniond& a, const Quaterniond& b);	// a + b
	Quaterniond Add(const Quaterniond& q);								// this += q
	static Quaterniond Sub(const Quaterniond& a, const Quaterniond& b);	// a - b
	Quaterniond Sub(const Quaterniond& q);								// this -= q
	static Quaterniond Mul(const Quaterniond& a, const Quaterniond& b);	// a * b
	Quaterniond Mul(const Quaterniond& q);								// this *= q
	static Quaterniond Mul(const Quaterniond& a, const double& k);		// a * k
	Quaterniond Mul(const double& k);									// this *= k
	static Quaterniond Div(const Quaterniond& a, const Quaterniond& b);	// a / b
	Quaterniond Div(const Quaterniond& q);								// this /= q
	static Quaterniond Div(const Quaterniond& a, const double& k);		// a / k
	Quaterniond Div(const double& k);									// this /= k

	// Operators
public:
	Quaterniond operator=(const Quaterniond& v);						// assign operator

	bool operator==(const Quaterniond& v);								// compare operator
	bool operator!=(const Quaterniond& v);								// negative compare operator

	Quaterniond operator+=(const Quaterniond& v);						// unary addition operator
	Quaterniond operator-=(const Quaterniond& v);						// unary subtraction operator
	Quaterniond operator*=(const Quaterniond& v);						// unary multiplication operator (element-wise)
	Quaterniond operator*=(const double& k);							// unary scalar multiplication operator
	Quaterniond operator/=(const Quaterniond& v);						// unary division operator (element-wise)
	Quaterniond operator/=(const double& k);							// unary scalar division operator

	Quaterniond operator-();											// unary negation operator


	// Accessors
public:
	double& operator[](int i);
	double W();
	double X();
	double Y();
	double Z();

	void SetW(double nw);
	void SetX(double nx);
	void SetY(double ny);
	void SetZ(double nz);


protected:
	double val[4];
};

Quaterniond& operator+(const Quaterniond& a, const Quaterniond& b);		// binary addition operator
Quaterniond& operator-(const Quaterniond& a, const Quaterniond& b);		// binary subtraction operator
Quaterniond& operator*(const Quaterniond& a, const Quaterniond& b);		// binary multiplication operator (element-wise)
Quaterniond& operator*(const Quaterniond& v, const double& k);			// binary scalar multiplication operator
Quaterniond& operator*(const double& k, const Quaterniond& v);			// binary scalar multiplication operator
Quaterniond& operator/(const Quaterniond& a, const Quaterniond& b);		// binary division operator (element-wise)
Quaterniond& operator/(const Quaterniond& v, const double& k);			// binary scalar division operator
Quaterniond& operator/(const double& k, const Quaterniond& v);			// binary scalar division operator