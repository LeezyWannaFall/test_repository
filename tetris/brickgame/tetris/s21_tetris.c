#include "../../s21_tetris.h"

void zero_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j = A->columns; j++) {
      A->matrix[i][j] = 0;
    }
  }
}

void copy_matrix(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j = A->columns; j++) {
      A->matrix[i][j] = result->matrix[i][j];
    }
  }
}

void create_matrix_field(int rows, int columns, matrix_t *Tetris_field) {
  s21_create_matrix(10, 20, &Tetris_field);

}

int main() {
  
}
