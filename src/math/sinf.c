#include "cpu.h"
#include "vmath.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void vsinf_avx512(const float *input_array, float *result_array,
                  unsigned int size);
void vsinf_avx2(const float *input_array, float *result_array,
                unsigned int size);
void vsinf_avx(const float *input_array, float *result_array,
               unsigned int size);
void vsinf_sse(const float *input_array, float *result_array,
               unsigned int size);
void vsinf_scalar(const float *input_array, float *result_array,
                  unsigned int size);

static void (*funcs[])(const float *, float *, unsigned int) = {
    vsinf_avx512, vsinf_avx2, vsinf_avx, vsinf_sse, vsinf_scalar};

/* kernel with scalar fallback */
void vsinf_scalar(const float *input_array, float *result_array,
                  unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    result_array[i] = sinf(input_array[i]);
  }
}

/* vectorized sin wraper */
void ckl_vsinf(const float *input_array, float *result_array,
               unsigned int size) {
  funcs[func_index](input_array, result_array, size);
}
