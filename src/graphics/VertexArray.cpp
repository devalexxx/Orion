//
// Created by Alex on 23/12/2023.
//

#include "graphics/VertexArray.h"
#include "graphics/opengl/OpenGlApi.h"

#include <type_traits>
#include <iostream>

namespace orion {

    DeferredRegistry<VertexArray> VertexArray::REGISTRY = DeferredRegistry<VertexArray>("opengl");

    bool VertexArray::is_any_bind = false;

    void VertexArray::unbind() {
        gl_check(glBindVertexArray(0));
        is_any_bind = false;
    }

    std::shared_ptr<VertexArray> VertexArray::create() {
        return std::shared_ptr<VertexArray>(new VertexArray());
    }

    std::shared_ptr<VertexArray> VertexArray::create(Ref<std::vector<PackedVertex>> data, Ref<std::shared_ptr<Shader>> shader) {
        auto ret = std::shared_ptr<VertexArray>(new VertexArray());
        auto& buffer = ret->add_buffer(VertexBuffer::Type::ARRAY);
        buffer.set_data(data, shader);

        return std::move(ret);
    }

    VertexArray::VertexArray() {
        gl_check(glGenVertexArrays(1, &m_id));
        m_vertex_buffers.reserve(5);
    }

    VertexArray::~VertexArray() {
        gl_check(glDeleteVertexArrays(1, &m_id));
    }

    void VertexArray::bind() const {
        gl_check(glBindVertexArray(m_id));
        is_any_bind = true;
    }

    void VertexArray::draw(u32 first, u32 count, VertexArray::DrawMode mode) const {
        bind();

        if (m_index_buffer != std::nullopt) {
            m_index_buffer->bind();
            gl_check(glDrawElements(
                std::underlying_type<DrawMode>::type(mode),
                count,
                GL_UNSIGNED_SHORT,
                reinterpret_cast<const void *>(first))
            );
        }
        else {
            gl_check(glDrawArrays(
                std::underlying_type<DrawMode>::type(mode),
                first,
                count
            ));
        }

        VertexBuffer::unbind();
        VertexArray ::unbind();
    }

    void VertexArray::draw(u32 count, VertexArray::DrawMode mode) const {
        draw(0, count, mode);
    }

    void VertexArray::draw(VertexArray::DrawMode mode) const {
        auto count = m_index_buffer == std::nullopt ? m_vertex_buffers[0].count : m_index_buffer->count;
        draw(0, count, mode);
    }

    RefMut<VertexBuffer> VertexArray::add_buffer(VertexBuffer::Type type) {
        return add_buffer(type, VertexBuffer::Usage::STATIC);
    }

    // @todo : Voir si on remplace le buffer ou non ?
    RefMut<VertexBuffer> VertexArray::add_buffer(VertexBuffer::Type type, VertexBuffer::Usage usage) {
        bind();
        switch (type) {
            case VertexBuffer::Type::ARRAY:
                return m_vertex_buffers.emplace_back(type, usage);
            case VertexBuffer::Type::ELEMENT:
                if (m_index_buffer == std::nullopt)
                    return m_index_buffer.emplace(type, usage);
                else {
                    return *m_index_buffer;
                }
        }
    }

    // @todo : Voir si immuable ou non ?
    RefMut<std::optional<VertexBuffer>> VertexArray::get_ibo() {
        return m_index_buffer;
    }

} // orion