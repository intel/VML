#include "bench.h"
#include <math.h>
#define FLOAT double
#define POW
#define FUNCTION_LOOP                                               \
    for (unsigned int i = 0; i < loopCount; i++)                    \
    {                                                               \
        for (unsigned int j = i * dim; j < (i + 1) * dim; j++)      \
        {                                                           \
            result_array[j] = pow(input_array[j], input_array1[j]); \
        }                                                           \
    }
#define RANGE1 rand_in_range(1.0, 10.0)
#define RANGE2 rand_in_range(-100.0, 100.0)
#include "bench.c"
