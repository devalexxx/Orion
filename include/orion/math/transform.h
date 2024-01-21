//
// Created by Alex on 15/12/2023.
//

#ifndef ORION_MATRIX_TRANSFORM_H
#define ORION_MATRIX_TRANSFORM_H

#include "Vector3.h"
#include "Matrix4.h"

namespace orion {

    /**
     * Returns the given matrix rotate
     * @param m the matrix on which to apply the rotation
     * @param angle the angle in degree
     * @param axis the axis(es) to be rotated
     * @return the matrix m rotate
     */
    Matrix<4, 4, f32> rotate(Ref<Matrix<4, 4, f32>> m, f32 angle, Ref<Vector<3, f32>> axis);

    /**
     * Returns a rotation matrix
     * @param angle the angle in degree
     * @param axis the axis(es) to be rotated
     * @return the rotation matrix
     */
    Matrix<4, 4, f32> rotate(f32 angle, Ref<Vector<3, f32>> axis);

    Matrix<4, 4, f32> translate(Ref<Matrix<4, 4, f32>> m, Ref<Vector<3, f32>> v);
    Matrix<4, 4, f32> translate(Ref<Vector<3, f32>> v);

    Matrix<4, 4, f32> scale(Ref<Matrix<4, 4, f32>> m, Ref<Vector<3, f32>> v);
    Matrix<4, 4, f32> scale(Ref<Vector<3, f32>> v);

    template<typename T>
    inline Matrix<4, 4, T> look_at(Ref<Vector<3, T>> eye, Ref<Vector<3, T>> center, Ref<Vector<3, T>> up) {
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

        return std::move(ret);
    }

}

#endif //ORION_MATRIX_TRANSFORM_H
