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
        gl_check(glDrawArrays(std::underlying_type<DrawMode>::type(mode), first, count));
    }

    void VertexArray::draw(u32 count, VertexArray::DrawMode mode) const {
        draw(0, count, mode);
    }

    void VertexArray::draw(VertexArray::DrawMode mode) const {
        draw(0, count(), mode);
    }

    VertexBuffer& VertexArray::add_buffer(VertexBuffer::Type type) {
        bind();
        return m_buffers.emplace_back(type);
    }

    VertexBuffer &VertexArray::add_buffer(VertexBuffer::Type type, VertexBuffer::Usage usage) {
        bind();
        return m_buffers.emplace_back(type, usage);
    }

    u32 VertexArray::count() const {
        return m_buffers.empty() ? 0 : m_buffers[0].count;
    }

} // orion