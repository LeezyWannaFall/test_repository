#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка вычисления определителя для матрицы 1x1 
START_TEST(test_determinant_success_1x1) {
  matrix_t A;
  double result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 5.0;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 5.0, EPS);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[2]: Проверка вычисления определителя для матрицы 2x2 
START_TEST(test_determinant_success_2x2) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -2.0, EPS);  // 1*4 - 2*3 = -2

  s21_remove_matrix(&A);
}
END_TEST

// Тест[3]: Проверка вычисления определителя для матрицы 3x3 
START_TEST(test_determinant_success_3x3) {
  matrix_t A;
  double result;
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

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0,
                          EPS);  // Определитель вырожденной матрицы

  s21_remove_matrix(&A);
}
END_TEST

// Тест[4]: Проверка вычисления определителя для матрицы 3x3 с ненулевым определителем 
START_TEST(test_determinant_success_3x3_non_zero) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -40.0, EPS);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[5]: Проверка вычисления определителя с нулевыми элементами 
START_TEST(test_determinant_zero_elements) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, EPS);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[6]: Проверка вычисления определителя с отрицательными элементами 
START_TEST(test_determinant_negative_elements) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -2.0,
                          EPS);  // (-1)*(-4) - (-2)*(-3) = -2

  s21_remove_matrix(&A);
}
END_TEST

// Тест[7]: Проверка вычисления определителя с плавающими точками 
START_TEST(test_determinant_floating_point) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -1.29, EPS);  // 1.5*4.9 - 2.7*3.2

  s21_remove_matrix(&A);
}
END_TEST

// Тест[8]: Проверка вычисления определителя для не квадратной матрицы 
START_TEST(test_determinant_non_square) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 3, &A);

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR );

  s21_remove_matrix(&A);
}
END_TEST

// Тест[9]: Проверка вычисления определителя с NULL-указателем на A 
START_TEST(test_determinant_null_A) {
  double result;

  int status = s21_determinant(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[10]: Проверка вычисления определителя с NULL-указателем на result 
START_TEST(test_determinant_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_determinant(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[11]: Проверка вычисления определителя с некорректными размерами (rows <= 0) 
START_TEST(test_determinant_invalid_rows) {
  matrix_t A;
  double result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[12]: Проверка вычисления определителя с некорректными размерами (columns <= 0) 
START_TEST(test_determinant_invalid_columns) {
  matrix_t A;
  double result;
  A.rows = 2;
  A.columns = -1;
  A.matrix = NULL;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[13]: Проверка вычисления определителя с NULL-указателем на matrix 
START_TEST(test_determinant_null_matrix) {
  matrix_t A;
  double result;
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[14]: Проверка вычисления определителя с максимальными размерами 
START_TEST(test_determinant_max_size) {
  matrix_t A;
  double result;
  int test_size = MAX_MATRIX_SIZE;
  int status_A = s21_create_matrix(test_size, test_size, &A);

  if (status_A == OK) {
    // Заполняем матрицу как диагональную для упрощения вычислений 
    for (int i = 0; i < test_size; i++) A.matrix[i][i] = 2.0;

    int status = s21_determinant(&A, &result);
    ck_assert_int_eq(status, OK);
    // Определитель диагональной матрицы равен произведению диагональных элементов 
    ck_assert_double_eq_tol(result, pow(2.0, test_size), EPS);

    s21_remove_matrix(&A);
  }
}
END_TEST

TCase *tcase_s21_determinant(void) {
  TCase *test_cases = tcase_create("s21_determinant");
  tcase_add_test(test_cases, test_determinant_success_1x1);
  tcase_add_test(test_cases, test_determinant_success_2x2);
  tcase_add_test(test_cases, test_determinant_success_3x3);
  tcase_add_test(test_cases, test_determinant_success_3x3_non_zero);
  tcase_add_test(test_cases, test_determinant_zero_elements);
  tcase_add_test(test_cases, test_determinant_negative_elements);
  tcase_add_test(test_cases, test_determinant_floating_point);
  tcase_add_test(test_cases, test_determinant_non_square);
  tcase_add_test(test_cases, test_determinant_null_A);
  tcase_add_test(test_cases, test_determinant_null_result);
  tcase_add_test(test_cases, test_determinant_invalid_rows);
  tcase_add_test(test_cases, test_determinant_invalid_columns);
  tcase_add_test(test_cases, test_determinant_null_matrix);
  tcase_add_test(test_cases, test_determinant_max_size);
  return test_cases;
}
