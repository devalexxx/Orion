//
// Created by Alex on 12/01/2024.
//

#include "doctest/doctest.h"

#include "omath.h"

TEST_SUITE("math") {

    TEST_CASE("dot") {

        SUBCASE("vector") {
            using orion::Vector3i;
            using orion::Vector3f;
            using orion::dot;

            auto v1 = Vector3i(1, 2, 3);
            auto v2 = Vector3i(1, 5, 7);

            CHECK_EQ(dot(v1, v2), 32);

            auto v3 = Vector3f(1.50, 2.25, 6.00);
            auto v4 = Vector3f(1.25, 5.00, 7.50);

            CHECK_EQ(dot(v3, v4), 58.125);
        }

        SUBCASE("matrix") {

        }

        SUBCASE("vector_matrix") {

        }

        SUBCASE("matrix_vector") {

        }

    }

}