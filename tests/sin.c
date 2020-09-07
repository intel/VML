#include "test_common.h"
#define FLOAT double
#define DOUBLE
typedef void (*test_func_vector)(const FLOAT *, FLOAT *, unsigned int);
typedef FLOAT (*test_func_scalar)(FLOAT);
test_func_vector fp_vector = ckl_vsin;
test_func_scalar fp_scalar = sin;
/**
Test values define:
The input array is SPECIAL_VALUES + 10 vaules from RANGES + dim values from
RANGE2; SPECIAL_VALUES array is for some special input values; SPEC_SIZE is its
size; RANGE1 is for large random values generation; RANGE2 is for little ramdom
values generation;
**/
#define SPEC_SIZE 32
#define SPECIAL_VALUES RADIANS
#define RANGE1 rand_in_range(-2.0 * PI, 2.0 * PI)
#define RANGE2 rand_in_range(-1.0, 1.0)
#include "test_common.c"
