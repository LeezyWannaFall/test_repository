#include "../s21_matrix.h"

// TO DO: s21_determinant
int s21_determinant(matrix_t *A, double *result) {
  if (!A || !A->matrix || isnan(*result)) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX; 
}