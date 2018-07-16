#include "core/mathlib.h"


#include <cmath>
#include <iostream>

#include "core/constants.h"


namespace
{


const float kEPS = 0.000001;


}

namespace bmce
{

// Mat4

Mat4::Mat4() :
    v{
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0}
{
}

Mat4::Mat4(
        FPType m00, FPType m01, FPType m02, FPType m03,
        FPType m10, FPType m11, FPType m12, FPType m13,
        FPType m20, FPType m21, FPType m22, FPType m23,
        FPType m30, FPType m31, FPType m32, FPType m33) :
    v{
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33}
{
}

void Mat4::init(
    FPType m00, FPType m01, FPType m02, FPType m03,
    FPType m10, FPType m11, FPType m12, FPType m13,
    FPType m20, FPType m21, FPType m22, FPType m23,
    FPType m30, FPType m31, FPType m32, FPType m33)
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

Mat4 Mat4::Perspective(FPType fovy, FPType aspect, FPType znear, FPType zfar)
{
    FPType halfa = fovy * static_cast<float>(kPI) / 360;
    FPType F = 1 / tan(halfa);
    FPType E = F / aspect;
    FPType A = (znear + zfar) / (znear - zfar);
    FPType B = (2 * zfar * znear) / (znear - zfar);

    return {
        E, 0, 0,  0,
        0, F, 0,  0,
        0, 0, A, -1,
        0, 0, B,  0};
}

Mat4 Mat4::Orthographic(FPType l, FPType r, FPType b, FPType t, FPType n, FPType f)
{
    FPType A = 2 / (r - l);
    FPType B = 2 / (t - b);
    FPType C = -2 / (f - n);
    FPType D = - (r + l) / (r - l);
    FPType E = - (t + b) / (t - b);
    FPType F = - (f + n) / (f - n);

    return {
        A, 0, 0, 0,
        0, B, 0, 0,
        0, 0, C, 0,
        D, E, F, 1};
}

Mat4 Mat4::operator*(const Mat4& r) const
{
    return {
        m[0][0]*r.m[0][0] + m[0][1]*r.m[1][0] + m[0][2]*r.m[2][0] + m[0][3]*r.m[3][0],
        m[0][0]*r.m[0][1] + m[0][1]*r.m[1][1] + m[0][2]*r.m[2][1] + m[0][3]*r.m[3][1],
        m[0][0]*r.m[0][2] + m[0][1]*r.m[1][2] + m[0][2]*r.m[2][2] + m[0][3]*r.m[3][2],
        m[0][0]*r.m[0][3] + m[0][1]*r.m[1][3] + m[0][2]*r.m[2][3] + m[0][3]*r.m[3][3],
        m[1][0]*r.m[0][0] + m[1][1]*r.m[1][0] + m[1][2]*r.m[2][0] + m[1][3]*r.m[3][0],
        m[1][0]*r.m[0][1] + m[1][1]*r.m[1][1] + m[1][2]*r.m[2][1] + m[1][3]*r.m[3][1],
        m[1][0]*r.m[0][2] + m[1][1]*r.m[1][2] + m[1][2]*r.m[2][2] + m[1][3]*r.m[3][2],
        m[1][0]*r.m[0][3] + m[1][1]*r.m[1][3] + m[1][2]*r.m[2][3] + m[1][3]*r.m[3][3],
        m[2][0]*r.m[0][0] + m[2][1]*r.m[1][0] + m[2][2]*r.m[2][0] + m[2][3]*r.m[3][0],
        m[2][0]*r.m[0][1] + m[2][1]*r.m[1][1] + m[2][2]*r.m[2][1] + m[2][3]*r.m[3][1],
        m[2][0]*r.m[0][2] + m[2][1]*r.m[1][2] + m[2][2]*r.m[2][2] + m[2][3]*r.m[3][2],
        m[2][0]*r.m[0][3] + m[2][1]*r.m[1][3] + m[2][2]*r.m[2][3] + m[2][3]*r.m[3][3],
        m[3][0]*r.m[0][0] + m[3][1]*r.m[1][0] + m[3][2]*r.m[2][0] + m[3][3]*r.m[3][0],
        m[3][0]*r.m[0][1] + m[3][1]*r.m[1][1] + m[3][2]*r.m[2][1] + m[3][3]*r.m[3][1],
        m[3][0]*r.m[0][2] + m[3][1]*r.m[1][2] + m[3][2]*r.m[2][2] + m[3][3]*r.m[3][2],
        m[3][0]*r.m[0][3] + m[3][1]*r.m[1][3] + m[3][2]*r.m[2][3] + m[3][3]*r.m[3][3]
    };
}

Mat4& Mat4::operator*=(const Mat4& r)
{
    init(
        m[0][0]*r.m[0][0] + m[0][1]*r.m[1][0] + m[0][2]*r.m[2][0] + m[0][3]*r.m[3][0],
        m[0][0]*r.m[0][1] + m[0][1]*r.m[1][1] + m[0][2]*r.m[2][1] + m[0][3]*r.m[3][1],
        m[0][0]*r.m[0][2] + m[0][1]*r.m[1][2] + m[0][2]*r.m[2][2] + m[0][3]*r.m[3][2],
        m[0][0]*r.m[0][3] + m[0][1]*r.m[1][3] + m[0][2]*r.m[2][3] + m[0][3]*r.m[3][3],
        m[1][0]*r.m[0][0] + m[1][1]*r.m[1][0] + m[1][2]*r.m[2][0] + m[1][3]*r.m[3][0],
        m[1][0]*r.m[0][1] + m[1][1]*r.m[1][1] + m[1][2]*r.m[2][1] + m[1][3]*r.m[3][1],
        m[1][0]*r.m[0][2] + m[1][1]*r.m[1][2] + m[1][2]*r.m[2][2] + m[1][3]*r.m[3][2],
        m[1][0]*r.m[0][3] + m[1][1]*r.m[1][3] + m[1][2]*r.m[2][3] + m[1][3]*r.m[3][3],
        m[2][0]*r.m[0][0] + m[2][1]*r.m[1][0] + m[2][2]*r.m[2][0] + m[2][3]*r.m[3][0],
        m[2][0]*r.m[0][1] + m[2][1]*r.m[1][1] + m[2][2]*r.m[2][1] + m[2][3]*r.m[3][1],
        m[2][0]*r.m[0][2] + m[2][1]*r.m[1][2] + m[2][2]*r.m[2][2] + m[2][3]*r.m[3][2],
        m[2][0]*r.m[0][3] + m[2][1]*r.m[1][3] + m[2][2]*r.m[2][3] + m[2][3]*r.m[3][3],
        m[3][0]*r.m[0][0] + m[3][1]*r.m[1][0] + m[3][2]*r.m[2][0] + m[3][3]*r.m[3][0],
        m[3][0]*r.m[0][1] + m[3][1]*r.m[1][1] + m[3][2]*r.m[2][1] + m[3][3]*r.m[3][1],
        m[3][0]*r.m[0][2] + m[3][1]*r.m[1][2] + m[3][2]*r.m[2][2] + m[3][3]*r.m[3][2],
        m[3][0]*r.m[0][3] + m[3][1]*r.m[1][3] + m[3][2]*r.m[2][3] + m[3][3]*r.m[3][3]);
    return *this;
}


// Vec4


Vec4::Vec4() :
    x(0), y(0), z(0), w(0)
{}

Vec4::Vec4(FPType x, FPType y, FPType z, FPType w) :
    x(x), y(y), z(z), w(w)
{}

FPType Vec4::norm() const
{
    return sqrt(len());
}

FPType Vec4::len() const
{
    return x*x + y*y + z*z + w*w;
}

Vec4 Vec4::unit() const
{
    FPType n = norm();
    return {x / n, y / n, z / n, w / n};
}

Vec4 Vec4::operator+(const Vec4& r) const
{
    return {x + r.x, y + r.y, z + r.z, w + r.w};
}

Vec4& Vec4::operator+=(const Vec4& r)
{
    x += r.x;
    y += r.y;
    z += r.z;
    w += r.w;
    return *this;
}

Vec4 Vec4::operator*(const Mat4& m) const
{
    return {
        x*m.m[0][0] + y*m.m[1][0] + z*m.m[2][0] + w*m.m[3][0],
        x*m.m[0][1] + y*m.m[1][1] + z*m.m[2][1] + w*m.m[3][1],
        x*m.m[0][2] + y*m.m[1][2] + z*m.m[2][2] + w*m.m[3][2],
        x*m.m[0][3] + y*m.m[1][3] + z*m.m[2][3] + w*m.m[3][3]};
}

Vec4& Vec4::operator*=(const Mat4& m)
{
    x = x*m.m[0][0] + y*m.m[1][0] + z*m.m[2][0] + w*m.m[3][0];
    y = x*m.m[0][1] + y*m.m[1][1] + z*m.m[2][1] + w*m.m[3][1];
    z = x*m.m[0][2] + y*m.m[1][2] + z*m.m[2][2] + w*m.m[3][2];
    w = x*m.m[0][3] + y*m.m[1][3] + z*m.m[2][3] + w*m.m[3][3];
    return *this;
}


// Quat


Quat::Quat() :
    w(0), x(0), y(0), z(0)
{}

Quat::Quat(FPType w, FPType x, FPType y, FPType z) :
    w(w), x(x), y(y), z(z)
{}

FPType Quat::norm() const
{
    return sqrt(len());
}

FPType Quat::len() const
{
    return w*w + x*x + y*y + z*z;
}

Quat Quat::unit() const
{
    FPType n = norm();
    return {w / n, x / n, y / n, z / n};
}

Quat Quat::conjugate() const
{
    return {w, -x, -y, -z};
}

Quat Quat::inverse() const
{
    Quat ret = conjugate();
    ret /= ret.len();
    return ret;
}

Mat4 Quat::matrix() const
{
    FPType xx2 = x * x * 2;
    FPType yy2 = y * y * 2;
    FPType zz2 = z * z * 2;
    FPType xy2 = x * y * 2;
    FPType xz2 = x * z * 2;
    FPType yz2 = y * z * 2;
    FPType wx2 = w * x * 2;
    FPType wy2 = w * y * 2;
    FPType wz2 = w * z * 2;

    return {
        1 - yy2 - zz2,      xy2 + wz2,      xz2 - wy2, 0,
            xy2 - wz2,  1 - xx2 - zz2,      yz2 + wx2, 0,
            xz2 + wy2,      yz2 - wx2,  1 - xx2 - yy2, 0,
                    0,              0,              0, 1};
}

Quat Quat::FromAngleAxis(FPType angle, FPType x, FPType y, FPType z)
{
    FPType halfa = angle * static_cast<float>(kPI) / 360;
    FPType sinha = sin(halfa);
    FPType cosha = cos(halfa);
    return {cosha, x * sinha, y * sinha, z * sinha};
}

Quat Quat::operator*(const Quat &r) const
{
    return {
        w*r.w - x*r.x - y*r.y - z*r.z,
        w*r.x + x*r.w + y*r.z - z*r.y,
        w*r.y + y*r.w + z*r.x - x*r.z,
        w*r.z + z*r.w + x*r.y - y*r.x};
}

Quat& Quat::operator*=(const Quat &r)
{
    FPType tw = w*r.w - x*r.x - y*r.y - z*r.z;
    FPType tx = w*r.x + x*r.w + y*r.z - z*r.y;
    FPType ty = w*r.y + y*r.w + z*r.x - x*r.z;
    FPType tz = w*r.z + z*r.w + x*r.y - y*r.x;
    w = tw;
    x = tx;
    y = ty;
    z = tz;
    return *this;
}

Quat Quat::operator/(FPType s) const
{
    return {w / s, x / s, y / s, z / s};
}

Quat& Quat::operator/=(FPType s)
{
    w /= s;
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

bool Quat::operator==(const Quat &r) const
{
    return std::abs(w - r.w) < kEPS
        && std::abs(x - r.x) < kEPS
        && std::abs(y - r.y) < kEPS
        && std::abs(z - r.z) < kEPS;
}

} // namespace bmce
