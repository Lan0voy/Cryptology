// matrix.hpp

#pragma once

#include <vector>
#include <concepts>
#include <utility>
/*
namespace cryptolibrium::math {
    template<typename T>
    concept MatrixElement = requires(T a, T b) {
        {a + b};
        {a - b};
        {a * b};
    };

    template<MatrixElement T>
    using Matrix = std::vector<std::vector<T>>;

    template<MatrixElement T>
    bool isSquare(const Matrix<T>& matrix);

    template<MatrixElement T>
    int determinant(const Matrix<T>& matrix);

    template<MatrixElement T>
    Matrix<T> multiply(const Matrix<T>& lhs, const Matrix<T>& rhs);

    template<MatrixElement T>
    Matrix<T> multiply(const Matrix<T>& matrix, int scalar);

    template<MatrixElement T>
    Matrix<T> multiply(const Matrix<T>& matrix, int scalar, int mod);

    template<MatrixElement T>
    Matrix<T> transpose(const Matrix<T>& matrix);

    template<MatrixElement T>
    Matrix<T> adjugate(const Matrix<T>& matrix);

    template<MatrixElement T>
    Matrix<T> inverse(const Matrix<T>& matrix);

    template<MatrixElement T>
    Matrix<T> inverse(const Matrix<T>& matrix, int mod);

    template<MatrixElement T>
    Matrix<T> applyModulo(const Matrix<T>& matrix, int mod);
}
    */
namespace cryptolibrium::math {
    template<typename T>
    concept MatrixElement = requires(T a, T b) {
        {a + b} -> std::same_as<T>;
        {a - b} -> std::same_as<T>;
        {a * b} -> std::same_as<T>;
        {a == b} -> std::same_as<bool>;
    };

    template<MatrixElement T>
    class Matrix {
        public:
            explicit Matrix(const std::vector<std::vector<T>>& data) : data_(std::move(data)) {};

            std::size_t rows() const noexcept { return data_.size(); };

            std::size_t cols() const noexcept { return data_.empty() ? 0 : data_[0].size(); };

            T* operator()(std::size_t row, std::size_t col) { return &data_[row][col]; };

            const T* operator()(std::size_t row, std::size_t col) const { return &data_[row][col]; };

            bool empty() const noexcept { return data_.empty(); };
            
            bool isSquare() const;
            
            Matrix transpose() const;

            Matrix inverse() const;

            Matrix inverse(T mod) const;

            Matrix adjugate() const;

            T determinant() const;

            Matrix operator*(const Matrix& rhs) const;

            Matrix operator*(T scalar) const;

            Matrix applyModulo(T mod) const;


        private:
            std::vector<std::vector<T>> data_;
    };
}

#include "matrix.tpp"