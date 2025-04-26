#include <check.h>

#include "../../s21_matrix.h"

// Тест[1]: Проверка на равенство матриц 
START_TEST(test_eq_matrix_same_matrices) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[2]: Проверка на неравенство матриц с разными размерами 
START_TEST(test_eq_matrix_different_sizes) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[3]: Проверка на неравенство матриц с одинаковыми размерами, но разными элементами 
START_TEST(test_eq_matrix_different_elements) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 5.0;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[4]: Проверка на равенство матриц с учетом погрешности EPSILON 
START_TEST(test_eq_matrix_within_epsilon) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0000001;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест[5]: Проверка на NULL-указатель 
START_TEST(test_eq_matrix_null_pointer) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  result = s21_eq_matrix(NULL, &A);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

// Тест[6]: Проверка на некорректные размеры матриц 
START_TEST(test_eq_matrix_invalid_matrix) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  B.rows = -1;
  B.columns = 2;
  B.matrix = NULL;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

TCase *tcase_s21_eq_matrix(void) {
  TCase *test_cases = tcase_create("s21_eq_matrix");
  tcase_add_test(test_cases, test_eq_matrix_same_matrices);
  tcase_add_test(test_cases, test_eq_matrix_different_sizes);
  tcase_add_test(test_cases, test_eq_matrix_different_elements);
  tcase_add_test(test_cases, test_eq_matrix_within_epsilon);
  tcase_add_test(test_cases, test_eq_matrix_null_pointer);
  tcase_add_test(test_cases, test_eq_matrix_invalid_matrix);
  return test_cases;
}
