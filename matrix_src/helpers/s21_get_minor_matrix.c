#include "../s21_matrix.h"

// Функция для создания подматрицы, исключая строку row и столбец col 
void s21_get_minor_matrix(matrix_t *A, int row, int col, matrix_t *minor) {
  int minor_row = 0, minor_col = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0; j < A->columns; j++) {
        if (j != col) {
          minor->matrix[minor_row][minor_col++] = A->matrix[i][j];
        }
      }
      minor_row++;
      minor_col = 0;
    }
  }
}
