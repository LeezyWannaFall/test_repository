// Includes
#include "s21_tetris.h"

// Defines
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define TETROMINO_SIZE 4

typedef struct {
    int shape[TETROMINO_SIZE][TETROMINO_SIZE];
    int x, y;  // позиция левого верхнего угла на поле
} Tetromino;

static Tetromino current;

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
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}
};

static void copyBlock(const int src[4][4], int dest[4][4]) {
    for (int i = 0; i < TETROMINO_SIZE; ++i)
        for (int j = 0; j < TETROMINO_SIZE; ++j)
            dest[i][j] = src[i][j];
}

static void spawnNewTetromino() {
    int r = rand() % 4;

    if (r == 0)
        copyBlock(O_BLOCK, current.shape);
    else if (r == 1)
        copyBlock(I_BLOCK, current.shape);
    else if (r == 2)
        copyBlock(T_BLOCK, current.shape);
    else
        copyBlock(L_BLOCK, current.shape);

    current.x = 3;  // центр по горизонтали
    current.y = 0;  // верх

    state = STATE_MOVE;
}

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

    game.next = NULL; // позже
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
            // пока ничего не делаем
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
            tryMove(1);   // направо
        }
    }

    if (action == Start && state == STATE_START) {
        state = STATE_SPAWN;
    }
}

void tryMove(int dx) {
    // Проверяем, можно ли сдвинуть тетромино
    for (int i = 0; i < TETROMINO_SIZE; ++i) {
        for (int j = 0; j < TETROMINO_SIZE; ++j) {
            if (current.shape[i][j]) {
                int newX = current.x + dx;
                if (newX < 0 || newX >= FIELD_WIDTH || game.field[current.y + i][newX]) {
                    return; // нельзя сдвинуть
                }
            }
        }
    }
    current.x += dx; // сдвигаем тетромино
}

void tryMoveDown(void) {
    // Проверяем, можно ли опустить тетромино
    for (int i = 0; i < TETROMINO_SIZE; ++i) {
        for (int j = 0; j < TETROMINO_SIZE; ++j) {
            if (current.shape[i][j]) {
                int newY = current.y + 1;
                if (newY >= FIELD_HEIGHT || game.field[newY][current.x + j]) {
                    return; // нельзя опустить
                }
            }
        }
    }
    current.y++; // опускаем тетромино
}
