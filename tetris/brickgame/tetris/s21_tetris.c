// Includes
#include "s21_tetris.h"

typedef enum {
  STATE_START,
  STATE_SPAWN,
  STATE_MOVE,
  STATE_SHIFT,
  STATE_CONNECT,
  STATE_GAME_OVER
} GameState;

static GameInfo_t game;
static GameState state = STATE_START;

static Tetromino current;

Tetromino getCurrentTetromino(void) {
  return current;  // возвращаем копию
}

static const int O_BLOCK[4][4] = {
  {0, 0, 0, 0}, 
  {0, 1, 1, 0}, 
  {0, 1, 1, 0}, 
  {0, 0, 0, 0}
};

static const int I_BLOCK[4][4] = {
  {0, 0, 0, 0}, 
  {1, 1, 1, 1}, 
  {0, 0, 0, 0}, 
  {0, 0, 0, 0}
};

static const int T_BLOCK[4][4] = {
  {0, 0, 0, 0}, 
  {0, 1, 0, 0}, 
  {1, 1, 1, 0}, 
  {0, 0, 0, 0}
};

static const int L_BLOCK[4][4] = {
  {0, 0, 0, 0}, 
  {1, 0, 0, 0}, 
  {1, 1, 1, 0}, 
  {0, 0, 0, 0}
};

static const int J_BLOCK[4][4] = {
  {0, 0, 0, 0},
  {0, 0, 1, 0}, 
  {1, 1, 1, 0}, 
  {0, 0, 0, 0}
};

static const int S_BLOCK[4][4] = {
  {0, 0, 0, 0}, 
  {0, 1, 1, 0}, 
  {1, 1, 0, 0}, 
  {0, 0, 0, 0}
};

static const int Z_BLOCK[4][4] = {
  {0, 0, 0, 0}, 
  {1, 1, 0, 0}, 
  {0, 1, 1, 0}, 
  {0, 0, 0, 0}
};


static void copyBlock(const int src[4][4], int dest[4][4]) {
  for (int i = 0; i < TETROMINO_SIZE; ++i)
    for (int j = 0; j < TETROMINO_SIZE; ++j) dest[i][j] = src[i][j];
}


static void spawnNewTetromino() {
  int r = rand() % 7;

  if (r == 0)
    copyBlock(O_BLOCK, current.shape);
  else if (r == 1)
    copyBlock(I_BLOCK, current.shape);
  else if (r == 2)
    copyBlock(T_BLOCK, current.shape);
  else if (r == 3)
    copyBlock(L_BLOCK, current.shape);
  else if (r == 4)
    copyBlock(J_BLOCK, current.shape);
  else if (r == 5)
    copyBlock(S_BLOCK, current.shape);
  else 
    copyBlock(Z_BLOCK, current.shape);

  current.x = 3;  // центр по горизонтали
  current.y = 0;  // верх

  state = STATE_MOVE;
}

// Функция для инициализации пустого поля
static void initField(void) {
  game.field = malloc(FIELD_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    game.field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  game.score = 0;
  game.high_score = 0;
  game.level = 1;
  game.speed = 1;
  game.pause = 0;

  game.next = NULL;  // later
}

static void tryMove(int dx) {
  int newX = current.x + dx;
  for (int i = 0; i < TETROMINO_SIZE; ++i) {
    for (int j = 0; j < TETROMINO_SIZE; ++j) {
      if (current.shape[i][j]) {
        int x = newX + j;
        int y = current.y + i;

        if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) return;
        if (game.field[y][x]) return;
      }
    }
  }

  current.x = newX;
}

static void tryMoveDown(void) {
  int newY = current.y + 1;
  for (int i = 0; i < TETROMINO_SIZE; ++i) {
    for (int j = 0; j < TETROMINO_SIZE; ++j) {
      if (current.shape[i][j]) {
        int x = current.x + j;
        int y = newY + i;

        if (y >= FIELD_HEIGHT || game.field[y][x]) {
          state = STATE_CONNECT;
          return;
        }
      }
    }
  }

  current.y = newY;
}

static void placeCurrentToField(void) {
  for (int i = 0; i < TETROMINO_SIZE; ++i) {
    for (int j = 0; j < TETROMINO_SIZE; ++j) {
      if (current.shape[i][j]) {
        int x = current.x + j;
        int y = current.y + i;

        if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH)
          game.field[y][x] = 1;
      }
    }
  }
}

static int clearLine(void) {
  int clearedLines = 0;

  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    bool full = true;
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (game.field[i][j] == 0) {
        full = false;
        break;
      }
    }

    if (full) {
      clearedLines++;
      for (int y = i; y > 0; y--) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
          game.field[y][x] = game.field[y - 1][x];
        }
      }

      for (int x = 0; x < FIELD_WIDTH; x++) {
        game.field[0][x] = 0;  // очищаем верхнюю строку
      }
      i++;
    }
  }
  return clearedLines;
}

void updateScore(int clearedLines) {
  game.score += clearedLines * 100;  // 100 очков за каждую очищенную линию
  if (game.score > game.high_score) {
    game.high_score = game.score;  // обновляем рекорд
  }

  // // Увеличиваем уровень и скорость каждые 500 очков
  // if (game.score / 500 > game.level - 1) {
  //   game.level++;
  //   game.speed = (game.level - 1) * 10 + 1;  // скорость увеличивается с уровнем
  // }
}

GameInfo_t updateCurrentState(void) {
  switch (state) {
    case STATE_START:
      initField();
      state = STATE_SPAWN;
      break;
    case STATE_SPAWN:
      spawnNewTetromino();
      state = STATE_MOVE;
      break;
    case STATE_MOVE:
      break;
    case STATE_CONNECT:
      placeCurrentToField();
      updateScore(clearLine());  // очищаем линии и обновляем счет

      for (int j = 0; j < FIELD_WIDTH; ++j) {
        if (game.field[1][j]) {
          state = STATE_GAME_OVER;
          return game;
        }
      }

      state = STATE_SPAWN;
      break;
    case STATE_GAME_OVER:
      game.pause = -1;  // сигнализируем о завершении игры
      break;
    default:
      break;
  }

  return game;
}

void userInput(UserAction_t action, bool hold) {
  if (state == STATE_MOVE) {
    if (action == Left) {
      tryMove(-1);  // налево
    } else if (action == Right) {
      tryMove(1);  // направо
    } else if (action == Down) {
      tryMoveDown();  // вниз
    }
  }

  if (action == Start && state == STATE_START) {
    state = STATE_SPAWN;
  }

  if (action == Restart && state == STATE_GAME_OVER) {
    state = STATE_START;
  }
}
