//
// Created by Alex on 14/12/2023.
//

#define _USE_MATH_DEFINES
#include <cmath>

#include "math/angle.h"

#include "math/Matrix4.h"
#include "math/Vector3.h"

namespace orion {

    float rad(float degree) {
        return degree / (180 / M_PI);
    }

    float degree(float rad) {
        return rad * (180 / M_PI);
    }

    Vector<3, float> euler_angle(Ref<Matrix<4, 4, float>> m) {
        return {
            atan2(-m[2][0], sqrt((m[2][1] * m[2][1]) + (m[2][2] * m[2][2]))),
            atan2(m[2][1], m[2][2]),
            atan2(m[0][0], m[1][0])
        };
    }

}
