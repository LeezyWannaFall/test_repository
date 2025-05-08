CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

TETRIS = s21_tetris

RM = rm -rf

SRC = $(wildcard brickgame/tetris/*.c)

OBJ = $(patsubst %.c, %.o, $(SRC))

all: clean $(TETRIS)

$(TETRIS): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TETRIS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) s21_tetris brickgame/tetris/*.o	