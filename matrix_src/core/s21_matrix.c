#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) return INCORRECT_MATRIX;

  result->rows = rows;
  result->columns = columns;

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

  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (!A || !A->matrix) return;

  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);

  A->matrix = NULL;
  A->columns = 0;
  A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || !A->matrix || !B || !B->matrix) return FAILURE;

  if (A->rows != B->rows || A->columns != B->columns) return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) return FAILURE;
    }
  }

  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !A->matrix || !B || !B->matrix || !result) return INCORRECT_MATRIX;

  if (A->rows != B->rows || A->columns != B->columns) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
  }

  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !A->matrix || !B || !B->matrix || !result) return INCORRECT_MATRIX;

  if (A->rows != B->rows || A->columns != B->columns) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
  }

  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A || !A->matrix || !result) return INCORRECT_MATRIX;

  if (isnan(number)) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
      }
  }

  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !A->matrix || !B || !B->matrix || !result) return INCORRECT_MATRIX;

  if (A->columns != B->rows) return CALCULATION_ERROR;

  if (s21_create_matrix(A->rows, B->columns, result) != OK) return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix || !result) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->columns, A->rows, result) != OK) return INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}

// TO DO: s21_calc_complements
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix || !result) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX; 
}

// TO DO: s21_determinant
int s21_determinant(matrix_t *A, double *result) {
  if (!A || !A->matrix || isnan(*result)) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX; 
}

// TO DO: s21_inverse_matrix
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix || !result) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX;  
}


