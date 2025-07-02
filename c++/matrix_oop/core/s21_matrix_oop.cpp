#include "s21_matrix_oop.h"

/* S21Matrix class implementation BY COPILOT I KNOW HOW THIS WORK BUT DK WHY HE
WRITE LIKE THIS, I WILL REWRITE IT BY MYSELF ADD TO UNDERSTAND C++ SYNTAX AND
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

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
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

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Matrices must have the same dimensions for addition.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Matrices must have the same dimensions for subtraction.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double number) const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= number;
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  S21Matrix temp(rows_, cols_);
  if (rows_ != cols_) {
    throw std::out_of_range("Determinant is only defined for square matrices.");
  }

  int n = rows_;
  double det = 1.0;
  S21Matrix temp = (*this);

  for (int i = 0; i < n; i++) {
    int max_row = i;

    for (int j = i + 1; j < n; j++) {
      if (fabs(temp.matrix_[j][i]) > fabs(temp.matrix_[max_row][i]))
        max_row = j;
    }

    if (max_row != i) {
      for (int k = 0; k < n; k++) {
        double tmp = temp.matrix_[i][k];
        temp.matrix_[i][k] = temp.matrix_[max_row][k];
        temp.matrix_[max_row][k] = tmp;
      }
      det *= -1.0;
    }

    if (fabs(temp.matrix_[i][i]) < EPS) {
      return 0;
    }

    for (int j = i + 1; j < n; j++) {
      double factor = temp.matrix_[j][i] / temp.matrix_[i][i];
      for (int k = i; k < n; k++)
        temp.matrix_[j][k] -= factor * temp.matrix_[i][k];
    }
    det *= temp.matrix_[i][i];
  }
  return det;
}