#ifndef _DOULBE2_H_
#define _DOULBE2_H_

class double2
{
public:
    double2();
    double2(double x, double y);
    ~double2();

    double x, y;

    double2& operator+=(const double2 &f);
    double2& operator-=(const double2 &f);
    double2& operator*=(const double2 &f);
    double2& operator/=(const double2 &f);

    double2& operator+=(double s);
    double2& operator-=(double s);
    double2& operator*=(double s);
    double2& operator/=(double s);

    double2 operator+(const double2 &f);
    double2 operator-(const double2 &f);
    double2 operator*(const double2 &f);
    double2 operator/(const double2 &f);

    double2 operator+(double s);
    double2 operator-(double s);
    double2 operator*(double s);
    double2 operator/(double s);

};

double2 operator+(double s, const double2 &f);
double2 operator-(double s, const double2 &f);
double2 operator*(double s, const double2 &f);
double2 operator/(double s, const double2 &f);

double dot(const double2 &f1, const double2 &f2);
double length(const double2 &f);

#endif // _DOULBE2_H_
