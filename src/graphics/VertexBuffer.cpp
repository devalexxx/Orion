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
        if (VertexArray::CURRENT_BOUND > 0) {
            gl_check(glGenBuffers(1, &m_id));
        }
        else
            fmt::print(stderr, "Can't generate buffer because no VAO is bind.\n");
    }

    VertexBuffer::VertexBuffer(VertexBuffer::Type type) : VertexBuffer(type, Usage::STATIC) {}

    void VertexBuffer::unbind() {
        if (CURRENT_BOUND != 0) {
            gl_check(glBindBuffer(EnumValue<Type>(Type::ARRAY), 0));
            gl_check(glBindBuffer(EnumValue<Type>(Type::ELEMENT), 0));
            CURRENT_BOUND = 0;
        }
    }

    VertexBuffer::~VertexBuffer() {
        gl_check(glDeleteBuffers(1, &m_id));
    }

    void VertexBuffer::bind() const {
        if (VertexArray::CURRENT_BOUND > 0) {
            if (CURRENT_BOUND != m_id) {
                gl_check(glBindBuffer(EnumValue<Type>(m_type), m_id));
                CURRENT_BOUND = m_id;
            }
        }
        else
            fmt::print(stderr, "Can't bind buffer {} because no VAO is bind.\n", m_id);
    }

    void VertexBuffer::set_data(Ref<PackedVertexContainer> v) {
        if (VertexArray::CURRENT_BOUND > 0) {
            bind();
            auto [arr, s] = to_float_array(v);
            gl_check(glBufferData(
                    EnumValue<Type>(m_type),
                    s * sizeof (f32),
                    arr,
                    EnumValue<Usage>(m_usage)
            ));

            count = v.size();
        }
        else
            fmt::print(stderr, "Can't set_current data for buffer {} because no VAO is bind.\n", m_id);
    }

    void VertexBuffer::set_data(Ref<IndexContainer> v) {
        if (VertexArray::CURRENT_BOUND > 0) {
            bind();
            gl_check(glBufferData(
                    EnumValue<Type>(m_type),
                    v.size() * sizeof (f32),
                    &v[0],
                    EnumValue<Usage>(m_usage)
            ));

            count = v.size();
        }
        else
            fmt::print(stderr, "Can't set_current data for buffer {} because no VAO is bind.\n", m_id);
    }

    u32 VertexBuffer::CURRENT_BOUND = 0;
}