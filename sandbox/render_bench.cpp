//
// Created by Alex on 15/01/2024.
//

#include "doctest/doctest.h"

#include "graphics.h"
#include "omath.h"

#include <chrono>
#include <numeric>
#include <algorithm>
#include <iostream>

TEST_SUITE("bench") {
    using orion::i32;
    using orion::f32;
    using orion::u32;

    void display_stats(orion::RefMut<std::vector<long long>> v) {
        auto to_fps = [](f32 us) {return (u32)(1.f / (us / 1000000.f));};

        std::sort(v.begin(), v.end());

        auto fq = v.begin() + (v.size() / 4);
        auto middle = v.begin() + (v.size() / 2);
        auto lq = v.end() - (v.size() / 4);
#ifdef ORION_DEBUG
        std::cout << "Draw call\t" << orion::OpenGlApi::CALL_TRACE.draw << "\n";
        std::cout << "Bind call\t" << orion::OpenGlApi::CALL_TRACE.bound << "\n";
        std::cout << "Prog call\t" << orion::OpenGlApi::CALL_TRACE.program << "\n";
        std::cout << "Unif call\t" << orion::OpenGlApi::CALL_TRACE.uniform << "\n\n";
#endif
        std::cout << "Central tendency :\n";
        auto avg = std::reduce(v.begin(), v.end()) / v.size();
        std::cout << "\tAverage\t\t" << avg << "\tus " << "(" << to_fps(avg) << ")\n";
        auto med = (v.size() % 2 == 0 ? (*middle + *(middle - 1)) / 2 : *middle);
        std::cout << "\tMedian\t\t" << med << "\tus " << "(" << to_fps(med) << ")\n";
        auto mm = (2 * std::reduce(fq, lq)) / v.size();
        std::cout << "\tMidMean\t\t" << mm << "\tus " << "(" << to_fps(mm) << ")\n";
        std::cout << "\nExtreme tendency:\n";
        std::cout << "\tMaximum\t\t" << *(v.end() - 1) << "\tus\n";
        std::cout << "\tMinimum\t\t" << *(v.begin()) << "\tus\n";
    }

    std::vector<orion::Shape> generate_shapes(orion::Ref<orion::Shape> shape, i32 t_x, i32 t_y, i32 t_z) {
        std::vector<orion::Shape> ret;
        ret.reserve(t_x * t_y * t_z);

        for (int x = -t_x; x < t_x; x += 2) {
            for (int y = -t_y; y < t_y; y += 2) {
                for (int z = -t_z; z < t_z; z += 2) {
                    ret.push_back(shape);
                    (ret.end() - 1)->get_transform().set_position(orion::Vector3f(x, y, z));
                }
            }
        }

        return ret;
    }

    TEST_CASE("render") {
        using orion::OpenGlApi;

        auto max_it =  1000;
        auto x_c_s  =  15;
        auto y_c_s  =  15;
        auto z_c_s  =  15;

        auto cam_offset = orion::Vector3f(0.f, 0.f, 50.f);
        auto cam_target = orion::Vector3f::zero();

        auto w = orion::Window::create("Bench");

        orion::Window::disable_vsync();

        w->get_view().translate(cam_offset);
        w->get_view().look_at  (cam_target);

        OpenGlApi::set_enable(orion::EnableCapability::CULL_FACE);
        OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
        OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

        SUBCASE("triangle") {
            auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::TRIANGLE), x_c_s, y_c_s, z_c_s);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                std::for_each(
                        shapes.begin(),
                        shapes.end(),
                        [&](orion::Ref<orion::Shape> shape) {
                            w->draw(shape);
                        }
                );

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<------------Triangle------------>\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("square") {
            auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::SQUARE), x_c_s, y_c_s, z_c_s);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                std::for_each(
                        shapes.begin(),
                        shapes.end(),
                        [&](orion::Ref<orion::Shape> shape) {
                            w->draw(shape);
                        }
                );

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<-------------Square------------->\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("indexed_circle") {
            auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::CIRCLE), x_c_s, y_c_s, z_c_s);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                std::for_each(
                        shapes.begin(),
                        shapes.end(),
                        [&](orion::Ref<orion::Shape> shape) {
                            w->draw(shape);
                        }
                );

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<---------Indexed-Circle--------->\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("circle") {
            auto&& shapes = generate_shapes(orion::Shape(orion::Mesh::REGISTRY.get(orion::mesh_name_builder(orion::Primitive::CIRCLE, false, "128")), true), x_c_s, y_c_s, z_c_s);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                std::for_each(
                        shapes.begin(),
                        shapes.end(),
                        [&](orion::Ref<orion::Shape> shape) {
                            w->draw(shape);
                        }
                );

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<-------------Circle------------->\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("indexed_cube") {
            auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::CUBE), x_c_s, y_c_s, z_c_s);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                std::for_each(
                        shapes.begin(),
                        shapes.end(),
                        [&](orion::Ref<orion::Shape> shape) {
                            w->draw(shape);
                        }
                );

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<----------Indexed-Cube---------->\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("cube") {
            auto&& shapes = generate_shapes(orion::Shape(orion::Mesh::REGISTRY.get(orion::mesh_name_builder(orion::Primitive::CUBE, false)), true), x_c_s, y_c_s, z_c_s);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                std::for_each(
                        shapes.begin(),
                        shapes.end(),
                        [&](orion::Ref<orion::Shape> shape) {
                            w->draw(shape);
                        }
                );

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<--------------Cube-------------->\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("4_subdivide_cube") {
            auto model = orion::Model::load_from_file(orion::resource::model::of("4_subdivide_cube.obj"), true);
            auto shape = orion::Shape(model.get_mesh(), true);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                w->draw(shape);

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<-------------4 Cube------------->\n\n";
            display_stats(elapsed_times);

        }

        SUBCASE("5_subdivide_cube") {
            auto model = orion::Model::load_from_file(orion::resource::model::of("5_subdivide_cube.obj"), true);
            auto shape = orion::Shape(model.get_mesh(), true);

            std::vector<long long> elapsed_times;

            auto it = 0;

            while (!w->is_close()) {

                auto start = std::chrono::high_resolution_clock::now();

                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

                w->draw(shape);

                w->display();

                auto stop = std::chrono::high_resolution_clock::now();

                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());

                if (++it == max_it)
                    w->close();

            }

            std::cout << "\n<-------------5 Cube------------->\n\n";
            display_stats(elapsed_times);

        }

//        SUBCASE("6_subdivide_cube") {
//            auto model = orion::Model::load_from_file(orion::resource::model::of("6_subdivide_cube.obj"), true);
//            auto shape = orion::Shape(model.get_mesh(), true);
//
//            std::vector<long long> elapsed_times;
//
//            auto it = 0;
//
//            while (!w->is_close()) {
//
//                auto start = std::chrono::high_resolution_clock::now();
//
//                w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);
//
//                w->draw(shape);
//
//                w->display();
//
//                auto stop = std::chrono::high_resolution_clock::now();
//
//                elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
//
//                if (++it == max_it)
//                    w->close();
//
//            }
//
//            std::cout << "\n<-------------6 Cube------------->\n\n";
//            display_stats(elapsed_times);
//
//        }

    }

}