//
// Created by Alex on 29/12/2023.
//

#include "graphics/shape/Square.h"

#include "graphics/PackedVertex.h"
#include "graphics/RenderTarget.h"

namespace orion {

    Square::Square() : Square(Vector3f(0)) {}

    Square::Square(Ref<Vector3f> position) {
        if (!VertexArray::REGISTRY.exist("shape:square")) {
            m_vao = VertexArray::REGISTRY.add("shape:square", VertexArray::create(default_shape, m_shader));
        } else {
            m_vao = VertexArray::REGISTRY.get("shape:square");;
        }
        m_transform.set_position(position);
    }

    void Square::draw(const RenderTarget &target, const RenderContext &context) const {
        OldShape::draw(target, context);

        target.draw(*m_vao, m_context);
    }

    std::vector<PackedVertex> Square::default_shape = {{
        PackedVertex(Vector3f(-1.0f,  1.0f, 0.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f,  1.0f, 0.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f,  1.0f, 0.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f( 1.0f, -1.0f, 0.0f),Vector2f(1.0f, 0.0f)),
    }};

} // orion