//
// Created by Alex on 18/01/2024.
//

#include "doctest/doctest.h"

#include "graphics.h"

TEST_SUITE("bench") {

    TEST_CASE("model_load") {
        using orion::Model;
        using namespace orion::resource;

        auto w = orion::Window::create("");

        w->close();

        SUBCASE("4_div_cube") {
            auto start = std::chrono::high_resolution_clock::now();

            auto model = Model::load_from_file(model::of("4_subdivide_cube.obj"));

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Cube with 4 subdiv\n";
            std::cout << "Load time :\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
            std::cout << "Mesh len :\t" << model.get_mesh()->get_length() << "\n\n";
        }

        SUBCASE("5_div_cube") {
            auto start = std::chrono::high_resolution_clock::now();

            auto model = Model::load_from_file(model::of("5_subdivide_cube.obj"));

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Cube with 5 subdiv\n";
            std::cout << "Load time :\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
            std::cout << "Mesh len :\t" << model.get_mesh()->get_length() << "\n\n";
        }

        SUBCASE("6_div_cube") {
            auto start = std::chrono::high_resolution_clock::now();

            auto model = Model::load_from_file(model::of("6_subdivide_cube.obj"));

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Cube with 6 subdiv\n";
            std::cout << "Load time :\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
            std::cout << "Mesh len :\t" << model.get_mesh()->get_length() << "\n\n";
        }

        SUBCASE("4_div_cube_index") {
            auto start = std::chrono::high_resolution_clock::now();

            auto model = Model::load_from_file(model::of("4_subdivide_cube.obj"), true);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Cube with 4 subdiv (indexed)\n";
            std::cout << "Load time :\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
            std::cout << "Mesh len :\t" << model.get_mesh()->get_length() << "\n\n";
        }

        SUBCASE("5_div_cube_index") {
            auto start = std::chrono::high_resolution_clock::now();

            auto model = Model::load_from_file(model::of("5_subdivide_cube.obj"), true);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Cube with 5 subdiv (indexed)\n";
            std::cout << "Load time :\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
            std::cout << "Mesh len :\t" << model.get_mesh()->get_length() << "\n\n";
        }

        SUBCASE("6_div_cube_index") {
            auto start = std::chrono::high_resolution_clock::now();

            auto model = Model::load_from_file(model::of("6_subdivide_cube.obj"), true);

            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Cube with 6 subdiv (indexed)\n";
            std::cout << "Load time :\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
            std::cout << "Mesh len :\t" << model.get_mesh()->get_length() << "\n\n";
        }

    }

}