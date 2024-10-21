#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>

namespace linalg {

    class Matrix {
    private:
        double* m_ptr;    // Pointer to hold matrix data
        size_t m_rows;    // Number of rows
        size_t m_columns; // Number of columns

        // Helper function to allocate memory
        void allocateMemory(size_t rows, size_t cols);

    public:
        Matrix();

        Matrix(size_t rows, size_t cols);

        Matrix(size_t rows);

        Matrix(const Matrix& other);

        Matrix(Matrix&& other) noexcept;

        Matrix(std::initializer_list<std::initializer_list<double>> list);
        Matrix(std::initializer_list<double> list);

        ~Matrix();

        size_t rows() const;

        size_t columns() const;

        bool empty() const;

        void reshape(size_t new_rows, size_t new_cols);

        void print() const;
    };

}

#endif
