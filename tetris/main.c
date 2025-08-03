#include <stdio.h>
#include "brickgame/tetris/s21_tetris.h"

int main() {
    srand(time(NULL));
    GameInfo_t g = updateCurrentState();
    printf("Score: %d, Level: %d\n", g.score, g.level);
    return 0;
}
