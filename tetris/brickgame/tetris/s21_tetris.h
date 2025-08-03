#ifndef S21_TETRIS_H
#define S21_TETRIS_H

// Includes
#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>  // для rand()
#include <stdio.h>
#include <stdbool.h>

// Structrs
typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct GameInfo_t {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;


// Functions
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);


#endif // S21_TETRIS_H