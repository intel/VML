#include "bench.h"
#define FLOAT float
#define scalar_cosf cosf
#define FUNCTION_LOOP FUNC_LOOP(cosf)
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
