//
// Created by Alex on 13/12/2023.
//

#ifndef ORION_VECTOR_H
#define ORION_VECTOR_H

#include <array>
#include <ostream>

#include "core/type.h"

namespace orion {

    template<size_t S, typename T>
    class VectorBase;

    template<size_t S, typename T>
    class Vector : public VectorBase<S, T> {};

    template<size_t R, size_t C, typename T>
    class Matrix;

    template<size_t S, typename T>
    class VectorBase {
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "Vector must use integral of floating point type.");
    public:
        static Vector<S, T> zero();
        static Vector<S, T> one();

        RefMut<T> operator[](size_t index);
        Ref<T>    operator[](size_t index) const;

        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator+(Ref<Vector<SS, TT>> lhs, Ref<Vector<SS, TT>> rhs);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator+(Ref<Vector<SS, TT>> lhs, TT value);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator-(Ref<Vector<SS, TT>> lhs, Ref<Vector<SS, TT>> rhs);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator-(Ref<Vector<SS, TT>> lhs, TT value);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator-(Ref<Vector<SS, TT>> lhs);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator*(Ref<Vector<SS, TT>> lhs, Ref<Vector<SS, TT>> rhs);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator*(Ref<Vector<SS, TT>> lhs, TT value);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator/(Ref<Vector<SS, TT>> lhs, Ref<Vector<SS, TT>> rhs);
        template<size_t SS, typename TT>
        friend Vector<SS, TT> operator/(Ref<Vector<SS, TT>> lhs, TT value);

        template<size_t SS, typename TT>
        friend bool operator==(Ref<Vector<SS, TT>> lhs, Ref<Vector<SS, TT>> rhs);
        template<size_t SS, typename TT>
        friend bool operator!=(Ref<Vector<SS, TT>> lhs, Ref<Vector<SS, TT>> rhs);

        template<size_t SS, typename TT>
        friend RefMut<std::ostream> operator<<(RefMut<std::ostream> os, Ref<Vector<SS, TT>> v);

    protected:
        VectorBase() = default;
        explicit VectorBase(std::array<T, S> data);
        T m_data[S] {};
    };

    template<size_t S, typename T>
    Vector<S, T> VectorBase<S, T>::zero() {
        return Vector<S, T>(0);
    }

    template<size_t S, typename T>
    Vector<S, T> VectorBase<S, T>::one() {
        return Vector<S, T>(1);
    }

    template<size_t S, typename T>
    RefMut<T> VectorBase<S, T>::operator[](size_t index) {
        return m_data[index];
    }

    template<size_t S, typename T>
    Ref<T> VectorBase<S, T>::operator[](size_t index) const {
        return m_data[index];
    }

    template<size_t S, typename T>
    Vector<S, T> operator+(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] += rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator+(Ref<Vector<S, T>> lhs, T value) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] += value;
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator-(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] -= rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator-(Ref<Vector<S, T>> lhs, T value) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret[i] -= value;
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator-(Ref<Vector<S, T>> &lhs) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret[i] = -ret[i];
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator*(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] *= rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator*(Ref<Vector<S, T>> lhs, T value) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] *= value;
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator/(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] /= rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S, typename T>
    Vector<S, T> operator/(Ref<Vector<S, T>> lhs, T value) {
        auto ret = lhs;
        for (int i = 0; i < S; ++i) {
            ret.m_data[i] /= value;
        }
        return ret;
    }

    template<size_t S, typename T>
    bool operator==(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        for (int i = 0; i < S; ++i) {
            if(lhs.m_data[i] != rhs.m_data[i])
                return false;
        }
        return true;
    }

    template<size_t S, typename T>
    bool operator!=(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        return !(lhs == rhs);
    }

    template<size_t S, typename T>
    RefMut<std::ostream> operator<<(RefMut<std::ostream> os, Ref<Vector<S, T>> v) {
        os << "Vector<" << S << ", " << typeid(T).name() << ">(";
        for (int i = 0; i < S - 1; ++i) {
            os << v.m_data[i] << ", ";
        }
        os << v.m_data[S - 1];
        os << ")";
        return os;
    }

    template<size_t S, typename T>
    VectorBase<S, T>::VectorBase(std::array<T, S> data) {
        for (int i = 0; i < S; ++i) {
            m_data[i] = data[i];
        }
    }

} // orion

#endif //ORION_VECTOR_H
