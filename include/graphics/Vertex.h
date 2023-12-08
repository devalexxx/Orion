//
// Created by Alex on 21/11/2023.
//

#ifndef ORION_VERTEX_H
#define ORION_VERTEX_H

#include "glm/glm.hpp"
#include "Color.h"

#include <cstddef>
#include <optional>

namespace orion {
    class Vertex {
    public:
        Vertex(const glm::vec3& position, const Color& color);
        Vertex(const glm::vec3& position, const glm::vec2& uv);
    private:
        glm::vec3 m_position;
        std::optional<Color> m_color;
        std::optional<glm::vec2> m_uv;
    };
}


#endif //ORION_VERTEX_H
