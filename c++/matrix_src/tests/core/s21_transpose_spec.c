#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка транспонирования матрицы 1x1 
START_TEST(test_transpose_success_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 3.0;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 3.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[2]: Проверка транспонирования матрицы 2x2 
START_TEST(test_transpose_success_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[3]: Проверка транспонирования матрицы 3x3 
START_TEST(test_transpose_success_3x3) {
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

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], 7.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], 8.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], 9.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[4]: Проверка транспонирования прямоугольной матрицы 2x3 
START_TEST(test_transpose_success_2x3) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[5]: Проверка транспонирования матрицы с нулевыми элементами 
START_TEST(test_transpose_zero_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[6]: Проверка транспонирования матрицы с отрицательными элементами 
START_TEST(test_transpose_negative_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], -1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -4.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[7]: Проверка транспонирования матрицы с плавающими точками 
START_TEST(test_transpose_floating_point) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.5, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.2, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.7, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.9, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[8]: Проверка транспонирования матрицы с NULL-указателем на A 
START_TEST(test_transpose_null_A) {
  matrix_t result;

  int status = s21_transpose(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[9]: Проверка транспонирования матрицы с NULL-указателем на result 
START_TEST(test_transpose_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_transpose(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[10]: Проверка транспонирования матрицы с некорректными размерами (rows <= 0) 
START_TEST(test_transpose_invalid_rows) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[11]: Проверка транспонирования матрицы с некорректными размерами (columns <= 0) 
START_TEST(test_transpose_invalid_columns) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = -1;
  A.matrix = NULL;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[12]: Проверка транспонирования матрицы с NULL-указателем на matrix 
START_TEST(test_transpose_null_matrix) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[13]: Проверка транспонирования матрицы с максимальными размерами 
START_TEST(test_transpose_max_size) {
  matrix_t A, result;
  int test_size = MAX_MATRIX_SIZE;
  int status_A = s21_create_matrix(test_size, test_size, &A);

  if (status_A == OK) {
    // Заполняем только угловые элементы для ускорения 
    A.matrix[0][0] = 1.0;
    A.matrix[0][test_size - 1] = 2.0;
    A.matrix[test_size - 1][0] = 3.0;
    A.matrix[test_size - 1][test_size - 1] = 4.0;

    int status = s21_transpose(&A, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_int_eq(result.rows, test_size);
    ck_assert_int_eq(result.columns, test_size);

    // Проверяем только угловые элементы 
    ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
    ck_assert_double_eq_tol(result.matrix[test_size - 1][0], 2.0, EPS);
    ck_assert_double_eq_tol(result.matrix[0][test_size - 1], 3.0, EPS);
    ck_assert_double_eq_tol(result.matrix[test_size - 1][test_size - 1], 4.0,
                            EPS);

    s21_remove_matrix(&result);
  }

  if (status_A == OK) s21_remove_matrix(&A);
}
END_TEST

// Тест[14]: Проверка транспонирования матрицы с максимальными размерами (прямоугольная) 
START_TEST(test_transpose_max_size_rectangular) {
  matrix_t A, result;
  int rows = MAX_MATRIX_SIZE;
  // Проверяем прямоугольную матрицу 
  int columns = MAX_MATRIX_SIZE / 2;
  int status_A = s21_create_matrix(rows, columns, &A);

  if (status_A == OK) {
    // Заполняем только угловые элементы для ускорения 
    A.matrix[0][0] = 1.0;
    A.matrix[0][columns - 1] = 2.0;
    A.matrix[rows - 1][0] = 3.0;
    A.matrix[rows - 1][columns - 1] = 4.0;

    int status = s21_transpose(&A, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_int_eq(result.rows, columns);
    ck_assert_int_eq(result.columns, rows);

    // Проверяем только угловые элементы 
    ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);
    ck_assert_double_eq_tol(result.matrix[columns - 1][0], 2.0, EPS);
    ck_assert_double_eq_tol(result.matrix[0][rows - 1], 3.0, EPS);
    ck_assert_double_eq_tol(result.matrix[columns - 1][rows - 1], 4.0,
                            EPS);

    s21_remove_matrix(&result);
  }

  if (status_A == OK) s21_remove_matrix(&A);
}
END_TEST

TCase *tcase_s21_transpose(void) {
  TCase *test_cases = tcase_create("s21_transpose");
  tcase_add_test(test_cases, test_transpose_success_1x1);
  tcase_add_test(test_cases, test_transpose_success_2x2);
  tcase_add_test(test_cases, test_transpose_success_3x3);
  tcase_add_test(test_cases, test_transpose_success_2x3);
  tcase_add_test(test_cases, test_transpose_zero_elements);
  tcase_add_test(test_cases, test_transpose_negative_elements);
  tcase_add_test(test_cases, test_transpose_floating_point);
  tcase_add_test(test_cases, test_transpose_null_A);
  tcase_add_test(test_cases, test_transpose_null_result);
  tcase_add_test(test_cases, test_transpose_invalid_rows);
  tcase_add_test(test_cases, test_transpose_invalid_columns);
  tcase_add_test(test_cases, test_transpose_null_matrix);
  tcase_add_test(test_cases, test_transpose_max_size);
  tcase_add_test(test_cases, test_transpose_max_size_rectangular);
  return test_cases;
}
