#include "../s21_matrix.h"

// TO DO: s21_determinant
int s21_determinant(matrix_t *A, double *result) {
  if (!A || !A->matrix || isnan(*result)) return INCORRECT_MATRIX;
  if (s21_check_matrix_size(A) != OK) return INCORRECT_MATRIX;
  if (s21_check_square_matrix(A) != OK) return CALCULATION_ERROR;

  int n = A->rows;
  // Если матрица 1x1, определитель равен единственному элементу
  if (n == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  // Если матрица 2x2, определитель вычисляется по формуле ad - bc
  if (n == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return OK;
  }

  
}