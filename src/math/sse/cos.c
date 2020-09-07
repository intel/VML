#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_cos(__m128d x);

#define SSE_NAME bN2v_cos

#include "../common/sse.c"

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void sse_3(const double *input_array,
                                                 double *result_array, int size,
                                                 int *array_index) {
  if (size == 3) {
    SSE_2_mask2(1, SSE_NAME)
  } else if (size == 2) {
    SSE_2__1
  } else {
    SSE_2_mask2(0, SSE_NAME)
  }
}

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void sse_7(const double *input_array,
                                                 double *result_array, int size,
                                                 int *array_index) {
  if (size == 7) {
    SSE_2_mask2(3, SSE_NAME)
  } else if (size == 6) {
    SSE_2__3
  } else if (size == 5) {
    SSE_2_mask2(2, SSE_NAME)
  } else if (size == 4) {
    SSE_2__2
  } else {
    sse_3(input_array, result_array, size, array_index);
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void sse_15(const double *input_array,
                                                  double *result_array,
                                                  int size, int *array_index) {
  if (size == 15) {
    SSE_2_mask2(7, SSE_NAME)
  } else if (size == 14) {
    SSE_2__7
  } else if (size == 13) {
    SSE_2_mask2(6, SSE_NAME)
  } else if (size == 12) {
    SSE_2__6
  } else if (size == 11) {
    SSE_2_mask2(5, SSE_NAME)
  } else if (size == 10) {
    SSE_2__5
  } else if (size == 9) {
    SSE_2_mask2(4, SSE_NAME)
  } else if (size == 8) {
    SSE_2__4
  } else if (size == 7) {
    SSE_2_mask2(3, SSE_NAME)
  } else if (size == 6) {
    SSE_2__3
  } else if (size == 5) {
    SSE_2_mask2(2, SSE_NAME)
  } else if (size == 4) {
    SSE_2__2
  } else if (size == 3) {
    SSE_2_mask2(1, SSE_NAME)
  } else if (size == 2) {
    SSE_2__1
  } else if (size == 1) {
    SSE_2_mask2(0, SSE_NAME)
  }
}

/* kernel with vectorization up to SSE */
void vcos_sse(const double *input_array, double *result_array,
              unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 4) {
    unsigned int count = size >> 2;
    unsigned int rest = size & 3;
    for (int i = 0; i < count; i++) {
      SSE_2__2
      *array_index += 4;
    }
    if (rest)
      sse_3(input_array, result_array, rest, array_index);
  } else if (size == 4) {
    SSE_2__2
  } else {
    sse_3(input_array, result_array, size, array_index);
  }
}
