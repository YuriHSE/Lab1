#include "include/matrix.h"
#include <iostream>

int main() {
    using namespace linalg;

    try {
        Matrix m1 = {{1, 2, 3}, {4, 5, 6}};
        Matrix m2 = {{7, 8}, {9, 10}, {11, 12}};

        std::cout << "Матрица m1:\n" << m1;
        std::cout << "Матрица m2:\n" << m2;

        Matrix m3 = m1.multiply(m2);
        std::cout << "m1 * m2 = \n" << m3;

        // Ошибочное сложение (размеры не совпадают)
        Matrix m4 = m1.add(m2);  // Это вызовет исключение
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
