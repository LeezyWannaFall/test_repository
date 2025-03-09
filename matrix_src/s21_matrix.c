#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // проверка на корректность входных данных
  if (rows <= 0 || columns <= 0 || result == NULL) return INCORRECT_MATRIX;

  // инициализация струткуры
  result->rows = rows;
  result->columns = columns;

  // выделение памяти под матрицу
  result->matrix = (double **)malloc(rows * sizeof(double *));

  // проверка на NULL
  if (!result) return INCORRECT_MATRIX;

  // выделение памяти под каждый столбец
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    // очистка уже выделенной памяти в случае ошибки
    if (!result->matrix[i]) {
      for (int j = 0; j < i; i++) {
        free(result->matrix[j]);
      }

      free(result->matrix);
      return INCORRECT_MATRIX;
    }
  }
  
  return OK;
}