//
// Created by Alex on 21/11/2023.
//

#ifndef ORION_RENDERTARGET_H
#define ORION_RENDERTARGET_H

#include <vector>

#include "Vertex.h"

namespace orion {
    class Drawable;

    class RenderTarget {
    public:
        void draw(const Drawable& drawable);

        void draw(const std::vector<Vertex>& vertices);
    };
}


#endif //ORION_RENDERTARGET_H
