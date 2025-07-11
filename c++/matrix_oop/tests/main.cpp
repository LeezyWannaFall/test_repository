#include <gtest/gtest.h>
#include "../s21_matrix_oop.h"

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
    EXPECT_THROW(S21Matrix(0, 2), std::invalid_argument);
    EXPECT_THROW(S21Matrix(2, 0), std::invalid_argument);
    EXPECT_THROW(S21Matrix(0, 0), std::invalid_argument);
}

// Test cases for copy constructor
TEST(S21MatrixTest, CopyConstructor) {
    S21Matrix matrix1(2, 2);
    matrix1(0, 0) = 1.0;
    matrix1(0, 1) = 2.0;
    matrix1(1, 0) = 3.0;
    matrix1(1, 1) = 4.0;

    S21Matrix matrix2(matrix1);
    EXPECT_EQ(matrix2.getRows(), 2);
    EXPECT_EQ(matrix2.getCols(), 2);
    EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(matrix2(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(matrix2(1, 1), 4.0);
}

// Test cases for move constructor
TEST(S21MatrixTest, MoveConstructor) {
    S21Matrix matrix1(2, 2);
    matrix1(0, 0) = 5.0;
    matrix1(0, 1) = 6.0;

    S21Matrix matrix2(std::move(matrix1));
    EXPECT_EQ(matrix2.getRows(), 2);
    EXPECT_EQ(matrix2.getCols(), 2);
    EXPECT_DOUBLE_EQ(matrix2(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(matrix2(0, 1), 6.0);
}

// Test cases for destructor
TEST(S21MatrixTest, Destructor) {
    S21Matrix* matrix = new S21Matrix(2, 2);
    EXPECT_NO_THROW(delete matrix);
}

// Test cases for equality operator
TEST(S21MatrixTest, EqMatrix) {
    S21Matrix matrix1(2, 2);
    matrix1(0, 0) = 1.0;
    matrix1(0, 1) = 2.0;
    matrix1(1, 0) = 3.0;
    matrix1(1, 1) = 4.0;

    S21Matrix matrix2(matrix1);
    EXPECT_TRUE(matrix1.EqMatrix(matrix2));

    matrix2(0, 0) = 5.0;
    EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Main function to run all tests
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}