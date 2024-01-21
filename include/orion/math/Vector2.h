//
// Created by Alex on 13/12/2023.
//

#ifndef ORION_VECTOR2_H
#define ORION_VECTOR2_H

#include "Vector.h"

namespace orion {

    template<typename T>
    class Vector<2, T> : public VectorBase<2, T> {
    public:
        static const Vector<2, T> UP;
        static const Vector<2, T> DOWN;
        static const Vector<2, T> LEFT;
        static const Vector<2, T> RIGHT;

        Vector() = default;
        Vector(T x, T y);
        explicit Vector(T value);
        explicit Vector(Ref<Vector<3, T>> v);
        explicit Vector(std::array<T, 2> a);

        T get_x() const;
        T get_y() const;
    };

    template<typename T>
    using Vector2 = Vector<2, T>;

    using Vector2i = Vector2<i32>;
    using Vector2u = Vector2<u32>;
    using Vector2f = Vector2<f32>;
    using Vector2d = Vector2<f64>;

    template<typename T>
    const Vector<2, T> Vector<2, T>::UP = Vector<2, T>(0, 1);

    template<typename T>
    const Vector<2, T> Vector<2, T>::DOWN = Vector<2, T>(0, -1);

    template<typename T>
    const Vector<2, T> Vector<2, T>::LEFT = Vector<2, T>(-1, 0);

    template<typename T>
    const Vector<2, T> Vector<2, T>::RIGHT = Vector<2, T>(1, 0);

    template<typename T>
    Vector<2, T>::Vector(T x, T y) : VectorBase<2, T>({std::move(x), std::move(y)}) {}

    template<typename T>
    Vector<2, T>::Vector(T value) : VectorBase<2, T>({value, value}) {}

    template<typename T>
    Vector<2, T>::Vector(Ref<Vector<3, T>> v) : VectorBase<2, T>({v[0], v[1]}) {}

    template<typename T>
    Vector<2, T>::Vector(std::array<T, 2> a) : VectorBase<2, T>(std::move(a)) {}

    template<typename T>
    T Vector<2, T>::get_x() const {
        return this->m_data[0];
    }

    template<typename T>
    T Vector<2, T>::get_y() const {
        return this->m_data[1];
    }

} // orion

#endif //ORION_VECTOR2_H
