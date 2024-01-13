//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_CROSS_H
#define ORION_CROSS_H

namespace orion {

    template<typename T>
    inline Vector<3, T> cross(Ref<Vector<3, T>> lhs, Ref<Vector<3, T>> rhs) {
        return Vector<3, T>(
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        );
    }

}

#endif //ORION_CROSS_H
