#ifndef _FLOAT4_H_
#define _FLOAT4_H_

class float4
{
public:
    float4();
    float4(float x, float y, float z, float w);
    ~float4();

    float x, y, z, w;

    float4& operator+=(const float4& f);
    float4& operator-=(const float4& f);
    float4& operator*=(const float4& f);
    float4& operator/=(const float4& f);

    float4& operator+=(float s);
    float4& operator-=(float s);
    float4& operator*=(float s);
    float4& operator/=(float s);

    float4 operator+(const float4& f);
    float4 operator-(const float4& f);
    float4 operator*(const float4& f);
    float4 operator/(const float4& f);

    float4 operator+(float s);
    float4 operator-(float s);
    float4 operator*(float s);
    float4 operator/(float s);

};

float4 operator+(float s, const float4& f);
float4 operator-(float s, const float4& f);
float4 operator*(float s, const float4& f);
float4 operator/(float s, const float4& f);

float dot(const float4& f1, const float4& f2);
float length(const float4& f);

#endif // _FLOAT4_H_
