#pragma once

#include <algorithm>
#include <ostream>
#include <iomanip>

#define VML_PI	3.141592654f
#define VML_PI2	6.283185307f

#define RADIANS VML_PI / 180.f
#define DEGREES 180.f / VML_PI

struct vec3f
{
    vec3f() : x(0.f), y(0.f), z(0.f) {}
    vec3f(float v) : x(v), y(v), z(v) {}
    vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

    inline float length() const;
    inline float* data() { return f;}
    inline const float* constData() const { return f;}
    
    union {
        struct {float x,y,z;};
        float f[3];
    };

    const vec3f operator-(const vec3f& rhs) const { return vec3f(x - rhs.x, y - rhs.y, z - rhs.z);};
    const vec3f operator+(const vec3f& rhs) const { return vec3f(x + rhs.x, y + rhs.y, z + rhs.z);};
    const vec3f operator*(const vec3f& rhs) const { return vec3f(x * rhs.x, y * rhs.y, z * rhs.z);};
    const vec3f operator/(const vec3f& rhs) const { return vec3f(x / rhs.x, y / rhs.y, z / rhs.z);};

    vec3f nomalized() const;

    static vec3f cross(const vec3f& a, const vec3f& b);
    static float dot(const vec3f& a, const vec3f& b);
    static vec3f nomalize(const vec3f& rhs);
    //static float dot()
};

inline float vec3f::length() const {
    return std::sqrtf(x * x + y * y + z * z);
}

inline vec3f vec3f::nomalized() const
{
    return vec3f::nomalize(*this);
}

inline vec3f vec3f::cross(const vec3f & a, const vec3f & b)
{
    float x = a.y * b.z - a.z * b.y;
    float y = a.z * b.x - a.x * b.z;
    float z = a.x * b.y - a.y * b.x;
    return vec3f(x,y,z);
}

inline float vec3f::dot(const vec3f & a, const vec3f & b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3f vec3f::nomalize(const vec3f & rhs)
{
    float factor = 1.0f / rhs.length();
    return vec3f(rhs.x * factor, rhs.y * factor, rhs.z * factor);
}

std::ostream& operator <<(std::ostream& os, const vec3f& v){
    os << std::setw(2) <<"vec3f(" << v.x << ", " <<
    v.y << ", " << v.z << ")"
     << std::endl;
    return os;
}

struct mat4f
{
    mat4f(){
        memset(this, 0, sizeof(float) * 16);
        m[0][0] = 1.f;m[1][1] = 1.f;m[2][2] = 1.f;m[3][3] = 1.f;
    };
    mat4f(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    ){
        m[0][0] = m00;m[0][1] = m01;m[0][2] = m02;m[0][3] = m03;
        m[1][0] = m10;m[1][1] = m11;m[1][2] = m12;m[1][3] = m13;
        m[2][0] = m20;m[2][1] = m21;m[2][2] = m22;m[2][3] = m23;
        m[3][0] = m30;m[3][1] = m31;m[3][2] = m32;m[3][3] = m33;
    }
    union {
        float m[4][4];
        float f[16];
    };

    static mat4f perspectiveLH(float fov, float aspec, float n, float f);
    static mat4f lookAt(const vec3f& eye, const vec3f& at, const vec3f& up);
    
};

inline mat4f mat4f::perspectiveLH(float fov, float aspec, float zn, float zf)
{
    //fov *= RADIANS;
    float sy = std::cosf(fov/2) / std::sinf(fov / 2);
    float sx = sy / aspec;
    // float const tanFov = std::tanf(RADIANS * fov * 0.5f);
    // float sx = 1.f / (aspec * tanFov);
    // float sy = 1.f / tanFov;

    mat4f m = {
         sx,   0.f,                  0.f,    0.f,
        0.f,    sy,                  0.f,    0.f,
        //0.f,   0.f,       zf / (zf - zn),    1.f,
        //0.f,   0.f, -zn * (zf / (zf - zn)),    0.f
        0.f,   0.f,        zf / (zf - zn),    1.f,
        // 0.f,   0.f, -(zf * zn) / (zf - zn),    0.f
        0.f,   0.f, (zf * zn) / (zn - zf),    0.f
    };

    return m;
}

inline mat4f mat4f::lookAt(const vec3f& eye, const vec3f& at, const vec3f& up)
{
    //vec3f zAxis = vec3f::nomalize(at - eye);
    vec3f zAxis = (at - eye).nomalized();
    vec3f xAxis = vec3f::nomalize(vec3f::cross(up, zAxis));
    vec3f yAxis = vec3f::nomalize(vec3f::cross(zAxis, xAxis));

    float x = -vec3f::dot(xAxis, eye);
    float y = -vec3f::dot(yAxis, eye);
    float z = -vec3f::dot(zAxis, eye);

    mat4f m = {
        xAxis.x, yAxis.x, zAxis.x, 0.f,
        xAxis.y, yAxis.y, zAxis.y, 0.f,
        xAxis.z, yAxis.z, zAxis.z, 0.f,
              x,       y,       z, 1.f
    };
    return m;
}
