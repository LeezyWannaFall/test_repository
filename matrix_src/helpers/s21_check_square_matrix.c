#include "../s21_matrix.h"

int s21_check_square_matrix(matrix_t *A) {
  if (A == NULL || A->rows != A->columns) return CALCULATION_ERROR;
  return OK;
}
