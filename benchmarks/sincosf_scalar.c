#include "bench.h"
#define FLOAT float
#define SINCOS
#define FUNCTION_LOOP                                                     \
    for (unsigned int i = 0; i < loopCount; i++)                          \
    {                                                                     \
        for (unsigned int j = i * dim; j < (i + 1) * dim; j++)            \
        {                                                                 \
            sincosf(input_array[j], &result_array[j], &result_array1[j]); \
        }                                                                 \
    }
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
