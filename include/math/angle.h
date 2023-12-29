//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_ANGLE_H
#define ORION_ANGLE_H

#include "Vector.h"

namespace orion {

    float rad(float degree);

    float degree(float rad);

    template<size_t S, typename T>
    float angle(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        return acos(dot(lhs, rhs) / (magnitude(lhs) * magnitude(rhs)));
    }

    Vector<3, float> euler_angle(Ref<Matrix<4, 4, float>> m);

}

#endif //ORION_ANGLE_H
