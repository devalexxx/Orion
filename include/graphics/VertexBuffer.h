//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_VERTEXBUFFER_H
#define ORION_VERTEXBUFFER_H

#include <vector>
#include <memory>

#include <GL/glew.h>
#include "core/type.h"

#include "opengl/OpenGlContextRequired.h"

namespace orion {

    template<size_t L, typename T>
    class Vector;

    class Shader;
    class VertexArray;
    class PackedVertex;

    using PackedVertexContainer = std::vector<PackedVertex>;

    class VertexBuffer : public OpenGlContextRequired {
    public:
        enum class Type {
            ARRAY   = GL_ARRAY_BUFFER,
            ELEMENT = GL_ELEMENT_ARRAY_BUFFER,
        };

        enum class Usage {
            STATIC  = GL_STATIC_DRAW,
            DYNAMIC = GL_DYNAMIC_DRAW,
            STREAM  = GL_STREAM_DRAW,
        };

        static void unbind();

        VertexBuffer(Type type, Usage usage);
        explicit VertexBuffer(Type type);

        ~VertexBuffer();

        void bind() const;

        void set_data(Ref<PackedVertexContainer> v, Ref<std::shared_ptr<Shader>> shader);

        void set_data(Ref<PackedVertexContainer> v);
        void set_data(Ref<IndexContainer> v);

    private:
        const Type  m_type;
        const Usage m_usage;
        u32   count{0};
        u32   m_id {};

        friend class VertexArray;
    };
}


#endif //ORION_VERTEXBUFFER_H
