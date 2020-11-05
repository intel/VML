#include "bench.h"
#include "ckl_math.h"
#define FLOAT float
#define POW
#define FUNCTION_LOOP                                                                          \
    for (unsigned int i = 0; i < loopCount; i++)                                               \
    {                                                                                          \
        ckl_vpowf(input_array + i * dim, input_array1 + i * dim, result_array + i * dim, dim); \
    }
#define RANGE1 rand_in_range(1.0, 10.0)
#define RANGE2 rand_in_range(-100.0, 100.0)
#include "bench.c"
