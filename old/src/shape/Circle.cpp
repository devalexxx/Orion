//
// Created by Alex on 12/01/2024.
//

#include "graphics/shape/Circle.h"

#include "graphics/RenderTarget.h"
#include "graphics/PackedVertex.h"
#include "graphics/Primitive.h"

namespace orion {

    Circle::Circle() : Circle(Vector3f(0, 0, 0)) {}

    Circle::Circle(Ref<Vector3f> position) {
        if (!VertexArray::REGISTRY.exist("shape:circle")) {
            m_vao = VertexArray::REGISTRY.add("shape:circle", VertexArray::create(default_shape, m_shader));
        } else {
            m_vao = VertexArray::REGISTRY.get("shape:circle");
        }
        m_transform.set_position(position);
    }

    void Circle::draw(const RenderTarget &target, const RenderContext &context) const {
        OldShape::draw(target, context);

        target.draw(*m_vao, m_context);
    }

    std::vector<PackedVertex> Circle::default_shape = generator::circle_vertices(128);

} // orion