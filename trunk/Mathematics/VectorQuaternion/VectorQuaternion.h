#ifndef HCCL_VECTORQUATERNION_H_
#define HCCL_VECTORQUATERNION_H_

#include <memory>
#include <math.h>
#include <algorithm>

#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
#define DEG2RAD M_PI/180.0
#endif
#ifndef RAD2DEG
#define RAD2DEG 180.0/M_PI
#endif

#define Vector3d Vector3<double>
#define Vector3f Vector3<float>
#define Vector3i Vector3<int>
#define Vector2d Vector2<double>			// TODO
#define Vector2f Vector2<float>				// TODO
#define Vector2i Vector2<int>				// TODO
#define Quaterniond Quaternion<double>		// TODO
#define Quaternionf Quaternion<float>		// TODO

template<class T> class Quaternion;

template <class T>
class Vector3
{
// Constructors
public:
	Vector3()															// zero vector
	{
		memset(val, 0, sizeof(T)*3);
	}
	Vector3(T x, T y, T z)												// (x, y, z)
	{
		val[0] = x;	val[1] = y;	val[2] = z;
	}
	Vector3(T* xyz)														// (xyz[0], xyz[1], xyz[2])
	{
		memcpy(val, xyz, sizeof(T)*3);
	}
	Vector3(const Vector3<T>& v)										// copy constructor
	{
		memcpy(this->val, v.val, sizeof(T)*3);
	}
	Vector3(const Quaternion<T>& q)										// typecast constructor
	{
		memcpy(this->val, q.val+1, sizeof(T)*3);
	}
	~Vector3(){}

// Methods (Algebra)
public:
	T Dot(const Vector3<T>& v) const									// this . v
	{
		return this->val[0]*v.val[0] + this->val[1]*v.val[1] + this->val[2]*v.val[2];
	}
	Vector3<T> Cross(const Vector3<T>& v) const							// this x v
	{
		return Vector3<T>(this->val[1]*v.val[2] - this->val[2]*v.val[1],
			this->val[2]*v.val[0] - this->val[0]*v.val[2],
			this->val[0]*v.val[1] - this->val[1]*v.val[0]);
	}
	T NormSquared() const												// |this|^2
	{
		return this->val[0]*this->val[0] + this->val[1]*this->val[1] + this->val[2]*this->val[2];
	}
	T Norm() const														// |this|
	{
		return sqrt(this->val[0]*this->val[0] + this->val[1]*this->val[1] + this->val[2]*this->val[2]);
	}
	Vector3<T> Normalize(void)											// this /= |this|
	{
		double n = this->Norm();
		this->val[0] /= n; this->val[1] /= n; this->val[2] /= n;
		return *this;
	}

	Vector3<T> Add(const Vector3<T>& v)									// this += v
	{
		this->val[0] += v[0];		this->val[1] += v[1];		this->val[2] += v[2];
		return *this;
	}
	Vector3<T> Add(const T& k)											// this += k
	{
		this->val[0] += k;		this->val[1] += k;		this->val[2] += k;
		return *this;
	}
	Vector3<T> Sub(const Vector3<T>& v)									// this -= v
	{
		this->val[0] -= v[0];		this->val[1] -= v[1];		this->val[2] -= v[2];
		return *this;
	}
	Vector3<T> Sub(const T& k)											// this -= k
	{
		this->val[0] -= k;		this->val[1] -= k;		this->val[2] -= k;
		return *this;
	}
	Vector3<T> Mul(const Vector3<T>& v)									// this *= v (element-wise)
	{
		this->val[0] *= v[0];		this->val[1] *= v[1];		this->val[2] *= v[2];
		return *this;
	}
	Vector3<T> Mul(const T& k)											// this *= k
	{
		this->val[0] *= k;		this->val[1] *= k;		this->val[2] *= k;
		return *this;
	}
	Vector3<T> Div(const Vector3<T>& v)									// this /= v (element-wise)
	{
		this->val[0] /= v[0];		this->val[1] /= v[1];		this->val[2] /= v[2];
		return *this;
	}
	Vector3<T> Div(const T& k)											// this /= k
	{
		this->val[0] /= k;		this->val[1] /= k;		this->val[2] /= k;
		return *this;
	}

// Operators
public:
	Vector3<T> operator=(const Vector3<T>& v)							// assign operator
	{
		memcpy(this->val, v.val, sizeof(double)*3);
	}

	bool operator==(const Vector3<T>& v) const							// compare operator
	{
		return (this->val[0] == v.val[0] && this->val[1] == v.val[1] && this->val[2] == v.val[2]);
	}
	bool operator!=(const Vector3<T>& v) const							// negative compare operator
	{	
		return (this->val[0] != v.val[0] || this->val[1] != v.val[1] || this->val[2] != v.val[2]);
	}

