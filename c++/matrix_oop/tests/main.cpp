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
TEST(S21MatrixTest, MatrixWithNegativeSize) {
    EXPECT_THROW(S21Matrix matrix(-3, -4), std::invalid_argument);
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

// Test cases for equality operator
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

TEST(S21MatrixTest, EqMatrixDifferentSizes) {
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(3, 3);
    EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrixWithZeroMatrix) {
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(2, 2);
    EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

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

TEST(S21MatrixTest, EqMatrixWithSelf) {
    S21Matrix matrix(2, 2);
    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    matrix(1, 0) = 3.0;
    matrix(1, 1) = 4.0;

    EXPECT_TRUE(matrix.EqMatrix(matrix));
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

    S21Matrix second; // Empty matrix

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

    S21Matrix second; // Empty matrix

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

// Test 8: Subtract with identity matrix
TEST(S21MatrixTest, SubWithIdentityMatrix) {
    S21Matrix first(2, 2);
    first(0, 0) = 5.0;
    first(0, 1) = 6.0;
    first(1, 0) = 7.0;
    first(1, 1) = 8.0;

    S21Matrix identity(2, 2);
    identity(0, 0) = 1.0;
    identity(0, 1) = 0.0;
    identity(1, 0) = 0.0;
    identity(1, 1) = 1.0;

    first.SubMatrix(identity);
    EXPECT_DOUBLE_EQ(first(0, 0), 4);
    EXPECT_DOUBLE_EQ(first(0, 1), 6);
    EXPECT_DOUBLE_EQ(first(1, 0), 7);
    EXPECT_DOUBLE_EQ(first(1, 1), 7);
}

// Test 9: Subtract with negative identity matrix
TEST(S21MatrixTest, SubWithNegativeIdentityMatrix) {
    S21Matrix first(2, 2);
    first(0, 0) = 5.0;
    first(0, 1) = 6.0;
    first(1, 0) = 7.0;
    first(1, 1) = 8.0;

    S21Matrix identity(2, 2);
    identity(0, 0) = -1.0;
    identity(0, 1) = 0.0;
    identity(1, 0) = 0.0;
    identity(1, 1) = -1.0;

    first.SubMatrix(identity);
    EXPECT_DOUBLE_EQ(first(0, 0), 6);
    EXPECT_DOUBLE_EQ(first(0, 1), 6);
    EXPECT_DOUBLE_EQ(first(1, 0), 7);
    EXPECT_DOUBLE_EQ(first(1, 1), 9);
}

// Test 10: Subtract with identity matrix with negative values
TEST(S21MatrixTest, SubWithIdentityMatrixNegativeValues) {
    S21Matrix first(2, 2);
    first(0, 0) = -5.0;
    first(0, 1) = -6.0;
    first(1, 0) = -7.0;
    first(1, 1) = -8.0;

    S21Matrix identity(2, 2);
    identity(0, 0) = 1.0;
    identity(0, 1) = 0.0;
    identity(1, 0) = 0.0;
    identity(1, 1) = 1.0;

    first.SubMatrix(identity);
    EXPECT_DOUBLE_EQ(first(0, 0), -6);
    EXPECT_DOUBLE_EQ(first(0, 1), -6);
    EXPECT_DOUBLE_EQ(first(1, 0), -7);
    EXPECT_DOUBLE_EQ(first(1, 1), -9);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR MULMATRIX
----------------------------------------------------------------------------------*/

// Test cases for matrix multiplication
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
/*--------------------------------------------------------------------------------
                                TESTS FOR MULNUMBER
----------------------------------------------------------------------------------*/

// // Test cases for multiplication by a number
// TEST(S21MatrixTest, MulNumber) {
//     S21Matrix matrix(2, 2);
//     matrix(0, 0) = 1.0;
//     matrix(0, 1) = 2.0;
//     matrix(1, 0) = 3.0;
//     matrix(1, 1) = 4.0;
// }

// Main function to run all tests
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}