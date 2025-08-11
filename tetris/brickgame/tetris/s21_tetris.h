#ifndef S21_TETRIS_H
#define S21_TETRIS_H

// Includes
#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // для rand()
#include <unistd.h>  // для usleep()
#include <sys/time.h> // для gettimeofday

// Defines
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define TETROMINO_SIZE 4
#define DELAY 50000  // задержка между кадрами (микросекунды)

// Structrs
typedef struct {
  int shape[TETROMINO_SIZE][TETROMINO_SIZE];
  int x, y;  // позиция левого верхнего угла на поле
} Tetromino;

typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Restart,
  Rotate,
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
Tetromino getCurrentTetromino(void);
Tetromino getNextTetromino(void);
void freeField(void);

#endif  // S21_TETRIS_H