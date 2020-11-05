#include "bench.h"
#include "ckl_math.h"
#define FLOAT float
#define FUNCTION_LOOP FUNC_VEC_LOOP(logf)
#define RANGE1 rand_in_range(1, 10000.0)
#include "bench.c"
