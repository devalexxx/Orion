//
// Created by Alex on 13/12/2023.
//

#include "doctest/doctest.h"

#include <iostream>

#include "omath.h"

TEST_SUITE("vector") {

    TEST_CASE("vector_2") {
        CHECK_EQ(orion::Vector2i::UP, orion::Vector2i(0, 1));
        CHECK_EQ(orion::Vector2i::DOWN, orion::Vector2i(0, -1));
        CHECK_EQ(orion::Vector2i::LEFT, orion::Vector2i(-1, 0));
        CHECK_EQ(orion::Vector2i::RIGHT, orion::Vector2i(1, 0));

        CHECK_EQ(orion::Vector2i::zero(), orion::Vector2i(0));
        CHECK_EQ(orion::Vector2i::one(), orion::Vector2i(1));

        auto v1 = orion::Vector2f(6.f, 12.f);
        auto v2 = orion::Vector2f(0.5, 2.f);
        CHECK_EQ(v1 + v2, orion::Vector2f(6.5, 14.f));
        CHECK_EQ(v1 + 0.5f, orion::Vector2f(6.5, 12.5));
        CHECK_EQ(v1 - v2, orion::Vector2f(5.5, 10.));
        CHECK_EQ(v1 - 0.5f, orion::Vector2f(5.5, 11.5));
        CHECK_EQ(v1 * v2, orion::Vector2f(3.f, 24.f));
        CHECK_EQ(v1 * 0.5f, orion::Vector2f(3.f, 6.f));
        CHECK_EQ(v1 / v2, orion::Vector2f(12.f, 6.f));
        CHECK_EQ(v1 / 0.5f, orion::Vector2f(12.f, 24.f));

        auto v3 = orion::Vector2f::one();
        CHECK_EQ(orion::magnitude(v3), doctest::Approx(sqrt(2.f)).epsilon(0.00001));

        auto nv1 =  orion::normalize(v1);
        CHECK_EQ(nv1.get_x(), doctest::Approx(v1.get_x() / orion::magnitude(v1)).epsilon(0.00001));
        CHECK_EQ(nv1.get_y(), doctest::Approx(v1.get_y() / orion::magnitude(v1)).epsilon(0.00001));

        CHECK_EQ(dot(v1, v2), 27.f);

        CHECK_EQ(orion::degree(angle(v1, v2)), doctest::Approx(12.5288).epsilon(0.00001));
        CHECK_EQ(angle(v1, v2), doctest::Approx(orion::rad(12.5288)).epsilon(0.00001));

        auto v4 = orion::Vector3f (1, 2, 3);
        auto v5 = orion::Vector3f (3, 2, 1);

        CHECK_EQ(distance(v1, v2), doctest::Approx(11.4127).epsilon(0.00001));

        CHECK_EQ(cross(v4, v5), orion::Vector3f(-4, 8, -4));

        auto m0 = orion::Matrix4f (1);
        auto v6 = orion::Vector4f (1, 2, 3, 4);
        CHECK_EQ(dot(m0, v6), orion::Vector4f(10, 10, 10, 10));
        CHECK_EQ(dot(m0, v6), dot(v6, m0));
    }

}