//
// Created by Alex on 15/12/2023.
//

#ifndef ORION_MATRIX_H
#define ORION_MATRIX_H

#include <array>
#include <ostream>

#include "core/type.h"

namespace orion {

    template<size_t R, size_t C, typename T>
    class MatrixBase;

    template<size_t R, size_t C, typename T>
    class Matrix : public MatrixBase<R, C, T> {};

    template<size_t S, typename T>
    class Vector;

    template<size_t R, size_t C, typename T>
    class MatrixBase {
        static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "Vector must use integral of floating point type.");
    public:
        static Matrix<R, C, T> zero();
        static Matrix<R, C, T> one();
        static Matrix<R, C, T> identity();

        const T* data() const;

        RefMut<Vector<C, T>> operator[](size_t row);
        Ref<Vector<C, T>>    operator[](size_t row) const;

        template<size_t RR, size_t CC, typename TT>
        friend Matrix<RR, CC, TT> operator+(Ref<Matrix<RR, CC, TT>> lhs, Ref<Matrix<RR, CC, TT>> rhs);

        template<size_t RR, size_t CR, size_t CC, typename TT>
        friend Matrix<RR, CC, TT> operator*(Ref<Matrix<RR, CR, TT>> lhs, Ref<Matrix<CR, CC, TT>> rhs);

        template<size_t RR, size_t CC, typename TT>
        friend bool operator==(Ref<Matrix<RR, CC, TT>> lhs, Ref<Matrix<RR, CC, TT>> rhs);
        template<size_t RR, size_t CC, typename TT>
        friend bool operator!=(Ref<Matrix<RR, CC, TT>> lhs, Ref<Matrix<RR, CC, TT>> rhs);

        template<size_t RR, size_t CC, typename TT>
        friend RefMut<std::ostream> operator<<(RefMut<std::ostream> os, Ref<Matrix<RR, CC, TT>> v);

    protected:
        MatrixBase() = default;
        explicit MatrixBase(std::array<T, R * C> data);
        explicit MatrixBase(T value);

        Vector<C, T> m_data[R];
    };

    template<size_t RR, size_t CR, size_t CC, typename TT>
    Matrix<RR, CC, TT> operator*(Ref<Matrix<RR, CR, TT>> lhs, Ref<Matrix<CR, CC, TT>> rhs) {
        return dot(lhs, rhs);
    }

    template<size_t R, size_t C, typename T>
    Matrix<R, C, T> MatrixBase<R, C, T>::zero() {
        return Matrix<R, C, T>(0);
    }

    template<size_t R, size_t C, typename T>
    Matrix<R, C, T> MatrixBase<R, C, T>::one() {
        return Matrix<R, C, T>(1);
    }

    template<size_t R, size_t C, typename T>
    Matrix<R, C, T> MatrixBase<R, C, T>::identity() {
        auto m = Matrix<R, C, T>(0);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (i == j)
                    m[i][j] = 1;
            }
        }
        return m;
    }

    template<size_t R, size_t C, typename T>
    Ptr<T> MatrixBase<R, C, T>::data() const {
        return &m_data[0][0];
    }

    template<size_t R, size_t C, typename T>
    RefMut<Vector<C, T>> MatrixBase<R, C, T>::operator[](size_t row) {
        return m_data[row];
    }

    template<size_t R, size_t C, typename T>
    Ref<Vector<C, T>> MatrixBase<R, C, T>::operator[](size_t row) const {
        return m_data[row];
    }

    template<size_t RR, size_t CC, typename TT>
    Matrix<RR, CC, TT> operator+(Ref<Matrix<RR, CC, TT>> lhs, Ref<Matrix<RR, CC, TT>> rhs) {
        Matrix<RR, CC, TT> ret;
        for (int i = 0; i < RR; ++i) {
            for (int j = 0; j < CC; ++j) {
                ret[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return ret;
    }

    template<size_t RR, size_t CC, typename TT>
    bool operator==(Ref<Matrix<RR, CC, TT>> lhs, Ref<Matrix<RR, CC, TT>> rhs) {
        for (int i = 0; i < RR; ++i) {
            for (int j = 0; j < CC; ++j) {
                if (lhs[i][j] != rhs[i][j])
                    return false;
            }
        }
        return true;
    }

    template<size_t RR, size_t CC, typename TT>
    bool operator!=(Ref<Matrix<RR, CC, TT>> lhs, Ref<Matrix<RR, CC, TT>> rhs) {
        return !(lhs == rhs);
    }

    template<size_t RR, size_t CC, typename TT>
    RefMut<std::ostream> operator<<(RefMut<std::ostream> os, Ref<Matrix<RR, CC, TT>> &m) {
        os << "Matrix<" << RR << ", " << CC << ", " << typeid(TT).name() << ">(\n";
        for (int i = 0; i < RR; ++i) {
            os << "\t";
            for (int j = 0; j < CC - 1; ++j) {
                os << m[i][j] << ", ";
            }
            os << m[i][CC - 1] << "\n";
        }
        os << ")";
        return os;
    }

    template<size_t R, size_t C, typename T>
    MatrixBase<R, C, T>::MatrixBase(std::array<T, R * C> data) {
        for (int i = 0; i < R; ++i) {
            m_data[i] = Vector<C, T>::zero();
            for (int j = 0; j < C; ++j) {
                m_data[i][j] = data[i * C + j];
            }
        }
    }

    template<size_t R, size_t C, typename T>
    MatrixBase<R, C, T>::MatrixBase(T value) {
        for (int i = 0; i < R; ++i) {
            m_data[i] = Vector<C, T>(value);
        }
    }

} // orion

#endif //ORION_MATRIX_H
