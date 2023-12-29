//
// Created by Alex on 09/12/2023.
//

#include "graphics/shape/Shape.h"

#include <utility>

namespace orion {

    Shape::Shape() : m_shader(Shader::REGISTRY.get("default")), m_context(RenderContext(m_shader, m_texture, VertexArray::DrawMode::TRIANGLES)) {}

    const std::shared_ptr<Texture> &Shape::get_texture() const {
        return m_texture;
    }

    const std::shared_ptr<Shader> &Shape::get_shader() const {
        return m_shader;
    }

    void Shape::set_texture(std::shared_ptr<Texture> texture) {
        m_texture = std::move(texture);
        m_context.set_texture(m_texture);
    }

    void Shape::set_shader(std::shared_ptr<Shader> shader) {
        m_shader = std::move(shader);
        m_context.set_shader(m_shader);
    }

    RefMut<Transform> Shape::get_transform() {
        return m_transform;
    }

} // orion