#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || (A != NULL && A->matrix == NULL)) return INCORRECT_MATRIX;
  if (A == NULL || A->rows <= 0 || A->columns <= 0) return INCORRECT_MATRIX;
  if (A == NULL || A->rows != A->columns) return CALCULATION_ERROR;

  // Вычисляем определитель матрицы A 
  double det;
  if (s21_determinant(A, &det) != OK) return s21_determinant(A, &det);

  // Проверяем, что определитель не равен 0 (иначе обратной матрицы не существует) 
  if (fabs(det) < EPS) return CALCULATION_ERROR;

  // Если матрица 1x1, обратная матрица равна 1/A[0][0] 
  if (A->rows == 1) {
    if (s21_create_matrix(1, 1, result) != OK) {
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return OK;
    }
  }

  // Вычисляем матрицу алгебраических дополнений 
  matrix_t complements;
  if (s21_calc_complements(A, &complements) != OK) return (s21_calc_complements(A, &complements) != OK);

  // Транспонируем матрицу алгебраических дополнений 
  matrix_t complements_transposed;
  if (s21_transpose(&complements, &complements_transposed) != OK) {
    s21_remove_matrix(&complements);
    return s21_transpose(&complements, &complements_transposed);
  }

  // Создаём результирующую матрицу 
  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    s21_remove_matrix(&complements_transposed);
    return s21_create_matrix(A->rows, A->columns, result);
  }


  // Умножаем транспонированную матрицу алгебраических дополнений на 1/|A| 
  for (int i = 0; i < result->rows; i++)
    for (int j = 0; j < result->columns; j++)
      result->matrix[i][j] = complements_transposed.matrix[i][j] / det;

  s21_remove_matrix(&complements_transposed);

  return OK;
}