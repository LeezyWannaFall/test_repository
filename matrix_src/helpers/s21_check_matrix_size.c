#include "../s21_matrix.h"

// Проверка корректности размеров матрицы
int s21_check_matrix_size(matrix_t *A) {
  if (A == NULL || A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  return OK;
}
