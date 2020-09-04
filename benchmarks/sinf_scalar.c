#include "bench.h"
#define FLOAT float
#define scalar_sinf sinf
#define FUNCTION_LOOP FUNC_LOOP(sinf)
#include "bench.c"
