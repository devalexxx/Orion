//
// Created by Alex on 13/12/2023.
//

#ifndef ORION_VECTOR4_H
#define ORION_VECTOR4_H

#include "Vector.h"
#include "core/type.h"

namespace orion {

    template<typename T>
    class Vector<4, T> : public VectorBase<4, T> {
    public:
        Vector() = default;

        explicit Vector(T value);

        Vector(T x, T y, T z, T w);
        Vector(Ref<Vector<3, T>> v, T w);

        T get_x() const;
        T get_y() const;
        T get_z() const;
        T get_w() const;
    };

    template<typename T>
    using Vector4 = Vector<4, T>;

    using Vector4i = Vector4<i32>;
    using Vector4u = Vector4<u32>;
    using Vector4f = Vector4<f32>;
    using Vector4d = Vector4<f64>;

    template<typename T>
    Vector<4, T>::Vector(T x, T y, T z, T w) : VectorBase<4, T>({x, y, z, w}) {}

    template<typename T>
    Vector<4, T>::Vector(T value) : VectorBase<4, T>({value, value, value, value}) {}

    template<typename T>
    Vector<4, T>::Vector(Ref<Vector<3, T>> v, T w) : VectorBase<4, T>({v[0], v[1], v[2], w}) {}

    template<typename T>
    T Vector<4, T>::get_x() const {
        return this->m_data[0];
    }

    template<typename T>
    T Vector<4, T>::get_y() const {
        return this->m_data[1];
    }

    template<typename T>
    T Vector<4, T>::get_z() const {
        return this->m_data[2];
    }

    template<typename T>
    T Vector<4, T>::get_w() const {
        return this->m_data[3];
    }

} // orion

#endif //ORION_VECTOR4_H
