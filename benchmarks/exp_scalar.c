#include "bench.h"
#define FLOAT double
#define scalar_exp exp
#define FUNCTION_LOOP FUNC_LOOP(exp)
#define RANGE1 rand_in_range(-100.0, 100.0)
#include "bench.c"
