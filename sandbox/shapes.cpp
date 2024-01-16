//
// Created by Alex on 12/01/2024.
//

#include "doctest/doctest.h"

#include "graphics.h"
#include "omath.h"

#include <chrono>

TEST_CASE("triangle") {
    auto w = orion::Window::create("triangle");

    auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
    auto texture = orion::Texture::create_from_image(image);

    auto image2 = orion::Image::load_from_file("resource/texture/triangle.png", true);
    auto texture2 = orion::Texture::create_from_image(image2);

    auto triangle = orion::Shape(orion::Primitive::TRIANGLE);
    triangle.set_texture(texture);

    auto triangle2 = orion::Shape(orion::Primitive::TRIANGLE);
    triangle2.get_transform().set_position(orion::Vector3f(2, 0, 0));
    triangle2.set_texture(texture2);

    auto triangle3 = orion::Shape(orion::Primitive::TRIANGLE);
    triangle3.get_transform().set_position(orion::Vector3f(-2, 0, 0));
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

    auto square = orion::Shape(orion::Primitive::SQUARE);
    square.set_texture(texture);

    auto square1 = orion::Shape(orion::Primitive::SQUARE);
    square1.set_texture(texture);
    square1.get_transform().set_position(orion::Vector3f(-2, 0, 0));
    square1.get_transform().set_scale(orion::Vector3f(2));

    auto square2 = orion::Shape(orion::Primitive::SQUARE);;
    square2.set_texture(texture);
    square2.get_transform().set_position(orion::Vector3f(2, 0, 0));
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

TEST_CASE("cube") {
    auto w = orion::Window::create("cube");

    auto image = orion::Image::load_from_file(orion::resource::texture::of("dirt.png"), true);
    auto texture = orion::Texture::create_from_image(image);

    auto cube = orion::Shape(orion::Primitive::CUBE);
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

TEST_CASE("circle") {
    auto w = orion::Window::create("circle");

    auto image = orion::Image::load_from_file(orion::resource::texture::of("weird-circle.png"), true);
    auto texture = orion::Texture::create_from_image(image);

    auto circle = orion::Shape(orion::Primitive::CIRCLE);
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

TEST_CASE("sphere") {
    auto w = orion::Window::create("sphere");

//    auto image = orion::Image::load_from_file(orion::resource::texture::of("weird-circle.png"), true);
//    auto texture = orion::Texture::create_from_image(image);

    auto sphere = orion::Shape(orion::Primitive::SPHERE);
//    sphere.set_color(orion::Color::RED);

    auto& rot = sphere.get_transform().get_rotation();

    auto& view = w->get_view();
    view.translate(orion::Vector3f(0, 0, 5));
    view.look_at(orion::Vector3f::zero());

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    while (!w->is_close()) {
        w->clear(orion::ClearMask::COLOR | orion::ClearMask::DEPTH);

        sphere.get_transform().set_rotation(rot + orion::Vector3f(0.01f, 0.01f, 0.01f));

        w->draw(sphere);

        w->display();
    }
}

TEST_CASE("index_cube") {
    using orion::PackedVertex;
    using orion::u32;
    using orion::Vector3f;
    using orion::Vector2f;
    using orion::generator::index;
    using orion::generator::cube_vertices;
    using orion::generator::sphere_vertices;
    using orion::generator::circle_vertices;
    using namespace orion::resource;

    auto w = orion::Window::create("ibo");

    auto& view = w->get_view();
    view.translate(Vector3f(0.f, 0.f, 5.f));
    view.look_at(Vector3f::zero());

    auto model = orion::translate(Vector3f::zero());

    auto [vertices, indices] = index(cube_vertices());

    auto shader = orion::Shader::load_from_file(shader::of("shape_vertex.glsl"),shader::of("shape_fragment.glsl"));

    auto context = orion::RenderContext();
    context.set_shader(shader);

    auto vao = orion::VertexArray();
    auto& vbo = vao.add_buffer(orion::VertexBuffer::Type::ARRAY, orion::VertexBuffer::Usage::STATIC);
    vbo.set_data(vertices);

    auto& ibo = vao.add_buffer(orion::VertexBuffer::Type::ELEMENT, orion::VertexBuffer::Usage::STATIC);
    ibo.set_data(indices);

    shader->set_uniform("view",         view.get_view());
    shader->set_uniform("projection",   view.get_projection());
    shader->set_uniform("model",        model);
    shader->set_uniform("uniform_color",orion::Color::WHITE);
    shader->set_uniform("sample_mode",  2);

    vbo.bind();
    shader->set_float_attrib_pointer("position", 3, 8, 0);
    shader->set_float_attrib_pointer("normal",   3, 8, 3);
    shader->set_float_attrib_pointer("uv",       2, 8, 6);

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    while (!w->is_close()) {
        w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

        shader->use();

        vao.bind();
        ibo.bind();
//        gl_check(glDrawElements(std::underlying_type<orion::VertexArray::DrawMode>::type (context.get_draw_mode()), indices.size(), GL_UNSIGNED_BYTE, nullptr));
        gl_check(glDrawElements(std::underlying_type<orion::VertexArray::DrawMode>::type (context.get_draw_mode()), indices.size(), GL_UNSIGNED_SHORT, nullptr));

        orion::VertexArray::unbind();

        orion::Shader::unbind();

        w->display();
    }

}

TEST_CASE("index_cube_w_mesh") {
    using orion::PackedVertex;
    using orion::u32;
    using orion::Vector3f;
    using orion::Vector2f;
    using orion::Mesh;
    using orion::generator::index;
    using orion::generator::cube_vertices;
    using orion::generator::sphere_vertices;
    using orion::generator::circle_vertices;
    using namespace orion::resource;

    auto w = orion::Window::create("ibo");

    auto& view = w->get_view();
    view.translate(Vector3f(0.f, 0.f, 5.f));
    view.look_at(Vector3f::zero());

    auto model = orion::translate(Vector3f::zero());

    auto mesh = Mesh::create(index(cube_vertices()));

    auto shader = orion::Shader::load_from_file(shader::of("shape_vertex.glsl"),shader::of("shape_fragment.glsl"));

    auto context = orion::RenderContext();
    context.set_shader(shader);

    shader->set_uniform("view",         view.get_view());
    shader->set_uniform("projection",   view.get_projection());
    shader->set_uniform("model",        model);
    shader->set_uniform("uniform_color",orion::Color::WHITE);
    shader->set_uniform("sample_mode",  2);

    mesh->get_vao().bind();
    mesh->get_vao().get_buffer(0).bind();
    shader->set_float_attrib_pointer("position", 3, 8, 0);
    shader->set_float_attrib_pointer("normal",   3, 8, 3);
    shader->set_float_attrib_pointer("uv",       2, 8, 6);

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    while (!w->is_close()) {
        w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

        shader->use();

        mesh->get_vao().bind();
        mesh->get_vao().get_ibo()->bind();
        gl_check(glDrawElements(std::underlying_type<orion::VertexArray::DrawMode>::type (context.get_draw_mode()), mesh->get_length(), GL_UNSIGNED_SHORT, nullptr));

        orion::VertexBuffer::unbind();
        orion::VertexArray ::unbind();

        orion::Shader::unbind();

        w->display();
    }

}

TEST_CASE("mesh_shape") {
    using orion::Vector3f;

    auto w = orion::Window::create("ibo");

    auto& view = w->get_view();
    view.translate(Vector3f(0.f, 0.f, 5.f));
    view.look_at(Vector3f::zero());

    auto cube = orion::Shape(orion::Primitive::TRIANGLE);
    auto cube2 = orion::Shape(orion::Primitive::TRIANGLE);
    auto cube3 = orion::Shape(orion::Primitive::TRIANGLE);
    auto cube4 = orion::Shape(orion::Primitive::TRIANGLE);
    auto cube5 = orion::Shape(orion::Primitive::TRIANGLE);
    auto cube6 = orion::Shape(orion::Primitive::TRIANGLE);

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    while (!w->is_close()) {
        w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

        w->draw(cube);

        w->display();
    }

}

TEST_CASE("time_tester") {
    auto w = orion::Window::create("ibo");

    auto& view = w->get_view();
    view.translate(orion::Vector3f(0.f, 0.f, 5.f));
    view.look_at(orion::Vector3f::zero());

    auto cube = orion::Shape(orion::Primitive::TRIANGLE);

    orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
    orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);

    std::vector<long long> elapsed_times;

    auto max_it = 1000;
    auto it     = 0;

    while (!w->is_close()) {

        auto start = std::chrono::high_resolution_clock::now();

        w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);

        w->draw(cube);

        w->display();

        auto stop = std::chrono::high_resolution_clock::now();

        elapsed_times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(start - stop).count());

        if (++it == max_it)
            w->close();

    }

}