#include "test_common.h"
#define FLOAT float
#define POW
#define TEST_SCALAR_ARRAY 1
typedef void (*test_func_vector)(const FLOAT, const FLOAT *, FLOAT *, unsigned int);
typedef FLOAT (*test_func_scalar)(FLOAT, FLOAT);
test_func_vector fp_vector = ckl_vpowf_sv;
test_func_scalar fp_scalar = powf;
/**
Test values define:
The input array is SPECIAL_VALUES + 10 vaules from RANGES + dim values from
RANGE2; SPECIAL_VALUES array is for some special input values; SPEC_SIZE is its
size; RANGE1 is for large random values generation; RANGE2 is for little ramdom
values generation;
**/
#define SPEC_SIZE 50
#define SPECIAL_VALUES \
  {1.9348611798824013607855931695667095482349395751953125, NAN, NAN, NAN, NAN, NAN, NAN, NAN, \
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, \
  -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, \
  -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, \
  INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, \
  -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY};
#define SPECIAL_VALUEST \
  {-1.593880658583753273660477134399116039276123046875, NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY,\
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY,\
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY};
#define RANGE1 rand_in_range(-2.0, 2.0)
#define RANGE2 rand_in_range(RAND_MAX * -1.0, RAND_MAX * 1.0)
#include "test_common.c"
