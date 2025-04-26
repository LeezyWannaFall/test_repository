#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Проверка входных параметров
  if (A == NULL || result == NULL || A->matrix == NULL) return INCORRECT_MATRIX;
  if (A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  // Инициализация result
  int status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) return status;

  // Если матрица 1x1
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
    return OK;
  }

  // Создаём временную матрицу для миноров
  matrix_t minor;
  status = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  if (status != OK) {
    s21_remove_matrix(result);
    return status;
  }

  // Заполняем матрицу алгебраических дополнений
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      s21_get_minor_matrix(A, i, j, &minor);
      
      double minor_det;
      status = s21_determinant(&minor, &minor_det);
      if (status != OK) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return status;
      }
        
      result->matrix[i][j] = minor_det * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }

  s21_remove_matrix(&minor);
  return OK;
}