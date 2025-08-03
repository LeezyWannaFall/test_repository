#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "../../brickgame/tetris/s21_tetris.h"

#define DELAY 100000  // задержка между кадрами (микросекунды)

void drawGame(const GameInfo_t game, const Tetromino current);

int main() {
    srand(time(NULL));

    initscr();              // инициализация ncurses
    noecho();               // не показывать нажатия клавиш
    cbreak();               // не ждать Enter
    keypad(stdscr, TRUE);   // включить стрелки
    nodelay(stdscr, TRUE);  // getch() не блокирует
    curs_set(FALSE);        // скрыть курсор

    GameInfo_t game = updateCurrentState();  // START → SPAWN
    game = updateCurrentState();             // SPAWN → MOVE

    while (1) {
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                userInput(Left, false);
                break;
            case KEY_RIGHT:
                userInput(Right, false);
                break;
            case KEY_DOWN:
                userInput(Down, false);
                break;
            case 'q':
                endwin();
                printf("Exiting...\n");
                return 0;
        }

        game = updateCurrentState();
        Tetromino t = getCurrentTetromino();
        clear();
        drawGame(game, t);  // ← мы напишем её
        refresh();
        usleep(DELAY);
    }

    endwin();
    return 0;
}

void drawGame(const GameInfo_t game, const Tetromino current) {
    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            if (game.field[y][x])
                mvprintw(y, x * 2, "[]");
            else
                mvprintw(y, x * 2, " .");
        }
    }

    // текущая фигура
    for (int i = 0; i < TETROMINO_SIZE; ++i) {
        for (int j = 0; j < TETROMINO_SIZE; ++j) {
            if (current.shape[i][j]) {
                int y = current.y + i;
                int x = current.x + j;
                if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH)
                    mvprintw(y, x * 2, "[]");
            }
        }
    }
}
