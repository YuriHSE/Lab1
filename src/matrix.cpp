#include "../include/matrix.h"
#include <iostream>
#include <stdexcept>

namespace linalg {

void Matrix::allocateMemory(size_t rows, size_t cols) {
    m_rows = rows;
    m_columns = cols;
    m_ptr = new double[rows * cols]{0};
}

// Дефольтный конструктор
Matrix::Matrix() : m_ptr(nullptr), m_rows(0), m_columns(0) {}

// Конструктор с 1 параметром
Matrix::Matrix(size_t rows) {
    allocateMemory(rows, 1);
}

// Конструктор с 2 параметрами
Matrix::Matrix(size_t rows, size_t cols) {
    allocateMemory(rows, cols);
}

// Копирование конструктора
Matrix::Matrix(const Matrix& other) {
    allocateMemory(other.m_rows, other.m_columns);
    std::copy(other.m_ptr, other.m_ptr + m_rows * m_columns, m_ptr);
}

Matrix::Matrix(Matrix&& other) noexcept
    : m_ptr(other.m_ptr), m_rows(other.m_rows), m_columns(other.m_columns) {
    other.m_ptr = nullptr;
    other.m_rows = 0;
    other.m_columns = 0;
}

    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) {
    // Определяем количество строк
    m_rows = list.size();

    // Определяем количество столбцов, исходя из первой строки
    m_columns = list.begin()->size();  // Каждая строка одинаковой длины

    allocateMemory(m_rows, m_columns);

    size_t i = 0;
    for (const auto& row : list) {
        // Проверяем, что все строки имеют одинаковое количество элементов
        if (row.size() != m_columns) {
            throw std::invalid_argument("All rows must have the same number of columns.");
        }
        std::copy(row.begin(), row.end(), m_ptr + i * m_columns);
        ++i;
    }
}


// 1D
Matrix::Matrix(std::initializer_list<double> list) {
    m_rows = 1;
    m_columns = list.size();

    allocateMemory(m_rows, m_columns);
    std::copy(list.begin(), list.end(), m_ptr);  // Copy elements into matrix
}


Matrix::~Matrix() {
    delete[] m_ptr;
}

size_t Matrix::rows() const {
    return m_rows;
}

size_t Matrix::columns() const {
    return m_columns;
}

bool Matrix::empty() const {
    return m_rows == 0 || m_columns == 0;
}


void Matrix::reshape(size_t new_rows, size_t new_cols) {
    if (new_rows * new_cols != m_rows * m_columns) {
        throw std::invalid_argument("Различие в размерах");
    }
    m_rows = new_rows;
    m_columns = new_cols;
}

void Matrix::print() const {
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            std::cout << m_ptr[i * m_columns + j] << " ";
        }
        std::cout << std::endl;
    }
}

}
