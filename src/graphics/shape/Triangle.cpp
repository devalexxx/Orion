//
// Created by Alex on 23/12/2023.
//

#include "graphics/shape/Triangle.h"

#include "graphics/VertexArray.h"
#include "graphics/PackedVertex.h"
#include "graphics/RenderTarget.h"

namespace orion {

    Triangle::Triangle(Ref<Vector3f> position) {
        if (default_vao == nullptr) {
            default_vao = VertexArray::create(default_shape, m_shader);
        }
        m_vao = default_vao;
        m_transform.set_position(position);
    }

    Triangle::Triangle() : Triangle(Vector3f(0)) {}

    void Triangle::draw(const RenderTarget &target, const RenderContext &context) const {
        if (m_shader->has_uniform("model")) {
            m_shader->set_uniform("model", m_transform.get_matrix());
        }

        target.draw(*m_vao, m_context);
    }

    std::shared_ptr<VertexArray> Triangle::default_vao = nullptr;

    std::vector<PackedVertex>    Triangle::default_shape = {{
        PackedVertex(Vector3f(0.0f, 1.0f, 0.0f),Vector2f(0.5f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f(1.0f, -1.0f, 0.0f),Vector2f(1.0f, 0.0f))
    }};

} // orion