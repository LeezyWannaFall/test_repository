#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || (A != NULL && A->matrix == NULL)) return INCORRECT_MATRIX;
  if (A == NULL || A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A == NULL || A->rows != A->columns) return CALCULATION_ERROR;

  // Вычисляем определитель матрицы A 
  double det;
  int temp_status = s21_determinant(A, &det);
  if (temp_status != OK) return temp_status;

  // Проверяем, что определитель не равен 0 (иначе обратной матрицы не существует) 
  if (fabs(det) < EPS) return CALCULATION_ERROR;

  // Если матрица 1x1, обратная матрица равна 1/A[0][0] 
  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) != OK) return INCORRECT_MATRIX;
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return OK;
  }

  // Вычисляем матрицу алгебраических дополнений 
  matrix_t complements;
  temp_status = s21_calc_complements(A, &complements);
  if (temp_status != OK) return temp_status;

  // Транспонируем матрицу алгебраических дополнений 
  matrix_t complements_transposed;
  temp_status = s21_transpose(&complements, &complements_transposed);
  if (temp_status != OK) {
    s21_remove_matrix(&complements);
    return temp_status;
  }

  // Создаём результирующую матрицу 
  temp_status = s21_create_matrix(A->rows, A->columns, result);
  if (temp_status != OK) {
    s21_remove_matrix(&complements_transposed);
    return temp_status;
  }


  // Умножаем транспонированную матрицу алгебраических дополнений на 1/|A| 
  for (int i = 0; i < result->rows; i++)
    for (int j = 0; j < result->columns; j++)
      result->matrix[i][j] = complements_transposed.matrix[i][j] / det;

  s21_remove_matrix(&complements_transposed);

  return OK;
}