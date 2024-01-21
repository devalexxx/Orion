//
// Created by Alex on 21/11/2023.
//

#ifndef ORION_COLOR_H
#define ORION_COLOR_H

#include "orion/math/Vector4.h"
#include "orion/math/Vector3.h"

namespace orion {

    class Color {
    public:
        static const Color WHITE;
        static const Color BLACK;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;

        explicit Color(f32 r, f32 g, f32 b, f32 a);

        RefMut<f32> operator[](size_t index);
        Ref<f32>    operator[](size_t index) const;

        [[nodiscard]] Vector3f to_rgb() const;

    private:
        Vector4f m_data;
    };
}


#endif //ORION_COLOR_H
