#include "bench.h"
#include "ckl_math.h"
#define FLOAT double
#define FUNCTION_LOOP FUNC_VEC_LOOP(sin)
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
