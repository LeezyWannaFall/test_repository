#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

/*--------------------------------------------------------------------------------
                                TESTS FOR CONSTRUCTORS
----------------------------------------------------------------------------------*/

// Test cases for S21Matrix class
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
}

// Test cases for S21Matrix with specific size
TEST(S21MatrixTest, ConstructorWithSize) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);
}

// Test cases for invalid size
TEST(S21MatrixTest, ConstructorWithNegativeSize) {
  EXPECT_THROW(S21Matrix(-1, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix(2, -1), std::invalid_argument);
  EXPECT_THROW(S21Matrix(0, 0), std::invalid_argument);
}

// Test cases for zero size
TEST(S21MatrixTest, ConstructorWithZeroSize) {
  EXPECT_THROW(S21Matrix(0, 3), std::invalid_argument);
  EXPECT_THROW(S21Matrix(3, 0), std::invalid_argument);
  EXPECT_THROW(S21Matrix(0, 0), std::invalid_argument);
}

// Test cases for copy constructor
TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix copy(matrix);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 2);
  EXPECT_DOUBLE_EQ(copy(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(copy(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(copy(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(copy(1, 1), 4.0);
}

// Test cases for move constructor
TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 5.0;
  matrix(0, 1) = 6.0;

  S21Matrix copy(std::move(matrix));
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 2);
  EXPECT_DOUBLE_EQ(copy(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(copy(0, 1), 6.0);
}

// Test cases for destructor
TEST(S21MatrixTest, Destructor) {
  S21Matrix* matrix = new S21Matrix(2, 2);
  EXPECT_NO_THROW(delete matrix);
}

TEST(S21MatrixTest, DestructorWithEmptyMatrix) {
  S21Matrix* matrix = new S21Matrix();
  EXPECT_NO_THROW(delete matrix);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR EQMATRIX
----------------------------------------------------------------------------------*/

// Test 1: Check if two identical matrices are equal
TEST(S21MatrixTest, EqMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix copy(matrix);
  EXPECT_TRUE(matrix.EqMatrix(copy));

  copy(0, 0) = 5.0;
  EXPECT_FALSE(matrix.EqMatrix(copy));
}

// Test 2: Check if two matrices with different sizes are not equal
TEST(S21MatrixTest, EqMatrixDifferentSizes) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Test 3: Check if two natrices with zero values are equal
TEST(S21MatrixTest, EqMatrixWithZeroMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

// Test 4: Check if two matrices with negative values are equal
TEST(S21MatrixTest, EqMatrixWithNegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -1.0;
  matrix1(0, 1) = -2.0;
  matrix1(1, 0) = -3.0;
  matrix1(1, 1) = -4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = -1.0;
  matrix2(0, 1) = -2.0;
  matrix2(1, 0) = -3.0;
  matrix2(1, 1) = -4.0;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

// Test 5: Check if Matrix with itself is equal
TEST(S21MatrixTest, EqMatrixWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_TRUE(matrix.EqMatrix(matrix));
}

// Test 6: Check if two matrices with different values are not equal
TEST(S21MatrixTest, EqMatrixWithDifferentValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 8.0;
  matrix2(0, 1) = 7.0;
  matrix2(1, 0) = 6.0;
  matrix2(1, 1) = 5.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Test 7: Check if two matrices with floating point precision are equal
TEST(S21MatrixTest, EqMatrixWithEPSILON) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0000001;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

/*--------------------------------------------------------------------------------
                                TESTS FOR SUMMATRIX
----------------------------------------------------------------------------------*/

// Test 1: Sum two matrices of the same size
TEST(S21MatrixTest, SumMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  first.SumMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 5);
  EXPECT_DOUBLE_EQ(first(0, 1), 5);
  EXPECT_DOUBLE_EQ(first(1, 0), 5);
  EXPECT_DOUBLE_EQ(first(1, 1), 5);
}

// Test 2: Sum matrices of different sizes (should throw an exception)
TEST(S21MatrixTest, SumMatrixDifferentSizes) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(3, 3);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  EXPECT_THROW(first.SumMatrix(second), std::out_of_range);
}

// Test 3: Sum a matrix with a zero matrix
TEST(S21MatrixTest, SumMatrixWithZero) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  first.SumMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 1);
  EXPECT_DOUBLE_EQ(first(0, 1), 2);
  EXPECT_DOUBLE_EQ(first(1, 0), 3);
  EXPECT_DOUBLE_EQ(first(1, 1), 4);
}

// Test 4: Sum negative values
TEST(S21MatrixTest, SumMatrixWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = -1.0;
  first(0, 1) = -2.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  first.SumMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), -5);
  EXPECT_DOUBLE_EQ(first(0, 1), -5);
  EXPECT_DOUBLE_EQ(first(1, 0), -5);
  EXPECT_DOUBLE_EQ(first(1, 1), -5);
}

// Test 5: Sum a positive matrix with a negative matrix
TEST(S21MatrixTest, SumPositiveWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  first.SumMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), -3);
  EXPECT_DOUBLE_EQ(first(0, 1), -1);
  EXPECT_DOUBLE_EQ(first(1, 0), 1);
  EXPECT_DOUBLE_EQ(first(1, 1), 3);
}

// Test 6: Sum with an empty matrix (should throw an exception)
TEST(S21MatrixTest, SumWithEmptyMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second;  // Empty matrix

  EXPECT_THROW(first.SumMatrix(second), std::out_of_range);
}

// Test 7: Sum with self
TEST(S21MatrixTest, SumWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.SumMatrix(matrix);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 2);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8);
}

// Test 8: Sum with identity matrix
TEST(S21MatrixTest, SumWithIdentityMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix identity(2, 2);
  identity(0, 0) = 1.0;
  identity(0, 1) = 0.0;
  identity(1, 0) = 0.0;
  identity(1, 1) = 1.0;

  first.SumMatrix(identity);
  EXPECT_DOUBLE_EQ(first(0, 0), 2);
  EXPECT_DOUBLE_EQ(first(0, 1), 2);
  EXPECT_DOUBLE_EQ(first(1, 0), 3);
  EXPECT_DOUBLE_EQ(first(1, 1), 5);
}

// Test 9: Sum Matrices with 1x1 size
TEST(S21MatrixTest, SumMatrix1x1) {
  S21Matrix first(1, 1);
  S21Matrix second(1, 1);

  first(0, 0) = 1.0;
  second(0, 0) = 2.0;

  first.SumMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 3.0);
}

