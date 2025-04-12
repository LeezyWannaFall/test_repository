#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || (A != NULL && A->matrix == NULL)) return INCORRECT_MATRIX;
  if (A == NULL || A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A == NULL || A->rows != A->columns) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) return INCORRECT_MATRIX;

  // Если матрица 1x1, алгебраическое дополнение равно 1 
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
    return OK;
  }

  // Создаём временную матрицу для миноров 
  matrix_t minor;
  int temp_status = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  if (temp_status != OK) {
    s21_remove_matrix(result);
    return temp_status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      s21_get_minor_matrix(A, i, j, &minor);
      double minor_det;
      int temp_status = s21_determinant(&minor, &minor_det);
      if (temp_status != OK) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return temp_status;
      }
      // minor * (-1)^(i+j) 
      result->matrix[i][j] = minor_det * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }

  s21_remove_matrix(&minor);

  return OK;
}