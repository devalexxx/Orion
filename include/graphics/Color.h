//
// Created by Alex on 21/11/2023.
//

#ifndef ORION_COLOR_H
#define ORION_COLOR_H

#include "glm/glm.hpp"

namespace orion {
    class Color {
    public:
        explicit Color(float r, float g, float b);
        [[nodiscard]] glm::vec3 data() const;
    private:
        glm::vec3 m_data;
    };
}


#endif //ORION_COLOR_H
