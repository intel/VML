#include "cpu.h"
#include "vmath.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void vsin_avx512(const double *input_array, double *result_array,
                 unsigned int size);
void vsin_avx2(const double *input_array, double *result_array,
               unsigned int size);
void vsin_avx(const double *input_array, double *result_array,
              unsigned int size);
void vsin_sse(const double *input_array, double *result_array,
              unsigned int size);
void vsin_scalar(const double *input_array, double *result_array,
                 unsigned int size);

static void (*funcs[])(const double *, double *, unsigned int) = {
    vsin_avx512, vsin_avx2, vsin_avx, vsin_sse, vsin_scalar};

/* kernel with scalar fallback */
void vsin_scalar(const double *input_array, double *result_array,
                 unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    result_array[i] = sin(input_array[i]);
  }
}

/* vectorized sin wraper */
void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size) {
  funcs[func_index](input_array, result_array, size);
}
