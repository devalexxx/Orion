//
// Created by Alex on 14/12/2023.
//

#ifndef ORION_DOT_H
#define ORION_DOT_H

namespace orion {

    template<size_t S, typename T>
    inline T dot(Ref<Vector<S, T>> lhs, Ref<Vector<S, T>> rhs) {
        T result {};
        for (int i = 0; i < S; ++i) {
            result += lhs[i] * rhs[i];
        }
        return result;
    }

    template<size_t R, size_t CR, size_t C, typename T>
    inline Matrix<R, C, T> dot(Ref<Matrix<R, CR, T>> lhs, Ref<Matrix<CR, C, T>> rhs) {
        Matrix<R, C, T> ret;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                T sum {0};
                for (int k = 0; k < CR; ++k) {
                    sum += lhs[i][k] * rhs[k][j];
                }
                ret[i][j] = sum;
            }
        }
        return ret;
    }

    template<size_t R, size_t C, typename T>
    inline Vector<C, T> dot(Ref<Vector<R, T>> lhs, Ref<Matrix<R, C, T>> rhs) {
        Vector<R, T> ret;
        for (int j = 0; j < C; ++j) {
            T sum {0};
            for (int k = 0; k < R; ++k) {
                sum += lhs[k] * rhs[k][j];
            }
            ret[j] = sum;
        }
        return ret;
    }

    template<size_t R, size_t C, typename T>
    inline Vector<R, T> dot(Ref<Matrix<R, C, T>> lhs, Ref<Vector<C, T>> rhs) {
        Vector<R, T> ret;
        for (int i = 0; i < R; ++i) {
            T sum {0};
            for (int k = 0; k < C; ++k) {
                sum += lhs[i][k] * rhs[k];
            }
            ret[i] = sum;
        }
        return ret;
    }

}

#endif //ORION_DOT_H
