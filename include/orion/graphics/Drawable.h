//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_DRAWABLE_H
#define ORION_DRAWABLE_H

#include "orion/core/type.h"

namespace orion {

    class RenderTarget;
    class RenderContext;

    class Drawable {
    public:
        virtual void draw(Ref<RenderTarget> target, Ref<RenderContext> context) const = 0;
    };

} // orion

#endif //ORION_DRAWABLE_H
