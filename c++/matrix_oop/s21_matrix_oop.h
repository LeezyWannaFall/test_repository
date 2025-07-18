#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

// Includes
#include <cmath>
#include <iostream>
#include <stdexcept>

// Constants
#define EPS 1e-6

// Class Declaration
class S21Matrix {
 private:
  int rows_;
  int cols_;
  double** matrix_;

  // Private methods
  double DeterminantGauss() const;
  void GetMinorMatrix(int row, int col, S21Matrix& minor) const;
  void CheckSquareMatrix(const S21Matrix& other) const;
  void CheckSquareMatrixWithSelf() const;

 public:
  // Constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  // Destructor
  ~S21Matrix();

  // Methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(double number);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  // Accessor
  int getCols() const;
  int getRows() const;

  // Mutator
  S21Matrix& setSize(int newCols, int newRows);

  // Overloaded operators
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double number) const;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(double number);
  double& operator()(int rows_, int cols_);
};

#endif  // S21_MATRIX_OOP_H