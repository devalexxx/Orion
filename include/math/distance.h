//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_DISTANCE_H
#define ORION_DISTANCE_H

namespace orion {

    template<size_t S, typename T>
    float distance(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        T result {};
        for (int i = 0; i < S; ++i) {
            result += pow(lhs[i] - rhs[i], 2);
        }
        return sqrt(result);
    }

}

#endif //ORION_DISTANCE_H
