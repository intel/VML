#include "bench.h"
#define FLOAT float
#define scalar_sinf sinf
#define FUNCTION_LOOP FUNC_LOOP(sinf)
#define RANGE1 rand_in_range(-360.0, 360.0)
#include "bench.c"
