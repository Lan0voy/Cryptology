// matrix.cpp
#include <stdexcept>
#include <cryptolibrium/math/matrix.hpp>

namespace cryptolibrium::math {

    bool isSquare(const Matrix& matrix) {
        if (matrix.empty()) {
            return false;
        }

        const std::size_t rowsSize = matrix.size();
        
        for (const auto& row : matrix) {
            if (row.size() != rowsSize) {
                return false;
            }
        }

        return true;            
    }
}