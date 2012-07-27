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

template<class T> class Vector2;
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
		this->val[0] += v.val[0];		this->val[1] += v.val[1];		this->val[2] += v.val[2];
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

typedef Vector3<int>	Vector3i;
typedef Vector3<float>	Vector3f;
typedef Vector3<double>	Vector3d;


template <class T>
class Vector2
{
	// Constructors
public:
	Vector2()															// zero vector
	{
		memset(val, 0, sizeof(T)*2);
	}
	Vector2(T x, T y)													// (x, y)
	{
		val[0] = x;	val[1] = y;
	}
	Vector2(T* xy)														// (xy[0], xy[1])
	{
		memcpy(val, xyz, sizeof(T)*2);
	}
	Vector2(const Vector2<T>& v)										// copy constructor
	{
		memcpy(this->val, v.val, sizeof(T)*2);
	}
	Vector2(const Quaternion<T>& q)										// typecast constructor
	{
		memcpy(this->val, q.val+1, sizeof(T)*2);
	}
	~Vector2(){}

	// Methods (Algebra)
public:
	T Dot(const Vector2<T>& v) const									// this . v
	{
		return this->val[0]*v.val[0] + this->val[1]*v.val[1];
	}
	T Cross(const Vector2<T>& v) const									// this x v
	{
		return this->val[0]*v.val[1] - this->val[1]*v.val[0];			
	}
	T NormSquared() const												// |this|^2
	{
		return this->val[0]*this->val[0] + this->val[1]*this->val[1];
	}
	T Norm() const														// |this|
	{
		return sqrt(this->val[0]*this->val[0] + this->val[1]*this->val[1]);
	}
	Vector2<T> Normalize(void)											// this /= |this|
	{
		double n = this->Norm();
		this->val[0] /= n; this->val[1] /= n;
		return *this;
	}

	Vector2<T> Add(const Vector2<T>& v)									// this += v
	{
		this->val[0] += v.val[0];		this->val[1] += v.val[1];
		return *this;
	}
	Vector2<T> Add(const T& k)											// this += k
	{
		this->val[0] += k;		this->val[1] += k;
		return *this;
	}
	Vector2<T> Sub(const Vector2<T>& v)									// this -= v
	{
		this->val[0] -= v.val[0];		this->val[1] -= v.val[1];
		return *this;
	}
	Vector2<T> Sub(const T& k)											// this -= k
	{
		this->val[0] -= k;		this->val[1] -= k;
		return *this;
	}
	Vector2<T> Mul(const Vector2<T>& v)									// this *= v (element-wise)
	{
		this->val[0] *= v.val[0];		this->val[1] *= v.val[1];
		return *this;
	}
	Vector2<T> Mul(const T& k)											// this *= k
	{
		this->val[0] *= k;		this->val[1] *= k;
		return *this;
	}
	Vector2<T> Div(const Vector2<T>& v)									// this /= v (element-wise)
	{
		this->val[0] /= v.val[0];		this->val[1] /= v.val[1];
		return *this;
	}
	Vector2<T> Div(const T& k)											// this /= k
	{
		this->val[0] /= k;		this->val[1] /= k;
		return *this;
	}

	// Operators
public:
	Vector2<T> operator=(const Vector2<T>& v)							// assign operator
	{
		memcpy(this->val, v.val, sizeof(double)*2);
	}

	bool operator==(const Vector2<T>& v) const							// compare operator
	{
		return (this->val[0] == v.val[0] && this->val[1] == v.val[1]);
	}
	bool operator!=(const Vector2<T>& v) const							// negative compare operator
	{	
		return (this->val[0] != v.val[0] || this->val[1] != v.val[1]);
	}

	Vector2<T> operator+=(const Vector2<T>& v)							// unary addition operator
	{
		this->val[0] += v.val[0];		this->val[1] += v.val[1];
		return *this;
	}
	Vector2<T> operator+=(const T& k)									// unary scalar addition operator
	{
		this->val[0] += k;		this->val[1] += k;
		return *this;
	}
	Vector2<T> operator-=(const Vector2<T>& v)							// unary subtraction operator
	{
		this->val[0] -= v.val[0];		this->val[1] -= v.val[1];
		return *this;
	}
	Vector2<T> operator-=(const T& k)									// unary scalar subtraction operator
	{
		this->val[0] -= k;		this->val[1] -= k;
		return *this;
	}
	Vector2<T> operator*=(const Vector2<T>& v)							// unary multiplication operator (element-wise)
	{
		this->val[0] *= v.val[0];		this->val[1] *= v.val[1];
		return *this;
	}
	Vector2<T> operator*=(const T& k)									// unary scalar multiplication operator
	{
		this->val[0] *= k;		this->val[1] *= k;
		return *this;
	}
	Vector2<T> operator/=(const Vector2<T>& v)							// unary division operator (element-wise)
	{
		this->val[0] /= v.val[0];		this->val[1] /= v.val[1];
		return *this;
	}
	Vector2<T> operator/=(const T& k)									// unary scalar division operator
	{
		this->val[0] /= k;		this->val[1] /= k;
		return *this;
	}

