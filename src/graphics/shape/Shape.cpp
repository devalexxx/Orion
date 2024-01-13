//
// Created by Alex on 09/12/2023.
//

#include "graphics/shape/Shape.h"

#include "graphics/PackedVertex.h"
#include "omath.h"

#include <utility>

namespace orion {

    Shape::Shape() :
        m_shader(Shader::REGISTRY.get("shape")),
        m_context(RenderContext(m_shader, m_texture, VertexArray::DrawMode::TRIANGLES)),
        m_color(Color::WHITE),
        m_sample_mode(SampleMode::UNIFORM_COLOR)
    {}

    const std::shared_ptr<Texture> &Shape::get_texture() const {
        return m_texture;
    }

    const std::shared_ptr<Shader> &Shape::get_shader() const {
        return m_shader;
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

    RefMut<Transform> Shape::get_transform() {
        return m_transform;
    }

    void Shape::set_color(Ref<Color> color) {
        m_color = color;
    }

    void Shape::set_color(std::vector<Color> color) {
        // @todo
        m_sample_mode = SampleMode::COLOR;
    }

    void Shape::set_sample_mode(Shape::SampleMode mode) {
        m_sample_mode = mode;
    }

    void Shape::draw(Ref<RenderTarget> target, Ref<RenderContext> context) const {
        if (m_shader->has_uniform("sample_mode"))
            m_shader->set_uniform("sample_mode", std::underlying_type<SampleMode>::type(m_sample_mode));

        if (m_sample_mode == SampleMode::UNIFORM_COLOR)
            if (m_shader->has_uniform("uniform_color"))
                m_shader->set_uniform("uniform_color", m_color);

        if (m_shader->has_uniform("model"))
            m_shader->set_uniform("model", m_transform.get_matrix());
    }

    std::vector<PackedVertex> generator::circle_vertices(u32 v_count) {
        std::vector<PackedVertex> ret;

        f32 angle = 360.0f / v_count;

        u32 triangle_count = v_count - 2;

        std::vector<Vector3f> temp;

        for (u32 i = 0; i < v_count; i++)
        {
            f32 current_angle = angle * i;
            f32 x = cos(radian(current_angle));
            f32 y = sin(radian(current_angle));
            f32 z = 0.0f;

            temp.emplace_back(x, y, z);
        }

        static auto mapper = std::bind(map_range<3, f32>, std::placeholders::_1, -1.f, 1.f, 0.f, 1.f);
        for (u32 i = 0; i < triangle_count; i++)
        {
            ret.emplace_back(temp[0], Vector2f(mapper(temp[0])));
            ret.emplace_back(temp[i + 1], Vector2f(mapper(temp[i + 1])));
            ret.emplace_back(temp[i + 2], Vector2f(mapper(temp[i + 2])));
        }

        return std::move(ret);
    }
} // orion