#ifndef _DOULBE4_H_
#define _DOULBE4_H_

class double4
{
public:
    double4();
    double4(double x, double y, double z, double w);
    ~double4();

    double x, y, z, w;

    double4& operator+=(const double4 &f);
    double4& operator-=(const double4 &f);
    double4& operator*=(const double4 &f);
    double4& operator/=(const double4 &f);

    double4& operator+=(double s);
    double4& operator-=(double s);
    double4& operator*=(double s);
    double4& operator/=(double s);

    double4 operator+(const double4 &f);
    double4 operator-(const double4 &f);
    double4 operator*(const double4 &f);
    double4 operator/(const double4 &f);

    double4 operator+(double s);
    double4 operator-(double s);
    double4 operator*(double s);
    double4 operator/(double s);

};

double4 operator+(double s, const double4 &f);
double4 operator-(double s, const double4 &f);
double4 operator*(double s, const double4 &f);
double4 operator/(double s, const double4 &f);

double dot(const double4 &f1, const double4 &f2);
double length(const double4 &f);

#endif // _DOULBE4_H_
