#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_sin(__m128d x);
__m256d _ZGVcN4v_sin(__m256d x);
__m256d _ZGVdN4v_sin(__m256d x);

#define AVX2_NAME dN4v_sin

#include "../commonf2d/avx2.c"

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void avx2_7(const float *input_array,
                                                  float *result_array, int size,
                                                  int *array_index) {
  if (size == 7 || size == 6 || size == 5) {
    AVX2_4_mask4(1, AVX2_NAME)
  } else if (size == 4) {
    AVX2_4__1
  } else {
    AVX2_4_mask4(0, AVX2_NAME)
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void avx2_15(const float *input_array,
                                                   float *result_array,
                                                   int size, int *array_index) {
  if (size == 13 || size == 14 || size == 15) {
    AVX2_4_mask4(3, AVX2_NAME)
  } else if (size == 12) {
    AVX2_4__3
  } else if (size == 11 || size == 10 || size == 9) {
    AVX2_4_mask4(2, AVX2_NAME)
  } else if (size == 8) {
    AVX2_4__2
  } else if (size == 5 || size == 6 || size == 7) {
    AVX2_4_mask4(1, AVX2_NAME)
  } else if (size == 4) {
    AVX2_4__1
  } else {
    AVX2_4_mask4(0, AVX2_NAME)
  }
}

/* kernel with vectorization up to AVX2 */
void vsinf_avx2(const float *input_array, float *result_array,
                unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 8) {
    unsigned int count = size >> 3;
    unsigned int rest = size & 7;
    for (int i = 0; i < count; i++) {
      AVX2_4__2
      *array_index += 8;
    }
    if (rest)
      avx2_7(input_array, result_array, rest, array_index);
  } else if (size == 8) {
    AVX2_4__2
  } else {
    avx2_7(input_array, result_array, size, array_index);
  }
}