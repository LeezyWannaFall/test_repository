#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) return INCORRECT_MATRIX;

  if (rows > MAX_MATRIX_SIZE || columns > MAX_MATRIX_SIZE) {
    s21_init_matrix(result);
    return INCORRECT_MATRIX;
  }

  if ((size_t)rows * (size_t)columns > SIZE_MAX / sizeof(double)) {
    s21_init_matrix(result);
    return INCORRECT_MATRIX;
  }

  s21_init_matrix(result);
  
  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (!result->matrix) return INCORRECT_MATRIX;

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (!result->matrix[i]) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return INCORRECT_MATRIX;
    }
  }
  
  result->rows = rows;
  result->columns = columns;

  return OK;
}