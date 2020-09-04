#include "test_common.h"
#define FLOAT float
typedef void (*test_func_vector)(const FLOAT *, FLOAT *, unsigned int);
typedef FLOAT (*test_func_scalar)(FLOAT);
test_func_vector fp_vector = ckl_vsinf;
test_func_scalar fp_scalar = sinf;
#include "test_common.c"