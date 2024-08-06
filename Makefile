CC= gcc -Wall -Wextra -Werror

all: build

build: random.o
	$(CC) random.o -o ../build/random1

random.o: random.c
	$(CC) -c random.c 

rebuild: clean all

clean: 
	rm -rf *.o ../build/random*