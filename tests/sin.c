#include "test_common.h"
#define FLOAT double
#define DOUBLE
typedef void (*test_func_vector)(const FLOAT *, FLOAT *, unsigned int);
typedef FLOAT (*test_func_scalar)(FLOAT);
test_func_vector fp_vector = ckl_vsin;
test_func_scalar fp_scalar = sin;
#include "test_common.c"
