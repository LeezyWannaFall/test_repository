#include <check.h>
#include "../brick_game/tetris/s21_tetris.h"

START_TEST(backend) {
  // Initialize the game state
  game = updateCurrentState();
  
  // Check initial state
  ck_assert_int_eq(game.score, 0);
  ck_assert_int_eq(game.level, 1);
  ck_assert_int_eq(game.speed, 1000);
  
  // Simulate user input to start the game
  userInput(Start, false);
  
  // Check if the game state has changed to SPAWN_NEXT_FIGURE
  ck_assert_int_eq(state, STATE_SPAWN_NEXT_FIGURE);
  
  // Simulate spawning a new tetromino
  spawnNextTetromino();
  
  // Check if the new tetromino is set correctly
  Tetromino nextTetromino = getNewTetromino();
  ck_assert_int_eq(nextTetromino.shape[1][1], 1); // Example check for O_BLOCK
  
  // Simulate placing the tetromino on the field
  userInput(Down, false);
  
  // Check if the tetromino was placed correctly
  ck_assert_int_eq(game.field[19][4], nextTetromino.shape[1][1]);
}
END_TEST


int main(void) {
  Suite *s;
  SRunner *sr;

  s = suite_create("Tetris Tests");
  
  // Add test cases to the suite
  // Example: suite_add_tcase(s, tcase_create("Test Case Name"));
  suite_add_tcase(s, tcase_create("backend"));

  sr = srunner_create(s);
  
  // Run all tests
  srunner_run_all(sr, CK_NORMAL);
  
  // Check if any tests failed
  int number_failed = srunner_ntests_failed(sr);
  
  // Free resources
  srunner_free(sr);
  
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}