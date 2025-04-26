#include "../s21_matrix.h"

double s21_determinant_gauss(matrix_t *A) {
  int n = A->rows;
  double det = 1.0;
  matrix_t temp;

  if (s21_create_matrix(n, n, &temp) != OK) return 0;

  // Копируем матрицу
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      temp.matrix[i][j] = A->matrix[i][j];

  for (int i = 0; i < n; i++) {
  // Поиск строки с максимальным элементом в текущем столбце
    int max_row = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(temp.matrix[j][i]) > fabs(temp.matrix[max_row][i])) max_row = j;
    }

    // Перестановка строк
    if (max_row != i) {
      for (int k = 0; k < n; k++) {
        double tmp = temp.matrix[i][k];
        temp.matrix[i][k] = temp.matrix[max_row][k];
        temp.matrix[max_row][k] = tmp;
      }
      det *= -1; // При перестановке строк определитель меняет знак
    }

    // Проверка на вырожденность
    if (fabs(temp.matrix[i][i]) < EPS) {
      s21_remove_matrix(&temp);
      return 0; // Матрица вырожденная
    }

    // Обнуление элементов ниже ведущего
    for (int j = i + 1; j < n; j++) {
      double factor = temp.matrix[j][i] / temp.matrix[i][i];
      for (int k = i; k < n; k++)
        temp.matrix[j][k] -= factor * temp.matrix[i][k];
    }

    // Умножение определителя на диагональный элемент
    det *= temp.matrix[i][i];
  }

  s21_remove_matrix(&temp);
  return det;
}