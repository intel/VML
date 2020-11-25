#ifdef DOUBLE
typedef unsigned long long MASK_TYPE;
#else
typedef unsigned int MASK_TYPE;
#endif

/* generate a random floating point number from min to max */
FLOAT rand_in_range(FLOAT min, FLOAT max)
{
  FLOAT range = (max - min);
  FLOAT div = RAND_MAX / range;
  return min + (rand() / div);
}

static int almostEquals(FLOAT *n1, FLOAT *n2)
{
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
  if (sign_bit_mask & (*(MASK_TYPE *)(n1)))
  {
    // a negative number.
    bias1 = ~(*(MASK_TYPE *)(n1)) + 1;
  }
  else
  {
    // a positive number.
    bias1 = sign_bit_mask | (*(MASK_TYPE *)(n1));
  }
  if (sign_bit_mask & (*(MASK_TYPE *)(n2)))
  {
    // a negative number.
    bias2 = ~(*(MASK_TYPE *)(n2)) + 1;
  }
  else
  {
    // a positive number.
    bias2 = sign_bit_mask | (*(MASK_TYPE *)(n2));
  }
  // printf("bias2 - bias2=%d\n",
  //       (bias1 >= bias2) ? (bias1 - bias2) : (bias2 - bias1));
  return ((bias1 >= bias2) ? (bias1 - bias2) : (bias2 - bias1)) <= 4;
}

unsigned int round_up(unsigned int num, unsigned int factor)
{
  return num + factor - 1 - (num + factor - 1) % factor;
}

int main(int argc, char *argv[])
{
  int dim = atoi(argv[1]);
  int check_flag = 1;
  FLOAT special_values[SPEC_SIZE] = SPECIAL_VALUES;
#ifdef POW
  FLOAT special_values1[SPEC_SIZE] = SPECIAL_VALUEST;
#endif
  unsigned int array_size = dim + SPEC_SIZE + 10;
  unsigned int real_array_size = round_up(array_size, dim);
  FLOAT input_array[array_size];
#ifdef POW
  FLOAT input_array1[array_size];
#endif

  FLOAT result_array_scalar[array_size];
  FLOAT result_array_vector[array_size];
#ifdef SINCOS
  FLOAT result_array_scalar1[array_size];
  FLOAT result_array_vector1[array_size];
#endif
  while (real_array_size > array_size)
    real_array_size -= dim;

  for (unsigned int i = 0; i < array_size; i++)
  {
    if (i < SPEC_SIZE)
    {
      input_array[i] = special_values[i];
#ifdef POW
      input_array1[i] = special_values1[i];
#endif
    }
    else if (i >= SPEC_SIZE && i < SPEC_SIZE + 10)
    {
      input_array[i] = RANGE1;
#ifdef POW
      input_array1[i] = RANGE1;
#endif
    }
    else
    {
      input_array[i] = RANGE2;
#ifdef POW
      input_array1[i] = RANGE2;
#endif
    }
    result_array_scalar[i] = 0.0;
    result_array_vector[i] = 0.0;
#ifdef SINCOS
    result_array_scalar1[i] = 0.0;
    result_array_vector1[i] = 0.0;
#endif
  }

  for (unsigned int i = 0; i < real_array_size / dim; i++)
#ifdef POW
    fp_vector(input_array + i * dim, input_array1 + i * dim, result_array_vector + i * dim, dim);
#endif
#ifdef SINCOS
  fp_vector(input_array + i * dim, result_array_vector + i * dim, result_array_vector1 + i * dim, dim);
#endif
#if !defined(POW) && !defined(SINCOS)
  fp_vector(input_array + i * dim, result_array_vector + i * dim, dim);
#endif

  for (unsigned int i = 0; i < real_array_size; i++)
  {
#ifdef POW
    result_array_scalar[i] = fp_scalar(input_array[i], input_array1[i]);
#endif
#ifdef SINCOS
    fp_scalar(input_array[i], &result_array_scalar[i], &result_array_scalar1[i]);
#endif
#if !defined(POW) && !defined(SINCOS)
    result_array_scalar[i] = fp_scalar(input_array[i]);
#endif
  }

  for (unsigned int i = 0; i < real_array_size; i++)
  {
    // FLOAT diff = fabs(result_array_scalar[i] - result_array_vector[i]);
    // if (diff > ERROR_THRESHOLD) {
#ifdef SINCOS
    if (!almostEquals(&result_array_scalar[i], &result_array_vector[i]) || !almostEquals(&result_array_scalar1[i], &result_array_vector1[i]))
#else
    if (!almostEquals(&result_array_scalar[i], &result_array_vector[i]))
#endif
    {
      printf("array size=%d real_array_size=%d\n", array_size, real_array_size);
      printf("[Miss Match]: Scalar[%d] - %32.24lf\n", i, result_array_scalar[i]);
      printf("              Vector[%d] - %32.24lf\n", i, result_array_vector[i]);
#ifdef SINCOS
      printf("[Miss Match]: Scalar1[%d] - %32.24lf\n", i, result_array_scalar1[i]);
      printf("              Vector1[%d] - %32.24lf\n", i, result_array_vector1[i]);
#endif
#ifdef POW
      printf("              Input [%d]:  %32.24lf, Input value1 [%d]:  %32.24lf\n", i, input_array[i], i, input_array1[i]);
#else
      printf("              Input [%d]:  %32.24lf\n", i, input_array[i]);
#endif
      // printf("              diff   - %32.24lf\n", diff);
      check_flag = 0;
    }
  }

  if (check_flag)
  {
    printf("[Test Result]: PASS\n");
  }
  else
  {
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
