#include "bench.h"
#include "ckl_math.h"
#define FLOAT float
#define SINCOS
#define FUNCTION_LOOP                                                                              \
    for (unsigned int i = 0; i < loopCount; i++)                                                   \
    {                                                                                              \
        ckl_vsincosf(input_array + i * dim, result_array + i * dim, result_array1 + i * dim, dim); \
    }
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