// Test 10: Sum matrices with 3x3 size
TEST(S21MatrixTest, SumMatrix3x3) {
  S21Matrix first(3, 3);
  S21Matrix second(3, 3);

  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(0, 2) = 3.0;
  first(1, 0) = 4.0;
  first(1, 1) = 5.0;
  first(1, 2) = 6.0;
  first(2, 0) = 7.0;
  first(2, 1) = 8.0;
  first(2, 2) = 9.0;

  second(0, 0) = 1.0;
  second(0, 1) = 1.0;
  second(0, 2) = 1.0;
  second(1, 0) = 1.0;
  second(1, 1) = 1.0;
  second(1, 2) = 1.0;
  second(2, 0) = 1.0;
  second(2, 1) = 1.0;
  second(2, 2) = 1.0;

  first.SumMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(first(0, 2), 4.0);
  EXPECT_DOUBLE_EQ(first(1, 0), 5.0);
  EXPECT_DOUBLE_EQ(first(1, 1), 6.0);
  EXPECT_DOUBLE_EQ(first(1, 2), 7.0);
  EXPECT_DOUBLE_EQ(first(2, 0), 8.0);
  EXPECT_DOUBLE_EQ(first(2, 1), 9.0);
  EXPECT_DOUBLE_EQ(first(2, 2), 10.0);
}

// Test 11: Sum matrices with zero values
TEST(S21MatrixTest, SumMatrixWithZeroValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 0.0;
  first(0, 1) = 0.0;
  first(1, 0) = 0.0;
  first(1, 1) = 0.0;

  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  first.SumMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(first(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(first(1, 1), 0.0);
}

// Test 12: Sum matrices with floating point
TEST(S21MatrixTest, SumMatrixWithFloatingPoint) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 1.5;
  first(0, 1) = 2.2;
  first(1, 0) = 3.3;
  first(1, 1) = 4.7;

  second(0, 0) = 0.5;
  second(0, 1) = 1.2;
  second(1, 0) = 2.8;
  second(1, 1) = 3.9;

  first.SumMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 3.4);
  EXPECT_DOUBLE_EQ(first(1, 0), 6.1);
  EXPECT_DOUBLE_EQ(first(1, 1), 8.6);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR SUBMATRIX
----------------------------------------------------------------------------------*/

// Test 1: Subtract two matrices of the same size
TEST(S21MatrixTest, SubMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second(2, 2);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 1);
  EXPECT_DOUBLE_EQ(first(0, 1), 3);
  EXPECT_DOUBLE_EQ(first(1, 0), 5);
  EXPECT_DOUBLE_EQ(first(1, 1), 7);
}

// Test 2: Subtract matrices of different sizes (should throw an exception)
TEST(S21MatrixTest, SubMatrixDifferentSizes) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second(3, 3);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  EXPECT_THROW(first.SubMatrix(second), std::out_of_range);
}

// Test 3: Subtract a matrix with a zero matrix
TEST(S21MatrixTest, SubMatrixWithZero) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second(2, 2);
  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 5);
  EXPECT_DOUBLE_EQ(first(0, 1), 6);
  EXPECT_DOUBLE_EQ(first(1, 0), 7);
  EXPECT_DOUBLE_EQ(first(1, 1), 8);
}

// Test 4: Subtract negative values
TEST(S21MatrixTest, SubMatrixWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = -1.0;
  first(0, 1) = -2.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 3);
  EXPECT_DOUBLE_EQ(first(0, 1), 1);
  EXPECT_DOUBLE_EQ(first(1, 0), -1);
  EXPECT_DOUBLE_EQ(first(1, 1), -3);
}

// Test 5: Subtract a positive matrix with a negative matrix
TEST(S21MatrixTest, SubPositiveWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 5);
  EXPECT_DOUBLE_EQ(first(0, 1), 5);
  EXPECT_DOUBLE_EQ(first(1, 0), 5);
  EXPECT_DOUBLE_EQ(first(1, 1), 5);
}

// Test 6: Subtract with an empty matrix (should throw an exception)
TEST(S21MatrixTest, SubWithEmptyMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second;  // Empty matrix

  EXPECT_THROW(first.SubMatrix(second), std::out_of_range);
}

// Test 7: Subtract with self
TEST(S21MatrixTest, SubWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 5.0;
  matrix(0, 1) = 6.0;
  matrix(1, 0) = 7.0;
  matrix(1, 1) = 8.0;

  matrix.SubMatrix(matrix);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 0);
}

// Test 8: Sub matrices with 1x1 size
TEST(S21MatrixTest, SubMatrixWith1x1Size) {
  S21Matrix first(1, 1);
  S21Matrix second(1, 1);

  first(0, 0) = 5.0;
  second(0, 0) = 2.0;

  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 3.0);
}

