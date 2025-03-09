#ifndef S21_CONVERSION_H_
#define S21_CONVERSION_H_
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../types/types.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

typedef enum s21_result_conversation {
  s21_flag_ok = 0,
  s21_flag_error = 1
} s21_result_flag;

#define DECIMAL_MAX 79228162514264337593543950335.0
#define DECIMAL_MIN 1e-28

#endif  // S21_CONVERSION_H_