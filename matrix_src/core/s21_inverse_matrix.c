#include "../s21_matrix.h"

// TO DO: s21_inverse_matrix
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix || !result) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX;  
}