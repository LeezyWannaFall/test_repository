#ifndef S21_TETRIS_H_
#define S21_TETRIS_H_

// INCLUDES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

// DEFINES
#define WIDTH 10
#define HEIGHT 20

// TYPES
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
  
void userInput(UserAction_t action, bool hold);
  
GameInfo_t updateCurrentState();
  

#endif // S21_TETRIS_H_