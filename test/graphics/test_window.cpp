//
// Created by Alex on 12/11/2023.
//

#include "doctest/doctest.h"

#include "orion/graphics.h"

TEST_SUITE("graphics") {

    TEST_CASE("window") {

        SUBCASE("creation") {
            auto w = orion::Window::create("");
            w->close();
        }
    }

}