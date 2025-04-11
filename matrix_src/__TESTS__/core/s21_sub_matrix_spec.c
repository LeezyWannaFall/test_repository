#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка на вычитание матриц 1x1 
START_TEST(test_sub_matrix_success_1x1) {
  matrix_t A, B, result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 3.0;
  B.matrix[0][0] = 2.0;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[2]: Проверка на вычитание матриц 2x2 
START_TEST(test_sub_matrix_success_2x2) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 1.0;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 3.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[3]: Проверка на вычитание матриц 3x3 
START_TEST(test_sub_matrix_success_3x3) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = 1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = 1.0;
  B.matrix[2][0] = 1.0;
  B.matrix[2][1] = 1.0;
  B.matrix[2][2] = 1.0;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], 5.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], 7.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], 8.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[4]: Проверка на вычитание матриц с нулевыми элементами 
START_TEST(test_sub_matrix_zero_elements) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;

  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 0.0;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[5]: Проверка на вычитание матриц с отрицательными элементами 
START_TEST(test_sub_matrix_negative_elements) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  B.matrix[0][0] = -1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[1][0] = -1.0;
  B.matrix[1][1] = -1.0;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -3.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[6]: Проверка на вычитание матриц с плавающими точками 
START_TEST(test_sub_matrix_floating_point) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;

  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 0.7;
  B.matrix[1][0] = 0.2;
  B.matrix[1][1] = 0.9;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[7]: Проверка на вычитание матриц с несовпадающими размерами 
START_TEST(test_sub_matrix_different_rows) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR );

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[8]: Проверка на вычитание матриц с несовпадающими размерами 
START_TEST(test_sub_matrix_different_columns) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 3, &B);

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR );

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[9]: Проверка на вычитание матриц с NULL-указателями 
START_TEST(test_sub_matrix_null_A) {
  matrix_t B, result;
  s21_create_matrix(2, 2, &B);

  int status = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

// Тест[10]: Проверка на вычитание матриц с NULL-указателями 
START_TEST(test_sub_matrix_null_B) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  int status = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[11]: Проверка на вычитание матриц с NULL-указателями 
START_TEST(test_sub_matrix_null_result) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int status = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[12]: Проверка на вычитание матриц с некорректными размерами 
START_TEST(test_sub_matrix_invalid_rows_A) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &B);
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

// Тест[13]: Проверка на вычитание матриц с некорректными размерами 
START_TEST(test_sub_matrix_invalid_columns_B) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  B.rows = 2;
  B.columns = -1;
  B.matrix = NULL;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[14]: Проверка на вычитание матриц с NULL-указателями 
START_TEST(test_sub_matrix_null_matrix_A) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &B);
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

// Тест[15]: Проверка на вычитание матриц с NULL-указателями 
START_TEST(test_sub_matrix_null_matrix_B) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  B.rows = 2;
  B.columns = 2;
  B.matrix = NULL;

  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[16]: Проверка на вычитание матриц с максимальными размерами 
START_TEST(test_sub_matrix_max_size) {
  matrix_t A, B, result;
  int test_size = MAX_MATRIX_SIZE;
  int status_A = s21_create_matrix(test_size, test_size, &A);
  int status_B = s21_create_matrix(test_size, test_size, &B);

  if (status_A == OK && status_B == OK) {
    // Заполняем только угловые элементы для ускорения 
    A.matrix[0][0] = 2.0;
    A.matrix[0][test_size - 1] = 2.0;
    A.matrix[test_size - 1][0] = 2.0;
    A.matrix[test_size - 1][test_size - 1] = 2.0;
    B.matrix[0][0] = 1.0;
    B.matrix[0][test_size - 1] = 1.0;
    B.matrix[test_size - 1][0] = 1.0;
    B.matrix[test_size - 1][test_size - 1] = 1.0;

    int status = s21_sub_matrix(&A, &B, &result);
    ck_assert_int_eq(status, OK);

    // Проверяем только угловые элементы 
    ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
    ck_assert_double_eq_tol(result.matrix[0][test_size - 1], 1.0, EPS);
    ck_assert_double_eq_tol(result.matrix[test_size - 1][0], 1.0, EPS);
    ck_assert_double_eq_tol(result.matrix[test_size - 1][test_size - 1], 1.0,
                            EPS);

    s21_remove_matrix(&result);
  }

  if (status_A == OK) s21_remove_matrix(&A);
  if (status_B == OK) s21_remove_matrix(&B);
}
END_TEST

TCase *tcase_s21_sub_matrix(void) {
  TCase *test_cases = tcase_create("s21_sub_matrix");
  tcase_add_test(test_cases, test_sub_matrix_success_1x1);
  tcase_add_test(test_cases, test_sub_matrix_success_2x2);
  tcase_add_test(test_cases, test_sub_matrix_success_3x3);
  tcase_add_test(test_cases, test_sub_matrix_zero_elements);
  tcase_add_test(test_cases, test_sub_matrix_negative_elements);
  tcase_add_test(test_cases, test_sub_matrix_floating_point);
  tcase_add_test(test_cases, test_sub_matrix_different_rows);
  tcase_add_test(test_cases, test_sub_matrix_different_columns);
  tcase_add_test(test_cases, test_sub_matrix_null_A);
  tcase_add_test(test_cases, test_sub_matrix_null_B);
  tcase_add_test(test_cases, test_sub_matrix_null_result);
  tcase_add_test(test_cases, test_sub_matrix_invalid_rows_A);
  tcase_add_test(test_cases, test_sub_matrix_invalid_columns_B);
  tcase_add_test(test_cases, test_sub_matrix_null_matrix_A);
  tcase_add_test(test_cases, test_sub_matrix_null_matrix_B);
  tcase_add_test(test_cases, test_sub_matrix_max_size);
  return test_cases;
}
