//
// Created by Alex on 21/11/2023.
//

#include "graphics/Color.h"

orion::Color::Color(float r, float g, float b) : m_data({r, g, b}) {}

glm::vec3 orion::Color::data() const {
    return m_data;
}
