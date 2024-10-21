#include "../include/matrix.h"
#include "iostream"
#include "iomanip"
#include "cmath"

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

    double Matrix::norm() const {
        double sum = 0;
        for (size_t i = 0; i < m_rows * m_columns; ++i) {
            sum += m_ptr[i] * m_ptr[i];
        }
        return std::sqrt(sum);
    }

    double Matrix::trace() const {
        if (m_rows != m_columns) {
            throw std::runtime_error("Матрица должна быть квадратной");
        }

        double trace = 0;
        for (size_t i = 0; i < m_rows; ++i) {
            trace += (*this)(i, i);
        }
        return trace;
    }

    double Matrix::det() const {
        if (m_rows != m_columns) {
            throw std::runtime_error("Матрица должна быть квадратной");
        }

        if (m_rows == 1) return m_ptr[0];
        if (m_rows == 2) {
            return (*this)(0,0) * (*this)(1,1) - (*this)(0,1) * (*this)(1,0);
        }

        double determinant = 0.0;
        for (size_t j = 0; j < m_columns; ++j) {
            determinant += (j % 2 == 0 ? 1 : -1) * (*this)(0, j) * dopMatrix(0, j).det();
        }
        return determinant;
    }

    Matrix Matrix::dopMatrix(size_t row, size_t col) const {
        Matrix sub(m_rows - 1, m_columns - 1);
        size_t subi = 0;
        for (size_t i = 0; i < m_rows; ++i) {
            if (i == row) continue;
            size_t subj = 0;
            for (size_t j = 0; j < m_columns; ++j) {
                if (j == col) continue;
                sub(subi, subj) = (*this)(i, j);
                ++subj;
            }
            ++subi;
        }
        return sub;
    }

    int Matrix::rank() {
        Matrix temp = *this;
        size_t rank = 0;

        for (size_t row = 0; row < m_rows; ++row) {
            if (temp(row, row) != 0) {
                ++rank;
                for (size_t i = row + 1; i < m_rows; ++i) {
                    double factor = temp(i, row) / temp(row, row);
                    for (size_t j = row; j < m_columns; ++j) {
                        temp(i, j) -= factor * temp(row, j);
                    }
                }
            }
        }

        return rank;
    }

    Matrix Matrix::concatenate(const Matrix& left, const Matrix& right) {
        if (left.rows() != right.rows()) {
            throw std::runtime_error("Количество строк должно совпадать");
        }

        Matrix result(left.rows(), left.columns() + right.columns());

        // Заполнение левой части
        for (size_t i = 0; i < left.rows(); ++i) {
            for (size_t j = 0; j < left.columns(); ++j) {
                result(i, j) = left(i, j);
            }
        }

        // Заполнение правой части
        for (size_t i = 0; i < right.rows(); ++i) {
            for (size_t j = 0; j < right.columns(); ++j) {
                result(i, j + left.columns()) = right(i, j);
            }
        }

        return result;
    }

    Matrix Matrix::transpose(const Matrix& matr) {
        Matrix result(matr.columns(), matr.rows());
        for (size_t i = 0; i < matr.rows(); ++i) {
            for (size_t j = 0; j < matr.columns(); ++j) {
                result(j, i) = matr(i, j);
            }
        }
        return result;
    }

    Matrix Matrix::identity(size_t size) {
        Matrix identity(size, size);
        for (size_t i = 0; i < size; ++i) {
            identity(i, i) = 1.0;  // Установка диагональных элементов в 1
        }
        return identity;
    }

    void Matrix::gaussJordan(Matrix& identity) noexcept {
        size_t n = rows();
        size_t m = columns();

        // Проверка на совместимость
        if (n != identity.rows() || n != identity.columns()) {
            throw std::runtime_error("Неправильные размеры матрицы");
        }

        for (size_t i = 0; i < n; ++i) {
            // Нормализация строки
            double pivot = (*this)(i, i);
            if (pivot == 0) {
                throw std::runtime_error("Матрица сингулярна");
            }

            for (size_t j = 0; j < m; ++j) {
                (*this)(i, j) /= pivot;
                identity(i, j) /= pivot;  // Применение к единичной матрице
            }

            // Обнуление остальных элементов в столбце
            for (size_t k = 0; k < n; ++k) {
                if (k != i) {
                    double factor = (*this)(k, i);
                    for (size_t j = 0; j < m; ++j) {
                        (*this)(k, j) -= factor * (*this)(i, j);
                        identity(k, j) -= factor * identity(i, j);
                    }
                }
            }
        }
    }

    Matrix Matrix::invert(const Matrix& matr) {
        if (matr.rows() != matr.columns()) {
            throw std::runtime_error("Матрица должна быть квадратной");
        }

        // Создаём расширенную матрицу (матрица | единичная матрица)
        Matrix result = matr;  // Копируем исходную матрицу
        Matrix identity = Matrix::identity(matr.rows());  // Единичная матрица

        // Применяем метод Гаусса для приведения матрицы к единичной
        // и в процессе преобразуем единичную матрицу в обратную
        result.gaussJordan(identity);

        return identity;
    }

    Matrix Matrix::power(const Matrix& matr, int exponent) {
        if (matr.rows() != matr.columns()) {
            throw std::runtime_error("Matrix must be square to raise to a power.");
        }

        Matrix result = Matrix::identity(matr.rows());  // Начинаем с единичной матрицы
        Matrix base = matr;

        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = result * base;  // Умножаем на базовую матрицу
            }
            base = base * base;  // Квадрат матрицы
            exponent /= 2;
        }

        return result;
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
