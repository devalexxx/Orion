//
// Created by Alex on 14/12/2023.
//

#include "graphics/VertexBuffer.h"

#include <iostream>

#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/PackedVertex.h"
#include "graphics/opengl/OpenGlApi.h"

namespace orion {

    VertexBuffer::VertexBuffer(VertexBuffer::Type type, VertexBuffer::Usage usage) : m_type(type), m_usage(usage) {
        if (VertexArray::is_any_bind) {
            unbind();
            gl_check(glGenBuffers(1, &m_id));
        }
        else
            std::cerr << "Can't generate buffer because no VAO is bind.\n";
    }

    VertexBuffer::VertexBuffer(VertexBuffer::Type type) : VertexBuffer(type, Usage::STATIC) {}

    void VertexBuffer::unbind() {
        gl_check(glBindBuffer(std::underlying_type<Type>::type(Type::ARRAY), 0));
        gl_check(glBindBuffer(std::underlying_type<Type>::type(Type::ELEMENT), 0));
    }

    VertexBuffer::~VertexBuffer() {
        gl_check(glDeleteBuffers(1, &m_id));
    }

    void VertexBuffer::bind() const {
        if (VertexArray::is_any_bind)
            gl_check(glBindBuffer(std::underlying_type<Type>::type(m_type), m_id));
        else
            std::cerr << "Can't bind buffer " << m_id << " because no VAO is bind.\n";
    }

    void VertexBuffer::set_data(Ref<PackedVertexContainer> v, Ref<std::shared_ptr<Shader>> shader) {
        if (VertexArray::is_any_bind) {
            bind();
            count = v.size();
            auto [arr, s] = to_float_array(v);
            gl_check(glBufferData(
                    std::underlying_type<Type>::type(m_type),
                    s * sizeof (f32),
                    arr,
                    std::underlying_type<Usage>::type(m_usage)
            ));

            if (shader->has_attrib("position"))
                shader->set_float_attrib_pointer("position", 3, 8, 0);

            if (shader->has_attrib("normal"))
                shader->set_float_attrib_pointer("normal", 3, 8, 3);

            if (shader->has_attrib("uv"))
                shader->set_float_attrib_pointer("uv", 2, 8, 6);
        }
        else
            std::cerr << "Can't set_current data for buffer " << m_id << " because no VAO is bind.\n";
    }

    void VertexBuffer::set_data(Ref<PackedVertexContainer> v) {
        if (VertexArray::is_any_bind) {
            bind();
            auto [arr, s] = to_float_array(v);
            gl_check(glBufferData(
                    std::underlying_type<Type>::type(m_type),
                    s * sizeof (f32),
                    arr,
                    std::underlying_type<Usage>::type(m_usage)
            ));

            count = v.size();
        }
        else
            std::cerr << "Can't set_current data for buffer " << m_id << " because no VAO is bind.\n";
    }

    void VertexBuffer::set_data(Ref<IndexContainer> v) {
        if (VertexArray::is_any_bind) {
            bind();
            gl_check(glBufferData(
                    std::underlying_type<Type>::type(m_type),
                    v.size() * sizeof (f32),
                    &v[0],
                    std::underlying_type<Usage>::type(m_usage)
            ));

            count = v.size();
        }
        else
            std::cerr << "Can't set_current data for buffer " << m_id << " because no VAO is bind.\n";
    }
}