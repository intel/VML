#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_log(__m128d x);
__m256d _ZGVcN4v_log(__m256d x);
__m256d _ZGVdN4v_log(__m256d x);
__m512d _ZGVeN8v_log(__m512d x);

#define AVX512_NAME eN8v_log
#define AVX2_NAME dN4v_log
#define SSE_NAME bN2v_log

#include "../common/avx.c"
#include "../common/avx2.c"
#include "../common/avx512.c"
#include "../common/sse.c"

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void avx512_7(const double *input_array,
                                                    double *result_array,
                                                    int size,
                                                    int *array_index) {
  if (size == 1) {
    result_array[*array_index] = log(input_array[*array_index]);
  } else if (size == 2) {
    SSE_2__1
  } else if (size == 3) {
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 4) {
    AVX_4_offset(0, AVX2_NAME)
  } else if (size == 5) {
    AVX2_4__1
    result_array[*array_index + 4] = log(input_array[*array_index + 4]);
  } else if (size == 6) {
    AVX2_4__1
    *array_index += 4;
    SSE_2__1
  } else if (size == 7) {
    AVX2_4__1
    *array_index += 4;
    SSE_2__1
    // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
    // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void avx512_15(const double *input_array,
                                                     double *result_array,
                                                     int size,
                                                     int *array_index) {
  if (size == 1) {
    result_array[*array_index] = log(input_array[*array_index]);
    // SSE_2_mask2(0, SSE_NAME)
  } else if (size == 2) {
    // result_array[*array_index] = log(input_array[*array_index]);
    // result_array[*array_index + 1] = log(input_array[*array_index + 1]);
    SSE_2__1
  } else if (size == 3) {
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 13) {
    AVX512_8__1
    AVX_4_offset(8, AVX2_NAME);
    result_array[*array_index + 12] = log(input_array[*array_index + 12]);
  } else if (size == 14) {
    AVX512_8__1
    AVX_4_offset(8, AVX2_NAME);
    *array_index += 12;
    SSE_2__1
  } else if (size == 15) {
    // AVX512_8_mask8(1, AVX512_NAME)
    AVX512_8__1
    AVX_4_offset(8, AVX2_NAME);
    *array_index += 12;
    SSE_2__1;
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 12) {
    AVX512_8__1
    AVX_4_offset(8, AVX2_NAME)
  } else if (size == 11) {
    AVX512_8__1;
    *array_index += 8;
    SSE_2__1;
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 10) {
    AVX512_8__1;
    *array_index += 8;
    SSE_2__1
  } else if (size == 9) {
    // AVX512_8_mask4(1, AVX2_NAME)
    AVX512_8__1;
    result_array[*array_index + 8] = log(input_array[*array_index + 8]);
  } else if (size == 8) {
    AVX512_8__1
  } else if (size == 5) {
    AVX2_4__1
    result_array[*array_index + 4] = log(input_array[*array_index + 4]);
  } else if (size == 6) {
    AVX2_4__1
    *array_index += 4;
    SSE_2__1
    // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
    // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
  } else if (size == 7) {
    AVX2_4__1
    *array_index += 4;
    SSE_2__1
    // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
    // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 4) {
    AVX_4_offset(0, AVX2_NAME)
  }
}

/*This function deals with size in 1~31 */
__attribute__((always_inline)) inline void avx512_31(const double *input_array,
                                                     double *result_array,
                                                     int size,
                                                     int *array_index) {
  if (size == 31) {
    AVX512_8__3
    AVX_4_offset(24, AVX2_NAME) *array_index += 28;
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 30) {
    AVX512_8__3
    AVX_4_offset(24, AVX2_NAME) *array_index += 28;
    SSE_2__1
  } else if (size == 29) {
    // AVX512_8_mask8(3, AVX512_NAME)
    AVX512_8__3
    AVX_4_offset(24, AVX2_NAME) result_array[*array_index + 28] =
        log(input_array[*array_index + 28]);
  } else if (size == 28) {
    AVX512_8__3
    AVX_4_offset(24, AVX2_NAME)
  } else if (size == 27) {
    AVX512_8__3
    *array_index += 24;
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 26) {
    AVX512_8__3
    *array_index += 24;
    SSE_2__1
  } else if (size == 25) {
    // AVX512_8_mask4(3, AVX2_NAME)
    AVX512_8__3
    result_array[*array_index + 24] = log(input_array[*array_index + 24]);
  } else if (size == 24) {
    AVX512_8__3
  } else if (size == 23 || size == 22 || size == 21) {
    AVX512_8_mask8(2, AVX512_NAME)
  } else if (size == 20) {
    AVX512_8__2
    AVX_4_offset(16, AVX2_NAME)
  } else if (size == 19) {
    AVX512_8__2
    *array_index += 16;
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  } else if (size == 18) {
    AVX512_8__2
    *array_index += 16;
    SSE_2__1
  } else if (size == 17) {
    // AVX512_8_mask4(2, AVX2_NAME)
    AVX512_8__2
    result_array[*array_index + 16] = log(input_array[*array_index + 16]);
  } else if (size == 16) {
    AVX512_8__2
  } else
    avx512_15(input_array, result_array, size, array_index);
}

#if 0
void vlog_avx512_32_group(const double *input_array, double *result_array,
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
void vlog_avx512(const double *input_array, double *result_array,
                 unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 16) {
    vlog_avx512_32_group(input_array, result_array, size);
  } else if (size == 16) {
    AVX512_8__2
  } else {
    avx512_15(input_array, result_array, size, array_index);
  }
}
#endif

/* kernel with vectorization up to AVX512 */
void vlog_avx512_16_group(const double *input_array, double *result_array,
                          unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 16) {
    unsigned int count = size >> 4;
    unsigned int rest = size & 15;
    for (int i = 0; i < count; i++) {
      AVX512_8__2
      *array_index += 16;
    }
    if (rest)
      avx512_15(input_array, result_array, rest, array_index);
  } else if (size == 16) {
    AVX512_8__2
  } else {
    avx512_15(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX512 */
void vlog_avx512(const double *input_array, double *result_array,
                 unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 8) {
    vlog_avx512_16_group(input_array, result_array, size);
  } else if (size == 8) {
    AVX512_8__1
  } else {
    avx512_7(input_array, result_array, size, array_index);
  }
}