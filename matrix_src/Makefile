GCC = gcc

CFLAGS = -Wall -Wextra -Werror -Wuninitialized -Wmaybe-uninitialized -pedantic -std=c11
CFLAGS_T = -Wall -Wextra -Werror -Wuninitialized -Wmaybe-uninitialized -pedantic -std=c11 -fprofile-arcs -ftest-coverage

ifeq ($(shell uname), Darwin)
    GCOVFLAGS = -lcheck -fprofile-arcs -ftest-coverage
else
    GCOVFLAGS = -lcheck -lsubunit -fprofile-arcs -ftest-coverage
endif

RM = rm -rf

LIBRARY = s21_matrix.a