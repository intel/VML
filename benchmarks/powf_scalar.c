#include "bench.h"
#include <math.h>
#define FLOAT float
#define POW
#define FUNCTION_LOOP                                                \
    for (unsigned int i = 0; i < loopCount; i++)                     \
    {                                                                \
        for (unsigned int j = i * dim; j < (i + 1) * dim; j++)       \
        {                                                            \
            result_array[j] = powf(input_array[j], input_array1[j]); \
        }                                                            \
    }
#include "bench.c"
