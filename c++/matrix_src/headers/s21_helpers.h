#ifndef S21_HELPERS_HEADERS_H_
#define S21_HELPERS_HEADERS_H_

#include "../s21_matrix.h"

double s21_determinant_gauss(matrix_t *A);
void s21_get_minor_matrix(matrix_t *A, int row, int col, matrix_t *minor);
void s21_init_matrix(matrix_t *result);

#endif // S21_HELPERS_HEADERS_H_