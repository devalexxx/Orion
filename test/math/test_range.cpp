//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "common.h"
#include <functional>

TEST_SUITE("math") {

    TEST_CASE("range") {
        using orion::map_range;

        SUBCASE("value") {
            CHECK_EQ(map_range(5.f, 0.f, 10.f, 0.f, 100.f), 50.f);
            CHECK_EQ(map_range(5.,  0.,  10.,  0.,  100.),  50.);

            CHECK_EQ(map_range(0.8f, 0.f, 1.f, 0.f, 10.f), 8.f);
            CHECK_EQ(map_range(0.8,  0.,  1.,  0.,  10.),  8.);
        }

        SUBCASE("vector") {
            using orion::f32;
            using orion::f64;
            using orion::Vector2f;
            using orion::Vector3f;
            using orion::Vector2d;
            using orion::Vector3d;

            auto v1 = Vector2f(0.33f, 0.73f);
            CHECK(vector_approx(map_range(v1, 0.f, 1.f, 0.f, 10.f), Vector2f(3.3f, 7.3f)));

            auto v2 = Vector2d(0.33, 0.73);
            CHECK(vector_approx(map_range(v2, 0., 1., 0., 10.), Vector2d(3.3, 7.3)));

            auto v3 = Vector3f(3.25f, 2.115f, 6.76f);
            CHECK(vector_approx(map_range(v3, 0.f, 10.f, 0.f, 1.f), Vector3f(0.325f, 0.2115f, 0.676f)));

            auto v4 = Vector3d(3.25, 2.115, 6.76);
            CHECK(vector_approx(map_range(v4, 0., 10., 0., 1.), Vector3d(0.325, 0.2115, 0.676)));
        }

    }

}