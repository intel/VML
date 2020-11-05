#include "bench.h"
#define FLOAT double
#define scalar_sin sin
#define FUNCTION_LOOP FUNC_LOOP(sin)
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
