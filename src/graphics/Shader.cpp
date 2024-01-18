//
// Created by Alex on 09/12/2023.
//

#include "graphics/Shader.h"

#include "core/Resource.h"
#include "graphics/Color.h"
#include "graphics/opengl/OpenGlApi.h"

#include "GL/glew.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <fmt/core.h>
#include <fmt/ostream.h>

namespace orion {

    DeferredRegistry<Shader> Shader::REGISTRY = DeferredRegistry<Shader>("opengl",
            [](RefMut<DeferredRegistry<Shader>> registry) {
                registry.add(
                    "shape",
                    Shader::load_from_file(
                        resource::shader::of("shape_vertex.glsl"),
                        resource::shader::of("shape_fragment.glsl")
                    )
                );
            }
    );

    u32 Shader::CURRENT_USE = 0;

    std::shared_ptr<Shader> Shader::load_from_file(Ref<Path> vertex, Ref<Path> fragment) {
        std::string     v_code;
        std::ifstream   v_stream(vertex.c_str(), std::ios::in);
        if(v_stream.is_open()) {
            std::stringstream v_sstr;
            v_sstr << v_stream.rdbuf();
            v_code = v_sstr.str();
            v_stream.close();
        }
        else
            fmt::print(stderr, "Impossible to open {}. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex.c_str());

        std::string     f_code;
        std::ifstream   f_stream(fragment.c_str(), std::ios::in);
        if(f_stream.is_open()) {
            std::stringstream f_sstr;
            f_sstr << f_stream.rdbuf();
            f_code = f_sstr.str();
            f_stream.close();
        }
        else
            fmt::print(stderr, "Impossible to open {}. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment.c_str());

        return std::shared_ptr<Shader>(new Shader(v_code, f_code));
    }

    void Shader::unbind() {
        if (CURRENT_USE != 0) {
            gl_check(glUseProgram(0));
            CURRENT_USE = 0;
        }
    }

    Shader::~Shader() {
        gl_check(glDeleteProgram(m_id));
    }

    void Shader::use() const {
        if (CURRENT_USE != m_id) {
            gl_check(glUseProgram(m_id));
            CURRENT_USE = m_id;
        }
    }

    bool Shader::has_attrib(Ptr<char> name) const {
        return m_attrib.contains(name);
    }

    bool Shader::has_uniform(Ptr<char> name) const {
        return m_uniform.contains(name);
    }

    int Shader::get_uniform_location(Ptr<char> name) const {
        if (!has_uniform(name)) {
            fmt::print(stderr, "Shader does not contain uniform '{}'\n", name);
            return -1;
        }
        else
            return glGetUniformLocation(m_id, name);
    }

    int Shader::get_attrib_location(Ptr<char> name) const {
        if (!has_attrib(name)) {
            fmt::print(stderr, "Shader does not contain attribute '{}'\n", name);
            return -1;
        }
        else
            return glGetAttribLocation(m_id, name);
    }

    void Shader::set_uniform(Ptr<char> name, int value) const {
        use();
        gl_check(glUniform1i(get_uniform_location(name), value));
    }

    void Shader::set_uniform(Ptr<char> name, Ref<Matrix4f> value) const {
        use();
        gl_check(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value.data()));
    }

    void Shader::set_uniform(Ptr<char> name, Ref<Color> value) const {
        use();
        gl_check(glUniform4fv(get_uniform_location(name), 1, &value[0]));
    }

    void Shader::set_float_attrib_pointer(Ptr<char> name, u32 size, u32 stride, u32 offset) const {
        use();
        gl_check(glEnableVertexAttribArray(get_attrib_location(name)));
        gl_check(glVertexAttribPointer(get_attrib_location(name), size,GL_FLOAT,GL_FALSE,stride * sizeof(f32),(void*)(offset * sizeof(f32))));
    }

    Shader::Shader(Ref<std::string> vertex, Ref<std::string> fragment) {
        m_id = glCreateProgram();

        compute_mapping(vertex, Type::VERTEX);
        compute_mapping(fragment, Type::FRAGMENT);

        auto vertex_id    = glCreateShader(GL_VERTEX_SHADER);
        auto fragment_id  = glCreateShader(GL_FRAGMENT_SHADER);

        auto v_code = vertex.c_str();
        gl_check(glShaderSource(vertex_id, 1, &v_code , nullptr));
        gl_check(glCompileShader(vertex_id));
        handle_compile_error(vertex_id);

        auto f_code = fragment.c_str();
        gl_check(glShaderSource(fragment_id, 1, &f_code , nullptr));
        gl_check(glCompileShader(fragment_id));
        handle_compile_error(fragment_id);

        gl_check(glAttachShader(m_id, vertex_id));
        gl_check(glAttachShader(m_id, fragment_id));
        gl_check(glLinkProgram(m_id));
        handle_link_error(m_id);

        gl_check(glDetachShader(m_id, vertex_id));
        gl_check(glDetachShader(m_id, fragment_id));

        gl_check(glDeleteShader(vertex_id));
        gl_check(glDeleteShader(fragment_id));

//        for(auto& it: m_uniform) {
//            it.second.location = glGetUniformLocation(m_id, it.first.c_str());
//        }
//
//        for (auto& it: m_attrib) {
//            it.second.location = glGetAttribLocation(m_id, it.first.c_str());
//        }
    }

    void Shader::handle_compile_error(u32 id) {
        i32 result = GL_FALSE;
        i32 length;
        gl_check(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE){
            gl_check(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            std::vector<i8> errorMessage(length);
            gl_check(glGetShaderInfoLog(id, length, &length, &errorMessage[0]));
            std::cerr << std::string(errorMessage.begin(), errorMessage.end()) << "\n";
        }
    }

    void Shader::handle_link_error(u32 id) {
        i32 result = GL_FALSE;
        i32 length;
        gl_check(glGetProgramiv(id, GL_LINK_STATUS, &result));
        if (result == GL_FALSE){
            gl_check(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));
            std::vector<i8> errorMessage(length);
            gl_check(glGetShaderInfoLog(id, length, &length, &errorMessage[0]));
            std::cerr << std::string(errorMessage.begin(), errorMessage.end()) << "\n";
        }
    }

    void Shader::compute_mapping(Ref<std::string> code, Type type) {
        bool end = false;

        std::string::size_type fcursor = 0;
        std::string::size_type cursor  = 0;

        auto fn = [&, this](bool attr) {
            std::string k, v;
            for (auto c: code.substr(cursor)) {
                if (c == ' ')
                    break;
                v.push_back(c);
            }
            cursor += v.size() + 1;
            for (auto c: code.substr(cursor)) {
                if (c == ';')
                    break;
                k.push_back(c);
            }

//            if (attr)
//                m_attrib.emplace(k, Description {v});
//            else
//                m_uniform.emplace(k, Description {v});

            if (attr)
                m_attrib.emplace(k, v);
            else
                m_uniform.emplace(k, v);
        };

        while (!end) {
            if (type == Type::VERTEX && (fcursor = code.find("in ", cursor)) != std::string::npos) {
                cursor = fcursor + 3;
                fn(true);
            }
            else if ((fcursor = code.find("uniform ", cursor)) != std::string::npos) {
                cursor = fcursor + 8;
                fn(false);
            }
            else
                end = true;
        }
    }

}