// Test 9: Subtract matrices with 3x3 size
TEST(S21MatrixTest, SubMatrixWith3x3Size) {
  S21Matrix first(3, 3);
  S21Matrix second(3, 3);

  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(0, 2) = 7.0;
  first(1, 0) = 8.0;
  first(1, 1) = 9.0;
  first(1, 2) = 10.0;
  first(2, 0) = 11.0;
  first(2, 1) = 12.0;
  first(2, 2) = 13.0;

  second(0, 0) = 1.0;
  second(0, 1) = 2.0;
  second(0, 2) = 3.0;
  second(1, 0) = 4.0;
  second(1, 1) = 5.0;
  second(1, 2) = 6.0;
  second(2, 0) = -1.0;
  second(2, 1) = -2.0;
  second(2, 2) = -3.0;

  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(first(0, 2), 4.0);
  EXPECT_DOUBLE_EQ(first(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(first(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(first(1, 2), 4.0);
  EXPECT_DOUBLE_EQ(first(2, 0), 12.0);
  EXPECT_DOUBLE_EQ(first(2, 1), 14.0);
  EXPECT_DOUBLE_EQ(first(2, 2), 16.0);
}

// Test 10: Subtract matrices with zero values
TEST(S21MatrixTest, SubMatrixWithZeroValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 0.0;
  first(0, 1) = 0.0;
  first(1, 0) = 0.0;
  first(1, 1) = 0.0;

  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  first.SubMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(first(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(first(1, 1), 0.0);
}

// Test 11: Subtract matrices with floating point values
TEST(S21MatrixTest, SubMatrixWithFloatingPoint) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 5.5;
  first(0, 1) = 6.6;
  first(1, 0) = 7.7;
  first(1, 1) = 8.8;

  second(0, 0) = 1.1;
  second(0, 1) = 2.2;
  second(1, 0) = 3.3;
  second(1, 1) = 4.4;

  first.SubMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), 4.4);
  EXPECT_DOUBLE_EQ(first(0, 1), 4.4);
  EXPECT_DOUBLE_EQ(first(1, 0), 4.4);
  EXPECT_DOUBLE_EQ(first(1, 1), 4.4);
}

// Test 12: Subtract matrices with negative floating point values
TEST(S21MatrixTest, SubMatrixWithNegativeFloatingValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = -1.5;
  first(0, 1) = -2.5;
  first(1, 0) = -3.5;
  first(1, 1) = -4.5;

  second(0, 0) = -0.5;
  second(0, 1) = -1.5;
  second(1, 0) = -2.5;
  second(1, 1) = -3.5;

  first.SubMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(first(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(first(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(first(1, 1), -1.0);
}
/*--------------------------------------------------------------------------------
                                TESTS FOR MULMATRIX
----------------------------------------------------------------------------------*/

// Test 1: Multiply two matrices 2x3 and 3x2
TEST(S21MatrixTest, Mulmatrix) {
  S21Matrix first(2, 3);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(0, 2) = 3.0;
  first(1, 0) = 4.0;
  first(1, 1) = 5.0;
  first(1, 2) = 6.0;

  S21Matrix second(3, 2);
  second(0, 0) = 7.0;
  second(0, 1) = 8.0;
  second(1, 0) = 9.0;
  second(1, 1) = 10.0;
  second(2, 0) = 11.0;
  second(2, 1) = 12.0;

  first.MulMatrix(second);

  EXPECT_DOUBLE_EQ(first.getRows(), 2);
  EXPECT_DOUBLE_EQ(first.getCols(), 2);
  EXPECT_DOUBLE_EQ(first(0, 0), 58);
  EXPECT_DOUBLE_EQ(first(0, 1), 64);
  EXPECT_DOUBLE_EQ(first(1, 0), 139);
  EXPECT_DOUBLE_EQ(first(1, 1), 154);
}

// Test 2: Mult matrices with zero matrix
TEST(S21MatrixTest, MulMatrixWithZero) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  first.MulMatrix(second);

  EXPECT_DOUBLE_EQ(first(0, 0), 0);
  EXPECT_DOUBLE_EQ(first(0, 1), 0);
  EXPECT_DOUBLE_EQ(first(1, 0), 0);
  EXPECT_DOUBLE_EQ(first(1, 1), 0);
}

// Test 3: Multiply matrices of incompatible sizes (should throw an exception)
TEST(S21MatrixTest, MulMatrixIncompatibleSizes) {
  S21Matrix first(2, 3);
  S21Matrix second(2, 2);

  EXPECT_THROW(first.MulMatrix(second), std::out_of_range);
}

// Test 4: Multiply matrices with negative values
TEST(S21MatrixTest, MulMatrixWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = -1.0;
  first(0, 1) = -2.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -5.0;
  second(0, 1) = -6.0;
  second(1, 0) = -7.0;
  second(1, 1) = -8.0;

  first.MulMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 19);
  EXPECT_DOUBLE_EQ(first(0, 1), 22);
  EXPECT_DOUBLE_EQ(first(1, 0), 43);
  EXPECT_DOUBLE_EQ(first(1, 1), 50);
}

// Test 5: Multiply matrices with 1x1 size
TEST(S21MatrixTest, MulMatrixWith1x1Size) {
  S21Matrix first(1, 1);
  S21Matrix second(1, 1);

  first(0, 0) = 2.0;
  second(0, 0) = 3.0;

  first.MulMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 6.0);
}

// Test 7: Multiply matrices with zero values
TEST(S21MatrixTest, MulMatrixWithZeroValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 0.0;
  first(0, 1) = 0.0;
  first(1, 0) = 0.0;
  first(1, 1) = 0.0;

  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  first.MulMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(first(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(first(1, 1), 0.0);
}

// Test 8: Multiply matrices with floating point values
TEST(S21MatrixTest, MulMatrixWithFloatingPoint) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 1.5;
  first(0, 1) = 2.5;
  first(1, 0) = 3.5;
  first(1, 1) = 4.5;

  second(0, 0) = 0.5;
  second(0, 1) = 1.5;
  second(1, 0) = 2.5;
  second(1, 1) = 3.5;

  first.MulMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 7.0);
  EXPECT_DOUBLE_EQ(first(0, 1), 11.0);
  EXPECT_DOUBLE_EQ(first(1, 0), 13.0);
  EXPECT_DOUBLE_EQ(first(1, 1), 21.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR MULNUMBER
----------------------------------------------------------------------------------*/

// Test 1: Multiply matrix by a number
TEST(S21MatrixTest, MulNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 2.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

// Test 2: Multiply matrix with zero
TEST(S21MatrixTest, MulNumberWithZero) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 0.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 0.0);
}

// Test 3: Multiply matrix with negative number
TEST(S21MatrixTest, MulNumberWithNegative) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = -2.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), -6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), -8.0);
}

// Test 4: Multiply matrix with 1
TEST(S21MatrixTest, MulNumberWithOne) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 1.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
}

// Test 5: Multiply matrix with a large number
TEST(S21MatrixTest, MulNumberWithLargeValue) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 1000000.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1000000.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2000000.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3000000.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4000000.0);
}

// Test 6: Multiply matrix 1x1 by a number
TEST(S21MatrixTest, MulNumberWith1x1Size) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  double number = 3.0;
  matrix.MulNumber(number);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 15.0);
}

// Test 7: Multiply matrix with floating point number
TEST(S21MatrixTest, MulNumberWithFloatingPoint) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.5;
  matrix(0, 1) = 2.5;
  matrix(1, 0) = 3.5;
  matrix(1, 1) = 4.5;

  double number = 2.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 9.0);
}

// Test 8: Multiply matrix with negative values
TEST(S21MatrixTest, MulNumberWithNegativeValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1.5;
  matrix(0, 1) = -2.5;
  matrix(1, 0) = -3.5;
  matrix(1, 1) = -4.5;

  double number = 2.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), -5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), -7.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), -9.0);
}

// Test 9: Multiply matrix with zero values
TEST(S21MatrixTest, MulNumberWithZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;

  double number = 5.0;

  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 0.0);
}

// Test 10: Multiply matrix 3x3
TEST(S21MatrixTest, MulNumberWith3x3Size) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double number = -1.0;
  matrix.MulNumber(number);

  EXPECT_DOUBLE_EQ(matrix(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), -5.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), -6.0);
  EXPECT_DOUBLE_EQ(matrix(2, 0), -7.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), -8.0);
  EXPECT_DOUBLE_EQ(matrix(2, 2), -9.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR TRANSPOSE
----------------------------------------------------------------------------------*/

// Test 1: Transpose a 2x3 matrix
TEST(S21MatrixTest, Transpose) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 3);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 2);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposed(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposed(2, 1), 6.0);
}

