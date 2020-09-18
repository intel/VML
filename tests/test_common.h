#ifndef TEST_COMMON_H
#define TEST_COMMON_H
#include "vmath.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define ERROR_THRESHOLD (1.0E-15)
#define PI                                                                     \
  3.1415926535897932384626433832795028841971693993751058209749445923078164062
#define RADIANS                                                                \
  {0.0,                                                                        \
   PI / 6.0,                                                                   \
   PI / 4.0,                                                                   \
   PI / 3.0,                                                                   \
   PI / 2.0,                                                                   \
   2.0 * PI / 3.0,                                                             \
   3.0 * PI / 4.0,                                                             \
   4.0 * PI / 5.0,                                                             \
   5.0 * PI / 6.0,                                                             \
   PI,                                                                         \
   5.0 * PI / 4.0,                                                             \
   3.0 * PI / 2.0,                                                             \
   4.0 * PI / 3.0,                                                             \
   6.0 * PI / 5.0,                                                             \
   2.0 * PI,                                                                   \
   -PI / 6.0,                                                                  \
   -PI / 4.0,                                                                  \
   -PI / 3.0,                                                                  \
   -PI / 2.0,                                                                  \
   -2.0 * PI / 3.0,                                                            \
   -3.0 * PI / 4.0,                                                            \
   -4.0 * PI / 5.0,                                                            \
   -5.0 * PI / 6.0,                                                            \
   -PI,                                                                        \
   -5.0 * PI / 4.0,                                                            \
   -3.0 * PI / 2.0,                                                            \
   -4.0 * PI / 3.0,                                                            \
   -6.0 * PI / 5.0,                                                            \
   -2.0 * PI,                                                                  \
   -PI / 6.0,                                                                  \
   -PI / 4.0,                                                                  \
   -PI / 3.0};
#define E_VALUE                                                                \
  2.7182818284590452353602874713526624977572470936999595749669676277240766304
#endif