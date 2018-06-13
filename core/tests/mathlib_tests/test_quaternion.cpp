#include "core/mathlib.h"

#include "gtest/gtest.h"

#include <iostream>


TEST(mathlib_tests, quat_mul_test1)
{
    bmce::Quat quat1(1, 3, 4, 3);
    bmce::Quat quat2(4, 3.9f, -1, -3);
    bmce::Quat quat3(5.3f, 6.9f, 35.7f, -9.6f);
    EXPECT_EQ(quat1 * quat2, quat3);
}


TEST(mathlib_tests, quat_mul_test2)
{
    bmce::Quat quat1(4, 1, 2, 3);
    bmce::Quat quat2(1, 2, 3, 4);
    bmce::Quat quat3(-16, 8, 16, 18);
    EXPECT_EQ(quat1 *= quat2, quat3);
}
