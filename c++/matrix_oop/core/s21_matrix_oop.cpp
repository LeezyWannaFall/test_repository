#include "s21_matrix_oop.h"

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

void S21Matrix::SumMatrix(const S21Matrix& other) {
  CheckSquareMatrix(other);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  CheckSquareMatrix(other);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double number) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= number;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix temp_result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp_result.matrix_[i][j] = 0;
      for (int k = 0; k < other.cols_; k++) {
        temp_result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = temp_result;
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
  if (rows_ != cols_) {
    throw std::out_of_range("Determinant is only defined for square matrices.");
  }
  return DeterminantGauss();
}

double S21Matrix::DeterminantGauss() const {
  S21Matrix copy(*this);
  int n = copy.rows_;
  double det = 1.0;
  
  for (int i = 0; i < n; i++) {
    int max_row = i;

    for (int j = i + 1; j < n; j++) {
      if (fabs(copy.matrix_[j][i]) > fabs(copy.matrix_[max_row][i]))
        max_row = j;
    }

    if (max_row != i) {
      for (int k = 0; k < n; k++) {
        double tmp = copy.matrix_[i][k];
        copy.matrix_[i][k] = copy.matrix_[max_row][k];
        copy.matrix_[max_row][k] = tmp;
      }
      det *= -1.0;
    }

    if (fabs(copy.matrix_[i][i]) < EPS) {
      return 0;
    }

    for (int j = i + 1; j < n; j++) {
      double factor = copy.matrix_[j][i] / copy.matrix_[i][i];
      for (int k = i; k < n; k++)
        copy.matrix_[j][k] -= factor * copy.matrix_[i][k];
    }
    det *= copy.matrix_[i][i];
  }
  return det;
}

void S21Matrix::CheckSquareMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Matrices must be square for this operation.");
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(*this);

  if (rows_ == 1 || cols_ == 1) {
    result.matrix_[0][0] = 1;
    return result;
  }

  S21Matrix CopyMinor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      GetMinorMatrix(i, j, CopyMinor);
      double DetMinor = CopyMinor.Determinant();
      result.matrix_[i][j] = DetMinor * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }
}

void S21Matrix::GetMinorMatrix(int row, int col, S21Matrix& minor) const {
  int minor_row = 0, minor_col = 0;

  for (int i = 0; i < rows_; i++) {
    if (i != row) {
      for (int j = 0; j < cols_; j++) {
        if (j != col) {
          minor.matrix_[minor_row][minor_col++] = matrix_[i][j];
        }
      }
      minor_row++;
      minor_col = 0;
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::out_of_range("Inverse is only defined for square matrices.");
  }

  double det = Determinant();
  if (fabs(det) < EPS) {
    throw std::runtime_error("Matrix is singular and cannot be inverted.");
  }

  S21Matrix complements = CalcComplements();
  S21Matrix inverse(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      inverse.matrix_[i][j] = complements.matrix_[i][j] / det;
    }
  }
  return inverse;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
      }
      delete[] matrix_;

      rows_ = other.rows_;
      cols_ = other.cols_;
      matrix_ = new double*[rows_];
      for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
          matrix_[i][j] = other.matrix_[i][j];
        }
      }
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  CheckSquareMatrix(other);
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  CheckSquareMatrix(other);
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  CheckSquareMatrix(other);
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  CheckSquareMatrix(other);
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  CheckSquareMatrix(other);
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  CheckSquareMatrix(other);
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  CheckSquareMatrix(other);
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range.");
  }
  return matrix_[row][col];
}