//
// Created by Alex on 08/12/2023.
//

#include "doctest/doctest.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "fmt/ranges.h"

#include <fstream>
#include <sstream>
#include <random>
#include <tuple>

#include "graphics.h"
#include "omath.h"

TEST_SUITE("sandbox") {

    TEST_CASE("window") {

        auto w = orion::Window::create("Sandbox");

        SUBCASE("clean_code_texture") {
            auto shader = orion::Shader::load_from_file("resource/shader/cc_texture_vertex.glsl",
                                                        "resource/shader/cc_texture_fragment.glsl");

            auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
            auto texture = orion::Texture::create_from_image(image);

            GLuint vertexarray;
            glGenVertexArrays(1, &vertexarray);
            glBindVertexArray(vertexarray);

            auto vertices = std::vector<float>{
                    0.0f, 0.8f, 0.0f, 0.5f, 1.0f,
                    -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
                    0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(shader->get_attrib_location("position"));
            glVertexAttribPointer(shader->get_attrib_location("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                  (void *) nullptr);

            glEnableVertexAttribArray(shader->get_attrib_location("uv"));
            glVertexAttribPointer(shader->get_attrib_location("uv"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                  (void *) (3 * sizeof(float)));

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->use();

                glActiveTexture(GL_TEXTURE0);
                texture->bind();
                shader->set_uniform("texture_sampler", 0);

                glBindVertexArray(vertexarray);

                glDrawArrays(GL_TRIANGLES, 0, 3);

                glBindVertexArray(0);
                orion::Shader::unbind();

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &vertexarray);
        }

        SUBCASE("clean_code_texture_view") {
            auto shader = orion::Shader::load_from_file("resource/shader/basic_texture_vertex.glsl",
                                                        "resource/shader/basic_texture_fragment.glsl");

            auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
            auto texture = orion::Texture::create_from_image(image);

            auto view = orion::View(orion::Vector3f(3, 3, 3));

            auto model = orion::Matrix4f::identity();

            GLuint vertexarray;
            glGenVertexArrays(1, &vertexarray);
            glBindVertexArray(vertexarray);

            auto vertices = std::vector<float>{
                    0.0f, 0.8f, 0.0f, 0.5f, 1.0f,
                    -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
                    0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(shader->get_attrib_location("position"));
            glVertexAttribPointer(shader->get_attrib_location("position"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                  (void *) nullptr);

            glEnableVertexAttribArray(shader->get_attrib_location("uv"));
            glVertexAttribPointer(shader->get_attrib_location("uv"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                                  (void *) (3 * sizeof(float)));

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->use();

                shader->set_uniform("projection", view.get_projection());
                shader->set_uniform("view", view.get_view());

                shader->set_uniform("model", model);

                glActiveTexture(GL_TEXTURE0);
                texture->bind();
                shader->set_uniform("texture_sampler", 0);

                glBindVertexArray(vertexarray);

                glDrawArrays(GL_TRIANGLES, 0, 3);

                glBindVertexArray(0);
                orion::Texture::unbind();
                orion::Shader::unbind();

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &vertexarray);
        }

        SUBCASE("text_vao_vbo_obj") {
            using orion::Vector3f;
            using orion::Vector2f;
            using orion::PackedVertex;

            auto shader = orion::Shader::load_from_file("resource/shader/basic_texture_vertex.glsl",
                                                        "resource/shader/basic_texture_fragment.glsl");

            auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
            auto texture = orion::Texture::create_from_image(image);

            auto view = orion::View(orion::Vector3f(3, 3, 3));

            auto model = orion::Matrix4f::identity();
            auto model2 = orion::translate(orion::Matrix4f::identity(), -orion::Vector3f(3, 0, 0));

            auto vao = orion::VertexArray::create();
            vao->bind();

            auto data = std::vector<PackedVertex>{{
                                                          PackedVertex(Vector3f(0.0f, 1.0f, 0.0f),
                                                                       Vector2f(0.5f, 1.0f)),
                                                          PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),
                                                                       Vector2f(0.0f, 0.0f)),
                                                          PackedVertex(Vector3f(1.0f, -1.0f, 0.0f),
                                                                       Vector2f(1.0f, 0.0f))
                                                  }};

            auto buffer = orion::VertexBuffer(orion::VertexBuffer::Type::ARRAY);
            buffer.set_data(data, shader);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->use();

                shader->set_uniform("projection", view.get_projection());
                shader->set_uniform("view", view.get_view());

                shader->set_uniform("model", model);

                glActiveTexture(GL_TEXTURE0);
                texture->bind();
                shader->set_uniform("texture_sampler", 0);

                vao->draw(3);

                shader->set_uniform("model", model2);
                vao->draw(3);

                orion::VertexArray::unbind();
                orion::Texture::unbind();
                orion::Shader::unbind();

                w->display();
            }
        }

        SUBCASE("vbo_into_vao") {
            using orion::Vector3f;
            using orion::Vector2f;
            using orion::PackedVertex;

            auto shader = orion::Shader::load_from_file("resource/shader/basic_texture_vertex.glsl",
                                                        "resource/shader/basic_texture_fragment.glsl");

            auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
            auto texture = orion::Texture::create_from_image(image);

            auto view = orion::View(orion::Vector3f(3, 3, 3));

            auto model = orion::Matrix4f::identity();
            auto model2 = orion::translate(orion::Matrix4f::identity(), -orion::Vector3f(3, 0, 0));

            auto vao = orion::VertexArray::create();

            auto data = std::vector<PackedVertex>{{
                PackedVertex(Vector3f(0.0f, 1.0f, 0.0f),Vector2f(0.5f, 1.0f)),
                PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),Vector2f(0.0f, 0.0f)),
                PackedVertex(Vector3f(1.0f, -1.0f, 0.0f),Vector2f(1.0f, 0.0f))
            }};

            auto &buffer = vao->add_buffer(orion::VertexBuffer::Type::ARRAY);
            buffer.set_data(data, shader);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->use();

                shader->set_uniform("projection", view.get_projection());
                shader->set_uniform("view", view.get_view());

                shader->set_uniform("model", model);

                glActiveTexture(GL_TEXTURE0);
                texture->bind();
                shader->set_uniform("texture_sampler", 0);

                vao->draw(3);

                shader->set_uniform("model", model2);
                vao->draw(3);

                orion::VertexArray::unbind();
                orion::Texture::unbind();
                orion::Shader::unbind();

                w->display();
            }

        }

    }

    TEST_CASE("shapes") {
        using orion::Vector3f;
        using orion::Vector2f;

        auto w = orion::Window::create("Sandbox");

        SUBCASE("triangle_obj") {

            auto image = orion::Image::load_from_file("resource/texture/hazard.png", true);
            auto texture = orion::Texture::create_from_image(image);

            auto image2 = orion::Image::load_from_file("resource/texture/triangle.png", true);
            auto texture2 = orion::Texture::create_from_image(image2);

            auto triangle = orion::Triangle();
            triangle.set_texture(texture);

            auto triangle2 = orion::Triangle(Vector3f(2, 0, 0));
            triangle2.set_texture(texture2);

            auto triangle3 = orion::Triangle(Vector3f(-2, 0, 0));
            triangle3.set_texture(texture2);


            auto& view = w->get_view();
            view.set_position(Vector3f(3, 3, 3));
            view.look_at(Vector3f::zero());

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                w->draw(triangle);
                w->draw(triangle2);
                w->draw(triangle3);

                w->display();
            }
        }

        SUBCASE("square_obj") {

            auto image = orion::Image::load_from_file("resource/texture/facebook.png", true);
            auto texture = orion::Texture::create_from_image(image);

            auto square = orion::Square();
            square.set_texture(texture);

            auto square1 = orion::Square(Vector3f(-2, 0, 0));
            square1.set_texture(texture);
            square1.get_transform().set_scale(Vector3f(2));

            auto square2 = orion::Square(Vector3f(2, 0, 0));
            square2.set_texture(texture);
            square2.get_transform().set_scale(Vector3f(1, 2, 1));


            auto& view = w->get_view();
            view.set_position(Vector3f(3, 3, 10));
            view.look_at(Vector3f::zero());

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                w->draw(square);
                w->draw(square1);
                w->draw(square2);

                w->display();
            }
        }
    }
}
