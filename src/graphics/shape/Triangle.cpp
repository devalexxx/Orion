//
// Created by Alex on 23/12/2023.
//

#include "graphics/shape/Triangle.h"

#include "graphics/VertexArray.h"
#include "graphics/PackedVertex.h"
#include "graphics/RenderTarget.h"

#include <iostream>

namespace orion {

    Triangle::Triangle(Ref<Vector3f> position) {
        if (!VertexArray::REGISTRY.exist("shape:triangle")) {
            m_vao = VertexArray::REGISTRY.add("shape:triangle", VertexArray::create(default_shape, m_shader));
        } else {
            m_vao = VertexArray::REGISTRY.get("shape:triangle");
        }
        m_transform.set_position(position);
    }

    Triangle::Triangle() : Triangle(Vector3f(0)) {}

    void Triangle::draw(const RenderTarget &target, const RenderContext &context) const {
        Shape::draw(target, context);

        target.draw(*m_vao, m_context);
    }

    std::vector<PackedVertex> Triangle::default_shape = {{
        PackedVertex(Vector3f(0.0f, 1.0f, 0.0f),Vector2f(0.5f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f(1.0f, -1.0f, 0.0f),Vector2f(1.0f, 0.0f))
    }};

} // orion