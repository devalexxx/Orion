//
// Created by Alex on 13/01/2024.
//

#include "doctest/doctest.h"

#include "orion/omath.h"

template<size_t S, typename T>
inline bool vector_approx(orion::Ref<orion::Vector<S, T>> lhs, orion::Ref<orion::Vector<S, T>> rhs) {
    static_assert(std::is_floating_point_v<T>);
    for (orion::u32 i = 0; i < S; ++i)
        if (lhs[i] != doctest::Approx(rhs[i]))
            return false;
    return true;
}

template<size_t R, size_t C, typename T>
inline bool matrix_approx(orion::Ref<orion::Matrix<R, C, T>> lhs, orion::Ref<orion::Matrix<R, C, T>> rhs) {
    static_assert(std::is_floating_point_v<T>);
    for (orion::u32 i = 0; i < R; ++i)
        for (orion::u32 j = 0; j < C; ++j)
            if (lhs[i][j] != doctest::Approx(rhs[i][j]))
                return false;
    return true;
}