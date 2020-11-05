#include "bench.h"
#define FLOAT float
#define scalar_logf logf
#define FUNCTION_LOOP FUNC_LOOP(logf)
#define RANGE1 rand_in_range(1, 10000.0)
#include "bench.c"
