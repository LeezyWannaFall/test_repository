#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка на создание матрицы 
START_TEST(test_create_matrix_success) {
  matrix_t matrix;
  int result = s21_create_matrix(3, 3, &matrix);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(matrix.rows, 3);
  ck_assert_int_eq(matrix.columns, 3);

  // Проверяем, что все элементы матрицы инициализированы нулями 
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++)
      ck_assert_double_eq(matrix.matrix[i][j], 0.0);
  }

  s21_remove_matrix(&matrix);
}
END_TEST

// Тест[2]: Проверка на некорректное количество строк и столбцов 
START_TEST(test_create_matrix_invalid_size) {
  matrix_t matrix;
  int result = s21_create_matrix(-1, 3, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);

  result = s21_create_matrix(3, 0, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

// Тест[3]: Проверка на нулевую матрицу 
START_TEST(test_create_matrix_null_result) {
  int result = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

// Тест[4]: Проверка на недостаток памяти 
START_TEST(test_create_matrix_memory_failure) {
  matrix_t matrix;
  int result =
      s21_create_matrix(MAX_MATRIX_SIZE + 1, MAX_MATRIX_SIZE + 1, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест[5]: Проверка на освобождение памяти при ошибке 
START_TEST(test_create_matrix_partial_memory_failure) {
  matrix_t matrix;
  int result = s21_create_matrix(3, 3, &matrix);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&matrix);
}
END_TEST

// Тест[6]: Проверка на переполнение памяти 
START_TEST(test_create_matrix_overflow) {
  matrix_t matrix;
  int result = s21_create_matrix(INT_MAX, INT_MAX, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

// Тест[7]: Проверка на частичное выделение памяти 
START_TEST(test_create_matrix_partial_allocation_failure) {
  matrix_t matrix;
  // Проверяем переполнение памяти
  int result = s21_create_matrix(INT_MAX, INT_MAX, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

// Тест[8]: Проверка на максимальный размер матрицы 
START_TEST(test_create_matrix_max_size) {
  matrix_t matrix;
  int result = s21_create_matrix(10001, 10001, &matrix);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

TCase *tcase_s21_create_matrix(void) {
  TCase *test_cases = tcase_create("s21_create_matrix");
  tcase_add_test(test_cases, test_create_matrix_success);
  tcase_add_test(test_cases, test_create_matrix_invalid_size);
  tcase_add_test(test_cases, test_create_matrix_null_result);
  tcase_add_test(test_cases, test_create_matrix_memory_failure);
  tcase_add_test(test_cases, test_create_matrix_partial_memory_failure);
  tcase_add_test(test_cases, test_create_matrix_overflow);
  tcase_add_test(test_cases, test_create_matrix_partial_allocation_failure);
  tcase_add_test(test_cases, test_create_matrix_max_size);
  return test_cases;
}
