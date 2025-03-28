#include "../s21_matrix.h"

// Проверка корректности размеров матриц
int s21_check_matrix_sizes(matrix_t *A, matrix_t *B) {
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    return INCORRECT_MATRIX;
  return OK;
}
