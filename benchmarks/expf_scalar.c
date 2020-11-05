#include "bench.h"
#define FLOAT float
#define scalar_expf expf
#define FUNCTION_LOOP FUNC_LOOP(expf)
#define RANGE1 rand_in_range(-100.0, 100.0)
#include "bench.c"
