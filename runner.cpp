#include "include/matrix.h"
#include <iostream>

int main() {
    using namespace linalg;

    Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    Matrix m2 = {{7, 8, 9}, {10, 11, 12}};
    Matrix m4 = {{1, 2}, {3, 4}, {5, 6}};

    // Операция сложения
    Matrix m3 = m1 + m2;
    std::cout << "m1 + m2:\n" << m3;

    // Умножение на скаляр
    m3 *= 2.0;
    std::cout << "m3 * 2:\n" << m3 << std::endl;

    // Умножение матриц
    std::cout << "m1 * m4:\n" << m1 * m4 << std::endl;

    return 0;
}
