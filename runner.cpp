#include "include/matrix.h"
#include <iostream>

int main() {
    using namespace linalg;

    Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
    Matrix m2 = {{7, 8, 9}, {10, 11, 12}, {1, 2}};

    // Операция сложения
    Matrix m3 = m1 + m2;
    std::cout << "m1 + m2:\n" << m3;


    return 0;
}
