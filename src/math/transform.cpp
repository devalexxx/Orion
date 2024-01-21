//
// Created by Alex on 15/12/2023.
//

#include "orion/math/transform.h"

#include "orion/math/Matrix.h"
#include "orion/math/Vector.h"
#include "orion/math/normalize.h"

#include <cmath>

namespace orion {

    Matrix<4, 4, f32> rotate(Ref<Matrix<4, 4, f32>> m, const f32 angle, Ref<Vector<3, f32>> v) {
        f32 const c = cos(angle);
        f32 const s = sin(angle);

        auto axis = normalize(v);
        auto temp = axis * (1 - c);

        auto rotate = Matrix<4, 4, f32>::identity();
        rotate[0][0] = c + temp[0] * axis[0];
        rotate[1][0] =     temp[0] * axis[1] + s * axis[2];
        rotate[2][0] =     temp[0] * axis[2] - s * axis[1];

        rotate[0][1] =     temp[1] * axis[0] - s * axis[2];
        rotate[1][1] = c + temp[1] * axis[1];
        rotate[2][1] =     temp[1] * axis[2] + s * axis[0];

        rotate[0][2] =     temp[2] * axis[0] + s * axis[1];
        rotate[1][2] =     temp[2] * axis[1] - s * axis[0];
        rotate[2][2] = c + temp[2] * axis[2];

        Matrix<4, 4, f32> ret;

        ret[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
        ret[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
        ret[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
        ret[3] = m[3];

        return ret;
    }

    Matrix<4, 4, f32> rotate(const f32 angle, Ref<Vector<3, f32>> axis) {
        return rotate(Matrix<4, 4, f32>::identity(), angle, axis);
    }

    Matrix<4, 4, f32> translate(Ref<Matrix<4, 4, f32>> m, Ref<Vector<3, f32>> v) {
        auto ret = m;
        ret[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];

        return ret;
    }

    Matrix<4, 4, f32> translate(Ref<Vector<3, f32>> v) {
        return translate(Matrix<4, 4, f32>::identity(), v);
    }

    Matrix<4, 4, f32> scale(Ref<Matrix<4, 4, f32>> m, Ref<Vector<3, f32>> v) {
        Matrix<4, 4, f32> ret;
        ret[0] = m[0] * v[0];
        ret[1] = m[1] * v[1];
        ret[2] = m[2] * v[2];
        ret[3] = m[3];

        return ret;
    }

    Matrix<4, 4, f32> scale(Ref<Vector<3, f32>> v) {
        return scale(Matrix<4, 4, f32>::identity(), v);
    }

}