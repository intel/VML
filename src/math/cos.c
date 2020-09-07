#include "cpu.h"
#include "vmath.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void vcos_avx512(const double *input_array, double *result_array,
                 unsigned int size);
void vcos_avx2(const double *input_array, double *result_array,
               unsigned int size);
void vcos_avx(const double *input_array, double *result_array,
              unsigned int size);
void vcos_sse(const double *input_array, double *result_array,
              unsigned int size);
void vcos_scalar(const double *input_array, double *result_array,
                 unsigned int size);

static void (*funcs[])(const double *, double *, unsigned int) = {
    vcos_avx512, vcos_avx2, vcos_avx, vcos_sse, vcos_scalar};

/* kernel with scalar fallback */
void vcos_scalar(const double *input_array, double *result_array,
                 unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    result_array[i] = cos(input_array[i]);
  }
}

/* vectorized sin wraper */
void ckl_vcos(const double *input_array, double *result_array,
              unsigned int size) {
  funcs[func_index](input_array, result_array, size);
}
