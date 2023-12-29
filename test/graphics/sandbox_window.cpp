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

    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if(VertexShaderStream.is_open()){
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        }else{
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
            getchar();
            return 0;
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if(FragmentShaderStream.is_open()){
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;


        // Compile Vertex Shader
        printf("Compiling shader : %s\n", vertex_file_path);
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }



        // Compile Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }



        // Link the program
        printf("Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }


        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;
    }

    static auto cube_vertices() {
        auto vertices = std::vector<glm::vec3> {
            glm::vec3 (-1.0f,-1.0f,-1.0f),
            glm::vec3 (-1.0f,-1.0f, 1.0f),
            glm::vec3 (-1.0f, 1.0f, 1.0f),

            glm::vec3 (1.0f, 1.0f,-1.0f),
            glm::vec3 (-1.0f,-1.0f,-1.0f),
            glm::vec3 (-1.0f, 1.0f,-1.0f),

            glm::vec3 (1.0f,-1.0f, 1.0f),
            glm::vec3 (-1.0f,-1.0f,-1.0f),
            glm::vec3 (1.0f,-1.0f,-1.0f),

            glm::vec3 (1.0f, 1.0f,-1.0f),
            glm::vec3 (1.0f,-1.0f,-1.0f),
            glm::vec3 (-1.0f,-1.0f,-1.0f),

            glm::vec3 (-1.0f,-1.0f,-1.0f),
            glm::vec3 (-1.0f, 1.0f, 1.0f),
            glm::vec3 (-1.0f, 1.0f,-1.0f),

            glm::vec3 (1.0f,-1.0f, 1.0f),
            glm::vec3 (-1.0f,-1.0f, 1.0f),
            glm::vec3 (-1.0f,-1.0f,-1.0f),

            glm::vec3 (-1.0f, 1.0f, 1.0f),
            glm::vec3 (-1.0f,-1.0f, 1.0f),
            glm::vec3 (1.0f,-1.0f, 1.0f),

            glm::vec3 (1.0f, 1.0f, 1.0f),
            glm::vec3 (1.0f,-1.0f,-1.0f),
            glm::vec3 (1.0f, 1.0f,-1.0f),

            glm::vec3 (1.0f,-1.0f,-1.0f),
            glm::vec3 (1.0f, 1.0f, 1.0f),
            glm::vec3 (1.0f,-1.0f, 1.0f),

            glm::vec3 (1.0f, 1.0f, 1.0f),
            glm::vec3 (1.0f, 1.0f,-1.0f),
            glm::vec3 (-1.0f, 1.0f,-1.0f),

            glm::vec3 (1.0f, 1.0f, 1.0f),
            glm::vec3 (-1.0f, 1.0f,-1.0f),
            glm::vec3 (-1.0f, 1.0f, 1.0f),

            glm::vec3 (1.0f, 1.0f, 1.0f),
            glm::vec3 (-1.0f, 1.0f, 1.0f),
            glm::vec3 (1.0f,-1.0f, 1.0f),
        };
        return vertices;
    }

    static auto custom_vec3_cube_vertices() {
        auto vertices = std::vector<orion::Vector3f> {
                orion::Vector3f(-1.0f,-1.0f,-1.0f),
                orion::Vector3f(-1.0f,-1.0f, 1.0f),
                orion::Vector3f(-1.0f, 1.0f, 1.0f),

                orion::Vector3f(1.0f, 1.0f,-1.0f),
                orion::Vector3f(-1.0f,-1.0f,-1.0f),
                orion::Vector3f(-1.0f, 1.0f,-1.0f),

                orion::Vector3f(1.0f,-1.0f, 1.0f),
                orion::Vector3f(-1.0f,-1.0f,-1.0f),
                orion::Vector3f(1.0f,-1.0f,-1.0f),

                orion::Vector3f(1.0f, 1.0f,-1.0f),
                orion::Vector3f(1.0f,-1.0f,-1.0f),
                orion::Vector3f(-1.0f,-1.0f,-1.0f),

                orion::Vector3f(-1.0f,-1.0f,-1.0f),
                orion::Vector3f(-1.0f, 1.0f, 1.0f),
                orion::Vector3f(-1.0f, 1.0f,-1.0f),

                orion::Vector3f(1.0f,-1.0f, 1.0f),
                orion::Vector3f(-1.0f,-1.0f, 1.0f),
                orion::Vector3f(-1.0f,-1.0f,-1.0f),

                orion::Vector3f(-1.0f, 1.0f, 1.0f),
                orion::Vector3f(-1.0f,-1.0f, 1.0f),
                orion::Vector3f(1.0f,-1.0f, 1.0f),

                orion::Vector3f(1.0f, 1.0f, 1.0f),
                orion::Vector3f(1.0f,-1.0f,-1.0f),
                orion::Vector3f(1.0f, 1.0f,-1.0f),

                orion::Vector3f(1.0f,-1.0f,-1.0f),
                orion::Vector3f(1.0f, 1.0f, 1.0f),
                orion::Vector3f(1.0f,-1.0f, 1.0f),

                orion::Vector3f(1.0f, 1.0f, 1.0f),
                orion::Vector3f(1.0f, 1.0f,-1.0f),
                orion::Vector3f(-1.0f, 1.0f,-1.0f),

                orion::Vector3f(1.0f, 1.0f, 1.0f),
                orion::Vector3f(-1.0f, 1.0f,-1.0f),
                orion::Vector3f(-1.0f, 1.0f, 1.0f),

                orion::Vector3f(1.0f, 1.0f, 1.0f),
                orion::Vector3f(-1.0f, 1.0f, 1.0f),
                orion::Vector3f(1.0f,-1.0f, 1.0f),
        };
        return vertices;
    }

    static auto cube_uvs() {
        auto uvs = std::vector<glm::vec2> {
            glm::vec2 (0.f, 0.f),
            glm::vec2 (0.f, 1.f),
            glm::vec2 (1.f, 1.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 0.f),
            glm::vec2 (0.f, 1.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 0.f),
            glm::vec2 (1.f, 0.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (1.f, 0.f),
            glm::vec2 (0.f, 0.f),

            glm::vec2 (0.f, 0.f),
            glm::vec2 (1.f, 1.f),
            glm::vec2 (1.f, 0.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 1.f),
            glm::vec2 (0.f, 0.f),

            glm::vec2 (0.f, 1.f),
            glm::vec2 (0.f, 0.f),
            glm::vec2 (1.f, 0.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 0.f),
            glm::vec2 (1.f, 0.f),

            glm::vec2 (0.f, 0.f),
            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 1.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (1.f, 0.f),
            glm::vec2 (0.f, 0.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 0.f),
            glm::vec2 (0.f, 1.f),

            glm::vec2 (1.f, 1.f),
            glm::vec2 (0.f, 1.f),
            glm::vec2 (1.f, 0.f),
        };
        return uvs;
    }

    static auto default_mvp(const std::shared_ptr<orion::Window>& w) {
        auto position = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));

        glm::rotate(glm::mat4(0), 0.f, glm::vec3(1, 0, 0));

        auto x_rotation = glm::rotate(0.f, glm::vec3(1, 0, 0));
        auto y_rotation = glm::rotate(0.f, glm::vec3(0, 1, 0));
        auto z_rotation = glm::rotate(0.f, glm::vec3(0, 0, 1));
        auto rotation = x_rotation + y_rotation + z_rotation;


        auto scale = glm::scale(glm::mat4 (1), glm::vec3(1, 1, 1));

        auto model = position * rotation * scale;

        auto view = glm::lookAt(
                glm::vec3(4,3,3),
                glm::vec3(0,0,0),
                glm::vec3(0,1,0)
        );

        auto projection = glm::perspective(
                glm::radians(45.0f),
                ((float) w->get_size().get_x()) / ((float) w->get_size().get_y()),
                0.1f,
                100.0f
        );

        return projection * view * model;
    }

    TEST_CASE("window") {

        auto w = orion::Window::create("Sandbox");

//        glewExperimental = true;
//        CHECK_EQ(glewInit(), GLEW_OK);

        SUBCASE("triangles") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            auto vertices = std::vector<glm::vec3>{
                    glm::vec3(-1., -1., 0.),
                    glm::vec3(1., -1., 0.),
                    glm::vec3(0., 1., 0.),
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

            auto program = LoadShaders("resource/shader/simple_vertex.glsl", "resource/shader/simple_fragment.glsl");

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glUseProgram(program);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 3);
                glDisableVertexAttribArray(0);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
            glDeleteProgram(program);
        }

        SUBCASE("transformation") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            auto vertices = std::vector<glm::vec3>{
                    glm::vec3(-1., -1., 0.),
                    glm::vec3(1., -1., 0.),
                    glm::vec3(0., 1., 0.),
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

            auto program = LoadShaders("resource/shader/transform_vertex.glsl", "resource/shader/simple_fragment.glsl");

            auto mvp_id = glGetUniformLocation(program, "mvp");

            auto mvp = default_mvp(w);

            glUseProgram(program);

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 3);
                glDisableVertexAttribArray(0);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
            glDeleteProgram(program);
        }

        SUBCASE("rotate") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            auto vertices = std::vector<glm::vec3>{
                    glm::vec3(-1., -1., 0.),
                    glm::vec3(1., -1., 0.),
                    glm::vec3(0., 1., 0.),
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

            auto program = LoadShaders("resource/shader/transform_vertex.glsl", "resource/shader/simple_fragment.glsl");

            auto mvp_id = glGetUniformLocation(program, "mvp");

            auto position = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));

            auto x_rotation = glm::rotate(0.f, glm::vec3(1, 0, 0));
            auto y_rotation = glm::rotate(0.f, glm::vec3(0, 1, 0));
            auto z_rotation = glm::rotate(0.f, glm::vec3(0, 0, 1));
            auto rotation = x_rotation + y_rotation + z_rotation;

            auto scale = glm::scale(glm::vec3(1, 1, 1));

