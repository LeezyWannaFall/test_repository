#ifndef S21_HELPERS_HEADERS_H_
#define S21_HELPERS_HEADERS_H_

#include "../s21_matrix.h"

int s21_check_matching_size(matrix_t *A, matrix_t *B);
int s21_check_matching_size(matrix_t *A, matrix_t *B);
int s21_check_matrix_sizes(matrix_t *A, matrix_t *B);
int s21_check_null_pointer(matrix_t *A, matrix_t *result);
int s21_check_null_pointers(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_check_square_matrix(matrix_t *A);
double s21_determinant_gauss(matrix_t *A);
void s21_get_minor_matrix(matrix_t *A, int row, int col, matrix_t *minor);
void s21_init_matrix(matrix_t *result);

#endif // S21_HELPERS_HEADERS_H_