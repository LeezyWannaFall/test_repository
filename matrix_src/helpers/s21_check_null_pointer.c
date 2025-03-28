#include "../s21_matrix.h"

// Проверка на NULL-указатели
int s21_check_null_pointer(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || (A != NULL && A->matrix == NULL))
    return INCORRECT_MATRIX;
  return OK;
}
