#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../brickgame/tetris/s21_tetris.h"

#define DELAY 100000  // задержка между кадрами (микросекунды)

void drawGame(const GameInfo_t game, const Tetromino current);

int main() {
  srand(time(NULL));

  initscr();  // инициализация ncurses
  noecho();   // не показывать нажатия клавиш
  cbreak();   // не ждать Enter
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
      case 'Q':  
      case 'q':
        endwin();
        printf("Exiting...\n");
        return 0;
      case 'R':
      case 'r':
        userInput(Restart, false);
        break;
      case 'P':
      case 'p': 
        userInput(Pause, false);
        break;
    }

    game = updateCurrentState();

    if (game.pause == -1) {
      clear();
      mvprintw(
          FIELD_HEIGHT / 2, FIELD_WIDTH,
          "GAME OVER\n      Press 'q' to exit.\n      Press 'r' to restart.");
      refresh();
      usleep(500000);  // полсекунды паузы
      continue;        // не делаем больше ничего
    }

    Tetromino t = getCurrentTetromino();
    clear();
    drawGame(game, t);
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

  // Информация справа
  int info_x = FIELD_WIDTH * 2 + 4;  // правее от поля начиная с 22+4 клетки
  int info_y = 2;

  // Рисуем next фигуру справа
  mvprintw(info_y + 7, info_x, "Next:");
  mvprintw(info_y - 1, info_x, "=== TETRIS ===");
  mvprintw(info_y + 0, info_x, "Score:      %d", game.score);
  mvprintw(info_y + 1, info_x, "High Score: %d", game.high_score);
  mvprintw(info_y + 2, info_x, "Level:      %d", game.level);
  mvprintw(info_y + 3, info_x, "Speed:      %d", game.speed);

  if (game.pause) mvprintw(info_y + 5, info_x, "=== PAUSED ===");

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