	Vector3<T> operator+=(const Vector3<T>& v)							// unary addition operator
	{
		this->val[0] += v[0];		this->val[1] += v[1];		this->val[2] += v[2];
		return *this;
	}
	Vector3<T> operator+=(const T& k)									// unary scalar addition operator
	{
		this->val[0] += k;		this->val[1] += k;		this->val[2] += k;
		return *this;
	}
	Vector3<T> operator-=(const Vector3<T>& v)							// unary subtraction operator
	{
		this->val[0] -= v[0];		this->val[1] -= v[1];		this->val[2] -= v[2];
		return *this;
	}
	Vector3<T> operator-=(const T& k)									// unary scalar subtraction operator
	{
		this->val[0] -= k;		this->val[1] -= k;		this->val[2] -= k;
		return *this;
	}
	Vector3<T> operator*=(const Vector3<T>& v)							// unary multiplication operator (element-wise)
	{
		this->val[0] *= v[0];		this->val[1] *= v[1];		this->val[2] *= v[2];
		return *this;
	}
	Vector3<T> operator*=(const T& k)									// unary scalar multiplication operator
	{
		this->val[0] *= k;		this->val[1] *= k;		this->val[2] *= k;
		return *this;
	}
	Vector3<T> operator/=(const Vector3<T>& v)							// unary division operator (element-wise)
	{
		this->val[0] /= v[0];		this->val[1] /= v[1];		this->val[2] /= v[2];
		return *this;
	}
	Vector3<T> operator/=(const T& k)									// unary scalar division operator
	{
		this->val[0] /= k;		this->val[1] /= k;		this->val[2] /= k;
		return *this;
	}

	Vector3<T> operator-() const										// unary negation operator
	{
		return Vector3<T>(-this->val[0], -this->val[1], -this->val[2]);
	}



// Methods (Geometry)
public:
	Vector3<T> Rotate(const T rad, const Vector3<T>& axis)				// rotate this vector by given angle(rad) along the axis(must be unit)
	{
	}
	Vector3<T> Rotate(const Vector3<T>& axis)							// rotate this vector by given angle(norm of axis) along the axis
	{
	}
	Vector3<T> Rotate(const T* R)										// rotate this vector by multiplying the rotation matrix R (column-stacked)
	{
	}
	Vector3<T> Rotate(const Quaternion<T>& q)
	{
	}
	Vector3<T> Translate(const Vector3<T>& dx)							// this += dx
	{
	}
	Vector3<T> Translate(const T mag, const Vector3<T>& dir)			// this += mag*dir
	{
	}

	static T Angle(const Vector3<T>& a, const Vector3<T>& b)			// get angle between two vectors
	{
	}
	T Angle(const Vector3<T>& a)										// get angle between this and a
	{
	}


// Methods (Auxiliary)
	template <class T> friend std::istream& operator>>(std::istream& is, Vector3<T>& v)
	{
		char str[1024];
		char* tok;
		is >> str;
		tok = strtok(str, " ,()<>[]|:");
		v.val[0] = (T)atof(tok);
		tok = strtok(NULL, " ,()<>[]|:");
		v.val[1] = (T)atof(tok);
		tok = strtok(NULL, " ,()<>[]|:");
		v.val[2] = (T)atof(tok);
		return is;
	}
	template <class T> friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
	{
		os << "(" << v.val[0] << ", " << v.val[1] << ", " << v.val[2] << ")";
		return os;
	}

// Accessors
public:
	T& operator[](int i)	{	return val[i];	}
	T X() const				{	return val[0];	}
	T Y() const				{	return val[1];	}
	T Z() const				{	return val[2];	}

	void SetX(T nx)			{	val[0] = nx;	}
	void SetY(T ny)			{	val[1] = ny;	}
	void SetZ(T nz)			{	val[2] = nz;	}

public:
	T val[3];
};

template <class T> inline T Dot(const Vector3<T>& a, const Vector3<T>& b)					// a . b
{
	return sqrt(a.val[0]*b.val[0] + a.val[1]*b.val[1] + a.val[2]*b.val[2]);
}
template <class T> inline Vector3<T> Cross(const Vector3<T>& a, const Vector3<T>& b)		// a x b
{
	return Vector3<T>(a.val[1]*b.val[2] - a.val[2]*b.val[1],
		a.val[2]*b.val[0] - a.val[0]*b.val[2],
		a.val[0]*b.val[1] - a.val[1]*b.val[0]);
}
template <class T> inline T NormSquared(const Vector3<T>& v)								// |v|^2
{
	return v.val[0]*v.val[0] + v.val[1]*v.val[1] + v.val[2]*v.val[2];
}
template <class T> inline T Norm(const Vector3<T>& v)										// |v|
{
	return sqrt(v.val[0]*v.val[0] + v.val[1]*v.val[1] + v.val[2]*v.val[2]);
}
template <class T> inline Vector3<T> Normalize(Vector3<T>& v)								// v / |v|
{
	double n = Norm(v);
	v.val[0] /= n; v.val[1] /= n; v.val[2] /= n;
	return v;
}

