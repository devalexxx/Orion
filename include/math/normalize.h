//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_NORMALIZE_H
#define ORION_NORMALIZE_H

#include "Vector.h"

namespace orion {

    template<size_t S, typename T>
    Vector<S, T> normalize(Ref<Vector<S, T>> lhs) {
        static_assert(std::is_floating_point_v<T>);

        return lhs / magnitude(lhs);
    }

}

#endif //ORION_NORMALIZE_H
