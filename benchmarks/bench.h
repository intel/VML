#ifndef BENCH_H
#define BENCH_H
#define _GNU_SOURCE
#include <math.h>
#include "sys/time.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

#define FUNC_VEC_LOOP(name) FUNC_VEC_TMP_LOOP(name)
#define FUNC_VEC_TMP_LOOP(name)                                      \
  ckl_init();                                                        \
  for (unsigned int i = 0; i < loopCount; i++)                       \
  {                                                                  \
    ckl_v##name(input_array + i * dim, result_array + i * dim, dim); \
  }

#define FUNC_LOOP(name) FUNC_TMP_LOOP(name)
#define FUNC_TMP_LOOP(name)                                \
  for (unsigned int i = 0; i < loopCount; i++)             \
  {                                                        \
    for (unsigned int j = i * dim; j < (i + 1) * dim; j++) \
    {                                                      \
      result_array[j] = scalar_##name(input_array[j]);     \
    }                                                      \
  }

#endif
