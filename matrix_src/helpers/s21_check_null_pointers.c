#include "../s21_matrix.h"

// Проверка на NULL-указатели 
int s21_check_null_pointers(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL ||
      (A != NULL && A->matrix == NULL) || (B != NULL && B->matrix == NULL))
    return INCORRECT_MATRIX;
  return OK;
}
