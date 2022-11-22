#pragma once

#include "matrix.h"

template <typename T>
Matrix<T> getIdentityMatrix(int size) {
    Matrix<T> return_matrix(size, size);
    T* return_matrix_data = return_matrix.data();
    for (int i = 0; i < size; i++) {
        return_matrix_data[i * size + i] = 1;
    }
    return(return_matrix);
}