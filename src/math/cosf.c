#include "cpu.h"
#include "vmath.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void vcosf_avx512(const float *input_array, float *result_array,
                  unsigned int size);
void vcosf_avx2(const float *input_array, float *result_array,
                unsigned int size);
void vcosf_avx(const float *input_array, float *result_array,
               unsigned int size);
void vcosf_sse(const float *input_array, float *result_array,
               unsigned int size);
void vcosf_scalar(const float *input_array, float *result_array,
                  unsigned int size);

static void (*funcs[])(const float *, float *, unsigned int) = {
    vcosf_avx512, vcosf_avx2, vcosf_avx, vcosf_sse, vcosf_scalar};

/* kernel with scalar fallback */
void vcosf_scalar(const float *input_array, float *result_array,
                  unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    result_array[i] = cosf(input_array[i]);
  }
}

/* vectorized cos wraper */
void ckl_vcosf(const float *input_array, float *result_array,
               unsigned int size) {
  funcs[func_index](input_array, result_array, size);
}
