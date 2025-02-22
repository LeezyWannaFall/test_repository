#include "conversion.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_result_flag flag = s21_flag_ok;

  if (!dst) return s21_flag_error;

  int sign = (src.bits[3] && (1u << 31)) ? -1 : 1;
  int scale = src.bits[3] >> 16;

  float result = (float)src.bits[0];

  for (int i = 0; i < scale; i++) {
    result /= 10.0f;
  }

  result *= sign;

  if (result < -FLT_MAX || result > FLT_MAX) flag = s21_flag_error;

  *dst = result;
  return flag;
}