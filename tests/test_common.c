#ifdef DOUBLE
typedef unsigned long long MASK_TYPE;
#else
typedef unsigned int MASK_TYPE;
#endif
#define SPEC_SIZE 23
/* generate a random floating point number from min to max */
FLOAT rand_in_range(FLOAT min, FLOAT max) {
  FLOAT range = (max - min);
  FLOAT div = RAND_MAX / range;
  return min + (rand() / div);
}

static int almostEquals(FLOAT *n1, FLOAT *n2) {
  unsigned int bit_count = 8 * sizeof(FLOAT);
  //#ifdef DOUBLE
  // unsigned int fraction_bit_count = 52;
  //#else
  // unsigned int fraction_bit_count = 23;
  //#endif
  // MASK_TYPE exponent_bit_count = bit_count - 1 - fraction_bit_count;
  MASK_TYPE sign_bit_mask = 1 << (bit_count - 1);
  // MASK_TYPE fraction_bit_mask = ~(MASK_TYPE)(0) >> (exponent_bit_count + 1);
  // MASK_TYPE exponent_bit_mask = ~(sign_bit_mask | fraction_bit_mask);
  if (isnan(*n1) || isnan(*n2))
    return (0);
  MASK_TYPE bias1, bias2;
  if (sign_bit_mask & (*(MASK_TYPE *)(n1))) {
    // a negative number.
    bias1 = ~(*(MASK_TYPE *)(n1)) + 1;
  } else {
    // a positive number.
    bias1 = sign_bit_mask | (*(MASK_TYPE *)(n1));
  }
  if (sign_bit_mask & (*(MASK_TYPE *)(n2))) {
    // a negative number.
    bias2 = ~(*(MASK_TYPE *)(n2)) + 1;
  } else {
    // a positive number.
    bias2 = sign_bit_mask | (*(MASK_TYPE *)(n2));
  }
  // printf("bias1 - bias2=%d\n",
  //       (bias1 >= bias2) ? (bias1 - bias2) : (bias2 - bias1));
  return ((bias1 >= bias2) ? (bias1 - bias2) : (bias2 - bias1)) <= 4;
}

int main(int argc, char *argv[]) {
  int dim = atoi(argv[1]);
  int check_flag = 1;
  FLOAT special_values[SPEC_SIZE] = {
      0.0,    30.0,   45.0,   60.0,   90.0,   135.0,  150.0, 180.0,
      225.0,  270.0,  315.0,  360.0,  -30.0,  -45.0,  -60.0, -90.0,
      -135.0, -150.0, -180.0, -225.0, -270.0, -315.0, -360.0};
  unsigned int array_size = dim + SPEC_SIZE + 10;
  FLOAT input_array[array_size];
  FLOAT result_array_scalar[array_size];
  FLOAT result_array_vector[array_size];

  for (unsigned int i = 0; i < array_size; i++) {
    if (i < SPEC_SIZE)
      input_array[i] = special_values[i];
    else if (i >= SPEC_SIZE && i < SPEC_SIZE + 10)
      input_array[i] = rand_in_range(-360.0, 360.0);
    else
      input_array[i] = rand_in_range(-1.0, 1.0);
    result_array_scalar[i] = 0.0;
    result_array_vector[i] = 0.0;
  }

  fp_vector(input_array, result_array_vector, array_size);

  for (unsigned int i = 0; i < array_size; i++) {
    result_array_scalar[i] = fp_scalar(input_array[i]);
  }

  for (unsigned int i = 0; i < array_size; i++) {
    // FLOAT diff = fabs(result_array_scalar[i] - result_array_vector[i]);
    // if (diff > ERROR_THRESHOLD) {
    if (!almostEquals(&result_array_scalar[i], &result_array_vector[i])) {
      printf("[Miss Match]: Scalar - %32.24lf\n", result_array_scalar[i]);
      printf("              Vector - %32.24lf\n", result_array_vector[i]);
      // printf("              diff   - %32.24lf\n", diff);
      check_flag = 0;
    }
  }

  if (check_flag) {
    printf("[Test Result]: PASS\n");
  } else {
    printf("[Test Result]: FAIL\n");
  }
#if 0
  FLOAT a1 = 1.0000000000000000009;
  FLOAT a2 = 1.0000000000000000008;
  FLOAT b1 = 0.00000002;
  FLOAT b2 = 0.00000001;
  printf("======1 %d\n", almostEquals(&a1, &a2));
  printf("======2 %d\n", almostEquals(&b1, &b2));
#endif
  return 0;
}
