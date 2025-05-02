#ifndef S21_TETRIS_H_
#define S21_TETRIS_H_

// INCLUDES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

// DEFINES
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define EPS 1e-6
#define MAX_MATRIX_SIZE 20
#define WIDTH 10
#define HEIGHT 20

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

#endif // S21_TETRIS_H_