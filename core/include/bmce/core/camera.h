#ifndef BMCE_CORE_CAMERA_H
#define BMCE_CORE_CAMERA_H


#include "core/mathlib.h"


namespace bmce
{

class Camera
{
private:
    Vec4 position_;
    Quat rotation_;
    Mat4 projection_matrix_;

public:
    Camera() :
        position_(0, 0, 0, 1),
        rotation_(1, 0, 0, 0)
    {
    }

    void yaw(FPType angle)
    {
        rotation_ = Quat::FromAngleAxis(angle, 0, 1, 0) * rotation_;
    }

    void pitch(FPType angle)
    {
        rotation_ *= Quat::FromAngleAxis(angle, 1, 0, 0);
    }

    void roll(FPType angle)
    {
        rotation_ *= Quat::FromAngleAxis(angle, 0, 0, 1);
    }

    void forward(FPType pos)
    {
        Vec4 vec(0, 0, -pos, 0);
        position_ += vec * rotation_.matrix();
    }

    void right(FPType pos)
    {
        Vec4 vec(pos, 0, 0, 0);
        position_ += vec * rotation_.matrix();
    }

    void setPerspective(int width, int height)
    {
        auto fwidth = static_cast<FPType>(width);
        auto fheight = static_cast<FPType>(height);
        FPType aspect = fwidth / fheight;
        projection_matrix_ = Mat4::Perspective(
            45.0f, aspect, 0.01f, 100.0f);
    }

    void setOrthographic(int width, int height)
    {
        projection_matrix_ = Mat4::Orthographic(
            0, width, 0, height, 0.01f, 100.0f);
    }

    void setOrthographic(int l, int r, int b, int t)
    {
        projection_matrix_ = Mat4::Orthographic(
            l, r, b, t, 0.01f, 100.0f);
    }

    Mat4 projectionMatrix() const
    {
        return projection_matrix_;
    }

    Mat4 modelViewMatrix() const
    {
        FPType x = -position_.x;
        FPType y = -position_.y;
        FPType z = -position_.z;
        Mat4 t(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1);
        return t * rotation_.conjugate().matrix();
    }
};

}  // namespace bmce


#endif
