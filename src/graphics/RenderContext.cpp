//
// Created by Alex on 23/12/2023.
//

#include "orion/graphics/RenderContext.h"

#include <utility>

namespace orion {

    RenderContext::RenderContext() :
        m_shader(nullptr),
        m_texture(nullptr),
        m_draw_mode(VertexArray::DrawMode::TRIANGLES)
    {}

    RenderContext::RenderContext(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, VertexArray::DrawMode draw_mode) :
            m_shader(std::move(shader)),
            m_texture(std::move(texture)),
            m_draw_mode(draw_mode)
    {}

    Ref<std::shared_ptr<Shader>> RenderContext::get_shader() const {
        return m_shader;
    }

    Ref<std::shared_ptr<Texture>> RenderContext::get_texture() const {
        return m_texture;
    }

    VertexArray::DrawMode RenderContext::get_draw_mode() const {
        return m_draw_mode;
    }

    void RenderContext::set_shader(std::shared_ptr<Shader> shader) {
        m_shader = std::move(shader);
    }

    void RenderContext::set_texture(std::shared_ptr<Texture> texture) {
        m_texture = std::move(texture);
    }

    void RenderContext::set_draw_mode(VertexArray::DrawMode mode) {
        m_draw_mode = mode;
    }

    bool operator==(Ref<RenderContext> lhs, Ref<RenderContext> rhs) {
        return (
            lhs.m_texture    == rhs.m_texture &&
            lhs.m_shader     == rhs.m_shader  &&
            lhs.m_draw_mode  == rhs.m_draw_mode
        );
    }

    bool operator!=(Ref<RenderContext> lhs, Ref<RenderContext> rhs) {
        return !(lhs == rhs);
    }

    const RenderContext RenderContext::DEFAULT = RenderContext();
}