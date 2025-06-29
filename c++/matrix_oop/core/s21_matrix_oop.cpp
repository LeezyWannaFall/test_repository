#include "s21_matrix_oop.h"

/* S21Matrix class implementation BY COPILOT I KNOW HOW THIS WORK BUT DK WHY HE WRITE LIKE THIS,
I WILL REWRITE IT BY MYSELF
ADD TO UNDERSTAND C++ SYNTAX AND
ITS FUNNY TO PRESS TAB AND CODE APPEAR ON UR SCREEN LIKE DARK MF MAGIC */

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be positive integers.");
    }
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_]();
    }
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

