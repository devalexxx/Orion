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

    protected:
        bool m_frame_swap {false};

    private:
        View m_view {};
    };

}


#endif //ORION_RENDERTARGET_H
