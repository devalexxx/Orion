//
// Created by Alex on 21/11/2023.
//

#include "orion/graphics/Color.h"

namespace orion {

    const Color Color::WHITE = Color(1.f, 1.f, 1.f, 1.f);
    const Color Color::BLACK = Color(0.f, 0.f, 0.f, 1.f);
    const Color Color::RED   = Color(1.f, 0.f, 0.f, 1.f);
    const Color Color::GREEN = Color(0.f, 1.f, 0.f, 1.f);
    const Color Color::BLUE  = Color(0.f, 0.f, 1.f, 1.f);

    Color::Color(f32 r, f32 g, f32 b, f32 a) : m_data({r, g, b, a}) {}

    RefMut<f32> Color::operator[](size_t index) {
        return m_data[index];
    }

    Ref<f32> Color::operator[](size_t index) const {
        return m_data[index];
    }

    Vector3f Color::to_rgb() const {
        return Vector3f(m_data);
    }

}