// Test 2: Transpose a square matrix
TEST(S21MatrixTest, TransposeSquareMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 2);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 2);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 4.0);
}

// Test 3: Transpose a 1x1 matrix
TEST(S21MatrixTest, Transpose1x1Matrix) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 1);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 1);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 5.0);
}

// Test 4: Transpose a matrix with zero values
TEST(S21MatrixTest, TransposeWithZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 2);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 2);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 0.0);
}

// Test 5: Transpose a matrix with negative values
TEST(S21MatrixTest, TransposeWithNegativeValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1.0;
  matrix(0, 1) = -2.0;
  matrix(1, 0) = -3.0;
  matrix(1, 1) = -4.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 2);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 2);
  EXPECT_DOUBLE_EQ(transposed(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), -3.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), -2.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), -4.0);
}

// Test 6: Transpose a matrix with floating point values
TEST(S21MatrixTest, TransposeWithFloatingPoint) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.5;
  matrix(0, 1) = 2.5;
  matrix(1, 0) = 3.5;
  matrix(1, 1) = 4.5;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 2);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 2);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 3.5);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 2.5);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 4.5);
}

// Test 7: Transpose a matrix with 3x3 size
TEST(S21MatrixTest, TransposeWith3x3Size) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed.getRows(), 3);
  EXPECT_DOUBLE_EQ(transposed.getCols(), 3);
  EXPECT_DOUBLE_EQ(transposed(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposed(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposed(0, 2), 7.0);
  EXPECT_DOUBLE_EQ(transposed(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposed(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposed(1, 2), 8.0);
  EXPECT_DOUBLE_EQ(transposed(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposed(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(transposed(2, 2), 9.0);
}

// Test 8: Transpose a matrix with self
TEST(S21MatrixTest, TransposeWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_DOUBLE_EQ(transposed(0, 0), matrix(0, 0));
  EXPECT_DOUBLE_EQ(transposed(0, 1), matrix(1, 0));
  EXPECT_DOUBLE_EQ(transposed(1, 0), matrix(0, 1));
  EXPECT_DOUBLE_EQ(transposed(1, 1), matrix(1, 1));
}

/*--------------------------------------------------------------------------------
                                TESTS FOR DETERMINANT
----------------------------------------------------------------------------------*/
// Test 1: Calculate determinant of a 2x2 matrix
TEST(S21MatrixTest, Determinant2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, -2.0);
}

// Test 2: Calculate determinant of a 3x3 matrix
TEST(S21MatrixTest, Determinant3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, 0.0);  // Determinant of this matrix is zero
}

// Test 3: Calculate determinant of a 1x1 matrix
TEST(S21MatrixTest, Determinant1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det,
                   5.0);  // Determinant of a 1x1 matrix is the value itself
}

// Test 4: Calculate determinant of a matrix with zero values
TEST(S21MatrixTest, DeterminantWithZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, 0.0);  // Determinant of a zero matrix is zero
}

// Test 5: Calculate determinant of a matrix with negative values
TEST(S21MatrixTest, DeterminantWithNegativeValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1.0;
  matrix(0, 1) = -2.0;
  matrix(1, 0) = -3.0;
  matrix(1, 1) = -4.0;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, -2.0);
}

// Test 6: Calculate determinant of a matrix with floating point values
TEST(S21MatrixTest, DeterminantWithFloatingPoint) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.5;
  matrix(0, 1) = 2.5;
  matrix(1, 0) = 3.5;
  matrix(1, 1) = 4.5;

  double det = matrix.Determinant();

  EXPECT_DOUBLE_EQ(det, -2.0);  // Determinant of this matrix should be -1.0
}

// Test 7: Calculate determinant of a matrix with size 2x3
TEST(S21MatrixTest, Determinant2x3) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  EXPECT_THROW(
      matrix.Determinant(),
      std::out_of_range);  // Determinant is not defined for non-square matrices
}

/*--------------------------------------------------------------------------------
                                TESTS FOR CALCCOMPLEMENTS
----------------------------------------------------------------------------------*/