//            auto model = position * rotation * scale;

            auto view = glm::lookAt(
                    glm::vec3(4, 3, 3),
                    glm::vec3(0, 0, 0),
                    glm::vec3(0, 1, 0)
            );

            auto projection = glm::perspective(
                    glm::radians(45.0f),
                    ((float) w->get_size().get_x()) / ((float) w->get_size().get_y()),
                    0.1f,
                    100.0f
            );

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                rotation = glm::rotate(rotation, glm::radians(2.f), glm::vec3(0, 1, 0));

                auto model = position * rotation * scale;

                auto mvp = projection * view * model;

                glUseProgram(program);

                glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 3);
                glDisableVertexAttribArray(0);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
            glDeleteProgram(program);
        }

        SUBCASE("shader_class") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            auto vertices = std::vector<glm::vec3>{
                    glm::vec3(-1., -1., 0.),
                    glm::vec3(1., -1., 0.),
                    glm::vec3(0., 1., 0.),
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

            auto shader = orion::Shader::load_from_file("resource/shader/transform_vertex.glsl",
                                                        "resource/shader/simple_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 3);
                glDisableVertexAttribArray(0);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("colored_cube") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_vertices().size() * sizeof(glm::vec3), cube_vertices().data(),
                         GL_STATIC_DRAW);

            auto colors = std::vector<glm::vec3>();

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> rnd(0, 100);

            for (int v = 0; v < 12 * 3; v++) {
                colors.emplace_back((float) rnd(rng) / 100., (float) rnd(rng) / 100., (float) rnd(rng) / 100.);
            }

            GLuint colorbuffer;
            glGenBuffers(1, &colorbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
            glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

            auto shader = orion::Shader::load_from_file("resource/shader/color_vertex.glsl",
                                                        "resource/shader/color_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &colorbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("custom_vector3_cube") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, custom_vec3_cube_vertices().size() * sizeof(orion::Vector3f),
                         custom_vec3_cube_vertices().data(), GL_STATIC_DRAW);

            auto colors = std::vector<glm::vec3>();

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> rnd(0, 100);

            for (int v = 0; v < 12 * 3; v++) {
                colors.emplace_back((float) rnd(rng) / 100., (float) rnd(rng) / 100., (float) rnd(rng) / 100.);
            }

            GLuint colorbuffer;
            glGenBuffers(1, &colorbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
            glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

            auto shader = orion::Shader::load_from_file("resource/shader/color_vertex.glsl",
                                                        "resource/shader/color_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &colorbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("textured_cube") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_vertices().size() * sizeof(glm::vec3), cube_vertices().data(),
                         GL_STATIC_DRAW);

            GLuint uvbuffer;
            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_uvs().size() * sizeof(glm::vec2), cube_uvs().data(), GL_STATIC_DRAW);

            int width, height, channels;
            auto dirt = stbi_load("resource/texture/dirt.png", &width, &height, &channels, 0);

            GLuint texture;
            glGenTextures(1, &texture);

            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dirt);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(dirt);

            auto shader = orion::Shader::load_from_file("resource/shader/texture_vertex.glsl",
                                                        "resource/shader/texture_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

            auto texture_id = shader->get_uniform_location("texture_sampler");

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

//            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
//
//            glUniform1i(texture_id, 0);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &uvbuffer);
            glDeleteTextures(1, &texture);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("dyn_textured_cube") {
            auto event_manager = std::make_shared<orion::EventManager>();
            w->set_event_manager(event_manager);

            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_vertices().size() * sizeof(glm::vec3), cube_vertices().data(),
                         GL_STATIC_DRAW);

            GLuint uvbuffer;
            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_uvs().size() * sizeof(glm::vec2), cube_uvs().data(), GL_STATIC_DRAW);

            int width, height, channels;
            auto idirt = stbi_load("resource/texture/dirt.png", &width, &height, &channels, 0);

            GLuint dirt;
            glGenTextures(1, &dirt);

            glBindTexture(GL_TEXTURE_2D, dirt);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, idirt);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(idirt);

            auto istone = stbi_load("resource/texture/stone.png", &width, &height, &channels, 4);

            GLuint stone;
            glGenTextures(1, &stone);

            glBindTexture(GL_TEXTURE_2D, stone);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, istone);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(istone);

            auto shader = orion::Shader::load_from_file("resource/shader/texture_vertex.glsl",
                                                        "resource/shader/texture_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

            auto texture_id = shader->get_uniform_location("texture_sampler");

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

//            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, dirt);

//            glUniform1i(texture_id, 0);

            event_manager->subscribe<orion::Input::KeyEvent>([&](const orion::Input::KeyEvent &e) {
                if (e.key == orion::Input::Key::A && e.pressed) {
                    glBindTexture(GL_TEXTURE_2D, stone);
                }
                if (e.key == orion::Input::Key::Q && e.pressed) {
                    glBindTexture(GL_TEXTURE_2D, dirt);
                }
            });

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &uvbuffer);
            glDeleteTextures(1, &dirt);
            glDeleteTextures(1, &stone);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("image_class") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_vertices().size() * sizeof(glm::vec3), cube_vertices().data(),
                         GL_STATIC_DRAW);

            GLuint uvbuffer;
            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_uvs().size() * sizeof(glm::vec2), cube_uvs().data(), GL_STATIC_DRAW);

            auto image = orion::Image::load_from_file("resource/texture/dirt.png");

            GLuint texture;
            glGenTextures(1, &texture);

            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.get_width(), image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         image.get_pixels());

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, 0);

            auto shader = orion::Shader::load_from_file("resource/shader/texture_vertex.glsl",
                                                        "resource/shader/texture_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

            auto texture_id = shader->get_uniform_location("texture_sampler");

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            glBindTexture(GL_TEXTURE_2D, texture);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &uvbuffer);
            glDeleteTextures(1, &texture);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("texture_class") {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_vertices().size() * sizeof(glm::vec3), cube_vertices().data(),
                         GL_STATIC_DRAW);

            GLuint uvbuffer;
            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, cube_uvs().size() * sizeof(glm::vec2), cube_uvs().data(), GL_STATIC_DRAW);

            auto image = orion::Image::load_from_file("resource/texture/dirt.png");
            auto texture = orion::Texture::create_from_image(image);

            auto shader = orion::Shader::load_from_file("resource/shader/texture_vertex.glsl",
                                                        "resource/shader/texture_fragment.glsl");

            auto mvp_id = shader->get_uniform_location("mvp");

//            auto texture_id = shader->get_uniform_location("texture_sampler");

            texture->bind();

            auto mvp = default_mvp(w);

            shader->use();

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteBuffers(1, &uvbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        SUBCASE("clean_code") {
            auto shader = orion::Shader::load_from_file("resource/shader/cc_simple_vertex.glsl",
                                                        "resource/shader/cc_simple_fragment.glsl");

            GLuint vertexarray;
            glGenVertexArrays(1, &vertexarray);
            glBindVertexArray(vertexarray);

            auto vertices = std::vector<orion::Vector3f>{
                    orion::Vector3f(-1, -1, 0),
                    orion::Vector3f(1, -1, 0),
                    orion::Vector3f(0, 1, 0)
            };

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(shader->get_attrib_location("position"));
            glVertexAttribPointer(shader->get_attrib_location("position"), 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

            while (!w->is_close()) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->use();
                glBindVertexArray(vertexarray);

                glDrawArrays(GL_TRIANGLES, 0, 3);

                glBindVertexArray(0);
                orion::Shader::unbind();

                w->display();
            }

            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &vertexarray);
        }

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
