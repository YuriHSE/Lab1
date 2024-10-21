#include "include/matrix.h"
#include <iostream>

int main() {
    using namespace linalg;

    Matrix m1 = {{1, 2}, {3, 4}};
    Matrix m2 = {{5, 6}, {7, 8}};
    Matrix m3 = Matrix::invert(m2);
    std::cout << m3;
    return 0;
}
