// Includes
#include "s21_tetris.h"

typedef enum {
  STATE_START,
  STATE_SPAWN_NEXT_FIGURE,
  STATE_SPAWN,
  STATE_MOVE,
  STATE_SHIFT,
  STATE_CONNECT,
  STATE_PAUSE,
  STATE_GAME_OVER
} GameState;

static GameInfo_t game;
static GameState state = STATE_START;
static Tetromino current;
static Tetromino newTetromino = {0};
static Tetromino queue[QUEUE_SIZE];

Tetromino getCurrentTetromino(void) {
  return current;  // возвращаем копию current
}

Tetromino getNewTetromino(void) {
  return newTetromino;  // возвращаем копию next
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


static void spawnNextTetromino() {
  for (int i = 0; i < QUEUE_SIZE - 1; ++i) {
    queue[i] = queue[i + 1];
  }

  int RandomValue = rand() % 7;
  if (RandomValue == 0) {
    copyBlock(O_BLOCK, newTetromino.shape);
  } else if (RandomValue == 1) {
    copyBlock(I_BLOCK, newTetromino.shape);
  } else if (RandomValue == 2) {
    copyBlock(T_BLOCK, newTetromino.shape);
  } else if (RandomValue == 3) {
    copyBlock(L_BLOCK, newTetromino.shape);
  } else if (RandomValue == 4) {
    copyBlock(J_BLOCK, newTetromino.shape);
  } else if (RandomValue == 5) {
    copyBlock(S_BLOCK, newTetromino.shape);
  } else { 
    copyBlock(Z_BLOCK, newTetromino.shape);
  }

  newTetromino.x = 12;
  newTetromino.y = 10;
  queue[QUEUE_SIZE - 1] = newTetromino;
  state = STATE_SPAWN;
}

static void spawnCurrentTetromino() {
  current = queue[0];
  current.x = 3;  // центр по горизонтали
  current.y = 0;  // верх
  state = STATE_MOVE;
}

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

  game.next =  malloc(TETROMINO_SIZE * sizeof(int *));
  for (int i = 0; i < TETROMINO_SIZE; ++i) {
    game.next[i] = calloc(TETROMINO_SIZE, sizeof(int));
  }

  for (int i = 0; i < QUEUE_SIZE; ++i) {
    spawnNextTetromino();
  }
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
}

void freeField(void) {
  if (!game.field) return;

  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    if (game.field[i]) {
      free(game.field[i]);
      game.field[i] = NULL;
    }
  }
  free(game.field);
  game.field = NULL;
}

void freeNext(void) {
  if (!game.next) return;

  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    if (game.next[i]) {
      free(game.next[i]);
      game.next[i] = NULL;
    }
  }
  free(game.next);
  game.next = NULL;
}

void rotateTetromino(Tetromino *src, Tetromino *dest) {
  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      dest->shape[i][j] = src->shape[TETROMINO_SIZE - 1 - j][i];
    }
  }
}


void tryRotate(void) {
  Tetromino tmp = {0};
  tmp.x = current.x;
  tmp.y = current.y;
  rotateTetromino(&current, &tmp);

  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      if (tmp.shape[i][j]) {
        int newX = tmp.x + j;
        int newY = tmp.y + i;

        if (newX < 0 || newX >= FIELD_WIDTH || newY < 0 || newY >= FIELD_HEIGHT)
          return;

        if (game.field[newY][newX])
          return;
      }
    }
  }

  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      current.shape[i][j] = tmp.shape[i][j];
    }
  }
}

static unsigned long lastFallMs = 0;
static int fallDelay = 1000; // между падениями 1 сек

unsigned long currentTimeMs() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

GameInfo_t updateCurrentState(void) {
  if (state == STATE_PAUSE) {
    return game;
  }

  switch (state) {
    case STATE_START:
      initField();
      state = STATE_SPAWN_NEXT_FIGURE;
      break;
    case STATE_SPAWN_NEXT_FIGURE:
      spawnNextTetromino();
      state = STATE_SPAWN;
      break;
    case STATE_SPAWN:
      spawnCurrentTetromino();
      state = STATE_MOVE;
      break;
    case STATE_MOVE: {
      unsigned long now = currentTimeMs();
      if (now - lastFallMs >= (unsigned long)fallDelay) {
        tryMoveDown(); 
        lastFallMs = now;
      }
    } break;
    case STATE_CONNECT:
      placeCurrentToField();
      updateScore(clearLine());  // очищаем линии и обновляем счет

      for (int j = 0; j < FIELD_WIDTH; ++j) {
        if (game.field[1][j]) {
          state = STATE_GAME_OVER;
          return game;
        }
      }

      state = STATE_SPAWN_NEXT_FIGURE;
      break;
    case STATE_GAME_OVER:
      freeField();
      // freeNext();
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
    } else if (action == Rotate) {
      tryRotate(); // поворот фигуры
    }
  }

  game.pause = (state == STATE_PAUSE) ? 1 : 0;

  if (action == Pause) {
    if (state == STATE_MOVE || state == STATE_SPAWN) {
      state = STATE_PAUSE;
    } else if (state == STATE_PAUSE) {
      state = STATE_MOVE;  // продолжаем игру
    }
  }

  if (action == Restart && state == STATE_GAME_OVER) {
    freeField();
    state = STATE_START;
  }
}
