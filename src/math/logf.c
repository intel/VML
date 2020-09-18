#include "cpu.h"
#include "vmath.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void vlogf_avx512(const float *input_array, float *result_array,
                  unsigned int size);
void vlogf_avx2(const float *input_array, float *result_array,
                unsigned int size);
void vlogf_avx(const float *input_array, float *result_array,
               unsigned int size);
void vlogf_sse(const float *input_array, float *result_array,
               unsigned int size);
void vlogf_scalar(const float *input_array, float *result_array,
                  unsigned int size);

static void (*funcs[])(const float *, float *, unsigned int) = {
    vlogf_avx512, vlogf_avx2, vlogf_avx, vlogf_sse, vlogf_scalar};

/* kernel with scalar fallback */
void vlogf_scalar(const float *input_array, float *result_array,
                  unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
  {
    result_array[i] = logf(input_array[i]);
  }
}

/* vectorized log wraper */
void ckl_vlogf(const float *input_array, float *result_array,
               unsigned int size)
{
  funcs[func_index](input_array, result_array, size);
}
