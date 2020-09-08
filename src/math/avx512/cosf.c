#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_cos(__m128d x);
__m256d _ZGVcN4v_cos(__m256d x);
__m256d _ZGVdN4v_cos(__m256d x);
__m512d _ZGVeN8v_cos(__m512d x);

#define AVX512_NAME eN8v_cos
#define AVX2_NAME dN4v_cos

#include "../commonf2d/avx.c"
#include "../commonf2d/avx2.c"
#include "../commonf2d/avx512.c"

/*This function deal with size in 1~15*/
__attribute__((always_inline)) static inline void
avx512_15(const float *input_array, float *result_array, int size,
          int *array_index) {
  if (size == 13 || size == 14 || size == 15) {
    AVX512_8_mask8(1, AVX512_NAME)
  } else if (size == 12) {
    AVX512_8__1
    AVX_4_offset(8, AVX2_NAME)
  } else if (size == 11 || size == 10 || size == 9) {
    AVX512_8_mask4(1, AVX2_NAME)
  } else if (size == 8) {
    AVX512_8__1
  } else if (size == 5 || size == 6 || size == 7) {
    AVX512_8_mask8(0, AVX512_NAME)
  } else if (size == 4) {
    AVX_4_offset(0, AVX2_NAME)
  } else {
    AVX512_8_mask4(0, AVX2_NAME)
  }
}

/*This function deals with size in 1~31 */
__attribute__((always_inline)) static inline void
avx512_31(const float *input_array, float *result_array, int size,
          int *array_index) {
  if (size == 31 || size == 30 || size == 29) {
    AVX512_8_mask8(3, AVX512_NAME)
  } else if (size == 28) {
    AVX512_8__3
    AVX_4_offset(24, AVX2_NAME)
  } else if (size == 27 || size == 26 || size == 25) {
    AVX512_8_mask4(3, AVX2_NAME)
  } else if (size == 24) {
    AVX512_8__3
  } else if (size == 23 || size == 22 || size == 21) {
    AVX512_8_mask8(2, AVX512_NAME)
  } else if (size == 20) {
    AVX512_8__2
    AVX_4_offset(16, AVX2_NAME)
  } else if (size == 19 || size == 18 || size == 17) {
    AVX512_8_mask4(2, AVX2_NAME)
  } else if (size == 16) {
    AVX512_8__2
  } else
    avx512_15(input_array, result_array, size, array_index);
}

static void vcos_avx512_sub(const float *input_array, float *result_array,
                            unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 32) {
    unsigned int count = size >> 5;
    unsigned int rest = size & 31;
    for (int i = 0; i < 2 * count; i++) {
      AVX512_8__2
      *array_index += 16;
    }
    if (rest)
      avx512_31(input_array, result_array, rest, array_index);
  } else if (size == 32) {
    AVX512_8__4
  } else {
    avx512_31(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX512 */
void vcosf_avx512(const float *input_array, float *result_array,
                  unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 16) {
    vcos_avx512_sub(input_array, result_array, size);
  } else if (size == 16) {
    AVX512_8__2
  } else {
    avx512_15(input_array, result_array, size, array_index);
  }
}