template <class T> inline Vector3<T> Add(const Vector3<T>& a, const Vector3<T>& b)			// a + b
{
	return Vector3<T>(a.val[0] + b.val[0], a.val[1] + b.val[1], a.val[2] + b.val[2]);
}
template <class T> inline Vector3<T> Add(const Vector3<T>& a, const T& k)					// a + k
{
	return Vector3<T>(a.val[0] + k, a.val[1] + k, a.val[2] + k);
}
template <class T> inline Vector3<T> Add(const T& k, const Vector3<T>& a)					// k + a
{
	return Vector3<T>(a.val[0] + k, a.val[1] + k, a.val[2] + k);
}
template <class T> inline Vector3<T> Sub(const Vector3<T>& a, const Vector3<T>& b)			// a - b
{
	return Vector3<T>(a.val[0] - b.val[0], a.val[1] - b.val[1], a.val[2] - b.val[2]);
}
template <class T> inline Vector3<T> Sub(const Vector3<T>& a, const T& k)					// a - k
{
	return Vector3<T>(a.val[0] - k, a.val[1] - k, a.val[2] - k);
}
template <class T> inline Vector3<T> Sub(const T& k, const Vector3<T>& a)					// k - a
{
	return Vector3<T>(k - a.val[0], k - a.val[1], k - a.val[2]);
}
template <class T> inline Vector3<T> Mul(const Vector3<T>& a, const Vector3<T>& b)			// a * b (element-wise)
{
	return Vector3<T>(a.val[0] * b.val[0], a.val[1] * b.val[1], a.val[2] * b.val[2]);
}
template <class T> inline Vector3<T> Mul(const Vector3<T>& a, const T& k)					// a * k
{
	return Vector3<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k);
}
template <class T> inline Vector3<T> Mul(const T& k, const Vector3<T>& a)					// k * a
{
	return Vector3<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k);
}
template <class T> inline Vector3<T> Div(const Vector3<T>& a, const Vector3<T>& b)			// a / b (element-wise)
{
	return Vector3<T>(a.val[0] / b.val[0], a.val[1] / b.val[1], a.val[2] / b.val[2]);
}
template <class T> inline Vector3<T> Div(const Vector3<T>& a, const T& k)					// a / k
{
	return Vector3<T>(a.val[0] / k, a.val[1] / k, a.val[2] / k);
}
template <class T> inline Vector3<T> Div(const T& k, const Vector3<T>& a)					// (k / a_x, k / a_y, k / a_z)
{
	return Vector3<T>(k / a.val[0], k / a.val[1], k / a.val[2]);
}

template <class T> inline Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b)	// binary addition operator
{
	return Vector3<T>(a.val[0] + b.val[0], a.val[1] + b.val[1], a.val[2] + b.val[2]);
}
template <class T> inline Vector3<T> operator+(const Vector3<T>& a, const T& k)				// binary scalar addition operator
{
	return Vector3<T>(a.val[0] + k, a.val[1] + k, a.val[2] + k);
}
template <class T> inline Vector3<T> operator+(const T& k, const Vector3<T>& a)				// binary scalar addition operator
{
	return Vector3<T>(a.val[0] + k, a.val[1] + k, a.val[2] + k);
}
template <class T> inline Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b)	// binary subtraction operator
{
	return Vector3<T>(a.val[0] - b.val[0], a.val[1] - b.val[1], a.val[2] - b.val[2]);
}
template <class T> inline Vector3<T> operator-(const Vector3<T>& a, const T& k)				// binary scalar subtraction operator
{
	return Vector3<T>(a.val[0] - k, a.val[1] - k, a.val[2] - k);
}
template <class T> inline Vector3<T> operator-(const T& k, const Vector3<T>& a)				// binary scalar subtraction operator
{
	return Vector3<T>(k - a.val[0], k - a.val[1], k - a.val[2]);
}
template <class T> inline Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b)	// binary multiplication operator (element-wise)
{
	return Vector3<T>(a.val[0] * b.val[0], a.val[1] * b.val[1], a.val[2] * b.val[2]);
}
template <class T> inline Vector3<T> operator*(const Vector3<T>& v, const T& k)				// binary scalar multiplication operator
{
	return Vector3<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k);
}
template <class T> inline Vector3<T> operator*(const T& k, const Vector3<T>& v)				// binary scalar multiplication operator
{
	return Vector3<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k);
}
template <class T> inline Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b)	// binary division operator (element-wise)
{
	return Vector3<T>(a.val[0] / b.val[0], a.val[1] / b.val[1], a.val[2] / b.val[2]);
}
template <class T> inline Vector3<T> operator/(const Vector3<T>& v, const T& k)				// binary scalar division operator
{
	return Vector3<T>(a.val[0] / k, a.val[1] / k, a.val[2] / k);
}
template <class T> inline Vector3<T> operator/(const T& k, const Vector3<T>& v)				// binary scalar division operator
{
	return Vector3<T>(k / a.val[0], k / a.val[1], k / a.val[2]);
}


#endif // HCCL_VECTORQUATERNION_H_