// Test 1: Calculate complements of a 2x2 matrix
TEST(S21MatrixTest, CalculateComplements2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_EQ(complements.getRows(), 2);
  EXPECT_EQ(complements.getCols(), 2);
  EXPECT_DOUBLE_EQ(complements(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(complements(0, 1), -3.0);
  EXPECT_DOUBLE_EQ(complements(1, 0), -2.0);
  EXPECT_DOUBLE_EQ(complements(1, 1), 1.0);
}

// Test 2: Calculate complements of a 3x3 matrix
TEST(S21MatrixTest, CalculateComplements3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_EQ(complements.getRows(), 3);
  EXPECT_EQ(complements.getCols(), 3);
  EXPECT_DOUBLE_EQ(complements(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(complements(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(complements(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(complements(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(complements(1, 1), -12.0);
  EXPECT_DOUBLE_EQ(complements(1, 2), 6.0);
  EXPECT_DOUBLE_EQ(complements(2, 0), -3.0);
  EXPECT_DOUBLE_EQ(complements(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(complements(2, 2), -3.0);
}

// Test 3: Calculate complements of a 1x1 matrix
TEST(S21MatrixTest, CalculateComplements1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_EQ(complements.getRows(), 1);
  EXPECT_EQ(complements.getCols(), 1);
  EXPECT_DOUBLE_EQ(complements(0, 0),
                   1.0);  // Complements of a 1x1 matrix is always 1
}

// Test 4: Calculate complements of a matrix with zero values
TEST(S21MatrixTest, CalculateComplementsWithZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_EQ(complements.getRows(), 2);
  EXPECT_EQ(complements.getCols(), 2);
  EXPECT_DOUBLE_EQ(complements(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(complements(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(complements(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(complements(1, 1), 0.0);
}

// Test 5: Calculate complements of a matrix with negative values
TEST(S21MatrixTest, CalculateComplementsWithNegativeValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1.0;
  matrix(0, 1) = -2.0;
  matrix(1, 0) = -3.0;
  matrix(1, 1) = -4.0;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_EQ(complements.getRows(), 2);
  EXPECT_EQ(complements.getCols(), 2);
  EXPECT_DOUBLE_EQ(complements(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(complements(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(complements(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(complements(1, 1), -1.0);
}

// Test 6: Calculate complements of a matrix with floating point values
TEST(S21MatrixTest, CalculateComplementsWithFloatingPoint) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.5;
  matrix(0, 1) = 2.5;
  matrix(1, 0) = 3.5;
  matrix(1, 1) = 4.5;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_EQ(complements.getRows(), 2);
  EXPECT_EQ(complements.getCols(), 2);
  EXPECT_DOUBLE_EQ(complements(0, 0), 4.5);
  EXPECT_DOUBLE_EQ(complements(0, 1), -3.5);
  EXPECT_DOUBLE_EQ(complements(1, 0), -2.5);
  EXPECT_DOUBLE_EQ(complements(1, 1), 1.5);
}

// Test 7: Calculate complements of a matrix with size 2x3
TEST(S21MatrixTest, CalculateComplements2x3) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  EXPECT_THROW(
      matrix.CalcComplements(),
      std::out_of_range);  // Complements is not defined for non-square matrices
}

/*--------------------------------------------------------------------------------
                                TESTS FOR INVERSEMATRIX
----------------------------------------------------------------------------------*/

// Test 1: Inverse of a 2x2 matrix
TEST(S21MatrixTest, Inverse2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_EQ(inverse.getRows(), 2);
  EXPECT_EQ(inverse.getCols(), 2);
  EXPECT_DOUBLE_EQ(inverse(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(inverse(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(inverse(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(inverse(1, 1), -0.5);
}

// Test 2: Inverse of a 3x3 matrix
TEST(S21MatrixTest, Inverse3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 6.0;
  matrix(2, 2) = 0.0;

  S21Matrix inverse = matrix.InverseMatrix();
  EXPECT_EQ(inverse.getRows(), 3);
  EXPECT_EQ(inverse.getCols(), 3);
  EXPECT_NEAR(inverse(0, 0), -24.0, EPS);
  EXPECT_NEAR(inverse(0, 1), 18.0, EPS);
  EXPECT_NEAR(inverse(0, 2), 5.0, EPS);
  EXPECT_NEAR(inverse(1, 0), 20.0, EPS);
  EXPECT_NEAR(inverse(1, 1), -15.0, EPS);
  EXPECT_NEAR(inverse(1, 2), -4.0, EPS);
  EXPECT_NEAR(inverse(2, 0), -5.0, EPS);
  EXPECT_NEAR(inverse(2, 1), 4.0, EPS);
  EXPECT_NEAR(inverse(2, 2), 1.0, EPS);
}

// Test 3: Inverse of a 1x1 matrix
TEST(S21MatrixTest, Inverse1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_EQ(inverse.getRows(), 1);
  EXPECT_EQ(inverse.getCols(), 1);
  EXPECT_DOUBLE_EQ(inverse(0, 0),
                   0.2);  // Inverse of a 1x1 matrix is the reciprocal
}

// Test 4: Inverse of a matrix with zero values
TEST(S21MatrixTest, InverseWithZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;

  EXPECT_THROW(matrix.InverseMatrix(),
               std::runtime_error);  // Inverse is not defined for zero matrix
}

// Test 5: Inverse of a matrix with negative values
TEST(S21MatrixTest, InverseWithNegativeValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1.0;
  matrix(0, 1) = -2.0;
  matrix(1, 0) = -3.0;
  matrix(1, 1) = -4.0;

  S21Matrix inverse = matrix.InverseMatrix();
  EXPECT_EQ(inverse.getRows(), 2);
  EXPECT_EQ(inverse.getCols(), 2);
  EXPECT_DOUBLE_EQ(inverse(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(inverse(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(inverse(1, 0), -1.5);
  EXPECT_DOUBLE_EQ(inverse(1, 1), 0.5);
}

// Test 6: Inverse of a matrix with floating point values
TEST(S21MatrixTest, InverseWithFloatingPoint) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.5;
  matrix(0, 1) = 2.5;
  matrix(1, 0) = 3.5;
  matrix(1, 1) = 4.5;

  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_EQ(inverse.getRows(), 2);
  EXPECT_EQ(inverse.getCols(), 2);
  EXPECT_DOUBLE_EQ(inverse(0, 0), -2.25);
  EXPECT_DOUBLE_EQ(inverse(0, 1), 1.25);
  EXPECT_DOUBLE_EQ(inverse(1, 0), 1.75);
  EXPECT_DOUBLE_EQ(inverse(1, 1), -0.75);
}

// Test 7: Inverse of a matrix with size 2x3
TEST(S21MatrixTest, Inverse2x3) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  EXPECT_THROW(
      matrix.InverseMatrix(),
      std::out_of_range);  // Inverse is not defined for non-square matrices
}

// Test 8: Inverse Matrix with zero determinant
TEST(S21MatrixTest, InverseWithZeroDeterminant) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 4.0;

  EXPECT_THROW(matrix.InverseMatrix(),
               std::runtime_error);  // Inverse is not defined for matrices with
                                     // zero determinant
}

// Test 9: Iverse matrox with some zero values
TEST(S21MatrixTest, InverseWithSomeZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 1.0;
  matrix(1, 1) = 0.0;

  S21Matrix inverse = matrix.InverseMatrix();
  EXPECT_EQ(inverse.getRows(), 2);
  EXPECT_EQ(inverse.getCols(), 2);
  EXPECT_DOUBLE_EQ(inverse(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(inverse(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(inverse(1, 0), 1.0);
  EXPECT_DOUBLE_EQ(inverse(1, 1), 0.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR OPERATOR+
----------------------------------------------------------------------------------*/

// Test 1: Sum two matrices of the same size
TEST(S21MatrixTest, OperatorPlusSameSize) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  S21Matrix result = first + second;
  EXPECT_DOUBLE_EQ(result(0, 0), 5);
  EXPECT_DOUBLE_EQ(result(0, 1), 5);
  EXPECT_DOUBLE_EQ(result(1, 0), 5);
  EXPECT_DOUBLE_EQ(result(1, 1), 5);
}

// Test 2: Sum matrices of different sizes (should throw an exception)
TEST(S21MatrixTest, OperPlusDifferentSizes) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(3, 3);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  EXPECT_THROW(S21Matrix result = first + second, std::out_of_range);
}

// Test 3: Sum a matrix with a zero matrix
TEST(S21MatrixTest, OperPlusWithZero) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  S21Matrix result = first + second;
  EXPECT_DOUBLE_EQ(result(0, 0), 1);
  EXPECT_DOUBLE_EQ(result(0, 1), 2);
  EXPECT_DOUBLE_EQ(result(1, 0), 3);
  EXPECT_DOUBLE_EQ(result(1, 1), 4);
}

// Test 4: Sum negative values
TEST(S21MatrixTest, OperPlusWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = -1.0;
  first(0, 1) = -2.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  S21Matrix result = first + second;
  EXPECT_DOUBLE_EQ(result(0, 0), -5);
  EXPECT_DOUBLE_EQ(result(0, 1), -5);
  EXPECT_DOUBLE_EQ(result(1, 0), -5);
  EXPECT_DOUBLE_EQ(result(1, 1), -5);
}

// Test 5: Sum a positive matrix with a negative matrix
TEST(S21MatrixTest, OperPlusPositiveWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  S21Matrix result = first + second;
  EXPECT_DOUBLE_EQ(result(0, 0), -3);
  EXPECT_DOUBLE_EQ(result(0, 1), -1);
  EXPECT_DOUBLE_EQ(result(1, 0), 1);
  EXPECT_DOUBLE_EQ(result(1, 1), 3);
}

// Test 6: Sum with an empty matrix (should throw an exception)
TEST(S21MatrixTest, OperPlusithEmptyMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second;  // Empty matrix
  EXPECT_THROW(S21Matrix result = first + second, std::out_of_range);
}

// Test 7: Sum with self
TEST(S21MatrixTest, OperPlusWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix + matrix;
  EXPECT_DOUBLE_EQ(result(0, 0), 2);
  EXPECT_DOUBLE_EQ(result(0, 1), 4);
  EXPECT_DOUBLE_EQ(result(1, 0), 6);
  EXPECT_DOUBLE_EQ(result(1, 1), 8);
}

// Test 8: Sum with identity matrix
TEST(S21MatrixTest, OperPlusWithIdentityMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix identity(2, 2);
  identity(0, 0) = 1.0;
  identity(0, 1) = 0.0;
  identity(1, 0) = 0.0;
  identity(1, 1) = 1.0;

  S21Matrix result = first + identity;
  EXPECT_DOUBLE_EQ(result(0, 0), 2);
  EXPECT_DOUBLE_EQ(result(0, 1), 2);
  EXPECT_DOUBLE_EQ(result(1, 0), 3);
  EXPECT_DOUBLE_EQ(result(1, 1), 5);
}

// Test 9: Sum Matrices with 1x1 size
TEST(S21MatrixTest, OperPlus1x1) {
  S21Matrix first(1, 1);
  S21Matrix second(1, 1);

  first(0, 0) = 1.0;
  second(0, 0) = 2.0;

  S21Matrix result = first + second;
  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
}

// Test 10: Sum matrices with 3x3 size
TEST(S21MatrixTest, OperPlus3x3) {
  S21Matrix first(3, 3);
  S21Matrix second(3, 3);

  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(0, 2) = 3.0;
  first(1, 0) = 4.0;
  first(1, 1) = 5.0;
  first(1, 2) = 6.0;
  first(2, 0) = 7.0;
  first(2, 1) = 8.0;
  first(2, 2) = 9.0;

  second(0, 0) = 1.0;
  second(0, 1) = 1.0;
  second(0, 2) = 1.0;
  second(1, 0) = 1.0;
  second(1, 1) = 1.0;
  second(1, 2) = 1.0;
  second(2, 0) = 1.0;
  second(2, 1) = 1.0;
  second(2, 2) = 1.0;

  S21Matrix result = first + second;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(result(0, 2), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 5.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 7.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 8.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 9.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 10.0);
}

// Test 11: Sum matrices with zero values
TEST(S21MatrixTest, OperPlusWithZeroValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 0.0;
  first(0, 1) = 0.0;
  first(1, 0) = 0.0;
  first(1, 1) = 0.0;

  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  S21Matrix result = first + second;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

// Test 12: Sum matrices with floating point
TEST(S21MatrixTest, OperPlusWithFloatingPoint) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 1.5;
  first(0, 1) = 2.2;
  first(1, 0) = 3.3;
  first(1, 1) = 4.7;

  second(0, 0) = 0.5;
  second(0, 1) = 1.2;
  second(1, 0) = 2.8;
  second(1, 1) = 3.9;

  S21Matrix result = first + second;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 3.4);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.1);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.6);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR OPERATOR-
----------------------------------------------------------------------------------*/

// Test 1: Subtract two matrices of the same size
TEST(S21MatrixTest, OperSub) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second(2, 2);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  S21Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 1);
  EXPECT_DOUBLE_EQ(result(0, 1), 3);
  EXPECT_DOUBLE_EQ(result(1, 0), 5);
  EXPECT_DOUBLE_EQ(result(1, 1), 7);
}

// Test 2: Subtract matrices of different sizes (should throw an exception)
TEST(S21MatrixTest, OperSubDifferentSizes) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second(3, 3);
  second(0, 0) = 4.0;
  second(0, 1) = 3.0;
  second(1, 0) = 2.0;
  second(1, 1) = 1.0;

  EXPECT_THROW(S21Matrix result = first - second, std::out_of_range);
}

// Test 3: Subtract a matrix with a zero matrix
TEST(S21MatrixTest, OperSubWithZero) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second(2, 2);
  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  S21Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 5);
  EXPECT_DOUBLE_EQ(result(0, 1), 6);
  EXPECT_DOUBLE_EQ(result(1, 0), 7);
  EXPECT_DOUBLE_EQ(result(1, 1), 8);
}

// Test 4: Subtract negative values
TEST(S21MatrixTest, OperSubWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = -1.0;
  first(0, 1) = -2.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  S21Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 3);
  EXPECT_DOUBLE_EQ(result(0, 1), 1);
  EXPECT_DOUBLE_EQ(result(1, 0), -1);
  EXPECT_DOUBLE_EQ(result(1, 1), -3);
}

// Test 5: Subtract a positive matrix with a negative matrix
TEST(S21MatrixTest, OperSubPositiveWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -4.0;
  second(0, 1) = -3.0;
  second(1, 0) = -2.0;
  second(1, 1) = -1.0;

  S21Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 5);
  EXPECT_DOUBLE_EQ(result(0, 1), 5);
  EXPECT_DOUBLE_EQ(result(1, 0), 5);
  EXPECT_DOUBLE_EQ(result(1, 1), 5);
}

// Test 6: Subtract with an empty matrix (should throw an exception)
TEST(S21MatrixTest, OperSubWithEmptyMatrix) {
  S21Matrix first(2, 2);
  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(1, 0) = 7.0;
  first(1, 1) = 8.0;

  S21Matrix second;  // Empty matrix

  EXPECT_THROW(S21Matrix result = first - second, std::out_of_range);
}

// Test 7: Subtract with self
TEST(S21MatrixTest, OperSubWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 5.0;
  matrix(0, 1) = 6.0;
  matrix(1, 0) = 7.0;
  matrix(1, 1) = 8.0;

  S21Matrix result = matrix - matrix;
  EXPECT_DOUBLE_EQ(result(0, 0), 0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0);
}

// Test 8: Sub matrices with 1x1 size
TEST(S21MatrixTest, OperSubWith1x1Size) {
  S21Matrix first(1, 1);
  S21Matrix second(1, 1);

  first(0, 0) = 5.0;
  second(0, 0) = 2.0;

  S21Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
}

// Test 9: Subtract matrices with 3x3 size
TEST(S21MatrixTest, OperSubWith3x3Size) {
  S21Matrix first(3, 3);
  S21Matrix second(3, 3);

  first(0, 0) = 5.0;
  first(0, 1) = 6.0;
  first(0, 2) = 7.0;
  first(1, 0) = 8.0;
  first(1, 1) = 9.0;
  first(1, 2) = 10.0;
  first(2, 0) = 11.0;
  first(2, 1) = 12.0;
  first(2, 2) = 13.0;

  second(0, 0) = 1.0;
  second(0, 1) = 2.0;
  second(0, 2) = 3.0;
  second(1, 0) = 4.0;
  second(1, 1) = 5.0;
  second(1, 2) = 6.0;
  second(2, 0) = -1.0;
  second(2, 1) = -2.0;
  second(2, 2) = -3.0;

  S21Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 2), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 4.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 12.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 14.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 16.0);
}

// Test 10: Subtract matrices with zero values
TEST(S21MatrixTest, OperSubWithZeroValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 0.0;
  first(0, 1) = 0.0;
  first(1, 0) = 0.0;
  first(1, 1) = 0.0;

  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  S21Matrix result = first - second;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

// Test 11: Subtract matrices with floating point values
TEST(S21MatrixTest, OperSubWithFloatingPoint) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 5.5;
  first(0, 1) = 6.6;
  first(1, 0) = 7.7;
  first(1, 1) = 8.8;

  second(0, 0) = 1.1;
  second(0, 1) = 2.2;
  second(1, 0) = 3.3;
  second(1, 1) = 4.4;

  S21Matrix result = first - second;

  EXPECT_DOUBLE_EQ(result(0, 0), 4.4);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.4);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.4);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.4);
}

// Test 12: Subtract matrices with negative floating point values
TEST(S21MatrixTest, OperSubWithNegativeFloatingValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = -1.5;
  first(0, 1) = -2.5;
  first(1, 0) = -3.5;
  first(1, 1) = -4.5;

  second(0, 0) = -0.5;
  second(0, 1) = -1.5;
  second(1, 0) = -2.5;
  second(1, 1) = -3.5;

  S21Matrix result = first - second;

  EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -1.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR OPERATOR=
----------------------------------------------------------------------------------*/

// Test 1: operator= for a matrix
TEST(S21MatrixTest, EqualOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2 = matrix1;  // Using operator=
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 4.0);
}

// Test 2: operator= for a matrix with different sizes
TEST(S21MatrixTest, EqualOperatorDifferentSizes) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(0, 2) = 7.0;
  matrix2(1, 0) = 8.0;
  matrix2(1, 1) = 9.0;
  matrix2(1, 2) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;
  matrix2(2, 2) = 13.0;
  matrix1 = matrix2;  // Using operator=
  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 3);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 2), 7.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 9.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(2, 0), 11.0);
  EXPECT_DOUBLE_EQ(matrix1(2, 1), 12.0);
  EXPECT_DOUBLE_EQ(matrix1(2, 2), 13.0);
}

// Test 3: operator= for an empty matrix
TEST(S21MatrixTest, EqualOperatorEmptyMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2;  // Empty matrix
  EXPECT_THROW(
      matrix2 = matrix1,
      std::out_of_range);  // Should throw an exception for empty matrix
}

// Test 4: operator= for a matrix with negative values
TEST(S21MatrixTest, EqualOperatorNegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -1.0;
  matrix1(0, 1) = -2.0;
  matrix1(1, 0) = -3.0;
  matrix1(1, 1) = -4.0;

  S21Matrix matrix2 = matrix1;  // Using operator=
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), -4.0);
}

// Test 5: operator= for a matrix with floating point values
TEST(S21MatrixTest, EqualOperatorFloatingPoint) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.5;
  matrix1(0, 1) = 2.5;
  matrix1(1, 0) = 3.5;
  matrix1(1, 1) = 4.5;

  S21Matrix matrix2 = matrix1;  // Using operator=
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.5);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), 3.5);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 4.5);
}

// Test 6: operator= for a matrix with zero values
TEST(S21MatrixTest, EqualOperatorZeroValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 0.0;
  matrix1(1, 0) = 0.0;
  matrix1(1, 1) = 0.0;

  S21Matrix matrix2 = matrix1;  // Using operator=
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 0.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR OPERATOR*
----------------------------------------------------------------------------------*/

// Test 1: Multiply two matrices 2x3 and 3x2
TEST(S21MatrixTest, opermulmatrix) {
  S21Matrix first(2, 3);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(0, 2) = 3.0;
  first(1, 0) = 4.0;
  first(1, 1) = 5.0;
  first(1, 2) = 6.0;

  S21Matrix second(3, 2);
  second(0, 0) = 7.0;
  second(0, 1) = 8.0;
  second(1, 0) = 9.0;
  second(1, 1) = 10.0;
  second(2, 0) = 11.0;
  second(2, 1) = 12.0;

  S21Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result.getRows(), 2);
  EXPECT_DOUBLE_EQ(result.getCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 58);
  EXPECT_DOUBLE_EQ(result(0, 1), 64);
  EXPECT_DOUBLE_EQ(result(1, 0), 139);
  EXPECT_DOUBLE_EQ(result(1, 1), 154);
}

// Test 2: Mult matrices with zero matrix
TEST(S21MatrixTest, OperMulMatrixWithZero) {
  S21Matrix first(2, 2);
  first(0, 0) = 1.0;
  first(0, 1) = 2.0;
  first(1, 0) = 3.0;
  first(1, 1) = 4.0;

  S21Matrix second(2, 2);
  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  S21Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result(0, 0), 0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0);
}

// Test 3: Multiply matrices of incompatible sizes (should throw an exception)
TEST(S21MatrixTest, OperMulMatrixIncompatibleSizes) {
  S21Matrix first(2, 3);
  S21Matrix second(2, 2);

  EXPECT_THROW(first * second, std::out_of_range);
}

// Test 4: Multiply matrices with negative values
TEST(S21MatrixTest, OperMulMatrixWithNegativeValues) {
  S21Matrix first(2, 2);
  first(0, 0) = -1.0;
  first(0, 1) = -2.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;

  S21Matrix second(2, 2);
  second(0, 0) = -5.0;
  second(0, 1) = -6.0;
  second(1, 0) = -7.0;
  second(1, 1) = -8.0;

  S21Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result(0, 0), 19);
  EXPECT_DOUBLE_EQ(result(0, 1), 22);
  EXPECT_DOUBLE_EQ(result(1, 0), 43);
  EXPECT_DOUBLE_EQ(result(1, 1), 50);
}

// Test 5: Multiply matrices with 1x1 size
TEST(S21MatrixTest, OperMulMatrixWith1x1Size) {
  S21Matrix first(1, 1);
  S21Matrix second(1, 1);

  first(0, 0) = 2.0;
  second(0, 0) = 3.0;

  S21Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
}

// Test 7: Multiply matrices with zero values
TEST(S21MatrixTest, OperMulMatrixWithZeroValues) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 0.0;
  first(0, 1) = 0.0;
  first(1, 0) = 0.0;
  first(1, 1) = 0.0;

  second(0, 0) = 0.0;
  second(0, 1) = 0.0;
  second(1, 0) = 0.0;
  second(1, 1) = 0.0;

  S21Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

// Test 8: Multiply matrices with floating point values
TEST(S21MatrixTest, OperMulMatrixWithFloatingPoint) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);

  first(0, 0) = 1.5;
  first(0, 1) = 2.5;
  first(1, 0) = 3.5;
  first(1, 1) = 4.5;

  second(0, 0) = 0.5;
  second(0, 1) = 1.5;
  second(1, 0) = 2.5;
  second(1, 1) = 3.5;

  S21Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result(0, 0), 7.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 11.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 13.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 21.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR OPERATOR*(NUMBER)
----------------------------------------------------------------------------------*/

// Test 1: Multiply matrix by a number
TEST(S21MatrixTest, OperMulNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 2.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

// Test 2: Multiply matrix with zero
TEST(S21MatrixTest, OperMulNumberWithZero) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 0.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

// Test 3: Multiply matrix with negative number
TEST(S21MatrixTest, OperMulNumberWithNegative) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = -2.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -8.0);
}

// Test 4: Multiply matrix with 1
TEST(S21MatrixTest, OperMulNumberWithOne) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 1.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

// Test 5: Multiply matrix with a large number
TEST(S21MatrixTest, OperMulNumberWithLargeValue) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double number = 1000000.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), 1000000.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 2000000.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 3000000.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4000000.0);
}

