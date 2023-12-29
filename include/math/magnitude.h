//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_MAGNITUDE_H
#define ORION_MAGNITUDE_H

#include "Vector.h"

namespace orion {

    template<size_t S, typename T>
    T magnitude(Ref<Vector<S, T>> lhs) {
        static_assert(std::is_floating_point_v<T>);

        T result {};
        for (int i = 0; i < S; ++i) {
            result += lhs[i] * lhs[i];
        }
        return sqrt(result);
    }

}

#endif //ORION_MAGNITUDE_H
