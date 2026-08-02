// matrix.tpp
#pragma once

#include "matrix.hpp"

namespace cryptolibrium::math {

    template<MatrixElement T>
    bool Matrix<T>::isSquare() const {
        if (empty()) { return false; };

        return rows() == cols();
    }
}