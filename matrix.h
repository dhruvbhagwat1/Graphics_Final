#pragma once

#include <string>
#include <stdexcept>

template <typename T>
class Matrix
{
    private:
        unsigned int m_rows, m_columns;
        T* m_data;


    public:
        Matrix(unsigned int rows, unsigned int columns);
        Matrix(unsigned int rows, unsigned int columns, T data_[], unsigned int data_length);
        Matrix(const Matrix<T> &matrix);
        ~Matrix();

        unsigned int rows() const;
        unsigned int columns() const;

        T* data() const;
        T* data();

        T& operator() (unsigned int row, unsigned int column);
        T  operator() (unsigned int row, unsigned int column) const;

        Matrix<T>& operator= (Matrix<T> &matrix);
        Matrix<T>& operator= (const Matrix<T> matrix);
        Matrix<T> operator+ (Matrix<T> &matrix);
        Matrix<T> operator- (Matrix<T> &matrix);
        Matrix<T> operator* (const Matrix<T> matrix);
        //Matrix<T> operator* (Matrix<T> &matrix);
        Matrix<T> operator* (T scalar);

        std::string toString() const;
};

#include "matrix.tpp"