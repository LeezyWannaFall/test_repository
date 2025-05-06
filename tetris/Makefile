CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

TETRIS = s21_tetris

RM = rm -rf

SRC = $(wildcard core/*.c)

OBJ = $(patsubst %.c, %.o, $(SRC))

$(TETRIS): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TETRIS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) s21_tetris core/*.o	