	Vector2<T> operator-() const										// unary negation operator
	{
		return Vector2<T>(-this->val[0], -this->val[1]);
	}



	// Methods (Geometry)
public:
	Vector2<T> Rotate(const T rad, const Vector2<T>& axis)				// rotate this vector by given angle(rad) along the axis(must be unit)
	{
	}
	Vector2<T> Rotate(const Vector2<T>& axis)							// rotate this vector by given angle(norm of axis) along the axis
	{
	}
	Vector2<T> Rotate(const T* R)										// rotate this vector by multiplying the rotation matrix R (column-stacked)
	{
	}
	Vector2<T> Rotate(const Quaternion<T>& q)
	{
	}
	Vector2<T> Translate(const Vector2<T>& dx)							// this += dx
	{
	}
	Vector2<T> Translate(const T mag, const Vector2<T>& dir)			// this += mag*dir
	{
	}

	static T Angle(const Vector2<T>& a, const Vector2<T>& b)			// get angle between two vectors
	{
	}
	T Angle(const Vector2<T>& a)										// get angle between this and a
	{
	}


	// Methods (Auxiliary)
	template <class T> friend std::istream& operator>>(std::istream& is, Vector2<T>& v)
	{
		char str[1024];
		char* tok;
		is >> str;
		tok = strtok(str, " ,()<>[]|:");
		v.val[0] = (T)atof(tok);
		tok = strtok(NULL, " ,()<>[]|:");
		v.val[1] = (T)atof(tok);		
		return is;
	}
	template <class T> friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
	{
		os << "(" << v.val[0] << ", " << v.val[1] << ")";
		return os;
	}

	// Accessors
public:
	T& operator[](int i)	{	return val[i];	}
	T X() const				{	return val[0];	}
	T Y() const				{	return val[1];	}	

	void SetX(T nx)			{	val[0] = nx;	}
	void SetY(T ny)			{	val[1] = ny;	}	

public:
	T val[2];
};

template <class T> inline T Dot(const Vector2<T>& a, const Vector2<T>& b)					// a . b
{
	return sqrt(a.val[0]*b.val[0] + a.val[1]*b.val[1]);
}
template <class T> inline T NormSquared(const Vector2<T>& v)								// |v|^2
{
	return v.val[0]*v.val[0] + v.val[1]*v.val[1];
}
template <class T> inline T Norm(const Vector2<T>& v)										// |v|
{
	return sqrt(v.val[0]*v.val[0] + v.val[1]*v.val[1]);
}
template <class T> inline Vector2<T> Normalize(Vector2<T>& v)								// v / |v|
{
	double n = Norm(v);
	v.val[0] /= n; v.val[1] /= n;
	return v;
}

