//
// Created by Alex on 16/01/2024.
//

#include "doctest/doctest.h"

#include "orion/graphics.h"

#include "numeric"

TEST_SUITE("other") {

    TEST_CASE("model_load") {
        using orion::Vector3f;

        auto w = orion::Window::create("ibo");

        auto model = orion::Model::load_from_file(orion::resource::model::of("4_subdivide_cube.obj"), true);

        std::cout << "4 sub : " << model.get_mesh()->get_length() << "\n";

        model = orion::Model::load_from_file(orion::resource::model::of("5_subdivide_cube.obj"), true);

        std::cout << "5 sub : " << model.get_mesh()->get_length() << "\n";

        model = orion::Model::load_from_file(orion::resource::model::of("6_subdivide_cube.obj"), true);

        std::cout << "6 sub : " << model.get_mesh()->get_length() << "\n";

//        auto& view = w->get_view();
//        view.translate(Vector3f(0.f, 0.f, 5.f));
//        view.look_at(Vector3f::zero());
//
//        auto shape = orion::Shape(model.get_mesh(), true);
//
//        orion::OpenGlApi::set_enable(orion::EnableCapability::DEPTH_TEST);
//        orion::OpenGlApi::set_depth_function(orion::DepthFunction::LESS);
//
//        while (!w->is_close()) {
//            w->clear(orion::ClearMask::DEPTH | orion::ClearMask::COLOR);
//
//            w->draw(shape);
//
//            w->display();
//        }
    }

    TEST_CASE("raw") {
        auto max_it = 1000;

        auto w = orion::Window::create("raw");

        orion::Window::disable_vsync();

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        auto vertices = std::vector<orion::Vector3f>{
                orion::Vector3f(-1., -1., 0.),
                orion::Vector3f(1., -1., 0.),
                orion::Vector3f(0., 1., 0.),
        };

        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(orion::Vector3f), vertices.data(), GL_STATIC_DRAW);

        auto shader = orion::Shader::load_from_file(orion::resource::shader::of("shape_vertex.glsl"), orion::resource::shader::of("shape_fragment.glsl"));

        shader->set_float_attrib_pointer("position", 3, 0, 0);

        shader->set_uniform("uniform_color", orion::Color::WHITE);
        shader->set_uniform("sample_mode", orion::EnumValue<orion::Shape::SampleMode>(orion::Shape::SampleMode::UNIFORM_COLOR));

        auto& view = w->get_view();
        view.translate(orion::Vector3f(0, 0, 5));
        view.look_at(orion::Vector3f(0, 0, 0));

        shader->set_uniform("view", view.get_view());
        shader->set_uniform("projection", view.get_projection());
        shader->set_uniform("model", orion::translate(orion::Vector3f(0, 0, 0)));

        shader->use();

        auto it = 0;

        std::vector<double> e_t;

        while (!w->is_close()) {

            auto start = glfwGetTime();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (int i = 0; i < 1; ++i) {
                glDrawArrays(GL_TRIANGLES, 0, 3);
            }

            w->display();

            e_t.push_back((glfwGetTime() - start) * 1000);

            if (++it == max_it)
                w->close();
        }

        std::cout << std::reduce(e_t.begin(), e_t.end()) / max_it << "\n";

        glDeleteBuffers(1, &vertexbuffer);
        glDeleteVertexArrays(1, &VertexArrayID);
    }

}