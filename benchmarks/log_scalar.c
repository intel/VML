#include "bench.h"
#define FLOAT double
#define scalar_log log
#define FUNCTION_LOOP FUNC_LOOP(log)
#define RANGE1 rand_in_range(1, 10000.0)
#include "bench.c"
