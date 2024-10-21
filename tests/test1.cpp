#include <iostream>
#include <cassert>
#include "../include/matrix.h"
#include <cmath>

void testConstructors() {
    linalg::Matrix m1; // Пустая матрица
    assert(m1.rows() == 0);
    assert(m1.columns() == 0);

    linalg::Matrix m2(2); // 2x2 матрица
    assert(m2.rows() == 2);
    assert(m2.columns() == 1);

    linalg::Matrix m3(3, 3); // 3x3 матрица
    assert(m3.rows() == 3);
    assert(m3.columns() == 3);

    linalg::Matrix m4{{1.0, 2.0}, {3.0, 4.0}}; // Инициализация
    assert(m4(0, 0) == 1.0);
    assert(m4(0, 1) == 2.0);
    assert(m4(1, 0) == 3.0);
    assert(m4(1, 1) == 4.0);
}

void testOperations() {
    linalg::Matrix m1{{1.0, 2.0}, {3.0, 4.0}};
    linalg::Matrix m2{{5.0, 6.0}, {7.0, 8.0}};

    auto m3 = m1 + m2; // Сложение
    assert(m3(0, 0) == 6.0);
    assert(m3(0, 1) == 8.0);
    assert(m3(1, 0) == 10.0);
    assert(m3(1, 1) == 12.0);

    auto m4 = m1 - m2; // Вычитание
    assert(m4(0, 0) == -4.0);
    assert(m4(0, 1) == -4.0);
    assert(m4(1, 0) == -4.0);
    assert(m4(1, 1) == -4.0);

    auto m5 = m1 * 2.0; // Умножение на скаляр
    assert(m5(0, 0) == 2.0);
    assert(m5(0, 1) == 4.0);
    assert(m5(1, 0) == 6.0);
    assert(m5(1, 1) == 8.0);

    auto m6 = m1 * m2; // Умножение матриц
    assert(m6(0, 0) == 19.0);
    assert(m6(0, 1) == 22.0);
    assert(m6(1, 0) == 43.0);
    assert(m6(1, 1) == 50.0);
}

void testProperties() {
    linalg::Matrix m{{1.0, 2.0}, {3.0, 4.0}};

    assert(m.trace() == 5.0); // След
    assert(m.norm() == std::sqrt(30.0)); // Норма
}

void testDeterminant() {
    linalg::Matrix m1{{1, 2}, {3, 4}};
    assert(m1.det() == -2); // Определитель 2x2 матрицы

    linalg::Matrix m2{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    assert(m2.det() == 1); // Определитель единичной матрицы
}

void testRank() {
    linalg::Matrix m1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    assert(m1.rank() == 2); // Ранг матрицы

    linalg::Matrix m2{{1, 2}, {3, 4}};
    assert(m2.rank() == 2); // Ранг 2x2 матрицы

    linalg::Matrix m3{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    assert(m3.rank() == 1); // Ранг должен быть 1
}

void testConcatenate() {
    linalg::Matrix m1{{1, 2}, {3, 4}};
    linalg::Matrix m2{{5, 6}, {7, 8}};
    linalg::Matrix result = linalg::Matrix::concatenate(m1, m2);

    assert(result.rows() == 2);
    assert(result.columns() == 4);
    assert(result(0, 0) == 1);
    assert(result(0, 2) == 5);
}

void testTranspose() {
    linalg::Matrix m{{1, 2, 3}, {4, 5, 6}};
    linalg::Matrix result = linalg::Matrix::transpose(m);

    assert(result.rows() == 3);
    assert(result.columns() == 2);
    assert(result(0, 0) == 1);
    assert(result(1, 0) == 2);
}

void testInvert() {
    linalg::Matrix m{{4, 7}, {2, 6}};
    linalg::Matrix result = linalg::Matrix::invert(m);

    // Проверка результатов с учетом возможной погрешности
    assert(std::abs(result(0, 0) - 0.6) < 1e-9);
    assert(std::abs(result(0, 1) + 0.7) < 1e-9);
    assert(std::abs(result(1, 0) + 0.2) < 1e-9);
    assert(std::abs(result(1, 1) - 0.4) < 1e-9);
}

void testPower() {
    linalg::Matrix m{{1, 2}, {3, 4}};
    linalg::Matrix result = linalg::Matrix::power(m, 2);

    assert(result(0, 0) == 7);
    assert(result(0, 1) == 10);
    assert(result(1, 0) == 15);
    assert(result(1, 1) == 22);
}

void runTests() {
    testConstructors();
    testOperations();
    testProperties();
    testDeterminant();
    testRank();
    testConcatenate();
    testTranspose();
    testInvert();
    testPower();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
