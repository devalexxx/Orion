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

    auto max_it = 100;
    auto x_c_s  =  10;
    auto y_c_s  =  10;
    auto z_c_s  =  10;

    auto cam_offset = orion::Vector3f(0.f, 0.f, 100.f);

    void display_stats(orion::RefMut<std::vector<long long>> v) {
        std::sort(v.begin(), v.end());
        std::cout << "Average\t\t" << std::reduce(v.begin(), v.end()) / v.size() << "\tus\n";
        std::cout << "Maximum\t\t" << *(v.end() - 1) << "\tus\n";
        std::cout << "Minimum\t\t" << *(v.begin()) << "\tus\n";
        auto middle = v.begin() + (v.size() / 2);
        std::cout << "Median\t\t" << (v.size() % 2 == 0 ? (*middle + *(middle - 1)) / 2 : *middle) << "\tus\n";
    }

    void configure_view(orion::RefMut<orion::View> view) {
        view.translate(cam_offset);
        view.look_at(orion::Vector3f::zero());
//        view.set_far(200.f);
    }

    void set_opengl_opt() {
        using orion::OpenGlApi;
        using orion::EnableCapability;
        using orion::DepthFunction;
        using orion::CullFace;
        using orion::FrontFace;

//        OpenGlApi::set_enable(EnableCapability::CULL_FACE);
//        OpenGlApi::set_cull_face(CullFace::FRONT);
//        OpenGlApi::set_front_face(FrontFace::CLOCKWISE);

        OpenGlApi::set_enable(EnableCapability::DEPTH_TEST);
        OpenGlApi::set_depth_function(DepthFunction::LESS);
    }

    std::vector<orion::Shape> generate_shapes(orion::Ref<orion::Shape> shape) {
        std::vector<orion::Shape> ret;
        ret.reserve(x_c_s * y_c_s * z_c_s);

        for (int x = -x_c_s; x < x_c_s; x += 2) {
            for (int y = -y_c_s; y < y_c_s; y += 2) {
                for (int z = -z_c_s; z < z_c_s; z += 2) {
                    ret.push_back(shape);
                    (ret.end() - 1)->get_transform().set_position(orion::Vector3f(x, y, z));
                }
            }
        }

        return ret;
    }

    TEST_CASE("triangle") {
        auto w = orion::Window::create("Triangle");

        auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::TRIANGLE));

        configure_view(w->get_view());
        set_opengl_opt();

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

    TEST_CASE("square") {
        auto w = orion::Window::create("Square");

        auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::SQUARE));

        configure_view(w->get_view());
        set_opengl_opt();

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

    TEST_CASE("indexed_circle") {
        auto w = orion::Window::create("Indexed-Circle");

        auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::CIRCLE));

        configure_view(w->get_view());
        set_opengl_opt();

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

    TEST_CASE("circle") {
        auto w = orion::Window::create("Circle");

        auto&& shapes = generate_shapes(orion::Shape(orion::Mesh::REGISTRY.get(orion::mesh_name_builder(orion::Primitive::CIRCLE, false, "128")), true));

        configure_view(w->get_view());
        set_opengl_opt();

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

    TEST_CASE("indexed_cube") {
        auto w = orion::Window::create("Indexed-Cube");

        auto&& shapes = generate_shapes(orion::Shape(orion::Primitive::CUBE));

        configure_view(w->get_view());
        set_opengl_opt();

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

    TEST_CASE("cube") {
        auto w = orion::Window::create("Cube");

        auto&& shapes = generate_shapes(orion::Shape(orion::Mesh::REGISTRY.get(orion::mesh_name_builder(orion::Primitive::CUBE, false)), true));

        configure_view(w->get_view());
        set_opengl_opt();

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

//    TEST_CASE("rotated-cube") {
//        auto w = orion::Window::create("Rotated-Cube");
//
//        auto cube = orion::Shape(orion::Primitive::CUBE);
////        auto cube = orion::Shape(orion::Mesh::REGISTRY.get(orion::mesh_name_builder(orion::Primitive::CUBE, false)),true);
//
//        auto& rot = cube.get_transform().get_rotation();
//
//        set_opengl_opt();
//
//        auto& view = w->get_view();
//        view.translate(orion::Vector3f(2.f, 3.f, 5));
//        view.look_at(orion::Vector3f::zero());
//
//        while (!w->is_close()) {
//            w->clear(orion::ClearMask::COLOR | orion::ClearMask::DEPTH);
//
//            cube.get_transform().set_rotation(rot + orion::Vector3f(0.0f, 0.01f, 0.0f));
//
//            w->draw(cube);
//
//            w->display();
//        }
//    }

}