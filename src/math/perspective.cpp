//
// Created by Alex on 15/12/2023.
//

#include "math/perspective.h"

#include "math/Vector.h"

namespace orion {

    Matrix<4, 4, float> perspective(float fov, float aspect, float z_near, float z_far) {
        float const tan_half_fov = tan(fov / 2.f);
        Matrix<4, 4, float> ret;
        ret[0][0] = 1 / (aspect * tan_half_fov);
        ret[1][1] = 1 / tan_half_fov;
        ret[2][2] = - (z_far + z_near) / (z_far - z_near);
        ret[2][3] = - 1;
        ret[3][2] = - (2 * z_far * z_near) / (z_far - z_near);
        return ret;
    }

}