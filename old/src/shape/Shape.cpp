//
// Created by Alex on 09/12/2023.
//

#include "graphics/shape/OldShape.h"

#include "graphics/PackedVertex.h"
#include "omath.h"

#include <utility>

namespace orion {

    OldShape::OldShape() :
        m_shader(Shader::REGISTRY.get("shape")),
        m_context(RenderContext(m_shader, m_texture, VertexArray::DrawMode::TRIANGLES)),
        m_color(Color::WHITE),
        m_sample_mode(SampleMode::UNIFORM_COLOR)
    {}

    const std::shared_ptr<Texture> &OldShape::get_texture() const {
        return m_texture;
    }

    const std::shared_ptr<Shader> &OldShape::get_shader() const {
        return m_shader;
    }

    void OldShape::set_texture(std::shared_ptr<Texture> texture) {
        m_texture = std::move(texture);
        m_context.set_texture(m_texture);
        m_sample_mode = SampleMode::TEXTURE;
    }

    void OldShape::set_shader(std::shared_ptr<Shader> shader) {
        m_shader = std::move(shader);
        m_context.set_shader(m_shader);
    }

    RefMut<Transform> OldShape::get_transform() {
        return m_transform;
    }

    void OldShape::set_color(Ref<Color> color) {
        m_color = color;
    }

    void OldShape::set_color(std::vector<Color> color) {
        // @todo
        m_sample_mode = SampleMode::COLOR;
    }

    void OldShape::set_sample_mode(OldShape::SampleMode mode) {
        m_sample_mode = mode;
    }

    void OldShape::draw(Ref<RenderTarget> target, Ref<RenderContext> context) const {
        if (m_shader->has_uniform("sample_mode"))
            m_shader->set_uniform("sample_mode", std::underlying_type<SampleMode>::type(m_sample_mode));

        if (m_sample_mode == SampleMode::UNIFORM_COLOR)
            if (m_shader->has_uniform("uniform_color"))
                m_shader->set_uniform("uniform_color", m_color);

        if (m_shader->has_uniform("model"))
            m_shader->set_uniform("model", m_transform.get_matrix());
    }
} // orion