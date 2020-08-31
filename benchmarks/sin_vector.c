#include "sys/time.h"
#include "time.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ckl.h"

int main(int argc, char *argv[]) {

  int dim = atoi(argv[1]);
  int loopCount = atoi(argv[2]);
  struct timeval start, finish, start1, finish1;
  double duration, duration1;

  gettimeofday(&start1, NULL);
  unsigned int array_size = dim * loopCount;
  double *input_array = (double *)malloc(sizeof(double) * array_size);
  double *result_array = (double *)malloc(sizeof(double) * array_size);

  for (unsigned int i = 0; i < array_size; i++) {
    input_array[i] = (double)(rand() / 1000.0);
    result_array[i] = 0.0;
  }
  gettimeofday(&finish1, NULL);

  gettimeofday(&start, NULL);
  for (unsigned int i = 0; i < loopCount; i++) {
    ckl_vsin(input_array + i * dim, result_array + i * dim, dim);
  }
  gettimeofday(&finish, NULL);

  for (unsigned int i = 0; i < array_size; i++) {
    result_array[0] += result_array[i];
  }
  printf("Vector result:\n");
  printf("%12.8lf\n", result_array[0]);
  duration = ((double)(finish.tv_sec - start.tv_sec) * 1000000 +
              (double)(finish.tv_usec - start.tv_usec)) /
             1000000;
  duration1 = ((double)(finish1.tv_sec - start1.tv_sec) * 1000000 +
               (double)(finish1.tv_usec - start1.tv_usec)) /
              1000000;
  // printf("prepare time: %lf s, loop time: %lf\n", duration1, duration);
  duration /= loopCount;
  double gflops = 2.0 * dim;
  gflops = gflops / duration * 1.0e-6;
  printf("[%d]:\t%lf s\t%lf MFLOPS\n", dim, duration, gflops);

  free(input_array);
  free(result_array);

  return 0;
}
