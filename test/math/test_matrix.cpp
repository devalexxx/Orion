//
// Created by Alex on 13/12/2023.
//
//
//#include "doctest/doctest.h"
//
//#include "fmt/core.h"
//#include "iostream"
//
//#include "omath.h"
//
//TEST_SUITE("matrix") {
//
//    TEST_CASE("matrix_4") {
//        auto m0 = orion::Matrix4f (1);
//        auto m1 = orion::Matrix4f ({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
//        CHECK_EQ(dot(m0, m1), orion::Matrix4f({28, 32, 36, 40, 28, 32, 36, 40, 28, 32, 36, 40, 28, 32, 36, 40}));
//        CHECK_EQ(dot(m1, m0), orion::Matrix4f({10, 10, 10, 10, 26, 26, 26, 26, 42, 42, 42, 42, 58, 58, 58, 58}));
//
//        auto m2 = orion::look_at(orion::Vector3f(3,-3,3), orion::Vector3f::zero(), orion::Vector3f::UP);
//
//        auto t_x = atan2(-m2[2][0], sqrt((m2[2][1] * m2[2][1]) + (m2[2][2] * m2[2][2])));
//        auto t_y = atan2(m2[2][1], m2[2][2]);
//        auto t_z = atan2(m2[0][0], m2[1][0]);
//
//        fmt::print("x : {}, y : {}, z : {}\n", orion::degree(t_x), orion::degree(t_y), orion::degree(t_z));
//    }
//
//}