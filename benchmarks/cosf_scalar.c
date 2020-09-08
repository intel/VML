#include "bench.h"
#define FLOAT float
#define scalar_cosf cosf
#define FUNCTION_LOOP FUNC_LOOP(cosf)
#include "bench.c"
