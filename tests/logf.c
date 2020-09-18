#include "test_common.h"
#define FLOAT float
typedef void (*test_func_vector)(const FLOAT *, FLOAT *, unsigned int);
typedef FLOAT (*test_func_scalar)(FLOAT);
test_func_vector fp_vector = ckl_vlogf;
test_func_scalar fp_scalar = logf;
/**
Test values define:
The input array is SPECIAL_VALUES + 10 vaules from RANGES + dim values from
RANGE2; SPECIAL_VALUES array is for some special input values; SPEC_SIZE is its
size; RANGE1 is for large random values generation; RANGE2 is for little ramdom
values generation;
**/
#define SPEC_SIZE 5
#define SPECIAL_VALUES \
  {1.0, E_VALUE, E_VALUE * E_VALUE, 1.0 / E_VALUE, 1.0 / (E_VALUE * E_VALUE)};
#define RANGE1 rand_in_range(0.0, 1.0)
#define RANGE2 rand_in_range(1.0, RAND_MAX * 1.0)
#include "test_common.c"