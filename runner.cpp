#include "include/matrix.h"
#include "iostream"

int main() {
    using namespace linalg;

    // Инициализация матрицы
    Matrix m1 = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
    Matrix m2 = { {7.0, 8.0, 9.0}, {10.0, 11.0, 12.0} };

    m1.print();
    std::cout << std::endl;
    m2.print();
    std::cout << std::endl;

    // Копирующее присваивание
    m1 = m2;
    m1.print();
    std::cout << std::endl;

    // Перемещающее присваивание
    m1 = Matrix{ 1, 2, 3, 4, 5, 6 };
    m1.print();
    std::cout << std::endl;

    // Индексирование
    double val = m1(0, 2);  // 3.0
    std::cout << val << std::endl;
    m1(0, 2) = 7.0;  // Теперь 1-ая строка, 3-ий элемент стал равен 7
    m1.print();
    std::cout << std::endl;

    const Matrix c_m = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
    c_m.print();
    std::cout << std::endl;
    double const_val = c_m(0, 2);  // 3.0
    // c_m(0, 2) = 7.0;  // Ошибка, нельзя менять константную матрицу
    std::cout << const_val;

    return 0;
}
