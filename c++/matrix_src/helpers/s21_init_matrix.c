#include "../s21_matrix.h"

// Вспомогательная функция для инициализации/обнуления структуры матрицы
void s21_init_matrix(matrix_t *result) {
  if (result != NULL) {
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
  }
}
