#include "bench.h"
#define FLOAT float
#define scalar_expf expf
#define FUNCTION_LOOP FUNC_LOOP(expf)
#include "bench.c"