template <class T> inline Vector2<T> Add(const Vector2<T>& a, const Vector2<T>& b)			// a + b
{
	return Vector2<T>(a.val[0] + b.val[0], a.val[1] + b.val[1]);
}
template <class T> inline Vector2<T> Add(const Vector2<T>& a, const T& k)					// a + k
{
	return Vector2<T>(a.val[0] + k, a.val[1] + k);
}
template <class T> inline Vector2<T> Add(const T& k, const Vector2<T>& a)					// k + a
{
	return Vector2<T>(a.val[0] + k, a.val[1] + k);
}
template <class T> inline Vector2<T> Sub(const Vector2<T>& a, const Vector2<T>& b)			// a - b
{
	return Vector2<T>(a.val[0] - b.val[0], a.val[1] - b.val[1]);
}
template <class T> inline Vector2<T> Sub(const Vector2<T>& a, const T& k)					// a - k
{
	return Vector2<T>(a.val[0] - k, a.val[1] - k);
}
template <class T> inline Vector2<T> Sub(const T& k, const Vector2<T>& a)					// k - a
{
	return Vector2<T>(k - a.val[0], k - a.val[1]);
}
template <class T> inline Vector2<T> Mul(const Vector2<T>& a, const Vector2<T>& b)			// a * b (element-wise)
{
	return Vector2<T>(a.val[0] * b.val[0], a.val[1] * b.val[1]);
}
template <class T> inline Vector2<T> Mul(const Vector2<T>& a, const T& k)					// a * k
{
	return Vector2<T>(a.val[0] * k, a.val[1] * k);
}
template <class T> inline Vector2<T> Mul(const T& k, const Vector2<T>& a)					// k * a
{
	return Vector2<T>(a.val[0] * k, a.val[1] * k);
}
template <class T> inline Vector2<T> Div(const Vector2<T>& a, const Vector2<T>& b)			// a / b (element-wise)
{
	return Vector2<T>(a.val[0] / b.val[0], a.val[1] / b.val[1]);
}
template <class T> inline Vector2<T> Div(const Vector2<T>& a, const T& k)					// a / k
{
	return Vector2<T>(a.val[0] / k, a.val[1] / k);
}
template <class T> inline Vector2<T> Div(const T& k, const Vector2<T>& a)					// (k / a_x, k / a_y)
{
	return Vector2<T>(k / a.val[0], k / a.val[1]);
}

template <class T> inline Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)	// binary addition operator
{
	return Vector2<T>(a.val[0] + b.val[0], a.val[1] + b.val[1]);
}
template <class T> inline Vector2<T> operator+(const Vector2<T>& a, const T& k)				// binary scalar addition operator
{
	return Vector2<T>(a.val[0] + k, a.val[1] + k);
}
template <class T> inline Vector2<T> operator+(const T& k, const Vector2<T>& a)				// binary scalar addition operator
{
	return Vector2<T>(a.val[0] + k, a.val[1] + k);
}
template <class T> inline Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)	// binary subtraction operator
{
	return Vector2<T>(a.val[0] - b.val[0], a.val[1] - b.val[1]);
}
template <class T> inline Vector2<T> operator-(const Vector2<T>& a, const T& k)				// binary scalar subtraction operator
{
	return Vector2<T>(a.val[0] - k, a.val[1] - k);
}
template <class T> inline Vector2<T> operator-(const T& k, const Vector2<T>& a)				// binary scalar subtraction operator
{
	return Vector2<T>(k - a.val[0], k - a.val[1]);
}
template <class T> inline Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b)	// binary multiplication operator (element-wise)
{
	return Vector2<T>(a.val[0] * b.val[0], a.val[1] * b.val[1]);
}
template <class T> inline Vector2<T> operator*(const Vector2<T>& v, const T& k)				// binary scalar multiplication operator
{
	return Vector2<T>(a.val[0] * k, a.val[1] * k);
}
template <class T> inline Vector2<T> operator*(const T& k, const Vector2<T>& v)				// binary scalar multiplication operator
{
	return Vector2<T>(a.val[0] * k, a.val[1] * k);
}
template <class T> inline Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b)	// binary division operator (element-wise)
{
	return Vector2<T>(a.val[0] / b.val[0], a.val[1] / b.val[1]);
}
template <class T> inline Vector2<T> operator/(const Vector2<T>& v, const T& k)				// binary scalar division operator
{
	return Vector2<T>(a.val[0] / k, a.val[1] / k);
}
template <class T> inline Vector2<T> operator/(const T& k, const Vector2<T>& v)				// binary scalar division operator
{
	return Vector2<T>(k / a.val[0], k / a.val[1]);
}

typedef Vector2<int>	Vector2i;
typedef Vector2<float>	Vector2f;
typedef Vector2<double>	Vector2d;



