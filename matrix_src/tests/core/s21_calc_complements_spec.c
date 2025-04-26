#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка вычисления матрицы алгебраических дополнений для матрицы 1x1 
START_TEST(test_calc_complements_success_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 5.0;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[2]: Проверка вычисления матрицы алгебраических дополнений для матрицы 2x2 
START_TEST(test_calc_complements_success_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, EPS);   // 1,1
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, EPS);  // 1,2
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, EPS);  // 2,1
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, EPS);   // 2,2

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[3]: Проверка вычисления матрицы алгебраических дополнений для матрицы 3x3 
START_TEST(test_calc_complements_success_3x3) {
  matrix_t A, result;
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

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 10.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], -20.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -14.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], 8.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], -8.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], 4.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[4]: Проверка вычисления матрицы алгебраических дополнений с нулевыми элементами 
START_TEST(test_calc_complements_zero_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;

  int status = s21_calc_complements(&A, &result);
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

// Тест[5]: Проверка вычисления матрицы алгебраических дополнений отрицательными элементами 
START_TEST(test_calc_complements_negative_elements) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], -4.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -1.0, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[6]: Проверка вычисления матрицы алгебраических дополнений с плавающими точками 
START_TEST(test_calc_complements_floating_point) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.7;
  A.matrix[1][0] = 3.2;
  A.matrix[1][1] = 4.9;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 4.9, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.2, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.7, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.5, EPS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест[7]: Проверка вычисления матрицы алгебраических дополнений для неквадратной матрицы 
START_TEST(test_calc_complements_non_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, CALCULATION_ERROR );

  s21_remove_matrix(&A);
}
END_TEST

