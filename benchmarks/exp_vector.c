#include "bench.h"
#include "ckl_math.h"
#define FLOAT double
#define FUNCTION_LOOP FUNC_VEC_LOOP(exp)
#define RANGE1 rand_in_range(-100.0, 100.0)
#include "bench.c"
