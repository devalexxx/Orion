//
// Created by Alex on 13/12/2023.
//

#ifndef ORION_VECTOR3_H
#define ORION_VECTOR3_H

#include "Vector.h"

namespace orion {

    template<typename T>
    class Vector<3, T> : public VectorBase<3, T> {
    public:
        static const Vector<3, T> UP;
        static const Vector<3, T> DOWN;
        static const Vector<3, T> LEFT;
        static const Vector<3, T> RIGHT;
        static const Vector<3, T> FORWARD;
        static const Vector<3, T> BACK;

        Vector() = default;
        Vector(T x, T y, T z);
        Vector(Ref<Vector<2, T>> v, T z);
        explicit Vector(T value);
        explicit Vector(Ref<Vector<4, T>> v);
        explicit Vector(std::array<T, 3> a);

        T get_x() const;
        T get_y() const;
        T get_z() const;
    };

    template<typename T>
    using Vector3 = Vector<3, T>;

    using Vector3i = Vector3<i32>;
    using Vector3u = Vector3<u32>;
    using Vector3f = Vector3<f32>;
    using Vector3d = Vector3<f64>;

    template<typename T>
    const Vector<3, T> Vector<3, T>::UP = Vector<3, T>(0, 1, 0);

    template<typename T>
    const Vector<3, T> Vector<3, T>::DOWN = Vector<3, T>(0, -1, 0);

    template<typename T>
    const Vector<3, T> Vector<3, T>::LEFT = Vector<3, T>(-1, 0, 0);

    template<typename T>
    const Vector<3, T> Vector<3, T>::RIGHT = Vector<3, T>(1, 0, 0);

    template<typename T>
    const Vector<3, T> Vector<3, T>::FORWARD = Vector<3, T>(0, 0, 1);

    template<typename T>
    const Vector<3, T> Vector<3, T>::BACK = Vector<3, T>(0, 0, -1);

    template<typename T>
    Vector<3, T>::Vector(T x, T y, T z) : VectorBase<3, T>({std::move(x), std::move(y), std::move(z)}) {}

    template<typename T>
    Vector<3, T>::Vector(Ref<Vector<2, T>> v, T z) : VectorBase<3, T>({v[0], v[1], std::move(z)}) {}

    template<typename T>
    Vector<3, T>::Vector(T value) : VectorBase<3, T>({value, value, value}) {}

    template<typename T>
    Vector<3, T>::Vector(Ref<Vector<4, T>> v) : VectorBase<3, T>({v[0], v[1], v[2]}) {}

    template<typename T>
    Vector<3, T>::Vector(std::array<T, 3> a) : VectorBase<3, T>(std::move(a)) {}

    template<typename T>
    T Vector<3, T>::get_x() const {
        return this->m_data[0];
    }

    template<typename T>
    T Vector<3, T>::get_y() const {
        return this->m_data[1];
    }

    template<typename T>
    T Vector<3, T>::get_z() const {
        return this->m_data[2];
    }

} // orion

#endif //ORION_VECTOR3_H
