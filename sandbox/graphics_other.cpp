//
// Created by Alex on 12/01/2024.
//

#include "doctest/doctest.h"

#include "graphics.h"
#include "omath.h"

TEST_CASE("sample_mode") {
    auto w = orion::Window::create("Sandbox");

    auto square_image = orion::Image::load_from_file(orion::resource::texture::of("facebook.png"), true);
    auto square_texture = orion::Texture::create_from_image(square_image);

    auto triangle_image = orion::Image::load_from_file(orion::resource::texture::of("hazard.png"), true);
    auto triangle_texture = orion::Texture::create_from_image(triangle_image);

    auto square0 = orion::Square();
    square0.set_texture(square_texture);

    auto square1 = orion::Square(orion::Vector3f(-3, 0, 0));
    square1.set_color(orion::Color::RED);

    auto triangle0 = orion::Triangle(orion::Vector3f(2, 0, 0));
    triangle0.set_texture(triangle_texture);

    auto triangle1 = orion::Triangle(orion::Vector3f(4, 0, 0));


    auto& view = w->get_view();
    view.translate(orion::Vector3f(3, 3, 10));
    view.look_at(orion::Vector3f::zero());

    while (!w->is_close()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        w->draw(square0);
        w->draw(square1);
        w->draw(triangle0);
        w->draw(triangle1);

        w->display();
    }
}

TEST_CASE("cam_move") {
    auto em = orion::EventManager::create();
    auto w = orion::Window::create("cam_move");
    w->set_event_manager(em);

    auto image = orion::Image::load_from_file(orion::resource::texture::of("dirt.png"), true);
    auto texture = orion::Texture::create_from_image(image);

    auto cube = orion::Cube();
    cube.set_texture(texture);

    auto& view = w->get_view();
    view.translate(orion::Vector3f(3, 3, 15));
    view.look_at(orion::Vector3f::zero());

    em->subscribe<orion::Input::KeyEvent>([&](orion::Ref<orion::Input::KeyEvent> e) {
        static auto& pos = view.get_position();

        if (e.pressed) {
            switch (e.key) {
                case orion::Input::Key::Z:
                view.translate(orion::Vector3f::FORWARD);
                break;
                case orion::Input::Key::Q:
                view.translate(orion::Vector3f::RIGHT);
                break;
                case orion::Input::Key::S:
                view.translate(orion::Vector3f::BACK);
                break;
                case orion::Input::Key::D:
                view.translate(orion::Vector3f::LEFT);
                break;
                case orion::Input::Key::ESCAPE:
                w->close();
                break;
                default:
                break;
            }
        }
    });

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    while (!w->is_close()) {
        w->clear(orion::ClearMask::COLOR | orion::ClearMask::DEPTH);

        w->draw(cube);

        w->display();
    }
}