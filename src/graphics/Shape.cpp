//
// Created by Alex on 14/01/2024.
//

#include "graphics/Shape.h"

#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Primitive.h"

namespace orion {

    Shape::Shape(std::shared_ptr<Mesh> mesh, bool use_attr) :
        m_mesh       (std::move(mesh)),
        m_shader     (Shader::get_registry().get("shape")),
        m_context    (RenderContext(m_shader, m_texture, VertexArray::DrawMode::TRIANGLES)),
        m_color      (Color::WHITE),
        m_sample_mode(SampleMode::UNIFORM_COLOR)
    {
        if (use_attr) {
            auto& vao = m_mesh->get_vao();
            auto& vbo = vao.get_buffer(0);

            vao.bind();
            vbo.bind();

            if (m_shader->has_attrib("position"))
                m_shader->set_float_attrib_pointer("position", 3, 8, 0);

            if (m_shader->has_attrib("normal"))
                m_shader->set_float_attrib_pointer("normal",   3, 8, 3);

            if (m_shader->has_attrib("uv"))
                m_shader->set_float_attrib_pointer("uv",       2, 8, 6);
        }
    }

    Shape::Shape(Primitive primitive) :
            Shape(Mesh::get_registry().get(default_mesh_name_of(primitive)), true)
    {}

    RefMut<Transform> Shape::get_transform() {
        return m_transform;
    }

    void Shape::set_texture(std::shared_ptr<Texture> texture) {
        m_texture = std::move(texture);
        m_context.set_texture(m_texture);
        m_sample_mode = SampleMode::TEXTURE;
    }

    void Shape::set_shader(std::shared_ptr<Shader> shader) {
        m_shader = std::move(shader);
        m_context.set_shader(m_shader);
    }

    void Shape::set_color(Color color) {
        m_color = std::move(color);
    }

    void Shape::set_color(std::vector<Color> color) {
        m_sample_mode = SampleMode::COLOR;

        // @todo impl
    }

    void Shape::set_sample_mode(Shape::SampleMode mode) {
        m_sample_mode = mode;
    }

    void Shape::draw(Ref<RenderTarget> target, Ref<RenderContext> context) const {

        if (m_shader->has_uniform("sample_mode"))
            m_shader->set_uniform("sample_mode", EnumValue<SampleMode>(m_sample_mode));

        if (m_sample_mode == SampleMode::UNIFORM_COLOR)
            if (m_shader->has_uniform("uniform_color"))
                m_shader->set_uniform("uniform_color", m_color);

        if (m_shader->has_uniform("model"))
            m_shader->set_uniform("model", m_transform.get_matrix());

        m_mesh->draw(target, m_context);
    }

} // orion