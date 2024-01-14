//
// Created by Alex on 13/01/2024.
//

#include "graphics/shape/Sphere.h"

#include "graphics/RenderTarget.h"
#include "graphics/PackedVertex.h"
#include "graphics/Primitive.h"

namespace orion {

    Sphere::Sphere() : Sphere(Vector3f(0)) {}

    Sphere::Sphere(Ref<Vector3f> position) {
        if (!VertexArray::REGISTRY.exist("shape:sphere")) {
            m_vao = VertexArray::REGISTRY.add("shape:sphere", VertexArray::create(default_shape, m_shader));
        } else {
            m_vao = VertexArray::REGISTRY.get("shape:sphere");
        }
        m_transform.set_position(position);
    }

    void Sphere::draw(const RenderTarget &target, const RenderContext &context) const {
        OldShape::draw(target, context);

        target.draw(*m_vao, m_context);
    }

    std::vector<PackedVertex> Sphere::default_shape = generator::sphere_vertices(2);

} // orion