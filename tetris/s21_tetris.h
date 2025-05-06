#ifndef S21_TETRIS_H_
#define S21_TETRIS_H_

// INCLUDES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

// DEFINES
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define EPS 1e-6
#define MAX_MATRIX_SIZE 20
#define WIDTH 10
#define HEIGHT 20

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
};
  
typedef struct GameInfo_t {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
};
  
  void userInput(UserAction_t action, bool hold);
  
  GameInfo_t updateCurrentState();
  

#endif // S21_TETRIS_H_