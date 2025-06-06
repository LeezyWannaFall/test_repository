#include "../../s21_tetris.h"

int static_figures[7][4][4] = {
    /* x x
       x x
    */
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* x x x x */
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /* x
       x x x
    */
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /*     x
       x x x
    */
    {
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /*    x x
        x x
    */
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /*    x
        x x x
    */
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    /*  x x 
          x x
    */
    {
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};