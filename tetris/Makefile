all: start_game

start_game:
	gcc -o tetris guii/cli/gui.c brickgame/tetris/s21_tetris.c -lncurses
	./tetris
clean:
	rm -f tetris

.PHONY: all start_game clean