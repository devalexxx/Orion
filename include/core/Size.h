//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_SIZE_H
#define ORION_SIZE_H

#include <cstdlib>

#include "glm/glm.hpp"

namespace orion {

    template<size_t S>
    struct ISize {
        virtual glm::vec<S, float> toVec() = 0;
    };

    struct Size2D : public ISize<2> {
        float width{}, height{};

        Size2D() = default;
        Size2D(float width, float height);

        glm::vec<2, float> toVec() override;
    };

    struct Size3D : public ISize<3> {
        float width{}, height{}, depth{};

        Size3D() = default;
        Size3D(float width, float height, float depth);

        glm::vec<3, float> toVec() override;
    };

} // orion

#endif //ORION_SIZE_H
