//
// Created by Alex on 15/12/2023.
//

#include "math/transform.h"

#include "math/Vector4.h"
#include "math/Matrix.h"
#include "math/Vector.h"


namespace orion {

    Matrix<4, 4, float> rotate(Ref<Matrix<4, 4, float>> m, float angle, Ref<Vector<3, float>> axis) {
        float const a = angle;
        float const c = cos(a);
        float const s = sin(a);

        auto temp = axis * (1 - c);

        auto rotate = Matrix<4, 4, float>::identity();
        rotate[0][0] = c              + temp[0]     * axis[0];
        rotate[0][1] = temp[0] * axis[1] + s * axis[2];
        rotate[0][2] = temp[0] * axis[2] - s * axis[1];

        rotate[1][0] = temp[1] * axis[0] - s * axis[2];
        rotate[1][1] = c              + temp[1]     * axis[1];
        rotate[1][2] = temp[1] * axis[2] + s * axis[0];

        rotate[2][0] = temp[2] * axis[0] + s * axis[1];
        rotate[2][1] = temp[2] * axis[1] - s * axis[0];
        rotate[2][2] = c              + temp[2]     * axis[2];

        auto ret = Matrix<4, 4, float>(0);

        ret[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
        ret[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
        ret[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
        ret[3] = m[3];

        return ret;
    }

    Matrix<4, 4, float> rotate(float angle, const Vector<3, float>& axis) {
        return rotate(Matrix<4, 4, float>::identity(), angle, axis);
    }

    Matrix<4, 4, float> translate(Ref<Matrix<4, 4, float>> m, Ref<Vector<3, float>> v) {
        auto ret = m;
        ret[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
        return ret;
    }

    Matrix<4, 4, f32> scale(Ref<Matrix<4, 4, f32>> m, Ref<Vector<3, f32>> v) {
        Matrix<4, 4, f32> ret;
        ret[0] = m[0] * v[0];
        ret[1] = m[1] * v[1];
        ret[2] = m[2] * v[2];
        ret[3] = m[3];
        return ret;
    }

}