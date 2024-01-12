//
// Created by Alex on 12/01/2024.
//

#include "doctest/doctest.h"

#include "graphics.h"
#include "omath.h"

TEST_CASE("triangle") {
    auto w = orion::Window::create("triangle");

    auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
    auto texture = orion::Texture::create_from_image(image);

    auto image2 = orion::Image::load_from_file("resource/texture/triangle.png", true);
    auto texture2 = orion::Texture::create_from_image(image2);

    auto triangle = orion::Triangle();
    triangle.set_texture(texture);

    auto triangle2 = orion::Triangle(orion::Vector3f(2, 0, 0));
    triangle2.set_texture(texture2);

    auto triangle3 = orion::Triangle(orion::Vector3f(-2, 0, 0));
    triangle3.set_texture(texture2);


    auto& view = w->get_view();
    view.translate(orion::Vector3f(3, 3, 3));
    view.look_at(orion::Vector3f::zero());

    while (!w->is_close()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        w->draw(triangle);
        w->draw(triangle2);
        w->draw(triangle3);

        w->display();
    }
}

TEST_CASE("square") {
    auto w = orion::Window::create("square");

    auto image = orion::Image::load_from_file("resource/texture/facebook.png", true);
    auto texture = orion::Texture::create_from_image(image);

    auto square = orion::Square();
    square.set_texture(texture);

    auto square1 = orion::Square(orion::Vector3f(-2, 0, 0));
    square1.set_texture(texture);
    square1.get_transform().set_scale(orion::Vector3f(2));

    auto square2 = orion::Square(orion::Vector3f(2, 0, 0));
    square2.set_texture(texture);
    square2.get_transform().set_scale(orion::Vector3f(1, 2, 1));


    auto& view = w->get_view();
    view.translate(orion::Vector3f(3, 3, 10));
    view.look_at(orion::Vector3f::zero());

    while (!w->is_close()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        w->draw(square);
        w->draw(square1);
        w->draw(square2);

        w->display();
    }
}

TEST_CASE("circle") {
    auto w = orion::Window::create("circle");

    auto image = orion::Image::load_from_file(orion::resource::texture::of("weird-circle.png"), true);
    auto texture = orion::Texture::create_from_image(image);

    auto circle = orion::Circle();
//    circle.set_texture(texture);

    auto& view = w->get_view();
    view.translate(orion::Vector3f(0, 0, 3));
    view.look_at(orion::Vector3f::zero());

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    while (!w->is_close()) {
        w->clear(orion::ClearMask::COLOR | orion::ClearMask::DEPTH);

        w->draw(circle);

        w->display();
    }
}

TEST_CASE("cube") {
    auto w = orion::Window::create("cube");

    auto image = orion::Image::load_from_file(orion::resource::texture::of("dirt.png"), true);
    auto texture = orion::Texture::create_from_image(image);

    auto cube = orion::Cube();
    cube.set_texture(texture);

    auto& rot = cube.get_transform().get_rotation();


    auto& view = w->get_view();
    view.translate(orion::Vector3f(3, 3, 10));
    view.look_at(orion::Vector3f::zero());

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    while (!w->is_close()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.get_transform().set_rotation(rot + orion::Vector3f(0.01f, 0.01f, 0.01f));

        w->draw(cube);

        w->display();
    }
}