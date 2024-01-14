//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_RENDERCONTEXT_H
#define ORION_RENDERCONTEXT_H

#include <memory>

#include "core/type.h"
#include "graphics/VertexArray.h"

namespace orion {

    class Shader;
    class Texture;
    class RenderTarget;

    class RenderContext {
    public:
        static const RenderContext DEFAULT;

        RenderContext();
        RenderContext(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, VertexArray::DrawMode draw_mode);

        [[nodiscard]] Ref<std::shared_ptr<Shader>>  get_shader   ()  const;
        [[nodiscard]] Ref<std::shared_ptr<Texture>> get_texture  () const;
        [[nodiscard]] VertexArray::DrawMode         get_draw_mode() const;

        void set_shader   (std::shared_ptr<Shader> shader);
        void set_texture  (std::shared_ptr<Texture> texture);
        void set_draw_mode(VertexArray::DrawMode mode);

        friend bool operator==(Ref<RenderContext> lhs, Ref<RenderContext> rhs);
        friend bool operator!=(Ref<RenderContext> lhs, Ref<RenderContext> rhs);
    private:
        std::shared_ptr<Shader>  m_shader;
        std::shared_ptr<Texture> m_texture;
        VertexArray::DrawMode    m_draw_mode = VertexArray::DrawMode::TRIANGLES;

        friend class RenderTarget;
    };

}


#endif //ORION_RENDERCONTEXT_H
