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

// Test 3: Check if two matrices with negative values are equal
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

// Test 4: Check if Matrix with itself is equal
TEST(S21MatrixTest, EqMatrixWithSelf) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_TRUE(matrix.EqMatrix(matrix));
}

// Test 5: Check if two matrices with different values are not equal
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

// Test 6: Check if two matrices with floating point precision are equal
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

//Test 5: Multiply matrices with 1x1 size
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


// Main function to run all tests
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}