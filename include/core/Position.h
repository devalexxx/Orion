//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_POSITION_H
#define ORION_POSITION_H

#include <cstdlib>

#include "glm/glm.hpp"

namespace orion {

    template<size_t S>
    struct IPosition {
        virtual glm::vec<S, float> toVec() = 0;
    };

    struct Position2D : public IPosition<2> {
        float x{}, y{};

        Position2D() = default;
        Position2D(float x, float y);

        glm::vec<2, float> toVec() override;
    };

    struct Position3D : public IPosition<3> {
        float x{}, y{}, z{};

        Position3D() = default;
        Position3D(float x, float y, float z);

        glm::vec<3, float> toVec() override;
    };

    using Scale2D = Position2D;
    using Scale3D = Position3D;

} // orion

#endif //ORION_POSITION_H
