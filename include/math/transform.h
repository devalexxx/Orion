//
// Created by Alex on 15/12/2023.
//

#ifndef ORION_MATRIX_TRANSFORM_H
#define ORION_MATRIX_TRANSFORM_H

#include "Vector3.h"
#include "Matrix4.h"
#include "core/type.h"

namespace orion {

    Matrix<4, 4, float> rotate(Ref<Matrix<4, 4, float>> m, float angle, Ref<Vector<3, float>> axis);
    Matrix<4, 4, float> rotate(float angle, const Vector<3, float>& axis);

    Matrix<4, 4, float> translate(Ref<Matrix<4, 4, float>> m, Ref<Vector<3, float>> v);

    Matrix<4, 4, f32> scale(Ref<Matrix<4, 4, f32>> m, Ref<Vector<3, f32>> v);

    template<typename T>
    Matrix<4, 4, T> look_at(Ref<Vector<3, T>> eye, Ref<Vector<3, T>> center, Ref<Vector<3, T>> up) {
        auto f = normalize(center - eye);
        auto s = normalize(cross(f, up));
        auto u = cross(s, f);

        auto ret = Matrix<4, 4, T>::identity();
        ret[0][0] =  s[0];
        ret[1][0] =  s[1];
        ret[2][0] =  s[2];
        ret[0][1] =  u[0];
        ret[1][1] =  u[1];
        ret[2][1] =  u[2];
        ret[0][2] = -f[0];
        ret[1][2] = -f[1];
        ret[2][2] = -f[2];
        ret[3][0] = -dot(s, eye);
        ret[3][1] = -dot(u, eye);
        ret[3][2] =  dot(f, eye);
        return ret;
    }

}

#endif //ORION_MATRIX_TRANSFORM_H
