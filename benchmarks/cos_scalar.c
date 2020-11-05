#include "bench.h"
#define FLOAT double
#define scalar_cos cos
#define FUNCTION_LOOP FUNC_LOOP(cos)
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
