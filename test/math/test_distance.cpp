//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "omath.h"

TEST_SUITE("math") {

    TEST_CASE("distance") {
        using orion::Vector3f;
        using orion::distance;

        auto v1 = Vector3f( 7, 4, 3);
        auto v2 = Vector3f(17, 6, 2);

        CHECK_EQ(distance(v1, v2), doctest::Approx(10.246951));
        CHECK_EQ(distance(v1, v2), doctest::Approx(distance(v2, v1)));
    }

}