#ifndef BMCE_CORE_MATHLIB_H
#define BMCE_CORE_MATHLIB_H


#include <cmath>

#include <cassert>
#include <memory.h>

#include "core/types.h"


namespace bmce
{

union Mat4
{
    FPType v[16];
    FPType m[4][4];

    Mat4();

    Mat4(
        FPType m00, FPType m01, FPType m02, FPType m03,
        FPType m10, FPType m11, FPType m12, FPType m13,
        FPType m20, FPType m21, FPType m22, FPType m23,
        FPType m30, FPType m31, FPType m32, FPType m33);

    void init(
        FPType m00, FPType m01, FPType m02, FPType m03,
        FPType m10, FPType m11, FPType m12, FPType m13,
        FPType m20, FPType m21, FPType m22, FPType m23,
        FPType m30, FPType m31, FPType m32, FPType m33);

    static Mat4 Perspective(
        FPType fovy, FPType aspect, FPType znear, FPType zfar);

    static Mat4 Orthographic(
        FPType l, FPType r, FPType b, FPType t, FPType n, FPType f);

    Mat4 operator*(const Mat4& r) const;
    Mat4& operator*=(const Mat4& r);
};

struct Vec4
{
    FPType x, y, z, w;

    Vec4();
    Vec4(FPType x, FPType y, FPType z, FPType w);

    FPType norm() const;
    FPType len() const;
    Vec4 unit() const;

    Vec4 operator+(const Vec4& r) const;
    Vec4& operator+=(const Vec4& r);
    Vec4 operator*(const Mat4& m) const;
    Vec4& operator*=(const Mat4& m);
};

struct Quat
{
    FPType w, x, y, z;

    Quat();
    Quat(FPType w, FPType x, FPType y, FPType z);

    FPType norm() const;
    FPType len() const;
    Quat unit() const;
    Quat conjugate() const;
    Quat inverse() const;
    Mat4 matrix() const;

    static Quat FromAngleAxis(FPType angle, FPType x, FPType y, FPType z);

    Quat operator*(const Quat& r) const;
    Quat& operator*=(const Quat& r);
    Quat operator/(FPType s) const;
    Quat& operator/=(FPType s);
    bool operator==(const Quat& r) const;
};

} // namespace bmce


#endif
