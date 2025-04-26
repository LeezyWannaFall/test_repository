#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка на удаление матрицы 
START_TEST(test_remove_matrix_success) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест[2]: Проверка на удаление нулевой матрицы 
START_TEST(test_remove_matrix_null) {
  matrix_t matrix = {NULL, 0, 0};
  s21_remove_matrix(&matrix);

  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест[3]: Проверка на нулевой указатель 
START_TEST(test_remove_matrix_null_pointer) { s21_remove_matrix(NULL); }
END_TEST

// Тест[4]: Проверка на удаление матрицы с некорректными rows 
START_TEST(test_remove_matrix_non_positive_rows) {
  matrix_t matrix;
  int result = s21_create_matrix(0, 3, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);

  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
  ck_assert_ptr_null(matrix.matrix);

  s21_remove_matrix(&matrix);
}
END_TEST

// Тест[5]: Проверка на удаление частично инициализированной матрицы 
START_TEST(test_remove_matrix_partial_init) {
  matrix_t matrix = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix);
  free(matrix.matrix[1]);
  matrix.matrix[1] = NULL;
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест[6]: Проверка на удаление большой матрицы 
START_TEST(test_remove_matrix_large_matrix) {
  matrix_t matrix = {NULL, 0, 0};
  s21_create_matrix(100, 100, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

TCase *tcase_s21_remove_matrix(void) {
  TCase *test_cases = tcase_create("s21_remove_matrix");
  tcase_add_test(test_cases, test_remove_matrix_success);
  tcase_add_test(test_cases, test_remove_matrix_null);
  tcase_add_test(test_cases, test_remove_matrix_null_pointer);
  tcase_add_test(test_cases, test_remove_matrix_non_positive_rows);
  tcase_add_test(test_cases, test_remove_matrix_partial_init);
  tcase_add_test(test_cases, test_remove_matrix_large_matrix);
  return test_cases;
}
