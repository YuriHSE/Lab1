#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
#include <stdexcept>

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

        // Оператор вывода
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

        // Matrix add(const Matrix& other) const;      // Операция сложения
        // Matrix multiply(const Matrix& other) const; // Операция умножения

        // Операторы сложения
        Matrix operator+(const Matrix& other) const;
        Matrix& operator+=(const Matrix& other);

        // Операторы вычитания
        Matrix operator-(const Matrix& other) const;
        Matrix& operator-=(const Matrix& other);

        // Операторы умножения
        Matrix operator*(double scalar) const;
        Matrix& operator*=(double scalar);
        Matrix operator*(const Matrix& other) const;
        Matrix& operator*=(const Matrix& other);

        // Операторы сравнения
        bool operator==(const Matrix& other) const noexcept;
        bool operator!=(const Matrix& other) const noexcept;
    };

}

#endif
