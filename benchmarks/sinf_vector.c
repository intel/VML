#include "bench.h"
#include "ckl_math.h"
#define FLOAT float
#define FUNCTION_LOOP FUNC_VEC_LOOP(sinf)
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
