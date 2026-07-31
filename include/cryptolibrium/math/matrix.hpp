// matrix.hpp

#pragma once

#include <vector>

namespace cryptolibrium::math {
    using Matrix = std::vector<std::vector<int>>;

    bool isSquare(const Matrix& matrix);

    int determinant(const Matrix& matrix);

    Matrix multiply(const Matrix& lhs, const Matrix& rhs);

    Matrix multiply(const Matrix& matrix, int scalar);

    Matrix multiply(const Matrix& matrix, int scalar, int mod);

    Matrix transpose(const Matrix& matrix);

    Matrix adjugate(const Matrix& matrix);

    Matrix inverse(const Matrix& matrix);

    Matrix inverse(const Matrix& matrix, int mod);

    Matrix applyModulo(const Matrix& matrix, int mod);
}