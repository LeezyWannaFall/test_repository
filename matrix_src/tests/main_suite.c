#include <check.h>

//  CORE IMPORT
#include "./core/s21_calc_complements_spec.c"
#include "./core/s21_create_matrix_spec.c"
#include "./core/s21_determinant_spec.c"
#include "./core/s21_eq_matrix_spec.c"
#include "./core/s21_inverse_matrix_spec.c"
#include "./core/s21_mult_matrix_spec.c"
#include "./core/s21_mult_number_spec.c"
#include "./core/s21_remove_matrix_spec.c"
#include "./core/s21_sub_matrix_spec.c"
#include "./core/s21_sum_matrix_spec.c"
#include "./core/s21_transpose_spec.c"

//  HELPERS IMPORT
#include "./helpers/s21_init_matrix_spec.c"

//  ARITHMETICS SUITE
Suite *core_suite(void) {
  Suite *cr_suite = suite_create("core_suite");
  suite_add_tcase(cr_suite, tcase_s21_create_matrix());
  suite_add_tcase(cr_suite, tcase_s21_remove_matrix());
  suite_add_tcase(cr_suite, tcase_s21_eq_matrix());
  suite_add_tcase(cr_suite, tcase_s21_sum_matrix());
  suite_add_tcase(cr_suite, tcase_s21_sub_matrix());
  suite_add_tcase(cr_suite, tcase_s21_mult_number());
  suite_add_tcase(cr_suite, tcase_s21_mult_matrix());
  suite_add_tcase(cr_suite, tcase_s21_transpose());
  suite_add_tcase(cr_suite, tcase_s21_calc_complements());
  suite_add_tcase(cr_suite, tcase_s21_determinant());
  suite_add_tcase(cr_suite, tcase_s21_inverse_matrix());
  return cr_suite;
}


//  HELPERS SUITE
Suite *helpers_suite(void) {
  Suite *help_suite = suite_create("helpers_suite");
  suite_add_tcase(help_suite, tcase_s21_init_matrix());
  return help_suite;
}

int main(void) {
  int failed_count;
  //  CORE RUNNER
  Suite *core = core_suite();
  SRunner *runner_core = srunner_create(core);
  srunner_run_all(runner_core, CK_NORMAL);
  failed_count = srunner_ntests_failed(runner_core);
  srunner_free(runner_core);
  //  HELPERS RUNNER
  Suite *help = helpers_suite();
  SRunner *runner_help = srunner_create(help);
  srunner_run_all(runner_help, CK_NORMAL);
  failed_count = srunner_ntests_failed(runner_help);
  srunner_free(runner_help);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
