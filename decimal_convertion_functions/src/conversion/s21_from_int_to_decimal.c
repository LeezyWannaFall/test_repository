#include "conversion.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_result_flag flag = s21_flag_ok;

  if (!dst) return s21_flag_error;

  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;

  int sign = (src < 0);

  if (src == INT_MIN) {
    dst->bits[0] = (unsigned)INT_MAX + 1;
  } else {
    if (sign)
      dst->bits[0] = -src;
    else
      dst->bits[0] = src;
  }

  if (sign) dst->bits[3] |= (1u << 31);

  return flag;
}