#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ckl.h"

#define ERROR_THRESHOLD (1.0E-15)
//#define ERROR_THRESHOLD (1.0E-16)

int main(int argc, char* argv[])
{
  int dim = atoi(argv[1]);  
  unsigned int  array_size = dim;  
  double input_array[dim];
  double result_array_scalar[dim];
  double result_array_vector[dim];
  int   check_flag = 1;

  for (unsigned int i = 0; i < array_size; i++) {
      input_array[i] = (double)(rand()/1000.0);
      result_array_scalar[i] = 0.0;
      result_array_vector[i] = 0.0;
  }

  ckl_vsin(input_array, result_array_vector, array_size);

  for (unsigned int i = 0; i < array_size; i++) {
      result_array_scalar[i] = sin(input_array[i]);
  }

  for (unsigned int i = 0; i < array_size; i++) {
      double diff = fabs(result_array_scalar[i] - result_array_vector[i]);
      if (diff > ERROR_THRESHOLD) {
          printf("[Miss Match]: Scalar - %32.24lf\n", result_array_scalar[i]);
          printf("              Vector - %32.24lf\n", result_array_vector[i]);
          printf("              diff   - %32.24lf\n", diff);
          check_flag = 0;
      }
  }

  if (check_flag) {
      printf("[Test Result]: PASS\n");
  } else {
      printf("[Test Result]: FAIL\n");
  }
  return 0;
}
