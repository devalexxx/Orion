//
// Created by Alex on 14/12/2023.
//

#define _USE_MATH_DEFINES
#include <cmath>

#include "orion/math/angle.h"

#include "orion/math/Matrix4.h"
#include "orion/math/Vector3.h"

namespace orion {

    float radian(f32 degree) {
        return degree / (180 / M_PI);
    }

    float degree(f32 rad) {
        return rad * (180 / M_PI);
    }

    Vector<3, f32> euler_angle(Ref<Matrix<4, 4, f32>> m) {
        f32 T1 = atan2(m[1][2], m[2][2]);
        f32 C2 = sqrt(m[0][0] * m[0][0] + m[0][1] * m[0][1]);
        f32 T2 = atan2(-m[0][2], C2);
        f32 S1 = sin(T1);
        f32 C1 = cos(T1);
        f32 T3 = atan2(S1 * m[2][0] - C1 * m[1][0], C1 * m[1][1] - S1 * m[2][1]);

        return { -T1, -T2, -T3 };
    }

}
