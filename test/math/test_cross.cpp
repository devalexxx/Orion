//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "common.h"

TEST_SUITE("math") {

    TEST_CASE("cross") {
        using orion::Vector3f;
        using orion::cross;

        auto v1 = Vector3f( 3, 6, -2);
        auto v2 = Vector3f(-6, 4,  2);

        CHECK(vector_approx(cross(v1, v2), Vector3f(20.f, 6.f, 48.f)));
        CHECK(vector_approx(cross(v1, v2), -cross(v2, v1)));
    }

}