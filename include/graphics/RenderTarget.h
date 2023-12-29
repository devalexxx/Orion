//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_RENDERTARGET_H
#define ORION_RENDERTARGET_H

#include "View.h"
#include "RenderContext.h"

namespace orion {

    class Drawable;
    class VertexArray;

    class RenderTarget {
    public:
        RenderTarget() = default;

        void draw(Ref<Drawable> drawable, Ref<RenderContext> context = RenderContext::DEFAULT) const;
        void draw(Ref<VertexArray> vao, Ref<RenderContext> context) const;

        RefMut<View> get_view();
    private:
        void apply_texture(Ref<Texture> texture, Ref<Shader> shader) const;

        View m_view {};

        bool m_is_new_frame {false};
    };

}


#endif //ORION_RENDERTARGET_H