// Тест[8]: Проверка вычисления матрицы алгебраических дополнений с NULL-указателем на A 
START_TEST(test_calc_complements_null_A) {
  matrix_t result;

  int status = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[9]: Проверка вычисления матрицы алгебраических дополнений с NULL-указателем на result 
START_TEST(test_calc_complements_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[10]: Проверка вычисления матрицы алгебраических дополнений с некорректными размерами (rows <= 0) 
START_TEST(test_calc_complements_invalid_rows) {
  matrix_t A, result;
  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[11]: Проверка вычисления матрицы алгебраических дополнений с некорректными размерами (columns <= 0) 
START_TEST(test_calc_complements_invalid_columns) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = -1;
  A.matrix = NULL;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[12]: Проверка вычисления матрицы алгебраических дополнений с NULL-указателем на matrix 
START_TEST(test_calc_complements_null_matrix) {
  matrix_t A, result;
  A.rows = 2;
  A.columns = 2;
  A.matrix = NULL;

  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

// Тест[13]: Проверка вычисления матрицы алгебраических дополнений с максимальными размерами 
START_TEST(test_calc_complements_max_size) {
  matrix_t A, result;
  int test_size = MAX_MATRIX_SIZE;

  // C[0][0] = 4.0 
  int status_A = s21_create_matrix(test_size, test_size, &A);
  if (status_A == OK) {
    for (int i = 0; i < test_size; i++) {
      for (int j = 0; j < test_size; j++) {
        A.matrix[i][j] = 0.0;
      }
    }

    // M[0][0] = 4.0 
    A.matrix[1][1] = 2.0;
    A.matrix[2][2] = 2.0;
    for (int i = 3; i < test_size; i++) {
      A.matrix[i][i] = 1.0;
    }

    int status = s21_calc_complements(&A, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_int_eq(result.rows, test_size);
    ck_assert_int_eq(result.columns, test_size);

    // C[0][0] = 4.0 
    ck_assert_double_eq_tol(result.matrix[0][0], pow(-1, 0 + 0) * 4.0,
                            EPS);

    s21_remove_matrix(&result);
    s21_remove_matrix(&A);
  }

  // C[0][n-1] = 3.0 * (-1)^{0 + (n-1)} 
  status_A = s21_create_matrix(test_size, test_size, &A);
  if (status_A == OK) {
    for (int i = 0; i < test_size; i++) {
      for (int j = 0; j < test_size; j++) {
        A.matrix[i][j] = 0.0;
      }
    }

    // M[0][n-1] = 3.0 
    for (int i = 1; i < test_size - 1; i++) {
      A.matrix[i][i] = 1.0;
    }
    // M[0][n-1] 
    A.matrix[test_size - 1][0] = 3.0;

    int status = s21_calc_complements(&A, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_int_eq(result.rows, test_size);
    ck_assert_int_eq(result.columns, test_size);

    // C[0][n-1] = 3.0 * (-1)^{0 + (n-1)} 
    ck_assert_double_eq_tol(result.matrix[0][test_size - 1],
                            pow(-1, 0 + test_size - 1) * 3.0, EPS);

    s21_remove_matrix(&result);
    s21_remove_matrix(&A);
  }

  // C[n-1][0] = 2.0 * (-1)^{n-1 + 0} 
  status_A = s21_create_matrix(test_size, test_size, &A);
  if (status_A == OK) {
    for (int i = 0; i < test_size; i++) {
      for (int j = 0; j < test_size; j++) {
        A.matrix[i][j] = 0.0;
      }
    }

    // M[n-1][0] = 2.0 
    for (int i = 1; i < test_size - 1; i++) {
      A.matrix[i][i] = 1.0;
    }
    // M[n-1][0] 
    A.matrix[0][test_size - 1] = 2.0;

    int status = s21_calc_complements(&A, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_int_eq(result.rows, test_size);
    ck_assert_int_eq(result.columns, test_size);

    // C[n-1][0] = 2.0 * (-1)^{n-1 + 0} 
    ck_assert_double_eq_tol(result.matrix[test_size - 1][0],
                            pow(-1, test_size - 1 + 0) * 2.0, EPS);

    s21_remove_matrix(&result);
    s21_remove_matrix(&A);
  }

  // C[n-1][n-1] = 1.0 * (-1)^{n-1 + n-1} 
  status_A = s21_create_matrix(test_size, test_size, &A);
  if (status_A == OK) {
    for (int i = 0; i < test_size; i++) {
      for (int j = 0; j < test_size; j++) {
        A.matrix[i][j] = 0.0;
      }
    }

    // Заполняем матрицу A так, чтобы M[n-1][n-1] = 1.0 
    for (int i = 0; i < test_size - 1; i++) {
      A.matrix[i][i] = 1.0;
    }

    int status = s21_calc_complements(&A, &result);
    ck_assert_int_eq(status, OK);
    ck_assert_int_eq(result.rows, test_size);
    ck_assert_int_eq(result.columns, test_size);

    // C[n-1][n-1] = 1.0 * (-1)^{n-1 + n-1} 
    ck_assert_double_eq_tol(result.matrix[test_size - 1][test_size - 1],
                            pow(-1, test_size - 1 + test_size - 1) * 1.0,
                            EPS);

    s21_remove_matrix(&result);
    s21_remove_matrix(&A);
  }
}
END_TEST

TCase *tcase_s21_calc_complements(void) {
  TCase *test_cases = tcase_create("s21_calc_complements");
  tcase_add_test(test_cases, test_calc_complements_success_1x1);
  tcase_add_test(test_cases, test_calc_complements_success_2x2);
  tcase_add_test(test_cases, test_calc_complements_success_3x3);
  tcase_add_test(test_cases, test_calc_complements_zero_elements);
  tcase_add_test(test_cases, test_calc_complements_negative_elements);
  tcase_add_test(test_cases, test_calc_complements_floating_point);
  tcase_add_test(test_cases, test_calc_complements_non_square);
  tcase_add_test(test_cases, test_calc_complements_null_A);
  tcase_add_test(test_cases, test_calc_complements_null_result);
  tcase_add_test(test_cases, test_calc_complements_invalid_rows);
  tcase_add_test(test_cases, test_calc_complements_invalid_columns);
  tcase_add_test(test_cases, test_calc_complements_null_matrix);
  tcase_add_test(test_cases, test_calc_complements_max_size);
  return test_cases;
}
