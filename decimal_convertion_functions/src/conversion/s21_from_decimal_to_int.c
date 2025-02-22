#include "conversion.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_result_flag flag = s21_flag_ok;

  if (!dst) return s21_flag_error;

  *dst = 0;

  int sign = (src.bits[3] & (1u << 31)) ? -1 : 1;
  int scale = (src.bits[3] >> 16);

  if ((scale > 28) || (src.bits[1] || src.bits[2])) {
    flag = s21_flag_error;
  } else {
    int value = src.bits[0];

    for (int i = 0; i < scale; i++) {
      value /= 10;
    }

    if (value > INT_MAX || (sign == -1 && value > (unsigned)INT_MAX + 1))
      flag = s21_flag_error;
    else
      *dst = value * sign;
  }

  return flag;
}