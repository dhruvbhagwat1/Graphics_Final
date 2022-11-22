#pragma once

template<typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns)
{
    if (rows == 0 || columns == 0) {
        throw std::invalid_argument("Matrix(uInt, uInt): matrix can't have 0 rows or colmns");
    }
    this->m_rows = rows;
    this->m_columns = columns;
    this->m_data = new T[this->m_rows * this->m_columns];
    for (unsigned int i = 0; i < this->m_rows * this->m_columns; i++) {
        this->m_data[i] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns, T data[], unsigned int data_length)
{
    if (rows == 0 || columns == 0) {
        throw std::invalid_argument("Matrix(uInt, uInt, T[], uInt): matrix can't have 0 rows or colmns");
    }
    if (data_length == 0 || rows * columns != data_length) {
        throw std::invalid_argument("Matrix(uInt, uInt, T[], uInt): invalid matrix provided");
    }
    this->m_rows = rows;
    this->m_columns = columns;

    this->m_data = new T[rows * columns];
    for (unsigned int i = 0; i < data_length; i++) {
        this->m_data[i] = data[i];
    }
    //std::copy(std::begin(data), std::end(data), std::begin(this->m_data));
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &source_matrix)
    : Matrix<T>(source_matrix.rows(), source_matrix.columns(), source_matrix.data(), source_matrix.rows() * source_matrix.columns())
{
}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] this->m_data;
}


template<typename T>
unsigned int Matrix<T>::rows() const
{
    return(this->m_rows);
}

template<typename T>
unsigned int Matrix<T>::columns() const
{
    return (this->m_columns);
}


template<typename T>
T* Matrix<T>::data() const
{
    return(this->m_data);
}

template<typename T>
T* Matrix<T>::data()
{
    return(this->m_data);
}


template<typename T>
T& Matrix<T>::operator() (unsigned int row, unsigned int column)
{
    if (row == 0 || column == 0 || this->m_rows < row || this->m_columns < column) {
        throw std::invalid_argument("matrix(uint, uint): matrix numbering starts at 1");
    }
    return(this->m_data[(row - 1) * this->m_columns + (column - 1)]);
}

template<typename T>
T Matrix<T>::operator() (unsigned int row, unsigned int column) const
{
    return(this(row, column));
}


template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T> source_matrix)
{
    this->m_rows = source_matrix.rows();
    this->m_columns = source_matrix.columns();

    delete[] this->m_data;
    this->m_data = new T[this->m_rows * this->m_columns];

    T* source_matrix_data = source_matrix.data();

    for (unsigned int i = 0; i < this->m_rows * this->m_columns; i++) {
        this->m_data[i] = source_matrix_data[i];
    }

    return(*this);
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> &source_matrix)
{
    /*
    this->m_rows = source_matrix.rows();
    this->m_columns = source_matrix.columns();

    delete[] this->m_data;
    this->m_data = new T[this->m_rows * this->m_columns];

    T* source_matrix_data = source_matrix.data();

    for (unsigned int i = 0; i < this->m_rows * this->m_columns; i++) {
        this->m_data[i] = source_matrix_data[i];
    }
    */
    return(this = source_matrix);
}

template<typename T>
Matrix<T> Matrix<T>::operator+ (Matrix<T> &added_matrix)
{
    if (this->m_rows != added_matrix.rows() || this->m_columns != added_matrix.columns()) {
        throw std::invalid_argument("matrix + matrix: only matrices of equal row and column count can be added together");
    }

    T* added_matrix_data = added_matrix.data();

    Matrix<T> return_matrix(this->m_rows, this->m_columns);
    T* return_matrix_data = return_matrix.data();

    for (unsigned int i = 0; i < this->m_rows * this->m_columns; i++) {
        return_matrix_data[i] = this->m_data[i] + added_matrix_data[i];
    }
    return(return_matrix);
}

template<typename T>
Matrix<T> Matrix<T>::operator- (Matrix<T> &subtracted_matrix)
{
    if (this->m_rows != subtracted_matrix.rows() || this->m_columns != subtracted_matrix.columns()) {
        throw std::invalid_argument("matrix - matrix: only matrices of equal row and column count can be subtracted from one another");
    }

    T* subtracted_matrix_data = subtracted_matrix.data();

    Matrix<T> return_matrix(this->m_rows, this->m_columns);
    T* return_matrix_data = return_matrix.data();

    for (unsigned int i = 0; i < this->m_rows * this->m_columns; i++) {
        return_matrix_data[i] = this->m_data[i] - subtracted_matrix_data[i];
    }
    return(return_matrix);
}

template<typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T> multiplied_matrix)
{
    if (this->m_columns != multiplied_matrix.rows()) {
        throw std::invalid_argument("matrix * matrix: you did a nono");
    }

    T* multiplied_matrix_data = multiplied_matrix.data();

    Matrix<T> return_matrix(this->m_rows, multiplied_matrix.columns());
    T* return_matrix_data = return_matrix.data();

    for (unsigned int i = 0; i < return_matrix.rows(); i++) {
        for (unsigned int j = 0; j < return_matrix.columns(); j++) {
            T entry_value = 0;
            for (unsigned int k = 0; k < this->m_columns; k++) {
                entry_value += this->m_data[i * this->m_columns + k] * multiplied_matrix_data[k * multiplied_matrix.columns() + j];
            }
            return_matrix_data[i * return_matrix.columns() + j] = entry_value;
        }
    }
    return(return_matrix);
}
/*
template<typename T>
Matrix<T> Matrix<T>::operator* (Matrix<T> &multiplied_matrix)
{
    if (this->m_columns != multiplied_matrix.rows()) {
        throw std::invalid_argument("matrix * matrix: you did a nono");
    }

    T* multiplied_matrix_data = multiplied_matrix.data();

    Matrix<T> return_matrix(this->m_rows, multiplied_matrix.columns());
    T* return_matrix_data = return_matrix.data();

    for (unsigned int i = 0; i < return_matrix.rows(); i++) {
        for (unsigned int j = 0; j < return_matrix.columns(); j++) {
            T entry_value = 0;
            for (unsigned int k = 0; k < this->m_columns; k++) {
                entry_value += this->m_data[i * this->m_columns + k] * multiplied_matrix_data[k * multiplied_matrix.columns() + j];
            }
            return_matrix_data[i * return_matrix.columns() + j] = entry_value;
        }
    }
    return(this);
}
*/
template<typename T>
Matrix<T> Matrix<T>::operator* (T scalar)
{
    Matrix<T> return_matrix(this->m_rows, this->m_columns);
    T* return_matrix_data = return_matrix.data();

    for (unsigned int i = 0; i < this->m_rows * this->m_columns; i++) {
        return_matrix_data[i] = this->m_data[i] * scalar;
    }
    return(return_matrix);
}


template<typename T>
std::string Matrix<T>::toString() const
{
    std::string return_string = "Rows: " + std::to_string(this->m_rows) + ", Columns: " + std::to_string(this->m_columns) + "\n";
    for (unsigned int i = 0; i < this->m_rows; i++) {
        for (unsigned int j = 0; j < this->m_columns; j++) {
            if (j == this->m_columns - 1) {
                return_string += std::to_string(this->m_data[i * this->m_columns + j]) + "\n";
            } else {
                return_string += std::to_string(this->m_data[i * this->m_columns + j]) + "\t";
            }
        }
    }
    return(return_string);
}