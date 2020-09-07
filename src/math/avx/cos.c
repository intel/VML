#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_cos(__m128d x);
__m256d _ZGVcN4v_cos(__m256d x);

#define AVX_NAME cN4v_cos
#define SSE_NAME bN2v_cos

#include "../common/avx.c"
#include "../common/sse.c"

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void avx_7(const double *input_array,
                                                 double *result_array, int size,
                                                 int *array_index) {
  if (size == 7 || size == 6) {
    AVX_4_mask4(1, AVX_NAME)
  } else if (size == 5) {
    AVX_4_mask2(1, SSE_NAME)
  } else if (size == 4) {
    AVX_4__1
  } else if (size == 3) {
    SSE_2__1
    *array_index += 2;
    SSE_2_mask2(0, SSE_NAME)
  } else if (size == 2)
    SSE_2__1
  else {
    AVX_4_mask2(0, SSE_NAME)
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void avx_15(const double *input_array,
                                                  double *result_array,
                                                  int size, int *array_index) {
  if (size == 13 || size == 14 || size == 15) {
    AVX_4_mask4(3, AVX_NAME)
  } else if (size == 12) {
    AVX_4__3
  } else if (size == 11 || size == 10 || size == 9) {
    AVX_4_mask4(2, AVX_NAME)
  } else if (size == 8) {
    AVX_4__2
  } else {
    avx_7(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX */
void vcos_avx(const double *input_array, double *result_array,
              unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 8) {
    if (size == 16) {
      AVX_4__4
    } else {
      unsigned int count = size >> 3;
      unsigned int rest = size & 7;
      for (int i = 0; i < count; i++) {
        AVX_4__2
        *array_index += 8;
      }
      if (rest)
        avx_7(input_array, result_array, rest, array_index);
    }
  } else if (size == 8) {
    AVX_4__2
  } else {
    avx_7(input_array, result_array, size, array_index);
  }
}
