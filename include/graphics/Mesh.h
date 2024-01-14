//
// Created by Alex on 14/01/2024.
//

#ifndef ORION_MESH_H
#define ORION_MESH_H

#include "core/type.h"
#include "PackedVertex.h"
#include "VertexArray.h"
#include "Drawable.h"

namespace orion {

    class Mesh : public Drawable {
    public:
        using Initializer = std::function<void(Ref<Shader>)>;

        static DeferredRegistry<Mesh> REGISTRY;

        static std::shared_ptr<Mesh> create(Ref<PackedVertexContainer> vertices);
        static std::shared_ptr<Mesh> create(Ref<PackedVertexContainer> vertices, Ref<IndexContainer> indices);
        static std::shared_ptr<Mesh> create(Ref<Pair<PackedVertexContainer, IndexContainer>> indexed);

        RefMut<VertexArray> get_vao();

        [[nodiscard]] u32 get_length() const;

        void draw(Ref<RenderTarget> target, Ref<RenderContext> context) const override;

    private:
        Mesh(bool indexed, u32 length);

        bool        m_indexed;
        u32         m_length;
        VertexArray m_vao;
    };

} // orion

#endif //ORION_MESH_H
