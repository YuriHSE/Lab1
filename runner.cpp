#include "include/matrix.h"
#include <iostream>

int main() {
    using namespace linalg;

    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    std::cout << "Норма:" << m.norm() << std::endl;
    std::cout << "След: " << m.trace() << std::endl;
    std::cout << "Определитель: " << m.det() << std::endl;
    return 0;
}
