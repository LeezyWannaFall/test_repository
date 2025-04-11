#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка нахождения обратной матрицы для матрицы 1x1 
START_TEST(test_inverse_matrix_success_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 2.0;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.5, EPS);  // 1/2

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[2]: Проверка нахождения обратной матрицы для матрицы 2x2 
START_TEST(test_inverse_matrix_success_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);

  // Обратная матрица для [[1, 2], [3, 4]] = [[-2, 1], [1.5, -0.5]]
  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.5, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[3]: Проверка нахождения обратной матрицы для матрицы 3x3 
START_TEST(test_inverse_matrix_success_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);

  // Обратная матрица для [[1, 2, 3], [0, 1, 4], [5, 6, 0]]
  // = [[-24, 18, 5], [20, -15, -4], [-5, 4, 1]]
  ck_assert_double_eq_tol(result.matrix[0][0], -24.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 18.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], 5.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 20.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -15.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], -4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], -5.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], 1.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[4]: Проверка нахождения обратной матрицы с нулевыми элементами 
START_TEST(test_inverse_matrix_zero_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);

  // Обратная матрица для [[0, 1], [1, 0]] = [[0, 1], [1, 0]]
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[5]: Проверка нахождения обратной матрицы с отрицательными элементами 
START_TEST(test_inverse_matrix_negative_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);

  // Обратная матрица для [[-1, -2], [-3, -4]] = [[2, -1], [-1.5, 0.5]]
  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -1.5, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.5, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[6]: Проверка нахождения обратной матрицы с плавающей точкой 
START_TEST(test_inverse_matrix_floating_point) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);

  // [[1.5, 2.7], [3.2, 4.9]] 
  // [[-3.798449612403101, 2.0930232558139537], [2.4806201550387597, -1.1627906976744186]] 
  ck_assert_double_eq_tol(result.matrix[0][0], -3.798449612403101, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0930232558139537, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.4806201550387597, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -1.1627906976744186, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[7]: Проверка на матрицу с определителем, равным 0 (обратной не существует) 
START_TEST(test_inverse_matrix_zero_determinant) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  // 1*4 - 2*2 = 0 
  A.matrix[1][1] = 4.0;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR );

  s21_remove_matrix(&A);
}
END_TEST

// Тест[8]: Проверка на неквадратную матрицу (обратной не существует) 
START_TEST(test_inverse_matrix_non_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR );

  s21_remove_matrix(&A);
}
END_TEST

// Тест[9]: Проверка на NULL указатель A 
START_TEST(test_inverse_matrix_null_A) {
  matrix_t result;

  int status = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[10]: Проверка на NULL указатель result 
START_TEST(test_inverse_matrix_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[11]: Проверка на матрицу с некорректными размерами (отрицательные строки) 
START_TEST(test_inverse_matrix_invalid_rows) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[12]: Проверка на матрицу с некорректными размерами (отрицательные столбцы) 
START_TEST(test_inverse_matrix_invalid_columns) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = -1;
  A.matrix = NULL;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[13]: Проверка на матрицу с NULL указателем matrix 
START_TEST(test_inverse_matrix_null_matrix) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[14]: Проверка нахождения обратной матрицы с максимальными размерами 
START_TEST(test_inverse_matrix_max_size) {
  matrix_t A, result;
  int test_size = MAX_MATRIX_SIZE;
  int status_A = s21_create_matrix(test_size, test_size, &A);

  if (status_A == OK) {
    // 1/a[i][i] 
    for (int i = 0; i < test_size; i++) {
      for (int j = 0; j < test_size; j++) {
        A.matrix[i][j] = (i == j) ? (double)(i + 1) : 0.0;
      }
    }

    int status = s21_inverse_matrix(&A, &result);
    ck_assert_int_eq(status, OK);

    ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);  // 1/1
    ck_assert_double_eq_tol(result.matrix[1][1], 0.5, EPS);  // 1/2
    ck_assert_double_eq_tol(result.matrix[test_size - 1][test_size - 1],
                            1.0 / test_size, EPS);  // 1/n
    ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPS);
    ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPS);

    s21_remove_matrix(&result);
  }

  if (status_A == OK) s21_remove_matrix(&A);
}
END_TEST

TCase *tcase_s21_inverse_matrix(void) {
  TCase *test_cases = tcase_create("s21_inverse_matrix");
  tcase_add_test(test_cases, test_inverse_matrix_success_1x1);
  tcase_add_test(test_cases, test_inverse_matrix_success_2x2);
  tcase_add_test(test_cases, test_inverse_matrix_success_3x3);
  tcase_add_test(test_cases, test_inverse_matrix_zero_elements);
  tcase_add_test(test_cases, test_inverse_matrix_negative_elements);
  tcase_add_test(test_cases, test_inverse_matrix_floating_point);
  tcase_add_test(test_cases, test_inverse_matrix_zero_determinant);
  tcase_add_test(test_cases, test_inverse_matrix_non_square);
  tcase_add_test(test_cases, test_inverse_matrix_null_A);
  tcase_add_test(test_cases, test_inverse_matrix_null_result);
  tcase_add_test(test_cases, test_inverse_matrix_invalid_rows);
  tcase_add_test(test_cases, test_inverse_matrix_invalid_columns);
  tcase_add_test(test_cases, test_inverse_matrix_null_matrix);
  tcase_add_test(test_cases, test_inverse_matrix_max_size);
  return test_cases;
}
