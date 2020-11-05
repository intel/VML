#include "bench.h"
//#define _GNU_SOURCE
//#include <math.h>
#define FLOAT double
#define SINCOS
#define FUNCTION_LOOP                                                    \
    for (unsigned int i = 0; i < loopCount; i++)                         \
    {                                                                    \
        for (unsigned int j = i * dim; j < (i + 1) * dim; j++)           \
        {                                                                \
            sincos(input_array[j], &result_array[j], &result_array1[j]); \
        }                                                                \
    }
//#pragma omp declare simd notinbranch linear(y, z)
//void sincos(double x, double *y, double *z);
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"