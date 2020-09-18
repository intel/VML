#include "cpu.h"
#include "vmath.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void vlog_avx512(const double *input_array, double *result_array,
                 unsigned int size);
void vlog_avx2(const double *input_array, double *result_array,
               unsigned int size);
void vlog_avx(const double *input_array, double *result_array,
              unsigned int size);
void vlog_sse(const double *input_array, double *result_array,
              unsigned int size);
void vlog_scalar(const double *input_array, double *result_array,
                 unsigned int size);

static void (*funcs[])(const double *, double *, unsigned int) = {
    vlog_avx512, vlog_avx2, vlog_avx, vlog_sse, vlog_scalar};

/* kernel with scalar fallback */
void vlog_scalar(const double *input_array, double *result_array,
                 unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    result_array[i] = log(input_array[i]);
  }
}

/* vectorized log wraper */
void ckl_vlog(const double *input_array, double *result_array,
              unsigned int size) {
  funcs[func_index](input_array, result_array, size);
}
