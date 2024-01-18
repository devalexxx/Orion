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

                auto mesh_wrapper = [](Ref<Pair<PackedVertexContainer, IndexContainer>> p) {
                    return std::move(Mesh::create(p.first, p.second));
                };

                registry.add(
                    mesh_name_builder(Primitive::TRIANGLE, false),
                    Mesh::create(triangle_vertices())
                );
                registry.add(
                    mesh_name_builder(Primitive::SQUARE, false),
                    Mesh::create(square_vertices())
                );
                registry.add(
                    mesh_name_builder(Primitive::CIRCLE, false, "128"),
                    mesh_wrapper(index(circle_vertices(128)))
                );
                registry.add(
                    mesh_name_builder(Primitive::CIRCLE, true, "128"),
                    mesh_wrapper(index(circle_vertices(128)))
                );
                registry.add(
                    mesh_name_builder(Primitive::CUBE, false),
                    mesh_wrapper(index(cube_vertices()))
                );
                registry.add(
                    mesh_name_builder(Primitive::CUBE, true),
                    mesh_wrapper(index(cube_vertices()))
                );
                registry.add(
                    mesh_name_builder(Primitive::SPHERE, false, "4"),
                    mesh_wrapper(index(sphere_vertices(4)))
                );
                registry.add(
                    mesh_name_builder(Primitive::SPHERE, true, "4"),
                    mesh_wrapper(index(sphere_vertices(4)))
                );
            }
    );

    std::shared_ptr<Mesh> Mesh::create(Ref<PackedVertexContainer> vertices) {
        auto ret = std::shared_ptr<Mesh>(new Mesh(false, vertices.size()));

        auto& vbo = ret->m_vao.add_buffer(VertexBuffer::Type::ARRAY);
        vbo.set_data(vertices);

        return std::move(ret);
    }

    std::shared_ptr<Mesh> Mesh::create(Ref<PackedVertexContainer> vertices, Ref<IndexContainer> indices) {
        auto ret = std::shared_ptr<Mesh>(new Mesh(true, indices.size()));

        auto& vbo = ret->m_vao.add_buffer(VertexBuffer::Type::ARRAY);
        vbo.set_data(vertices);

        auto& ibo = ret->m_vao.add_buffer(VertexBuffer::Type::ELEMENT);
        ibo.set_data(indices);

        return std::move(ret);
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

    std::string mesh_name_builder(Primitive p, bool indexed, Ref<String> opt) {
        std::string ret;

        ret.append(indexed ? "indexed" : "default");
        ret.append("|");
        ret.append(to_string(p));
        ret.append("|");
        ret.append(opt);

        return ret;
    }

    std::string default_mesh_name_of(Primitive p) {
        switch (p) {
            case Primitive::TRIANGLE:
            case Primitive::SQUARE:
                return std::move(mesh_name_builder(p, false));
            case Primitive::CIRCLE:
                return std::move(mesh_name_builder(p, true, "128"));
            case Primitive::CUBE:
                return std::move(mesh_name_builder(p, true));
            case Primitive::SPHERE:
                return std::move(mesh_name_builder(p, true, "4"));
        }
    }
} // orion