int main(int argc, char *argv[]) {

  int dim = atoi(argv[1]);
  int loopCount = atoi(argv[2]);
  struct timeval start, finish;
  FLOAT duration;

  unsigned int array_size = dim * loopCount;
  FLOAT *input_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
  FLOAT *result_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);

  for (unsigned int i = 0; i < array_size; i++) {
    input_array[i] = (FLOAT)(rand() / 1000.0);
    result_array[i] = 0.0;
  }

  // sleep(2);
  // printf("===start \n");
  gettimeofday(&start, NULL);
  FUNCTION_LOOP
  gettimeofday(&finish, NULL);
  // printf("===end \n");
  for (unsigned int i = 0; i < array_size; i++) {
    result_array[0] += result_array[i];
  }
  printf("Scalar result:\n");
  printf("%12.8lf\n", result_array[0]);
  duration = ((FLOAT)(finish.tv_sec - start.tv_sec) * 1000000 +
              (FLOAT)(finish.tv_usec - start.tv_usec)) /
             1000000;
  duration /= loopCount;
  FLOAT gflops = 2.0 * dim;
  gflops = gflops / duration * 1.0e-6;
  printf("[%d]:\t%lf s\t%lf MFLOPS\n", dim, duration, gflops);

  free(input_array);
  free(result_array);

  return 0;
}
