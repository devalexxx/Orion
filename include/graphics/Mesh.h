//
// Created by Alex on 14/01/2024.
//

#ifndef ORION_MESH_H
#define ORION_MESH_H

#include "core/type.h"
#include "PackedVertex.h"
#include "VertexArray.h"
#include "Drawable.h"
#include "Primitive.h"

namespace orion {

    class Mesh : public Drawable {
    public:
        static RefMut<DeferredRegistry<Mesh>> get_registry();

        static std::shared_ptr<Mesh> create(Ref<PackedVertexContainer> vertices);
        static std::shared_ptr<Mesh> create(Ref<PackedVertexContainer> vertices, Ref<IndexContainer> indices);

        RefMut<VertexArray> get_vao();

        [[nodiscard]] u32 get_length() const;

        void draw(Ref<RenderTarget> target, Ref<RenderContext> context) const override;

    private:
        Mesh(bool indexed, u32 length);

        bool        m_indexed;
        u32         m_length;
        VertexArray m_vao;
    };

    std::string mesh_name_builder(Primitive p, bool indexed, Ref<String> opt = "");
    std::string default_mesh_name_of(Primitive p);

} // orion

#endif //ORION_MESH_H
