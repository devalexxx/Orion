//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_VERTEXARRAY_H
#define ORION_VERTEXARRAY_H

#include "core/type.h"
#include "core/DeferredRegistry.h"
#include "VertexBuffer.h"

#include "opengl/OpenGlContextRequired.h"

#include "GL/glew.h"

#include <vector>

namespace orion {

    class VertexArray : public OpenGlContextRequired {
    public:
        enum class DrawMode {
            TRIANGLES = GL_TRIANGLES,
            LINE_LOOP = GL_LINE_LOOP,
            LINES     = GL_LINES,
            POINTS    = GL_POINTS
        };

        static DeferredRegistry<VertexArray> REGISTRY;

        static bool is_any_bind;
        static void unbind();

        static std::shared_ptr<VertexArray> create();
        static std::shared_ptr<VertexArray> create(Ref<std::vector<PackedVertex>> data, Ref<std::shared_ptr<Shader>> shader);

        ~VertexArray();

        void bind() const;

        [[nodiscard]] u32 count() const;
        VertexBuffer& add_buffer(VertexBuffer::Type type);
        VertexBuffer& add_buffer(VertexBuffer::Type type, VertexBuffer::Usage usage);

        void draw(u32 first, u32 count, DrawMode mode = DrawMode::TRIANGLES) const;
        void draw(u32 count, DrawMode mode = DrawMode::TRIANGLES) const;
        void draw(DrawMode mode = DrawMode::TRIANGLES) const;

    private:
        VertexArray();

        u32 m_id {};
        std::vector<VertexBuffer> m_buffers;

        friend class RenderTarget;
    };

} // orion

#endif //ORION_VERTEXARRAY_H
