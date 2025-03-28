#include "../s21_matrix.h"

// TO DO: s21_calc_complements
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !A->matrix || !result) return INCORRECT_MATRIX;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX; 
}