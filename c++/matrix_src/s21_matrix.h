#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define EPS 1e-6
#define MAX_MATRIX_SIZE 20

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

#include "headers/s21_core.h"
#include "headers/s21_helpers.h"

#endif // S21_MATRIX_H_
