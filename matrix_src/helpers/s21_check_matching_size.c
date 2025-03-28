#include "../s21_matrix.h"

int s21_check_matching_size(matrix_t *A, matrix_t *B) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALCULATION_ERROR;
    return OK;
}

