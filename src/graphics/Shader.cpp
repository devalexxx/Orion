//
// Created by Alex on 09/12/2023.
//

#include "graphics/Shader.h"

#include "GL/glew.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <fmt/core.h>

namespace orion {

    DeferredRegistry<Shader> Shader::REGISTRY = DeferredRegistry<Shader>("opengl",
            [](RefMut<DeferredRegistry<Shader>> reg) {
                reg.add("default", Shader::load_from_file("resource/shader/basic_texture_vertex.glsl","resource/shader/basic_texture_fragment.glsl"));
            }
    );

    std::shared_ptr<Shader> Shader::load_from_file(Ptr<char> vertex, Ptr<char> fragment) {
        std::string     v_code;
        std::ifstream   v_stream(vertex, std::ios::in);
        if(v_stream.is_open()) {
            std::stringstream v_sstr;
            v_sstr << v_stream.rdbuf();
            v_code = v_sstr.str();
            v_stream.close();
        } else {
            std::cerr << "Impossible to open " << vertex << ". Are you in the right directory ? Don't forget to read the FAQ !\n";
        }

        std::string     f_code;
        std::ifstream   f_stream(fragment, std::ios::in);
        if(f_stream.is_open()) {
            std::stringstream f_sstr;
            f_sstr << f_stream.rdbuf();
            f_code = f_sstr.str();
            f_stream.close();
        } else {
            std::cerr << "Impossible to open " << fragment << ". Are you in the right directory ? Don't forget to read the FAQ !\n";
        }

        return std::shared_ptr<Shader>(new Shader(v_code, f_code));
    }

    std::shared_ptr<Shader> Shader::load_from_code(Ref<std::string> vertex, Ref<std::string> fragment) {
        return std::shared_ptr<Shader>(new Shader(vertex, fragment));
    }

    void Shader::unbind() {
        glUseProgram(0);
    }

    Shader::~Shader() {
        glDeleteProgram(m_id);
    }

    void Shader::use() const {
        glUseProgram(m_id);
    }

    Shader::Shader(Ref<std::string> vertex, Ref<std::string> fragment) {
        m_id = glCreateProgram();

        compute_mapping(vertex, Type::VERTEX);
        compute_mapping(fragment, Type::FRAGMENT);

        auto vertex_id    = glCreateShader(GL_VERTEX_SHADER);
        auto fragment_id  = glCreateShader(GL_FRAGMENT_SHADER);

        auto v_code = vertex.c_str();
        glShaderSource(vertex_id, 1, &v_code , nullptr);
        glCompileShader(vertex_id);
        handle_compile_error(vertex_id);

        auto f_code = fragment.c_str();
        glShaderSource(fragment_id, 1, &f_code , nullptr);
        glCompileShader(fragment_id);
        handle_compile_error(fragment_id);

        glAttachShader(m_id, vertex_id);
        glAttachShader(m_id, fragment_id);
        glLinkProgram(m_id);
        handle_link_error(m_id);

        glDetachShader(m_id, vertex_id);
        glDetachShader(m_id, fragment_id);

        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
    }

    void Shader::handle_compile_error(u32 id) {
        i32 result = GL_FALSE;
        i32 length;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE){
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<i8> errorMessage(length);
            glGetShaderInfoLog(id, length, &length, &errorMessage[0]);
            std::cerr << std::string(errorMessage.begin(), errorMessage.end()) << "\n";
        }
    }

    void Shader::handle_link_error(u32 id) {
        i32 result = GL_FALSE;
        i32 length;
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        if (result == GL_FALSE){
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<i8> errorMessage(length);
            glGetShaderInfoLog(id, length, &length, &errorMessage[0]);
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

    int Shader::get_uniform_location(Ptr<char> name) const {
        if (!has_uniform(name))
            std::cerr << "Shader does not contain uniform '" << name << "'\n";
        return glGetUniformLocation(m_id, name);
    }

    int Shader::get_attrib_location(Ptr<char> name) const {
        if (!has_attrib(name))
            std::cerr << "Shader does not contain input '" << name << "'\n";
        return glGetAttribLocation(m_id, name);
    }

    void Shader::set_uniform(Ptr<char> name, int value) const {
        glUniform1i(get_uniform_location(name), value);
    }

    void Shader::set_uniform(Ptr<char> name, Ref<Matrix4f> value) const {
        glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value.data());
    }

    void Shader::set_float_attrib_pointer(Ptr<char> name, u32 size, u32 stride, u32 offset) const {
        glEnableVertexAttribArray(get_attrib_location(name));
        glVertexAttribPointer(get_attrib_location(name),size,GL_FLOAT,GL_FALSE,stride * sizeof(f32),(void*)(offset * sizeof(float)));
    }

    bool Shader::has_attrib(Ptr<char> name) const {
        return m_attrib.contains(name);
    }

    bool Shader::has_uniform(Ptr<char> name) const {
        return m_uniform.contains(name);
    }

//    void Shader::handle_uniform_name_and_type_error(const std::string &name, const std::string &type) const {
//        if (!m_uniform.contains(name))
//            std::cerr << "Shader does not contain uniform '" << name << "'\n";
//        else
//            if (m_uniform.at(name) != type)
//                std::cerr << "Shader expect '"<< m_uniform.at(name) << "' type for '" << name << "' but the given type is '" << type << "'\n";
//    }

}
