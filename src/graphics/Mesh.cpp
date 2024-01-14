//
// Created by Alex on 14/01/2024.
//

#include "graphics/Mesh.h"

#include "graphics/VertexArray.h"
#include "graphics/Primitive.h"
#include "graphics/RenderTarget.h"

namespace orion {

    DeferredRegistry<Mesh> Mesh::REGISTRY = DeferredRegistry<Mesh>(
            "opengl",
            [](RefMut<DeferredRegistry<Mesh>> registry) {
                using namespace generator;

                registry.add(to_string(Primitive::TRIANGLE), Mesh::create(triangle_vertices()));
                registry.add(to_string(Primitive::SQUARE  ), Mesh::create(square_vertices()));
                registry.add(to_string(Primitive::CIRCLE  ), Mesh::create(index(circle_vertices(128))));
                registry.add(to_string(Primitive::CUBE    ), Mesh::create(index(cube_vertices())));
                registry.add(to_string(Primitive::SPHERE  ), Mesh::create(index(sphere_vertices(4))));
            }
    );

    std::shared_ptr<Mesh> Mesh::create(Ref<PackedVertexContainer> vertices) {
        auto ret = std::shared_ptr<Mesh>(new Mesh(false, vertices.size()));

        auto& vbo = ret->m_vao.add_buffer(VertexBuffer::Type::ARRAY);
        vbo.set_data(vertices);

        VertexBuffer::unbind();
        VertexArray ::unbind();

        return std::move(ret);
    }

    std::shared_ptr<Mesh> Mesh::create(Ref<PackedVertexContainer> vertices, Ref<IndexContainer> indices) {
        auto ret = std::shared_ptr<Mesh>(new Mesh(true, indices.size()));

        auto& vbo = ret->m_vao.add_buffer(VertexBuffer::Type::ARRAY);
        vbo.set_data(vertices);

        auto& ibo = ret->m_vao.add_buffer(VertexBuffer::Type::ELEMENT);
        ibo.set_data(indices);

        VertexBuffer::unbind();
        VertexArray ::unbind();

        return std::move(ret);
    }

    std::shared_ptr<Mesh> Mesh::create(Ref<Pair<PackedVertexContainer, IndexContainer>> indexed) {
        return create(indexed.first, indexed.second);
    }

    RefMut<VertexArray> Mesh::get_vao() {
        return m_vao;
    }

    u32 Mesh::get_length() const {
        return m_length;
    }

    void Mesh::draw(Ref<RenderTarget> target, Ref<RenderContext> context) const {
        target.draw(m_vao, context);
    }

    Mesh::Mesh(bool indexed, u32 length) :
        m_indexed(indexed),
        m_length(length)
    {}
} // orion