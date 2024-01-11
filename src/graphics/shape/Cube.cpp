//
// Created by Alex on 05/01/2024.
//

#include "graphics/shape/Cube.h"

#include "graphics/RenderTarget.h"
#include "graphics/PackedVertex.h"

namespace orion {

    Cube::Cube() : Cube(Vector3f(0.f, 0.f, 0.f)) {}

    Cube::Cube(Ref<Vector3f> position)  {
        if (!VertexArray::REGISTRY.exist("shape:cube")) {
            m_vao = VertexArray::REGISTRY.add("shape:cube", VertexArray::create(default_shape, m_shader));
        } else {
            m_vao = VertexArray::REGISTRY.get("shape:cube");;
        }
        m_transform.set_position(position);
    }

    void Cube::draw(const RenderTarget &target, const RenderContext &context) const {
        Shape::draw(target, context);

        target.draw(*m_vao, m_context);
    }

    std::vector<PackedVertex> Cube::default_shape = {{
        // Front
        PackedVertex(Vector3f(-1.0f, 1.0f, 1.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f, 1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f, 1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f, 1.0f),Vector2f(1.0f, 0.0f)),
        // Back
        PackedVertex(Vector3f(-1.0f, 1.0f,-1.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f,-1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f,-1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f,-1.0f),Vector2f(1.0f, 0.0f)),
        // Left
        PackedVertex(Vector3f(-1.0f, 1.0f,-1.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f(-1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f(-1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f, 1.0f),Vector2f(1.0f, 0.0f)),
        // Right
        PackedVertex(Vector3f( 1.0f, 1.0f,-1.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f, 1.0f),Vector2f(1.0f, 0.0f)),
        // Bottom
        PackedVertex(Vector3f( 1.0f,-1.0f,-1.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f,-1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f,-1.0f, 1.0f),Vector2f(1.0f, 0.0f)),
        // Bottom
        PackedVertex(Vector3f( 1.0f, 1.0f,-1.0f),Vector2f(0.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, 1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, 1.0f,-1.0f),Vector2f(0.0f, 0.0f)),
        PackedVertex(Vector3f( 1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f)),
        PackedVertex(Vector3f(-1.0f, 1.0f, 1.0f),Vector2f(1.0f, 0.0f)),
    }};

} // orion