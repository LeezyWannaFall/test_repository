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

/*--------------------------------------------------------------------------------
                                TESTS FOR SUMMATRIX
----------------------------------------------------------------------------------*/

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
    EXPECT_DOUBLE_EQ(first.getRows(), 2);
    EXPECT_DOUBLE_EQ(first.getCols(), 2);
    EXPECT_DOUBLE_EQ(first(0, 0), 5);
    EXPECT_DOUBLE_EQ(first(0, 1), 5);
    EXPECT_DOUBLE_EQ(first(1, 0), 5);
    EXPECT_DOUBLE_EQ(first(1, 1), 5);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR SUBMATRIX
----------------------------------------------------------------------------------*/

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
    EXPECT_DOUBLE_EQ(first.getRows(), 2);
    EXPECT_DOUBLE_EQ(first.getCols(), 2);
    EXPECT_DOUBLE_EQ(first(0, 0), 1);
    EXPECT_DOUBLE_EQ(first(0, 1), 3);
    EXPECT_DOUBLE_EQ(first(1, 0), 5);
    EXPECT_DOUBLE_EQ(first(1, 1), 7);
}

/*--------------------------------------------------------------------------------
                                TESTS FOR MULMATRIX
----------------------------------------------------------------------------------*/

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

// Main function to run all tests
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}