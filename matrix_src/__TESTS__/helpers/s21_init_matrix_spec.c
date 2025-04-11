#include <check.h>

#include "../../s21_matrix.h"

/* Тест[1]: Проверка на NULL указателя */
START_TEST(test_init_matrix_null_pointer) {
  s21_init_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

/* Тест[2]: Проверка на передачу валидного указателя на структуру с ненулевыми
 * значениями */
START_TEST(test_init_matrix_non_zero_values) {
  matrix_t matrix;
  matrix.rows = 5;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(5 * sizeof(double *));

  if (matrix.matrix == NULL) ck_abort_msg("Memory allocation error");

  free(matrix.matrix);

  matrix.matrix = NULL;

  s21_init_matrix(&matrix);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);

  free(matrix.matrix);
}
END_TEST

/* Тест[3]: Проверка на передачу валидного указателя на уже обнуленную структуру
 */
START_TEST(test_init_matrix_already_zeroed) {
  matrix_t matrix = {NULL, 0, 0};

  s21_init_matrix(&matrix);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

/* Тест[4]: Проверка на передачу валидного указателя на структуру с
 * некорректными значениями
 */
START_TEST(test_init_matrix_invalid_values) {
  matrix_t matrix;
  matrix.rows = -1;
  matrix.columns = -2;
  matrix.matrix = (double **)malloc(5 * sizeof(double *));

  if (matrix.matrix == NULL) ck_abort_msg("Failed to allocate memory");

  free(matrix.matrix);

  matrix.matrix = NULL;

  s21_init_matrix(&matrix);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);

  free(matrix.matrix);
}
END_TEST

TCase *tcase_s21_init_matrix(void) {
  TCase *test_cases = tcase_create("s21_init_matrix");
  tcase_add_test(test_cases, test_init_matrix_null_pointer);
  tcase_add_test(test_cases, test_init_matrix_non_zero_values);
  tcase_add_test(test_cases, test_init_matrix_already_zeroed);
  tcase_add_test(test_cases, test_init_matrix_invalid_values);
  return test_cases;
}
