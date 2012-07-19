#pragma once

class Vector3d
{
public:
	Vector3d(void);													// zero vector
	Vector3d(double x, double y, double z);							// (x, y, z)
	Vector3d(double* xyz);											// (xyz[0], xyz[1], xyz[2])
	Vector3d(const double& v);										// copy constructor
	~Vector3d(void);

// Methods (Algebra)
public:
	static double Dot(const Vector3d& a, const Vector3d& b);		// a . b
	double Dot(const Vector3d& v);									// this . v
	static Vector3d Cross(const Vector3d& a, const Vector3d& b);	// a x b
	static double NormSquared(const Vector3d& v);					// |v|^2
	double NormSquared();											// |this|^2
	static double Norm(const Vector3d& v);							// |v|
	double Norm();													// |this|
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
	Vector3d Rotate(const double rad, const Vector3d& axis);
	Vector3d Rotate(const double* R);
	//Vector3d Rotate(const Quaterniond& q);
	Vector3d Translate(const Vector3d& dx);							// this += dx
	Vector3d Translate(const double mag, const Vector3d& dir);		// this += mag*dir

// Operators
public:
	Vector3d operator=(const Vector3d& v);

	bool operator==(const Vector3d& v);
	bool operator!=(const Vector3d& v);

	Vector3d operator+=(const Vector3d& v);
	Vector3d operator-=(const Vector3d& v);
	Vector3d operator*=(const Vector3d& v);
	Vector3d operator*=(const double& k);
	Vector3d operator/=(const Vector3d& v);
	Vector3d operator/=(const double& v);

	Vector3d operator-();											// negation operator

	Vector3d operator+(const Vector3d& v);
	Vector3d operator-(const Vector3d& v);
	Vector3d operator*(const Vector3d& v);
	Vector3d operator/(const Vector3d& v);


// Accessors
public:
	double& operator[](int i){ return val[i]; }
	double X(){ return val[0]; }
	double Y(){ return val[0]; }
	double Z(){ return val[0]; }

protected:
	double val[3];
};

Vector3d& operator+(const Vector3d& a, const Vector3d& b);
Vector3d& operator-(const Vector3d& a, const Vector3d& b);
Vector3d& operator*(const Vector3d& a, const Vector3d& b);
Vector3d& operator*(const Vector3d& v, const double& k);
Vector3d& operator*(const double& k, const Vector3d& v);
Vector3d& operator/(const Vector3d& a, const Vector3d& b);
Vector3d& operator/(const Vector3d& v, const double& k);
Vector3d& operator/(const double& k, const Vector3d& v);