#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || result == NULL) return INCORRECT_MATRIX;
  if (A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  double det;
  int temp_status = s21_determinant(A, &det);
  if (temp_status != OK) return temp_status;
  if (fabs(det) < EPS) return CALCULATION_ERROR;

  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) != OK) return INCORRECT_MATRIX;
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return OK;
  }

  matrix_t complements = {0};
  matrix_t complements_transposed = {0};

  temp_status = s21_calc_complements(A, &complements);
  if (temp_status != OK) {
    return temp_status;
  }

  temp_status = s21_transpose(&complements, &complements_transposed);
  s21_remove_matrix(&complements);
  if (temp_status != OK) {
    return temp_status;
  }

  temp_status = s21_create_matrix(A->rows, A->columns, result);
  if (temp_status != OK) {
    s21_remove_matrix(&complements_transposed);
    return temp_status;
  }

  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = complements_transposed.matrix[i][j] / det;
    }
  }

  s21_remove_matrix(&complements_transposed);
  return OK;
}
