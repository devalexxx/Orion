//
// Created by Alex on 21/11/2023.
//

#include "graphics/Vertex.h"

namespace orion {

    Vertex::Vertex(const glm::vec3 &position, const Color &color) : m_position(position), m_color(color) {}

    Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &uv) : m_position(position), m_uv(uv) {}

}