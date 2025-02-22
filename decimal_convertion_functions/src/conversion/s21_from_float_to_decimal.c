#include "conversion.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_result_flag flag = s21_flag_ok;

  if (!dst) return s21_flag_error;

  if (src == 0.0f) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
  }

  if ((fabs(src) < DECIMAL_MIN) || (fabs(src) > DECIMAL_MAX || isinf(src))) {
    flag = s21_flag_error;
  } else {
    int sign = (src < 0) ? 1 : 0;
    src = fabs(src);

    int exponent;
    float normalized = frexpf(src, &exponent);

    dst->bits[0] = (unsigned int)(normalized * (1 << 24));
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
  }

  return flag;
}