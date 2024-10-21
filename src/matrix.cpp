#include "../include/matrix.h"
#include "iostream"
#include "iomanip"

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

    // 2D
    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) {
        m_rows = list.size();
        m_columns = list.begin()->size();
        allocateMemory(m_rows, m_columns);

        size_t i = 0;
        for (const auto& row : list) {
            if (row.size() != m_columns) {
                throw std::invalid_argument("Строки должны иметь одинаковое количество столбцов");
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


    Matrix::~Matrix() noexcept {
        delete[] m_ptr;
    }


    // Оператор присваивания: копирование
    Matrix& Matrix::operator=(const Matrix& other) {
        if (this != &other) {
            delete[] m_ptr;
            allocateMemory(other.m_rows, other.m_columns);
            std::copy(other.m_ptr, other.m_ptr + m_rows * m_columns, m_ptr);
        }
        return *this;
    }

    // Оператор присваивания: перемещение
    Matrix& Matrix::operator=(Matrix&& other) noexcept {
        if (this != &other) {
            delete[] m_ptr;
            m_ptr = other.m_ptr;
            m_rows = other.m_rows;
            m_columns = other.m_columns;

            other.m_ptr = nullptr;  // Предотвращаем двойное удаление
            other.m_rows = 0;
            other.m_columns = 0;
        }
        return *this;
    }

    // Обращение по индексам: не константа
    double& Matrix::operator()(size_t row, size_t col) {
        if (row >= m_rows || col >= m_columns) {
            throw std::out_of_range("Выход за пределы");
        }
        return m_ptr[row * m_columns + col];
    }

    // Обращение по индексам: константа
    const double& Matrix::operator()(size_t row, size_t col) const {
        if (row >= m_rows || col >= m_columns) {
            throw std::out_of_range("Выход за пределы");
        }
        return m_ptr[row * m_columns + col];
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

    // Сложение матриц:
    Matrix Matrix::operator+(const Matrix& other) const {
        if (m_rows != other.m_rows || m_columns != other.m_columns) {
            throw std::runtime_error("Не подходят размеры матриц");
        }

        Matrix result(m_rows, m_columns);
        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            result.m_ptr[i] = m_ptr[i] + other.m_ptr[i];
        }
        return result;
    }

    Matrix& Matrix::operator+=(const Matrix& other) {
        if (m_rows != other.m_rows || m_columns != other.m_columns) {
            throw std::runtime_error("Не подходят размеры матриц");
        }

        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            m_ptr[i] += other.m_ptr[i];
        }
        return *this;
    }

    // Поэлементное вычитание
    Matrix Matrix::operator-(const Matrix& other) const {
        if (m_rows != other.m_rows || m_columns != other.m_columns) {
            throw std::runtime_error("Не подходят размеры матриц");
        }

        Matrix result(m_rows, m_columns);
        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            result.m_ptr[i] = m_ptr[i] - other.m_ptr[i];
        }
        return result;
    }

    Matrix& Matrix::operator-=(const Matrix& other) {
        if (m_rows != other.m_rows || m_columns != other.m_columns) {
            throw std::runtime_error("Не подходят размеры матриц");
        }

        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            m_ptr[i] -= other.m_ptr[i];
        }
        return *this;
    }

    // Умножение матрицы на число
    Matrix Matrix::operator*(double number) const {
        Matrix result(m_rows, m_columns);
        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            result.m_ptr[i] = m_ptr[i] * number;
        }
        return result;
    }

    Matrix& Matrix::operator*=(double number) {
        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            m_ptr[i] *= number;
        }
        return *this;
    }

    // Умножение матриц
    Matrix Matrix::operator*(const Matrix& other) const {
        if (m_columns != other.m_rows) {
            throw std::runtime_error("Не подходят размеры матриц");
        }

        Matrix result(m_rows, other.m_columns);
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < other.m_columns; ++j) {
                result.m_ptr[i * other.m_columns + j] = 0;
                for (size_t k = 0; k < m_columns; ++k) {
                    result.m_ptr[i * other.m_columns + j] += m_ptr[i * m_columns + k] * other.m_ptr[k * other.m_columns + j];
                }
            }
        }
        return result;
    }

    Matrix& Matrix::operator*=(const Matrix& other) {
        if (m_columns != other.m_rows) {
            throw std::runtime_error("Не подходят размеры матриц");
        }

        *this = *this * other;
        return *this;
    }

    // Операторы сравнения
    bool Matrix::operator==(const Matrix& other) const noexcept {
        if (m_rows != other.m_rows || m_columns != other.m_columns) {
            return false;
        }
        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            if (m_ptr[i] != other.m_ptr[i]) {
                return false;
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& other) const noexcept {
        return !(*this == other);
    }

    // Оператор вывода
    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        const int width = 3;  // Ширина для каждого элемента

        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.columns(); ++j) {
                os << std::setw(width) << matrix(i, j) << " ";  // Выравнивание и пробел
            }
            os << std::endl;  // Перевод строки после каждой строки матрицы
        }
        return os;
    }
}
