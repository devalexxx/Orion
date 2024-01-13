//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "omath.h"

TEST_SUITE("math") {

    TEST_CASE("magnitude") {
        using orion::magnitude;

        SUBCASE("float") {
            using orion::Vector2f;
            using orion::Vector3f;

            auto v1 = Vector2f(4.f, 3.f);

            CHECK_EQ(magnitude(v1), doctest::Approx(5.f));

            auto v2 = Vector3f(2.f, 4.f, 8.f);

            CHECK_EQ(magnitude(v2), doctest::Approx(2.f * sqrt(21.f)));
        }

        SUBCASE("double") {
            using orion::Vector2d;
            using orion::Vector3d;

            auto v1 = Vector2d(4.f, 3.f);

            CHECK_EQ(magnitude(v1), doctest::Approx(5.f));

            auto v2 = Vector3d(2.f, 4.f, 8.f);

            CHECK_EQ(magnitude(v2), doctest::Approx(2.f * sqrt(21.f)));
        }
    }

}