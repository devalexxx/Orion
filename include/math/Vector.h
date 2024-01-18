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
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "Vector must use integral or floating point type.");
    public:
        using value_type = T;

        static Vector<S, T> zero();
        static Vector<S, T> one();

        static constexpr size_t size();

        RefMut<T> operator[](size_t index);
        Ref<T>    operator[](size_t index) const;

        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator+(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator+(Ref<Vector<S_, T_>> lhs, T_ value);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator+(T_ value, Ref<Vector<S_, T_>> rhs);

        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator-(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator-(Ref<Vector<S_, T_>> lhs, T_ value);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator-(T_ value, Ref<Vector<S_, T_>> rhs);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator-(Ref<Vector<S_, T_>> lhs);

        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator*(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator*(Ref<Vector<S_, T_>> lhs, T_ value);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator*(T_ value, Ref<Vector<S_, T_>> rhs);

        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator/(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator/(Ref<Vector<S_, T_>> lhs, T_ value);
        template<size_t S_, typename T_>
        friend Vector<S_, T_> operator/(T_ value, Ref<Vector<S_, T_>> rhs);

        template<size_t S_, typename T_>
        friend bool operator==(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs);
        template<size_t S_, typename T_>
        friend bool operator!=(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs);

        template<size_t SS, typename TT>
        friend RefMut<std::ostream> operator<<(RefMut<std::ostream> os, Ref<Vector<SS, TT>> v);

    protected:
        VectorBase() = default;
        explicit VectorBase(std::array<T, S> data);
        std::array<T, S> m_data {};
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
    constexpr size_t VectorBase<S, T>::size() {
        return S;
    }

    template<size_t S, typename T>
    RefMut<T> VectorBase<S, T>::operator[](size_t index) {
        return m_data[index];
    }

    template<size_t S, typename T>
    Ref<T> VectorBase<S, T>::operator[](size_t index) const {
        return m_data[index];
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator+(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S_; ++i) {
            ret[i] += rhs[i];
        }
        return ret;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator+(Ref<Vector<S_, T_>> lhs, T_ value) {
        return lhs + Vector<S_, T_>(value);
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator+(T_ value, Ref<Vector<S_, T_>> rhs) {
        return Vector<S_, T_>(value) + rhs;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator-(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S_; ++i) {
            ret.m_data[i] -= rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator-(Ref<Vector<S_, T_>> lhs, T_ value) {
        return lhs - Vector<S_, T_>(value);
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator-(T_ value, Ref<Vector<S_, T_>> rhs) {
        return Vector<S_, T_>(value) - rhs;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator-(Ref<Vector<S_, T_>> lhs) {
        return static_cast<T_>(0) - lhs;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator*(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S_; ++i) {
            ret.m_data[i] *= rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator*(Ref<Vector<S_, T_>> lhs, T_ value) {
        return lhs * Vector<S_, T_>(value);
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator*(T_ value, Ref<Vector<S_, T_>> rhs) {
        return Vector<S_, T_>(value) * rhs;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator/(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs) {
        auto ret = lhs;
        for (int i = 0; i < S_; ++i) {
            ret.m_data[i] /= rhs.m_data[i];
        }
        return ret;
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator/(Ref<Vector<S_, T_>> lhs, T_ value) {
        return lhs / Vector<S_, T_>(value);
    }

    template<size_t S_, typename T_>
    Vector<S_, T_> operator/(T_ value, Ref<Vector<S_, T_>> rhs) {
        return Vector<S_, T_>(value) / rhs;
    }

    template<size_t S_, typename T_>
    bool operator==(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs) {
        for (int i = 0; i < S_; ++i) {
            if(lhs.m_data[i] != rhs.m_data[i])
                return false;
        }
        return true;
    }

    template<size_t S_, typename T_>
    bool operator!=(Ref<Vector<S_, T_>> lhs, Ref<Vector<S_, T_>> rhs) {
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
        m_data = std::move(data);
    }

} // orion

#endif //ORION_VECTOR_H
