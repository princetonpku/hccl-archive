#pragma once
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

	// Conversion
public:
	static Quaterniond FromAxisAngle(const double rad, const double axis_x, const double axis_y, const double axis_z);
	static Quaterniond FromMatrix(const double* R);
	static Quaterniond FromMatrix(const double R[3][3]);
	static Quaterniond FromEulerAngle(const double a, const double b, const double c, const char* order);

	static Quaterniond Log(const Quaterniond& q);
	Quaterniond Log(void);
	static Quaterniond Exp(const Quaterniond& a);
	Quaterniond Exp(void);


	// Methods (Algebra)
public:
	static double NormSquared(const Quaterniond& q);					// |q|^2
	double NormSquared();												// |this|^2
	static double Norm(const Quaterniond& q);							// |q|
	double Norm();														// |this|
	static Quaterniond Normalize(Quaterniond& q);					// q / |q|
	Quaterniond Normalize(void);										// this /= |this|
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
	double* GetData();
	double W();
	double X();
	double Y();
	double Z();

	void SetW(double nw);
	void SetX(double nx);
	void SetY(double ny);
	void SetZ(double nz);

public:
	double val[4];
};

Quaterniond operator+(const Quaterniond& a, const Quaterniond& b);		// binary addition operator
Quaterniond operator-(const Quaterniond& a, const Quaterniond& b);		// binary subtraction operator
Quaterniond operator*(const Quaterniond& a, const Quaterniond& b);		// binary multiplication operator (element-wise)
Quaterniond operator*(const Quaterniond& q, const double& k);			// binary scalar multiplication operator
Quaterniond operator*(const double& k, const Quaterniond& q);			// binary scalar multiplication operator
Quaterniond operator/(const Quaterniond& a, const Quaterniond& b);		// binary division operator (element-wise)
Quaterniond operator/(const Quaterniond& q, const double& k);			// binary scalar division operator
Quaterniond operator/(const double& k, const Quaterniond& q);			// binary scalar division operator
Quaterniond operator!(const Quaterniond& q);							// unary inversion operator