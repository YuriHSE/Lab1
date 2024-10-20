#include "include/matrix.h"
#include <iostream>

class Runner {
public:
    static void run() {

        linalg::Matrix mat(2, 3);

        mat.at(0, 0) = 1.0;
        mat.at(0, 1) = 2.0;
        mat.at(0, 2) = 3.0;
        mat.at(1, 0) = 4.0;
        mat.at(1, 1) = 5.0;
        mat.at(1, 2) = 6.0;

        std::cout << "Matrix before reshape:" << std::endl;
        printMatrix(mat);

        mat.reshape(3, 2);

        std::cout << "Matrix after reshape:" << std::endl;
        printMatrix(mat);
    }

private:
    static void printMatrix(const linalg::Matrix& mat) {
        for (size_t i = 0; i < mat.rows(); ++i) {
            for (size_t j = 0; j < mat.columns(); ++j) {
                std::cout << mat.at(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Runner::run();
    return 0;
}
