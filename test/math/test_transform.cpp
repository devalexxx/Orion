//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "common.h"

TEST_SUITE("math") {

    TEST_CASE("transform") {
        using orion::Matrix4f;
        using orion::Vector4f;
        using orion::Vector3f;

        SUBCASE("translate") {
            using orion::translate;

            auto t1 = Vector3f(3.2f, 5.5f, 7.6f);
            auto e1 = Matrix4f::identity();
            e1[3] = Vector4f(3.2f, 5.5f, 7.6f, 1.f);

            CHECK(matrix_approx(translate(t1), e1));

            auto t2 = Vector3f(4.4f, 1.5f, 0.4f);
            auto e2 = e1;
            e2[3] = Vector4f(t1 + t2, 1.f);

            CHECK(matrix_approx(translate(e1, t2), e2));
        }

        SUBCASE("scale") {
            using orion::scale;

            auto s1 = Vector3f(2);
            auto e1 = Matrix4f::identity();
            e1[0][0] *= s1[0];
            e1[1][1] *= s1[1];
            e1[2][2] *= s1[2];

            CHECK(matrix_approx(scale(s1), e1));

            auto s2 = Vector3f(2, 4, 3);
            auto e2 = e1;
            e2[0][0] *= s2[0];
            e2[1][1] *= s2[1];
            e2[2][2] *= s2[2];

            CHECK(matrix_approx(scale(e1, s2), e2));
        }

        SUBCASE("rotate") {
            using orion::rotate;

            auto a1 = 90.f;
            auto r1 = Vector3f::UP;
            auto e1 = Matrix4f({
                -0.4480736,  0.0000000,  0.8939967, 0.f,
                 0.0000000,  1.0000000,  0.0000000, 0.f,
                -0.8939967,  0.0000000, -0.4480736, 0.f,
                 0.f,        0.f,        0.f,       1.f,
            });

            CHECK(matrix_approx(rotate(a1, r1), e1));

            auto a2 = 90.f;
            auto r2 = Vector3f(1.f, 0.f, 1.f);
            auto e2 = Matrix4f({
                -0.770938, -0.632151, -0.077711, 0.f,
                 0.281891, -0.448074,  0.848391, 0.f,
                -0.571132,  0.632151,  0.523635, 0.f,
                 0.f,       0.f,       0.f,      1.f,
            });

            CHECK(matrix_approx(rotate(e1, a2, r2), e2));
        }

    }

}