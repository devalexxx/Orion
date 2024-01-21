//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_VERTEXARRAY_H
#define ORION_VERTEXARRAY_H

#include "orion/core/type.h"
#include "orion/core/DeferredRegistry.h"
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

        static u32 CURRENT_BOUND;
        static void unbind();

        VertexArray();
        ~VertexArray();

        void bind() const;

        RefMut<VertexBuffer> add_buffer(VertexBuffer::Type type);
        RefMut<VertexBuffer> add_buffer(VertexBuffer::Type type, VertexBuffer::Usage usage);

        RefMut<VertexBuffer> get_buffer(u32 index) { return m_vertex_buffers[index]; }
        RefMut<std::optional<VertexBuffer>> get_ibo();

    private:
        void draw(u32 first, u32 count, DrawMode mode = DrawMode::TRIANGLES) const;
        void draw(u32 count, DrawMode mode = DrawMode::TRIANGLES) const;
        void draw(DrawMode mode = DrawMode::TRIANGLES) const;

        u32 m_id {};

        std::vector<VertexBuffer>   m_vertex_buffers;
        std::optional<VertexBuffer> m_index_buffer;

        friend class RenderTarget;
    };

} // orion

#endif //ORION_VERTEXARRAY_H
