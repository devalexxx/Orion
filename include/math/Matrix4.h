//
// Created by Alex on 15/12/2023.
//

#ifndef ORION_MATRIX4_H
#define ORION_MATRIX4_H

#include "Matrix.h"
#include "Vector4.h"

#include "core/type.h"

namespace orion {

    template<typename T>
    class Matrix<4, 4, T> : public MatrixBase<4, 4, T> {
    public:
        Matrix() = default;
        explicit Matrix(T value);
        explicit Matrix(std::array<T, 16> array);
    };

    template<typename T>
    using Matrix4 = Matrix<4, 4, T>;

    using Matrix4i = Matrix<4, 4, i32>;
    using Matrix4u = Matrix<4, 4, u32>;
    using Matrix4f = Matrix<4, 4, f32>;
    using Matrix4d = Matrix<4, 4, f64>;

    template<typename T>
    Matrix<4, 4, T>::Matrix(T value) : MatrixBase<4, 4, T>(value) {}

    template<typename T>
    Matrix<4, 4, T>::Matrix(std::array<T, 16> array) : MatrixBase<4, 4, T>(array) {}

} // orion

#endif //ORION_MATRIX4_H
