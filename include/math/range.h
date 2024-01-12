//
// Created by Alex on 12/01/2024.
//

#ifndef ORION_RANGE_H
#define ORION_RANGE_H

#include "Vector.h"

namespace orion {

    template<typename T>
    T map_range(T value, T f_min, T f_max, T t_min, T t_max) {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
        return t_min + (t_max - t_min) * ((value - f_min) / (f_max - f_min));
    }

    template<size_t S, typename T>
    Vector<S, T> map_range(Ref<Vector<S, T>> value, T f_min, T f_max, T t_min, T t_max) {
        return ((value - f_min) / (f_max - f_min)) * (t_max - t_min) + t_min;
    }

} // orion

#endif //ORION_RANGE_H
