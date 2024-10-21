#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>

namespace linalg {

    class Matrix {
    private:
        double* m_ptr;    // Указатель на матрицу
        size_t m_rows;
        size_t m_columns;

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

        // Операторы присваивания
        Matrix& operator=(const Matrix& other);  // копирование
        Matrix& operator=(Matrix&& other) noexcept;  // перемещающее присваивание

        // Индексы
        double& operator()(size_t row, size_t col);  // Неконстантная версия
        const double& operator()(size_t row, size_t col) const;  // Константная

        size_t rows() const;
        size_t columns() const;
        bool empty() const;
        void reshape(size_t new_rows, size_t new_cols);
        void print() const;
    };

}

#endif
