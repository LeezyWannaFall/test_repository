#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Умножение матрицы 1x1 на число 
START_TEST(test_mult_number_success_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 3.0;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 6.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[2]: Умножение матрицы 2x2 на число 
START_TEST(test_mult_number_success_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 8.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[3]: Умножение матрицы 3x3 на число 
START_TEST(test_mult_number_success_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 8.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 10.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], 12.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], 14.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], 16.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], 18.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[4]: Умножение матрицы с нулевыми элементами 
START_TEST(test_mult_number_zero_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[5]: Умножение матрицы с отрицательными элементами 
START_TEST(test_mult_number_negative_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -8.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[6]: Умножение матрицы с числами с плавающей точкой 
START_TEST(test_mult_number_floating_point) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 5.4, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 6.4, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 9.8, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[7]: Умножение матрицы на ноль 
START_TEST(test_mult_number_zero_multiplier) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  double number = 0.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[8]: Умножение матрицы на отрицательное число 
START_TEST(test_mult_number_negative_multiplier) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  double number = -2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -8.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[9]: Проверка на NULL-указатель матрицы A 
START_TEST(test_mult_number_null_A) {
  matrix_t result;
  double number = 2.0;

  int status = s21_mult_number(NULL, number, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[10]: Проверка на NULL-указатель матрицы result 
START_TEST(test_mult_number_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  double number = 2.0;

  int status = s21_mult_number(&A, number, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[11]: Проверка на некорректные размеры матрицы A (отрицательные строки)
START_TEST(test_mult_number_invalid_rows_A) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[12]: Проверка на некорректные размеры матрицы A (отрицательные столбцы)
START_TEST(test_mult_number_invalid_columns_A) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = -1;
  A.matrix = NULL;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[13]: Проверка на NULL-указатель A->matrix 
START_TEST(test_mult_number_null_matrix_A) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;
  double number = 2.0;

  int status = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[14]: Проверка на максимальный размер матрицы 
START_TEST(test_mult_number_max_size) {
  matrix_t A, result;
  int test_size = MAX_MATRIX_SIZE;
  int status_A = s21_create_matrix(test_size, test_size, &A);
  double number = 2.0;

  if (status_A == OK) {
    // Заполняем только угловые элементы для ускорения 
    A.matrix[0][0] = 1.0;
    A.matrix[0][test_size - 1] = 2.0;
    A.matrix[test_size - 1][0] = 3.0;
    A.matrix[test_size - 1][test_size - 1] = 4.0;

    int status = s21_mult_number(&A, number, &result);
    ck_assert_int_eq(status, OK);

    // Проверяем только угловые элементы 
    ck_assert_double_eq_tol(result.matrix[0][0], 2.0, EPS);
    ck_assert_double_eq_tol(result.matrix[0][test_size - 1], 4.0, EPS);
    ck_assert_double_eq_tol(result.matrix[test_size - 1][0], 6.0, EPS);
    ck_assert_double_eq_tol(result.matrix[test_size - 1][test_size - 1], 8.0,
                            EPS);

    s21_remove_matrix(&result);
  }

  if (status_A == OK) s21_remove_matrix(&A);
}
END_TEST

TCase *tcase_s21_mult_number(void) {
  TCase *test_cases = tcase_create("s21_mult_number");
  tcase_add_test(test_cases, test_mult_number_success_1x1);
  tcase_add_test(test_cases, test_mult_number_success_2x2);
  tcase_add_test(test_cases, test_mult_number_success_3x3);
  tcase_add_test(test_cases, test_mult_number_zero_elements);
  tcase_add_test(test_cases, test_mult_number_negative_elements);
  tcase_add_test(test_cases, test_mult_number_floating_point);
  tcase_add_test(test_cases, test_mult_number_zero_multiplier);
  tcase_add_test(test_cases, test_mult_number_negative_multiplier);
  tcase_add_test(test_cases, test_mult_number_null_A);
  tcase_add_test(test_cases, test_mult_number_null_result);
  tcase_add_test(test_cases, test_mult_number_invalid_rows_A);
  tcase_add_test(test_cases, test_mult_number_invalid_columns_A);
  tcase_add_test(test_cases, test_mult_number_null_matrix_A);
  tcase_add_test(test_cases, test_mult_number_max_size);
  return test_cases;
}
