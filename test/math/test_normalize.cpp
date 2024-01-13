//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "omath.h"

#include "common.h"

TEST_SUITE("math") {

    TEST_CASE("normalize") {

        SUBCASE("float") {
            using orion::Vector2f;
            using orion::Vector3f;
            using orion::normalize;

            auto v1 = Vector2f(4.f, 3.f);

            CHECK(vector_approx(normalize(v1), Vector2f(0.8f, 0.6f)));

            auto v2 = Vector3f(2.f, 4.f, 8.f);

            CHECK(vector_approx(normalize(v2), Vector3f(0.2182179f, 0.4364358f, 0.8728715f)));
        }

        SUBCASE("double") {
            using orion::Vector2d;
            using orion::Vector3d;
            using orion::normalize;

            auto v1 = Vector2d(4., 3.);

            CHECK(vector_approx(normalize(v1), Vector2d(0.8, 0.6)));

            auto v2 = Vector3d(2., 4., 8.);

            CHECK(vector_approx(normalize(v2), Vector3d(0.2182179, 0.4364358, 0.8728715)));
        }

    }

}