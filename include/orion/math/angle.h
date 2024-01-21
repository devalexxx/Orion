//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_ANGLE_H
#define ORION_ANGLE_H

#include "Vector.h"

namespace orion {

    float radian(f32 degree);

    template<size_t S>
    inline Vector<S, f32> radian(Ref<Vector<S, f32>> v) {
        auto ret = Vector<S, f32>::zero();
        for (u32 i = 0; i < S; ++i) {
            ret[i] = radian(v[i]);
        }
        return std::move(ret);
    }

    float degree(f32 rad);

    template<size_t S>
    inline Vector<S, f32> degree(Ref<Vector<S, f32>> v) {
        auto ret = Vector<S, f32>::zero();
        for (u32 i = 0; i < S; ++i) {
            ret[i] = degree(v[i]);
        }
        return std::move(ret);
    }

    /**
     * Return the angle between the two vector as radian
     * @tparam S the vector length
     * @tparam T the vector data type
     * @param lhs the left hand vector
     * @param rhs the right hand vector
     * @return the angle between the two vector
     */
    template<size_t S, typename T>
    inline float angle(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        return acos(dot(lhs, rhs) / (magnitude(lhs) * magnitude(rhs)));
    }

    Vector<3, f32> euler_angle(Ref<Matrix<4, 4, f32>> m);

}

#endif //ORION_ANGLE_H