// Test 6: Multiply matrix 1x1 by a number
TEST(S21MatrixTest, OperMulNumberWith1x1Size) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  double number = 3.0;
  S21Matrix result = matrix * number;
  EXPECT_DOUBLE_EQ(result(0, 0), 15.0);
}

// Test 7: Multiply matrix with floating point number
TEST(S21MatrixTest, OperMulNumberWithFloatingPoint) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.5;
  matrix(0, 1) = 2.5;
  matrix(1, 0) = 3.5;
  matrix(1, 1) = 4.5;

  double number = 2.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 9.0);
}

// Test 8: Multiply matrix with negative values
TEST(S21MatrixTest, OperMulNumberWithNegativeValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1.5;
  matrix(0, 1) = -2.5;
  matrix(1, 0) = -3.5;
  matrix(1, 1) = -4.5;

  double number = 2.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -5.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -7.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -9.0);
}

// Test 9: Multiply matrix with zero values
TEST(S21MatrixTest, OperMulNumberWithZeroValues) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 0.0;

  double number = 5.0;

  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}

// Test 10: Multiply matrix 3x3
TEST(S21MatrixTest, OperMulNumberWith3x3Size) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double number = -1.0;
  S21Matrix result = matrix * number;

  EXPECT_DOUBLE_EQ(result(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(result(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -5.0);
  EXPECT_DOUBLE_EQ(result(1, 2), -6.0);
  EXPECT_DOUBLE_EQ(result(2, 0), -7.0);
  EXPECT_DOUBLE_EQ(result(2, 1), -8.0);
  EXPECT_DOUBLE_EQ(result(2, 2), -9.0);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR OPERATOR()
----------------------------------------------------------------------------------*/

TEST(S21MatrixTest, IndexOperator) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  ASSERT_NEAR(matrix(0, 0), 1.0, 1e-7);
  ASSERT_NEAR(matrix(0, 1), 2.0, 1e-7);
  ASSERT_NEAR(matrix(1, 0), 3.0, 1e-7);
  ASSERT_NEAR(matrix(1, 1), 4.0, 1e-7);

  matrix(0, 0) = 5.0;
  ASSERT_NEAR(matrix(0, 0), 5.0, 1e-7);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR EXCEPTIONS
----------------------------------------------------------------------------------*/

// Test for invalid set rows
TEST(S21MatrixExceptionTest, InvalidSetRows) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix.setSize(0, 0), std::invalid_argument);
  ASSERT_THROW(matrix.setSize(-1, -1), std::invalid_argument);
}

TEST(S21MatrixExceptionTest, IndexOutOfRange) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix(2, 0), std::out_of_range);
  ASSERT_THROW(matrix(0, 2), std::out_of_range);
  ASSERT_THROW(matrix(-1, 0), std::out_of_range);
  ASSERT_THROW(matrix(0, -1), std::out_of_range);
}

