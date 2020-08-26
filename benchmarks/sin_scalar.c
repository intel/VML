#include "sys/time.h"
#include "time.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int dim = atoi(argv[1]);
  int loopCount = atoi(argv[2]);
  struct timeval start, finish;
  double duration;

  unsigned int array_size = dim * loopCount;
  double *input_array = (double *)malloc(sizeof(double) * array_size);
  double *result_array = (double *)malloc(sizeof(double) * array_size);

  for (unsigned int i = 0; i < array_size; i++) {
    input_array[i] = (double)(rand() / 1000.0);
    result_array[i] = 0.0;
  }

  gettimeofday(&start, NULL);
  for (unsigned int i = 0; i < loopCount; i++) {
    for (unsigned int j = i * dim; j < (i + 1) * dim; j++) {
      result_array[j] = sin(input_array[j]);
    }
  }
  gettimeofday(&finish, NULL);

  for (unsigned int i = 0; i < array_size; i++) {
    result_array[0] += result_array[i];
  }
  printf("Scalar result:\n");
  printf("%12.8lf\n", result_array[0]);
  duration = ((double)(finish.tv_sec - start.tv_sec) * 1000000 +
              (double)(finish.tv_usec - start.tv_usec)) /
             1000000;
  duration /= loopCount;
  double gflops = 2.0 * dim;
  gflops = gflops / duration * 1.0e-6;
  printf("[%d]:\t%lf s\t%lf MFLOPS\n", dim, duration, gflops);

  free(input_array);
  free(result_array);

  return 0;
}
