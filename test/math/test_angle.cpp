//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "common.h"
#include <iostream>

TEST_SUITE("math") {

    TEST_CASE("angle") {

        SUBCASE("radian") {
            using orion::radian;

            CHECK_EQ(radian( 90.f), doctest::Approx(1.5708f));
            CHECK_EQ(radian(240.f), doctest::Approx(4.18879f));
        }

        SUBCASE("degree") {
            using orion::degree;

            CHECK_EQ(degree(1.5708f ), doctest::Approx( 90.f));
            CHECK_EQ(degree(4.18879f), doctest::Approx(240.f));
            CHECK_EQ(degree(1.f     ), doctest::Approx( 57.2958f));
        }

        SUBCASE("radian_degree") {
            using orion::radian;
            using orion::degree;

            CHECK_EQ(radian(degree(2.5f)), doctest::Approx(2.5f));
            CHECK_EQ(degree(radian(95.f)), doctest::Approx(95.f));
        }

        SUBCASE("angle_between_vector") {
            using orion::radian;
            using orion::angle;
            using orion::Vector2f;
            using orion::Vector3f;

            auto v1 = Vector2f(3.f, 2.f);
            auto v2 = Vector2f(5.f, 0.f);

            CHECK_EQ(angle(v1, v2), doctest::Approx(radian(33.690067525979785)));
            CHECK_EQ(angle(v1, v2), doctest::Approx(angle(v2, v1)));

            auto v3 = Vector3f(1.f, 6.f, 4.f);
            auto v4 = Vector3f(9.f, 5.f, 2.f);

            CHECK_EQ(angle(v3, v4), doctest::Approx(radian(52.00807961839339)));
            CHECK_EQ(angle(v3, v4), doctest::Approx(angle(v4, v3)));
        }

        SUBCASE("euler_angle") {
            using orion::Matrix4f;
            using orion::Vector3f;
            using orion::euler_angle;

            auto m1 = Matrix4f({
                0.5930296, -0.3851179,  0.7071068, 0.f,
                0.5930296, -0.3851179, -0.7071068, 0.f,
                0.5446391,  0.8386706,  0.f      , 0.f,
                0.f,        0.f,        0.f,       1.f
            });

            CHECK(vector_approx(euler_angle(m1), Vector3f(1.5707963, 0.7853981, 0.5759587)));

            auto m2 = Matrix4f({
                0.5000000,  0.0000000, -0.8660254, 0.f,
                0.5566704, -0.7660444,  0.3213938, 0.f,
               -0.6634139, -0.6427876, -0.3830222, 0.f,
                0.f,        0.f,        0.f,       1.f
            });

            CHECK(vector_approx(euler_angle(m2), Vector3f(-2.4434609, -1.0471975, 0)));
        }

    }

}