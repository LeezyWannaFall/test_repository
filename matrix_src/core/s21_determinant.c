#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL || A->matrix == NULL) return INCORRECT_MATRIX;
  if (A == NULL || A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A == NULL || A->rows != A->columns) return CALCULATION_ERROR;

  int n = A->rows;

  // Если матрица 1x1, определитель равен единственному элементу 
  if (n == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  // Если матрица 2x2, определитель вычисляется по формуле ad - bc 
  if (n == 2) {
    *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return OK;
  }

  *result = s21_determinant_gauss(A);
  return OK;
}
