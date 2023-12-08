//
// Created by Alex on 12/11/2023.
//

#include "core/Position.h"

namespace orion {

    Position2D::Position2D(float x, float y) : x(x), y(y) {}

    glm::vec<2, float> Position2D::toVec() {
        return {x, y};
    }

    Position3D::Position3D(float x, float y, float z) : x(x), y(y), z(z) {}

    glm::vec<3, float> Position3D::toVec() {
        return {x, y, z};
    }
} // orion