TEST(S21MatrixExceptionTest, PlusOperatorDifferentDimensions) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 2);
  ASSERT_THROW(matrix1 + matrix2, std::out_of_range);
}

TEST(S21MatrixExceptionTest, MinusOperatorDifferentDimensions) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 2);
  ASSERT_THROW(matrix1 - matrix2, std::out_of_range);
}

TEST(S21MatrixExceptionTest, MulMatrixOperatorIncompatibleDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 2);
  ASSERT_THROW(matrix1 * matrix2, std::out_of_range);
}

TEST(S21MatrixExceptionTest, PlusEqualOperatorDifferentDimensions) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 2);
  ASSERT_THROW(matrix1 += matrix2, std::out_of_range);
}

TEST(S21MatrixExceptionTest, MinusEqualOperatorDifferentDimensions) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 2);
  ASSERT_THROW(matrix1 -= matrix2, std::out_of_range);
}

TEST(S21MatrixExceptionTest, MulEqualMatrixOperatorIncompatibleDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 2);
  ASSERT_THROW(matrix1 *= matrix2, std::out_of_range);
}

TEST(S21MatrixTest, IndexOutOfRange) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix(3, 0), std::out_of_range);
  ASSERT_THROW(matrix(0, 3), std::out_of_range);
}

// Main function to run all tests
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}