template <class T>
class Quaternion
{
	// Constructors
public:
	Quaternion()															// Identity quaternion (1, 0, 0, 0)
	{
		val[0] = 1;
		val[1] = val[2] = val[3] = 0;
	}
	Quaternion(T w, T x, T y, T z)											// (w, x, y, z)
	{
		val[0] = w, val[1] = x;	val[2] = y;	val[3] = z;
	}
	Quaternion(T* wxyz)														// (wxyz[0], wxyz[1], wxyz[2], wxyz[3])
	{
		memcpy(val, wxyz, sizeof(T)*4);
	}
	Quaternion(const Quaternion<T>& v)										// copy constructor
	{
		memcpy(this->val, v.val, sizeof(T)*4);
	}
	Quaternion(const Vector3<T>& q)											// typecast constructor
	{
		// TODO
	}
	Quaternion(const Vector2<T>& q)											// typecast constructor
	{
		// TODO
	}
	~Quaternion(){}

// 	// Conversion ==> TODO
// public:
// 	Quaterniond FromAxisAngle(const double rad, const double axis_x, const double axis_y, const double axis_z);
// 	Quaterniond FromMatrix(const double* R);
// 	Quaterniond FromMatrix(const double R[3][3]);
// 	Quaterniond FromEulerAngle(const double a, const double b, const double c, const char* order);
// 
// 	static Quaterniond Log(const Quaterniond& q);
// 	Quaterniond Log(void);
// 	static Quaterniond Exp(const Quaterniond& a);
// 	Quaterniond Exp(void);

	// Methods (Algebra)
public:
	T NormSquared() const												// |this|^2
	{
		return this->val[0]*this->val[0] + this->val[1]*this->val[1] + this->val[2]*this->val[2] + this->val[3]*this->val[3];
	}
	T Norm() const														// |this|
	{
		return sqrt(this->val[0]*this->val[0] + this->val[1]*this->val[1] + this->val[2]*this->val[2] + this->val[3]*this->val[3]);
	}
	Quaternion<T> Normalize(void)											// this /= |this|
	{
		double n = this->Norm();
		this->val[0] /= n; this->val[1] /= n; this->val[2] /= n; this->val[3] /= n;
		return *this;
	}
	Quaternion<T> Inv(void)													// inverse(this)
	{
		T n = NormSquared();
		val[0] = val[0]/n;
		val[1] = -val[1]/n;
		val[2] = -val[2]/n;
		val[3] = -val[3]/n;

		return *this;
	}
	Quaternion<T> Add(const Quaternion<T>& q)									// this += q
	{
		this->val[0] += q[0];	this->val[1] += q[1];	this->val[2] += q[2];	this->val[3] += q[3];
		return *this;
	}
	Quaternion<T> Sub(const Quaternion<T>& q)									// this -= q
	{
		this->val[0] -= q[0];	this->val[1] -= q[1];	this->val[2] -= q[2];	this->val[3] -= q[3];
		return *this;
	}
	Quaternion<T> Mul(const Quaternion<T>& q)									// this *= q
	{ 
		double qtemp[4];
		memcpy(qtemp, this->val, sizeof(T)*4);

		val[0] = qtemp[0]*q.val[0] - qtemp[1]*q.val[1] - qtemp[2]*q.val[2] - qtemp[3]*q.val[3];
		val[1] = qtemp[1]*q.val[0] + qtemp[0]*q.val[1] - qtemp[3]*q.val[2] + qtemp[2]*q.val[3];
		val[2] = qtemp[2]*q.val[0] + qtemp[3]*q.val[1] + qtemp[0]*q.val[2] - qtemp[1]*q.val[3];
		val[3] = qtemp[3]*q.val[0] - qtemp[2]*q.val[1] + qtemp[1]*q.val[2] + qtemp[0]*q.val[3];

		return *this;
	}
	Quaternion<T> Mul(const T& k)											// this *= k
	{
		this->val[0] *= k;	this->val[1] *= k;	this->val[2] *= k;	this->val[3] *= k;
		return *this;
	}
	Quaternion<T> Div(const Quaternion<T>& q)								// this /= q
	{		
		return Mul(q.Inv());
	}
	Quaternion<T> Div(const T& k)											// this /= k
	{
		this->val[0] /= k;	this->val[1] /= k;	this->val[2] /= k;	this->val[3] /= k;
		return *this;
	}

	// Operators
public:
	Quaternion<T> operator=(const Quaternion<T>& q)							// assign operator
	{
		memcpy(this->val, q.val, sizeof(double)*4);
	}

	bool operator==(const Quaternion<T>& q) const							// compare operator
	{
		return (this->val[0] == q.val[0] && this->val[1] == q.val[1] && this->val[2] == q.val[2] && this->val[3] == q.val[3]);
	}
	bool operator!=(const Quaternion<T>& q) const							// negative compare operator
	{	
		return (this->val[0] != q.val[0] || this->val[1] != q.val[1] || this->val[2] != q.val[2] || this->val[3] != q.val[3]);
	}

