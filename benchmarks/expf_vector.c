#include "bench.h"
#include "ckl_math.h"
#define FLOAT float
#define FUNCTION_LOOP FUNC_VEC_LOOP(expf)
#define RANGE1 rand_in_range(-100.0, 100.0)
#include "bench.c"
