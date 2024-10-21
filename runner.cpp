#include "include/matrix.h"
#include "iostream"

int main() {
    using namespace linalg;

    Matrix m0;

    Matrix m1(4);     // 4 rows, 1 column
    Matrix m2(4, 6);  // 4 rows, 6 columns

    Matrix m3(m1);

    Matrix m4(std::move(m2));

    Matrix m5 = {{1, 2, 3}, {4, 5, 6}};
    Matrix m6 = {{1, 2, 3, 4, 5, 6}};
    Matrix m7 = {1, 2, 3, 4, 5, 6};
    Matrix m8 = {{1}, {2}, {3}, {4}, {5}, {6}};

    std::cout << std:: endl;
    m5.print();
    std::cout << std::endl;
    m7.print();
    std::cout << std::endl;
    m8.print();

    return 0;
}
