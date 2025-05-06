#include "../s21_tetris.h"

matrix_t Tetris_field;

// Вспомогательная функция для инициализации/обнуления структуры матрицы
void s21_init_matrix(matrix_t *result) {
    if (result != NULL) {
      result->rows = 0;
      result->columns = 0;
      result->matrix = NULL;
    }
  }

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    if (result != NULL) s21_init_matrix(result);
    return INCORRECT_MATRIX;
  }

  // Проверка на максимальный размер матрицы 
  if (rows > MAX_MATRIX_SIZE || columns > MAX_MATRIX_SIZE) {
    s21_init_matrix(result);
    return INCORRECT_MATRIX;
  }

  // Проверка на переполнение памяти 
  if ((size_t)rows * (size_t)columns > SIZE_MAX / sizeof(double)) {
    s21_init_matrix(result);
    return INCORRECT_MATRIX;
  }

  // Инициализация структуры матрицы 
  s21_init_matrix(result);

  // Выделение памяти для массива указателей 
  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL) return INCORRECT_MATRIX;

  // Выделение памяти для каждой строки 
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
    // Освобождение памяти, если выделение не удалось 
      for (int j = 0; j < i; j++) free(result->matrix[j]);
        free(result->matrix);
        result->matrix = NULL;
        return INCORRECT_MATRIX;
    }
  }

  result->rows = rows;
  result->columns = columns;
  return OK;
}

void print_field(matrix_t *Tetris_field) {
  for (int y = 0; y < Tetris_field->rows; y++) {
    for (int x = 0; x < Tetris_field->columns; x++) {
      if ((y == 9) || (x == 0 || x == 19))
        printf("%s", Tetris_field->matrix[y][x] ? " " : "\u2588");
      else
        printf("%s", Tetris_field->matrix[y][x] ? "\u2588" : " ");
    } 
    printf("\n");
  }
}

int main() {
  s21_create_matrix(10, 20, &Tetris_field);
  print_field(&Tetris_field);
}