	Quaternion<T> operator+=(const Quaternion<T>& q)							// unary addition operator
	{
		this->val[0] += q[0];	this->val[1] += q[1];	this->val[2] += q[2];	this->val[3] += q[3];
		return *this;
	}
	Quaternion<T> operator-=(const Quaternion<T>& q)							// unary subtraction operator
	{
		this->val[0] -= q[0];	this->val[1] -= q[1];	this->val[2] -= q[2];	this->val[3] -= q[3];
		return *this;
	}
	Quaternion<T> operator*=(const Quaternion<T>& q)							// unary multiplication operator (element-wise)
	{
		double qtemp[4];
		memcpy(qtemp, this->val, sizeof(T)*4);

		val[0] = qtemp[0]*q.val[0] - qtemp[1]*q.val[1] - qtemp[2]*q.val[2] - qtemp[3]*q.val[3];
		val[1] = qtemp[1]*q.val[0] + qtemp[0]*q.val[1] - qtemp[3]*q.val[2] + qtemp[2]*q.val[3];
		val[2] = qtemp[2]*q.val[0] + qtemp[3]*q.val[1] + qtemp[0]*q.val[2] - qtemp[1]*q.val[3];
		val[3] = qtemp[3]*q.val[0] - qtemp[2]*q.val[1] + qtemp[1]*q.val[2] + qtemp[0]*q.val[3];

		return *this;
	}
	Quaternion<T> operator*=(const T& k)									// unary scalar multiplication operator
	{
		this->val[0] *= k;	this->val[1] *= k;	this->val[2] *= k;	this->val[3] *= k;
		return *this;
	}
	Quaternion<T> operator/=(const Quaternion<T>& q)							// unary division operator (element-wise)
	{
		return Mul(q.Inv());
	}
	Quaternion<T> operator/=(const T& k)									// unary scalar division operator
	{
		this->val[0] /= k;	this->val[1] /= k;	this->val[2] /= k;	this->val[3] /= k;
		return *this;
	}

	Quaternion<T> operator-() const										// unary negation operator
	{
		return Quaternion<T>(-this->val[0], -this->val[1], -this->val[2], -this->val[3]);
	}


	// Methods (Auxiliary)
	template <class T> friend std::istream& operator>>(std::istream& is, Quaternion<T>& q)
	{
		char str[1024];
		char* tok;
		is >> str;
		tok = strtok(str, " ,()<>[]|:");
		q.val[0] = (T)atof(tok);
		tok = strtok(NULL, " ,()<>[]|:");
		q.val[1] = (T)atof(tok);
		tok = strtok(NULL, " ,()<>[]|:");
		q.val[2] = (T)atof(tok);
		tok = strtok(NULL, " ,()<>[]|:");
		q.val[3] = (T)atof(tok);
		return is;
	}
	template <class T> friend std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q)
	{
		os << "(" << q.val[0] << ", " << q.val[1] << ", " << q.val[2] << ", " << q.val[3] <<")";
		return os;
	}

	// Accessors
public:
	T& operator[](int i)	{	return val[i];	}
	T W() const				{	return val[0];	}
	T X() const				{	return val[1];	}
	T Y() const				{	return val[2];	}
	T Z() const				{	return val[3];	}

	void SetW(T nw)			{	val[0] = nw;	}
	void SetX(T nx)			{	val[1] = nx;	}
	void SetY(T ny)			{	val[2] = ny;	}
	void SetZ(T nz)			{	val[3] = nz;	}

public:
	T val[4];
};

template <class T> inline T NormSquared(const Quaternion<T>& q)								// |q|^2
{
	return q.val[0]*q.val[0] + q.val[1]*q.val[1] + q.val[2]*q.val[2] + q.val[3]*q.val[3];
}
template <class T> inline T Norm(const Quaternion<T>& q)										// |q|
{
	return sqrt(q.val[0]*q.val[0] + q.val[1]*q.val[1] + q.val[2]*q.val[2] + q.val[3]*q.val[3]);
}
template <class T> inline Quaternion<T> Normalize(Quaternion<T>& q)								// v / |v|
{
	T n = Norm(q);
	q.val[0] /= n; q.val[1] /= n; q.val[2] /= n; q.val[3] /= n;
	return q;
}
template <class T> inline Quaternion<T> Inv(const Quaternion<T>& q)								// inverse(this)
{
	T n = NormSquared(q);
	return Quaternion<T>(val[0]/n, -val[1]/n, -val[2]/n, -val[3]/n);
}

