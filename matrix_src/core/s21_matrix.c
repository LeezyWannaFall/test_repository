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
  if (!result->matrix) return INCORRECT_MATRIX;

  // выделение памяти под каждый столбец
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    // очистка уже выделенной памяти в случае ошибки
    if (!result->matrix[i]) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }

      free(result->matrix);
      return INCORRECT_MATRIX;
    }
  }

  return OK;
}

void s21_remove_matrix(matrix_t *A) {
    //  проверка на корректность входных данных
    if (!A || !A->matrix) return INCORRECT_MATRIX;

    // очищение памяти
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);

    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || A->matrix || !B || B->matrix) return FAILURE;

  if (A->rows != B->rows || A->columns != B->columns) return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) return FAILURE;
    }
  }

  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || A->matrix || !B || B->matrix || !result || !result->matrix) return INCORRECT_MATRIX;

  if (A->rows != B->rows || A->columns != B->columns) return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}