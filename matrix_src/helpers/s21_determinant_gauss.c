#include "../s21_matrix.h"

double s21_determinant_gauss(matrix_t *A) {
  int n = A->rows;
  double det = 1;
  matrix_t temp;

  if (s21_create_matrix(n, n, &temp) != OK) return 0;

  // Копируем матрицу, чтобы не менять оригинал
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) temp.matrix[i][j] = A->matrix[i][j];

  for (int i = 0; i < n; i++) {
    int pivot = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(temp.matrix[j][i]) > fabs(temp.matrix[pivot][i])) pivot = j;
    }
    if (pivot != i) {
      for (int j = 0; j < n; j++) {
        double tmp = temp.matrix[i][j];
        temp.matrix[i][j] = temp.matrix[pivot][j];
        temp.matrix[pivot][j] = tmp;
      }
      det *= -1;
    }

    if (fabs(temp.matrix[i][i]) < EPS) {
      s21_remove_matrix(&temp);
      return 0;
    }

    det *= temp.matrix[i][i];
    for (int j = i + 1; j < n; j++) {
      double factor = temp.matrix[j][i] / temp.matrix[i][i];
      for (int k = i; k < n; k++)
        temp.matrix[j][k] -= factor * temp.matrix[i][k];
    }
  }

  s21_remove_matrix(&temp);
  return det;
}
