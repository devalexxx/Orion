//
// Created by Alex on 12/11/2023.
//

#include "core/Size.h"

namespace orion {

    Size2D::Size2D(float width, float height) : width(width), height(height) {}

    glm::vec<2, float> Size2D::toVec() {
        return {width, height};
    }

    Size3D::Size3D(float width, float height, float depth) : width(width), height(height), depth(depth) {}

    glm::vec<3, float> Size3D::toVec() {
        return {width, height, depth};
    }
} // orion