#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

namespace linalg {

    class Matrix {
    public:

        Matrix(size_t rows, size_t cols);

        ~Matrix();

        size_t rows() const;
        size_t columns() const;
        bool empty() const;

        void reshape(size_t new_rows, size_t new_cols);

        double& at(size_t row, size_t col);
        const double& at(size_t row, size_t col) const;

    private:
        size_t m_rows;
        size_t m_columns;
        double* m_ptr;
    };

}

#endif
