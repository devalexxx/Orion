//
// Created by Alex on 13/12/2023.
//

#include "doctest/doctest.h"

#include "omath.h"

TEST_SUITE("math") {

    template<size_t S>
    bool fucking_float_operator(orion::Ref<orion::Vector<S, orion::f32>> lhs, orion::Ref<orion::Vector<S, orion::f32>> rhs) {
        for (orion::u32 i = 0; i < S; ++i) {
            if (lhs[i] != doctest::Approx(rhs[i]))
                return false;
        }
        return true;
    }

    TEST_CASE("vector2") {

        SUBCASE("vector2i") {
            using orion::Vector2i;
            using orion::Vector3i;

            CHECK_EQ(Vector2i::UP,    Vector2i( 0,  1));
            CHECK_EQ(Vector2i::DOWN,  Vector2i( 0, -1));
            CHECK_EQ(Vector2i::LEFT,  Vector2i(-1,  0));
            CHECK_EQ(Vector2i::RIGHT, Vector2i( 1,  0));

            CHECK_EQ(Vector2i::zero(), Vector2i(0, 0));
            CHECK_EQ(Vector2i::one(),  Vector2i(1, 1));

            CHECK_EQ(Vector2i(4), Vector2i(4, 4));

            auto v1 = Vector2i(8, 4);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);

            CHECK_EQ(v1 + 5, 5 + v1);
            CHECK_EQ(v1 - 1, Vector2i( 7,  3));
            CHECK_EQ(1 - v1, Vector2i(-7, -3));
            CHECK_EQ(0 - v1, -v1);
            CHECK_EQ(1 * v1, v1);
            CHECK_EQ(2 * v1, v1 * 2);
            CHECK_EQ(v1 / 2,  Vector2i(4, 2));
            CHECK_EQ(16 / v1, Vector2i(2, 4));

            auto v2 = Vector2i(-4, -9);

            CHECK_EQ(v1 + v2, Vector2i(4, -5));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector2i( 12,  13));
            CHECK_EQ(v2 - v1, Vector2i(-12, -13));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector2i(-32, -36));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector2i( 8 / -4,  4 / -9));
            CHECK_EQ(v2 / v1, Vector2i(-4 /  8, -9 /  4));

            auto v3 = Vector3i(3, 5, 1);

            CHECK_EQ(Vector2i(v3), Vector2i(3, 5));
        }

        SUBCASE("vector2u") {
            using orion::Vector2u;
            using orion::Vector3u;
            using orion::u32;

            CHECK_EQ(Vector2u::UP,    Vector2u(      0u,       1u));
            CHECK_EQ(Vector2u::DOWN,  Vector2u(      0u, (u32)-1u));
            CHECK_EQ(Vector2u::LEFT,  Vector2u((u32)-1u,       0u));
            CHECK_EQ(Vector2u::RIGHT, Vector2u(      1u,       0u));

            CHECK_EQ(Vector2u::zero(), Vector2u(0u, 0u));
            CHECK_EQ(Vector2u::one(),  Vector2u(1u, 1u));

            CHECK_EQ(Vector2u(4u), Vector2u(4u, 4u));

            auto v1 = Vector2u(8u, 4u);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);

            CHECK_EQ(v1 + 5u, 5u + v1);
            CHECK_EQ(v1 - 1u, Vector2u( 7u,  3u));
            CHECK_EQ(1u - v1, Vector2u(-7u, -3u));
            CHECK_EQ(0u - v1, -v1);
            CHECK_EQ(1u * v1, v1);
            CHECK_EQ(2u * v1, v1 * 2u);
            CHECK_EQ(v1 / 2u,  Vector2u(4u, 2u));
            CHECK_EQ(16u / v1, Vector2u(2u, 4u));

            auto v2 = Vector2u((u32)-4u, (u32)-9u);

            CHECK_EQ(v1 + v2, Vector2u(4u, (u32)-5u));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector2u(      12u,       13u));
            CHECK_EQ(v2 - v1, Vector2u((u32)-12u, (u32)-13u));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector2u((u32)-32u, (u32)-36u));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector2u(      8u / (u32)-4u,       4u / (u32)-9u));
            CHECK_EQ(v2 / v1, Vector2u((u32)-4u /       8u, (u32)-9u /       4u));

            auto v3 = Vector3u(3u, 5u, 1u);

            CHECK_EQ(Vector2u(v3), Vector2u(3u, 5u));
        }

        SUBCASE("vector2f") {
            using orion::Vector2f;
            using orion::Vector3f;

            CHECK_EQ(Vector2f::UP,    Vector2f( 0.f,  1.f));
            CHECK_EQ(Vector2f::DOWN,  Vector2f( 0.f, -1.f));
            CHECK_EQ(Vector2f::LEFT,  Vector2f(-1.f,  0.f));
            CHECK_EQ(Vector2f::RIGHT, Vector2f( 1.f,  0.f));

            CHECK_EQ(Vector2f::zero(), Vector2f(0.f, 0.f));
            CHECK_EQ(Vector2f::one(),  Vector2f(1.f, 1.f));

            CHECK_EQ(Vector2f(4.f), Vector2f(4.f, 4.f));

            auto v1 = Vector2f(8.f, 4.f);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);

            CHECK_EQ(v1 + 5.f, 5.f + v1);
            CHECK_EQ(v1 - 1.f, Vector2f( 7.f,  3.f));
            CHECK_EQ(1.f - v1, Vector2f(-7.f, -3.f));
            CHECK_EQ(0.f - v1, -v1);
            CHECK_EQ(1.f * v1, v1);
            CHECK_EQ(2.f * v1, v1 * 2.f);
            CHECK_EQ(v1 / 2.f,  Vector2f(4.f, 2.f));
            CHECK_EQ(16.f / v1, Vector2f(2.f, 4.f));

            auto v2 = Vector2f(-4.f, -9.f);

            CHECK_EQ(v1 + v2, Vector2f(4.f, -5.f));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector2f( 12.f,  13.f));
            CHECK_EQ(v2 - v1, Vector2f(-12.f, -13.f));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector2f(-32.f, -36.f));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector2f( 8.f / -4.f,  4.f / -9.f));
            CHECK_EQ(v2 / v1, Vector2f(-4.f /  8.f, -9.f /  4.f));

            auto v3 = Vector3f(3.f, 5.f, 1.f);

            CHECK_EQ(Vector2f(v3), Vector2f(3.f, 5.f));
        }

        SUBCASE("vector2d") {
            using orion::Vector2d;
            using orion::Vector3d;

            CHECK_EQ(Vector2d::UP,    Vector2d( 0.,  1.));
            CHECK_EQ(Vector2d::DOWN,  Vector2d( 0., -1.));
            CHECK_EQ(Vector2d::LEFT,  Vector2d(-1.,  0.));
            CHECK_EQ(Vector2d::RIGHT, Vector2d( 1.,  0.));

            CHECK_EQ(Vector2d::zero(), Vector2d(0., 0.));
            CHECK_EQ(Vector2d::one(),  Vector2d(1., 1.));

            CHECK_EQ(Vector2d(4.), Vector2d(4., 4.));

            auto v1 = Vector2d(8., 4.);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);

            CHECK_EQ(v1 + 5., 5. + v1);
            CHECK_EQ(v1 - 1., Vector2d( 7.,  3.));
            CHECK_EQ(1. - v1, Vector2d(-7., -3.));
            CHECK_EQ(0. - v1, -v1);
            CHECK_EQ(1. * v1, v1);
            CHECK_EQ(2. * v1, v1 * 2.);
            CHECK_EQ(v1 / 2.,  Vector2d(4., 2.));
            CHECK_EQ(16. / v1, Vector2d(2., 4.));

            auto v2 = Vector2d(-4., -9.);

            CHECK_EQ(v1 + v2, Vector2d(4., -5.));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector2d( 12.,  13.));
            CHECK_EQ(v2 - v1, Vector2d(-12., -13.));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector2d(-32., -36.));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector2d( 8. / -4.,  4. / -9.));
            CHECK_EQ(v2 / v1, Vector2d(-4. /  8., -9. /  4.));

            auto v3 = Vector3d(3., 5., 1.);

            CHECK_EQ(Vector2d(v3), Vector2d(3., 5.));
        }
    }

    TEST_CASE("vector3") {

        SUBCASE("vector3i") {
            using orion::Vector2i;
            using orion::Vector3i;
            using orion::Vector4i;

            CHECK_EQ(Vector3i::UP,      Vector3i( 0,  1,  0));
            CHECK_EQ(Vector3i::DOWN,    Vector3i( 0, -1,  0));
            CHECK_EQ(Vector3i::LEFT,    Vector3i(-1,  0,  0));
            CHECK_EQ(Vector3i::RIGHT,   Vector3i( 1,  0,  0));
            CHECK_EQ(Vector3i::FORWARD, Vector3i( 0,  0,  1));
            CHECK_EQ(Vector3i::BACK,    Vector3i( 0,  0, -1));

            CHECK_EQ(Vector3i::zero(), Vector3i(0, 0, 0));
            CHECK_EQ(Vector3i::one(),  Vector3i(1, 1, 1));

            CHECK_EQ(Vector3i(4), Vector3i(4, 4, 4));

            auto v1 = Vector3i(8, 4, 16);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);

            CHECK_EQ(v1 + 5, 5 + v1);
            CHECK_EQ(v1 - 1, Vector3i( 7,  3,  15));
            CHECK_EQ(1 - v1, Vector3i(-7, -3, -15));
            CHECK_EQ(0 - v1, -v1);
            CHECK_EQ(1 * v1, v1);
            CHECK_EQ(2 * v1, v1 * 2);
            CHECK_EQ(v1 / 2,  Vector3i(4, 2, 8));
            CHECK_EQ(16 / v1, Vector3i(2, 4, 1));

            auto v2 = Vector3i(-4, -9, 5);

            CHECK_EQ(v1 + v2, Vector3i(4, -5, 21));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector3i( 12,  13,  11));
            CHECK_EQ(v2 - v1, Vector3i(-12, -13, -11));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector3i(-32, -36,  80));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector3i( 8 / -4,  4 / -9, 16 /  5));
            CHECK_EQ(v2 / v1, Vector3i(-4 /  8, -9 /  4,  5 / 16));

            auto v3 = Vector2i(3, 5);

            CHECK_EQ(Vector3i(v3, 5), Vector3i(3, 5, 5));

            auto v4 = Vector4i(3, 5, 5, 2);

            CHECK_EQ(Vector3i(v4), Vector3i(3, 5, 5));
        }

        SUBCASE("vector3u") {
            using orion::Vector2u;
            using orion::Vector3u;
            using orion::Vector4u;
            using orion::u32;

            CHECK_EQ(Vector3u::UP,      Vector3u( 0u, 1u, 0u));
            CHECK_EQ(Vector3u::DOWN,    Vector3u( 0u,-1u, 0u));
            CHECK_EQ(Vector3u::LEFT,    Vector3u(-1u, 0u, 0u));
            CHECK_EQ(Vector3u::RIGHT,   Vector3u( 1u, 0u, 0u));
            CHECK_EQ(Vector3u::FORWARD, Vector3u( 0u, 0u, 1u));
            CHECK_EQ(Vector3u::BACK,    Vector3u( 0u, 0u,-1u));

            CHECK_EQ(Vector3u::zero(), Vector3u(0u, 0u, 0u));
            CHECK_EQ(Vector3u::one(),  Vector3u(1u, 1u, 1u));

            CHECK_EQ(Vector3u(4u), Vector3u(4u, 4u, 4u));

            auto v1 = Vector3u(8u, 4u, 16u);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);

            CHECK_EQ(v1 + 5u, 5u + v1);
            CHECK_EQ(v1 - 1u, Vector3u( 7u,  3u,  15u));
            CHECK_EQ(1u - v1, Vector3u(-7u, -3u, -15u));
            CHECK_EQ(0u - v1, -v1);
            CHECK_EQ(1u * v1, v1);
            CHECK_EQ(2u * v1, v1 * 2u);
            CHECK_EQ(v1 / 2u,  Vector3u(4u, 2u, 8u));
            CHECK_EQ(16u / v1, Vector3u(2u, 4u, 1u));

            auto v2 = Vector3u((u32)-4u, (u32)-9u, 5u);

            CHECK_EQ(v1 + v2, Vector3u(4u, -5u, 21u));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector3u( 12u,  13u,  11u));
            CHECK_EQ(v2 - v1, Vector3u(-12u, -13u, -11u));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector3u(-32u, -36u, 80u));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector3u( 8u / -4u,  4u / -9u, 16u /  5u));
            CHECK_EQ(v2 / v1, Vector3u(-4u /  8u, -9u /  4u,  5u / 16u));

            auto v3 = Vector2u(3u, 5u);

            CHECK_EQ(Vector3u(v3, 3u), Vector3u(3u, 5u, 3u));

            auto v4 = Vector4u(3u, 5u, 5u, 2u);

            CHECK_EQ(Vector3u(v4), Vector3u(3u, 5u, 5u));
        }

        SUBCASE("vector3f") {
            using orion::Vector2f;
            using orion::Vector3f;
            using orion::Vector4f;

            CHECK_EQ(Vector3f::UP,      Vector3f( 0.f,  1.f,  0.f));
            CHECK_EQ(Vector3f::DOWN,    Vector3f( 0.f, -1.f,  0.f));
            CHECK_EQ(Vector3f::LEFT,    Vector3f(-1.f,  0.f,  0.f));
            CHECK_EQ(Vector3f::RIGHT,   Vector3f( 1.f,  0.f,  0.f));
            CHECK_EQ(Vector3f::FORWARD, Vector3f( 0.f,  0.f,  1.f));
            CHECK_EQ(Vector3f::BACK,    Vector3f( 0.f,  0.f, -1.f));

            CHECK_EQ(Vector3f::zero(), Vector3f(0.f, 0.f, 0.f));
            CHECK_EQ(Vector3f::one(),  Vector3f(1.f, 1.f, 1.f));

            CHECK_EQ(Vector3f(4.f), Vector3f(4.f, 4.f, 4.f));

            auto v1 = Vector3f(8.f, 4.f, 16.f);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);

            CHECK_EQ(v1 + 5.f, 5.f + v1);
            CHECK_EQ(v1 - 1.f, Vector3f( 7.f,  3.f,  15.f));
            CHECK_EQ(1.f - v1, Vector3f(-7.f, -3.f, -15.f));
            CHECK_EQ(0.f - v1, -v1);
            CHECK_EQ(1.f * v1, v1);
            CHECK_EQ(2.f * v1, v1 * 2.f);
            CHECK_EQ(v1 / 2.f,  Vector3f(4.f, 2.f, 8.f));
            CHECK_EQ(16.f / v1, Vector3f(2.f, 4.f, 1.f));

            auto v2 = Vector3f(-4.f, -9.f, 5.f);

            CHECK_EQ(v1 + v2, Vector3f(4.f, -5.f, 21.f));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector3f( 12.f,  13.f,  11.f));
            CHECK_EQ(v2 - v1, Vector3f(-12.f, -13.f, -11.f));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector3f(-32.f, -36.f,  80.f));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector3f( 8.f / -4.f,  4.f / -9.f, 16.f /  5.f));
            CHECK_EQ(v2 / v1, Vector3f(-4.f /  8.f, -9.f /  4.f,  5.f / 16.f));

            auto v3 = Vector2f(3.f, 5.f);

            CHECK_EQ(Vector3f(v3, 5.f), Vector3f(3.f, 5.f, 5.f));

            auto v4 = Vector4f(3.f, 5.f, 5.f, 2.f);

            CHECK_EQ(Vector3f(v4), Vector3f(3.f, 5.f, 5.f));
        }

        SUBCASE("vector3d") {
            using orion::Vector2d;
            using orion::Vector3d;
            using orion::Vector4d;

            CHECK_EQ(Vector3d::UP,      Vector3d( 0.,  1.,  0.));
            CHECK_EQ(Vector3d::DOWN,    Vector3d( 0., -1.,  0.));
            CHECK_EQ(Vector3d::LEFT,    Vector3d(-1.,  0.,  0.));
            CHECK_EQ(Vector3d::RIGHT,   Vector3d( 1.,  0.,  0.));
            CHECK_EQ(Vector3d::FORWARD, Vector3d( 0.,  0.,  1.));
            CHECK_EQ(Vector3d::BACK,    Vector3d( 0.,  0., -1.));

            CHECK_EQ(Vector3d::zero(), Vector3d(0., 0., 0.));
            CHECK_EQ(Vector3d::one(),  Vector3d(1., 1., 1.));

            CHECK_EQ(Vector3d(4.), Vector3d(4., 4., 4.));

            auto v1 = Vector3d(8., 4., 16.);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);

            CHECK_EQ(v1 + 5., 5. + v1);
            CHECK_EQ(v1 - 1., Vector3d( 7.,  3.,  15.));
            CHECK_EQ(1. - v1, Vector3d(-7., -3., -15.));
            CHECK_EQ(0. - v1, -v1);
            CHECK_EQ(1. * v1, v1);
            CHECK_EQ(2. * v1, v1 * 2.);
            CHECK_EQ(v1 / 2.,  Vector3d(4., 2., 8.));
            CHECK_EQ(16. / v1, Vector3d(2., 4., 1.));

            auto v2 = Vector3d(-4., -9., 5.);

            CHECK_EQ(v1 + v2, Vector3d(4., -5., 21.));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector3d( 12.,  13.,  11.));
            CHECK_EQ(v2 - v1, Vector3d(-12., -13., -11.));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector3d(-32., -36.,  80.));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector3d( 8. / -4.,  4. / -9., 16. /  5.));
            CHECK_EQ(v2 / v1, Vector3d(-4. /  8., -9. /  4.,  5. / 16.));

            auto v3 = Vector2d(3., 5.);

            CHECK_EQ(Vector3d(v3, 5.), Vector3d(3., 5., 5.));

            auto v4 = Vector4d(3., 5., 5., 2.);

            CHECK_EQ(Vector3d(v4), Vector3d(3., 5., 5.));
        }
    }

    TEST_CASE("vector4") {

        SUBCASE("vector4i") {
            using orion::Vector3i;
            using orion::Vector4i;

            CHECK_EQ(Vector4i::zero(), Vector4i(0, 0, 0, 0));
            CHECK_EQ(Vector4i::one(),  Vector4i(1, 1, 1, 1));

            CHECK_EQ(Vector4i(4), Vector4i(4, 4, 4, 4));

            auto v1 = Vector4i(8, 4, 16, 32);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);
            CHECK_EQ(v1.get_w(), v1[3]);

            CHECK_EQ(v1 + 5, 5 + v1);
            CHECK_EQ(v1 - 1, Vector4i( 7,  3,  15, 31));
            CHECK_EQ(1 - v1, Vector4i(-7, -3, -15, -31));
            CHECK_EQ(0 - v1, -v1);
            CHECK_EQ(1 * v1, v1);
            CHECK_EQ(2 * v1, v1 * 2);
            CHECK_EQ(v1 / 2,  Vector4i(4, 2, 8, 16));
            CHECK_EQ(16 / v1, Vector4i(2, 4, 1, 16 / 32));

            auto v2 = Vector4i(-4, -9, 5, 2);

            CHECK_EQ(v1 + v2, Vector4i(4, -5, 21, 34));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector4i( 12,  13,  11,  30));
            CHECK_EQ(v2 - v1, Vector4i(-12, -13, -11, -30));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector4i(-32, -36,  80, 64));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector4i( 8 / -4,  4 / -9, 16 /  5, 16));
            CHECK_EQ(v2 / v1, Vector4i(-4 /  8, -9 /  4,  5 / 16,  2 / 32));

            auto v3 = Vector3i(3, 5, 3);

            CHECK_EQ(Vector4i(v3, 5), Vector4i(3, 5, 3, 5));
        }

        SUBCASE("vector4u") {
            using orion::Vector3u;
            using orion::Vector4u;

            CHECK_EQ(Vector4u::zero(), Vector4u(0u, 0u, 0u, 0u));
            CHECK_EQ(Vector4u::one(),  Vector4u(1u, 1u, 1u, 1u));

            CHECK_EQ(Vector4u(4u), Vector4u(4u, 4u, 4u, 4u));

            auto v1 = Vector4u(8u, 4u, 16u, 32u);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);
            CHECK_EQ(v1.get_w(), v1[3]);

            CHECK_EQ(v1 + 5u, 5u + v1);
            CHECK_EQ(v1 - 1u, Vector4u( 7u,  3u,  15u,  31u));
            CHECK_EQ(1u - v1, Vector4u(-7u, -3u, -15u, -31u));
            CHECK_EQ(0u - v1, -v1);
            CHECK_EQ(1u * v1, v1);
            CHECK_EQ(2u * v1, v1 * 2u);
            CHECK_EQ(v1 / 2u,  Vector4u(4u, 2u, 8u,       16u));
            CHECK_EQ(16u / v1, Vector4u(2u, 4u, 1u, 16u / 32u));

            auto v2 = Vector4u(-4u, -9u, 5u, 2u);

            CHECK_EQ(v1 + v2, Vector4u(4u, -5u, 21u, 34u));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector4u( 12u,  13u,  11u,  30u));
            CHECK_EQ(v2 - v1, Vector4u(-12u, -13u, -11u, -30u));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector4u(-32u, -36u, 80u, 64u));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector4u( 8u / -4u,  4u / -9u, 16u /  5u,       16u));
            CHECK_EQ(v2 / v1, Vector4u(-4u /  8u, -9u /  4u,  5u / 16u, 2u / 32u));

            auto v3 = Vector3u(3u, 5u, 3u);

            CHECK_EQ(Vector4u(v3, 5u), Vector4u(3u, 5u, 3u, 5u));
        }

        SUBCASE("vector4f") {
            using orion::Vector3f;
            using orion::Vector4f;

            CHECK_EQ(Vector4f::zero(), Vector4f(0.f, 0.f, 0.f, 0.f));
            CHECK_EQ(Vector4f::one(),  Vector4f(1.f, 1.f, 1.f, 1.f));

            CHECK_EQ(Vector4f(4.f), Vector4f(4.f, 4.f, 4.f, 4.f));

            auto v1 = Vector4f(8.f, 4.f, 16.f, 32.f);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);
            CHECK_EQ(v1.get_w(), v1[3]);

            CHECK_EQ(v1 + 5.f, 5.f + v1);
            CHECK_EQ(v1 - 1.f, Vector4f( 7.f,  3.f,  15.f,  31.f));
            CHECK_EQ(1.f - v1, Vector4f(-7.f, -3.f, -15.f, -31.f));
            CHECK_EQ(0.f - v1, -v1);
            CHECK_EQ(1.f * v1, v1);
            CHECK_EQ(2.f * v1, v1 * 2.f);
            CHECK_EQ(v1 / 2.f,  Vector4f(4.f, 2.f, 8.f,        16.f));
            CHECK(fucking_float_operator(16.f / v1, Vector4f(2.f, 4.f, 1.f, 16.f / 32.f)));

            auto v2 = Vector4f(-4.f, -9.f, 5.f, 2.f);

            CHECK_EQ(v1 + v2, Vector4f(4.f, -5.f, 21.f, 34.f));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector4f( 12.f,  13.f,  11.f,  30.f));
            CHECK_EQ(v2 - v1, Vector4f(-12.f, -13.f, -11.f, -30.f));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector4f(-32.f, -36.f,  80.f, 64.f));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK(fucking_float_operator(v1 / v2, Vector4f( 8.f / -4.f,  4.f / -9.f, 16.f /  5.f,       16.f)));
            CHECK(fucking_float_operator(v2 / v1, Vector4f(-4.f /  8.f, -9.f /  4.f,  5.f / 16.f, 2.f / 32.f)));

            auto v3 = Vector3f(3.f, 5.f, 3.f);

            CHECK_EQ(Vector4f(v3, 5.f), Vector4f(3.f, 5.f, 3.f, 5.f));
        }

        SUBCASE("vector4d") {
            using orion::Vector3d;
            using orion::Vector4d;

            CHECK_EQ(Vector4d::zero(), Vector4d(0., 0., 0., 0.));
            CHECK_EQ(Vector4d::one(),  Vector4d(1., 1., 1., 1.));

            CHECK_EQ(Vector4d(4.), Vector4d(4., 4., 4., 4.));

            auto v1 = Vector4d(8., 4., 16., 32.);

            CHECK_EQ(v1.get_x(), v1[0]);
            CHECK_EQ(v1.get_y(), v1[1]);
            CHECK_EQ(v1.get_z(), v1[2]);
            CHECK_EQ(v1.get_w(), v1[3]);

            CHECK_EQ(v1 + 5., 5. + v1);
            CHECK_EQ(v1 - 1., Vector4d( 7.,  3.,  15.,  31.));
            CHECK_EQ(1. - v1, Vector4d(-7., -3., -15., -31.));
            CHECK_EQ(0. - v1, -v1);
            CHECK_EQ(1. * v1, v1);
            CHECK_EQ(2. * v1, v1 * 2.);
            CHECK_EQ(v1 / 2.,  Vector4d(4., 2., 8.,        16.));
            CHECK_EQ(16. / v1, Vector4d(2., 4., 1., 16. / 32.));

            auto v2 = Vector4d(-4., -9., 5., 2.);

            CHECK_EQ(v1 + v2, Vector4d(4., -5., 21., 34.));
            CHECK_EQ(v2 + v1, v1 + v2);
            CHECK_EQ(v1 - v2, Vector4d( 12.,  13.,  11.,  30.));
            CHECK_EQ(v2 - v1, Vector4d(-12., -13., -11., -30.));
            CHECK_EQ(v2 - v1, -(v1 - v2));
            CHECK_EQ(v1 * v2, Vector4d(-32., -36.,  80., 64.));
            CHECK_EQ(v1 * v2, v2 * v1);
            CHECK_EQ(v1 / v2, Vector4d( 8. / -4.,  4. / -9., 16. /  5.,      16.));
            CHECK_EQ(v2 / v1, Vector4d(-4. /  8., -9. /  4.,  5. / 16., 2. / 32.));

            auto v3 = Vector3d(3., 5., 3.);

            CHECK_EQ(Vector4d(v3, 5.), Vector4d(3., 5., 3., 5.));
        }
    }

}