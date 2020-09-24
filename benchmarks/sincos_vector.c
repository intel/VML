#include "bench.h"
#include "vmath.h"
#define FLOAT double
#define SINCOS
#define FUNCTION_LOOP                                                                                 \
    for (unsigned int i = 0; i < loopCount; i++)                                                      \
    {                                                                                                 \
        for (unsigned int j = i * dim; j < (i + 1) * dim; j++)                                        \
        {                                                                                             \
            ckl_vsincos(input_array + i * dim, result_array + i * dim, result_array1 + i * dim, dim); \
        }                                                                                             \
    }
#include "bench.c"