template <class T> inline Quaternion<T> Add(const Quaternion<T>& a, const Quaternion<T>& b)			// a + b
{
	return Quaternion<T>(a.val[0] + b.val[0], a.val[1] + b.val[1], a.val[2] + b.val[2], a.val[3] + b.val[3]);
}
template <class T> inline Quaternion<T> Sub(const Quaternion<T>& a, const Quaternion<T>& b)			// a - b
{
	return Quaternion<T>(a.val[0] - b.val[0], a.val[1] - b.val[1], a.val[2] - b.val[2], a.val[3] - b.val[3]);
}
template <class T> inline Quaternion<T> Mul(const Quaternion<T>& a, const Quaternion<T>& b)			// a * b
{
	return Quaternion<T>(a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3],
						 a[1]*b[0] + a[0]*b[1] - a[3]*b[2] + a[2]*b[3],
						 a[2]*b[0] + a[3]*b[1] + a[0]*b[2] - a[1]*b[3],
						 a[3]*b[0] - a[2]*b[1] + a[1]*b[2] + a[0]*b[3]);
}
template <class T> inline Quaternion<T> Mul(const Quaternion<T>& a, const T& k)					// a * k
{
	return Quaternion<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k, a.val[3] * k);
}
template <class T> inline Quaternion<T> Mul(const T& k, const Quaternion<T>& a)					// k * a
{
	return Quaternion<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k, a.val[3] * k);
}
template <class T> inline Quaternion<T> Div(const Quaternion<T>& a, const Quaternion<T>& b)			// a / b
{
	return Mul(a, Inv(b));	
}
template <class T> inline Quaternion<T> Div(const Quaternion<T>& a, const T& k)						// a / k
{
	return Quaternion<T>(a.val[0] / k, a.val[1] / k, a.val[2] / k, a.val[3] / k);
}
template <class T> inline Quaternion<T> Div(const T& k, const Quaternion<T>& a)					// (k / a_w, k / a_x, k / a_y, k / a_z)
{
	return Quaternion<T>(k / a.val[0], k / a.val[1], k / a.val[2], k / a.val[3]);
}

template <class T> inline Quaternion<T> operator+(const Quaternion<T>& a, const Quaternion<T>& b)	// binary addition operator
{
	return Quaternion<T>(a.val[0] + b.val[0], a.val[1] + b.val[1], a.val[2] + b.val[2], a.val[3] + b.val[3]);
}
template <class T> inline Quaternion<T> operator-(const Quaternion<T>& a, const Quaternion<T>& b)	// binary subtraction operator
{
	return Quaternion<T>(a.val[0] - b.val[0], a.val[1] - b.val[1], a.val[2] - b.val[2], a.val[3] - b.val[3]);
}
template <class T> inline Quaternion<T> operator*(const Quaternion<T>& a, const Quaternion<T>& b)	// binary multiplication operator (element-wise)
{
	return Quaternion<T>(a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3],
						 a[1]*b[0] + a[0]*b[1] - a[3]*b[2] + a[2]*b[3],
						 a[2]*b[0] + a[3]*b[1] + a[0]*b[2] - a[1]*b[3],
						 a[3]*b[0] - a[2]*b[1] + a[1]*b[2] + a[0]*b[3]);
}
template <class T> inline Quaternion<T> operator*(const Quaternion<T>& v, const T& k)				// binary scalar multiplication operator
{
	return Quaternion<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k, a.val[3] * k);
}
template <class T> inline Quaternion<T> operator*(const T& k, const Quaternion<T>& v)				// binary scalar multiplication operator
{
	return Quaternion<T>(a.val[0] * k, a.val[1] * k, a.val[2] * k, a.val[3] * k);
}
template <class T> inline Quaternion<T> operator/(const Quaternion<T>& a, const Quaternion<T>& b)	// binary division operator (element-wise)
{
	return Mul(a, Inv(b));
}
template <class T> inline Quaternion<T> operator/(const Quaternion<T>& v, const T& k)				// binary scalar division operator
{
	return Quaternion<T>(a.val[0] / k, a.val[1] / k, a.val[2] / k, a.val[3] / k);
}
template <class T> inline Quaternion<T> operator/(const T& k, const Quaternion<T>& v)				// binary scalar division operator
{
	return Quaternion<T>(k / a.val[0], k / a.val[1], k / a.val[2], k / a.val[3]);
}

typedef Quaternion<double>	Quaterniond;
typedef Quaternion<float>	Quaternionf;


#endif // HCCL_VECTORQUATERNION_H_