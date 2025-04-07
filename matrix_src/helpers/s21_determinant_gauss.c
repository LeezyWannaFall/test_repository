#include "../s21_matrix.h"

double s21_determinant_gauss(matrix_t *A) {
  int n = A->rows;
  double det = 1;
  matrix_t temp;

  if (s21_create_matrix(n, n, &temp) != OK) return INCORRECT_MATRIX;

  //  Копируем матрицу A, во временную матрицу temp, чтобы не менять оригинал
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      temp.matrix[i][j] = A->matrix[i][j];
    }
  }
}
