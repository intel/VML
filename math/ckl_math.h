#ifndef CKL_MATH_H
#define CKL_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size);

#if defined(__AVX512F__)
__m128d _ZGVbN2v_sin(__m128d x);
__m256d _ZGVcN4v_sin(__m256d x);
__m256d _ZGVdN4v_sin(__m256d x);
__m512d _ZGVeN8v_sin(__m512d x);

#include "common/avx.c"
#include "common/avx512.c"
#include "common/sse.c"

/************** ckl_vsin *****************/
/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void
vsin_avx512_15(const double *input_array, double *result_array, int size,
               int *array_index) {
  if (size == 13 || size == 14 || size == 15) {
    AVX512_8_mask8(1, eN8v_sin)
  } else if (size == 12) {
    AVX512_8__1(eN8v_sin)
    AVX_4_offset(8, dN4v_sin)
  } else if (size == 11 || size == 10 || size == 9) {
    AVX512_8_mask4(1, eN8v_sin, dN4v_sin)
  } else if (size == 8) {
    AVX512_8__1(eN8v_sin)
  } else if (size == 5 || size == 6 || size == 7) {
    AVX512_8_mask8(0, eN8v_sin)
  } else if (size == 4) {
    AVX_4_offset(0, dN4v_sin)
  } else {
    AVX512_8_mask4(0, eN8v_sin, dN4v_sin)
  }
}

/*This function deals with size in 1~31 */
__attribute__((always_inline)) inline void
vsin_avx512_31(const double *input_array, double *result_array, int size,
               int *array_index) {
  if (size == 31 || size == 30 || size == 29) {
    AVX512_8_mask8(3, eN8v_sin)
  } else if (size == 28) {
    AVX512_8__3(eN8v_sin)
    AVX_4_offset(24, dN4v_sin)
  } else if (size == 27 || size == 26 || size == 25) {
    AVX512_8_mask4(3, eN8v_sin, dN4v_sin)
  } else if (size == 24) {
    AVX512_8__3(eN8v_sin)
  } else if (size == 23 || size == 22 || size == 21) {
    AVX512_8_mask8(2, eN8v_sin)
  } else if (size == 20) {
    AVX512_8__2(eN8v_sin)
    AVX_4_offset(16, dN4v_sin)
  } else if (size == 19 || size == 18 || size == 17) {
    AVX512_8_mask4(2, eN8v_sin, dN4v_sin)
  } else if (size == 16) {
    AVX512_8__2(eN8v_sin)
  } else
    vsin_avx512_15(input_array, result_array, size, array_index);
}

void vsin_avx512_sub(const double *input_array, double *result_array,
                     unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 32) {
    unsigned int count = size >> 5;
    unsigned int rest = size & 31;
    for (int i = 0; i < 2 * count; i++) {
      AVX512_8__2(eN8v_sin)
      *array_index += 16;
    }
    if (rest)
      vsin_avx512_31(input_array, result_array, rest, array_index);
  } else if (size == 32) {
    AVX512_8__4(eN8v_sin)
  } else {
    vsin_avx512_31(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX512 */
void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 16) {
    vsin_avx512_sub(input_array, result_array, size);
  } else if (size == 16) {
    AVX512_8__2(eN8v_sin)
  } else {
    vsin_avx512_15(input_array, result_array, size, array_index);
  }
}

#elif defined(__AVX2__)
__m128d _ZGVbN2v_sin(__m128d x);
__m256d _ZGVcN4v_sin(__m256d x);
__m256d _ZGVdN4v_sin(__m256d x);

#include "common/avx.c"
#include "common/sse.c"

/************** ckl_vsin *****************/
/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void
vsin_avx2_7(const double *input_array, double *result_array, int size,
            int *array_index) {
  if (size == 7 || size == 6 || size == 5) {
    AVX_4_mask4(1, dN4v_sin)
  } else if (size == 4) {
    AVX_4__1(dN4v_sin)
  } else {
    AVX_4_mask4(0, dN4v_sin)
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void
vsin_avx2_15(const double *input_array, double *result_array, int size,
             int *array_index) {
  if (size == 13 || size == 14 || size == 15) {
    AVX_4_mask4(3, dN4v_sin)
  } else if (size == 12) {
    AVX_4__3(dN4v_sin)
  } else if (size == 11 || size == 10 || size == 9) {
    AVX_4_mask4(2, dN4v_sin)
  } else if (size == 8) {
    AVX_4__2(dN4v_sin)
  } else if (size == 5 || size == 6 || size == 7) {
    AVX_4_mask4(1, dN4v_sin)
  } else if (size == 4) {
    AVX_4__1(dN4v_sin)
  } else {
    AVX_4_mask4(0, dN4v_sin)
  }
}

/* kernel with vectorization up to AVX2 */
void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 8) {
    unsigned int count = size >> 3;
    unsigned int rest = size & 7;
    for (int i = 0; i < count; i++) {
      AVX_4__2(dN4v_sin)
      *array_index += 8;
    }
    if (rest)
      vsin_avx2_7(input_array, result_array, rest, array_index);
  } else if (size == 8) {
    AVX_4__2(dN4v_sin)
  } else {
    vsin_avx2_7(input_array, result_array, size, array_index);
  }
}

#elif defined(__AVX__)
__m128d _ZGVbN2v_sin(__m128d x);
__m256d _ZGVcN4v_sin(__m256d x);

#include "common/avx.c"
#include "common/sse.c"

/************** ckl_vsin *****************/
/*This function deal with size in 1~3*/
__attribute__((always_inline)) inline void vsin_avx_3(const double *input_array,
                                                      double *result_array,
                                                      int size,
                                                      int *array_index) {
  if (size == 3) {
    SSE_2_mask2(1, bN2v_sin)
  } else if (size == 2) {
    SSE_2__1(bN2v_sin)
  } else {
    SSE_2_mask2(0, bN2v_sin)
  }
}

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void vsin_avx_7(const double *input_array,
                                                      double *result_array,
                                                      int size,
                                                      int *array_index) {
  if (size == 7 || size == 6) {
    AVX_4_mask4(1, cN4v_sin)
  } else if (size == 5) {
    AVX_4_mask2(1, cN4v_sin, bN2v_sin)
  } else if (size == 4) {
    AVX_4__1(cN4v_sin)
  } else if (size == 3) {
    SSE_2__1(bN2v_sin)
    *array_index += 2;
    SSE_2_mask2(0, bN2v_sin)
  } else if (size == 2)
    SSE_2__1(bN2v_sin)
  else {
    AVX_4_mask2(0, cN4v_sin, bN2v_sin)
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void
vsin_avx_15(const double *input_array, double *result_array, int size,
            int *array_index) {
  if (size == 13 || size == 14 || size == 15) {
    AVX_4_mask4(3, cN4v_sin)
  } else if (size == 12) {
    AVX_4__3(cN4v_sin)
  } else if (size == 11 || size == 10 || size == 9) {
    AVX_4_mask4(2, cN4v_sin)
  } else if (size == 8) {
    AVX_4__2(cN4v_sin)
  } else {
    vsin_avx_7(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX */
void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 4) {
    unsigned int count = size >> 2;
    unsigned int rest = size & 3;
    for (int i = 0; i < count; i++) {
      SSE_2__2(bN2v_sin)
      *array_index += 4;
    }
    if (rest)
      vsin_avx_3(input_array, result_array, rest, array_index);
  } else if (size == 4) {
    SSE_2__2(bN2v_sin)
  } else {
    vsin_avx_3(input_array, result_array, size, array_index);
  }
}

#elif defined(__SSE2__)
__m128d _ZGVbN2v_sin(__m128d x);

#include "common/sse.c"

/************** ckl_vsin *****************/
/*This function deal with size in 1~3*/
__attribute__((always_inline)) inline void vsin_sse_3(const double *input_array,
                                                      double *result_array,
                                                      int size,
                                                      int *array_index) {
  if (size == 3) {
    SSE_2_mask2(1, bN2v_sin)
  } else if (size == 2) {
    SSE_2__1(bN2v_sin)
  } else {
    SSE_2_mask2(0, bN2v_sin)
  }
}

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void vsin_sse_7(const double *input_array,
                                                      double *result_array,
                                                      int size,
                                                      int *array_index) {
  if (size == 7) {
    SSE_2_mask2(3, bN2v_sin)
  } else if (size == 6) {
    SSE_2__3(bN2v_sin)
  } else if (size == 5) {
    SSE_2_mask2(2, bN2v_sin)
  } else if (size == 4) {
    SSE_2__2(bN2v_sin)
  } else {
    vsin_sse_3(input_array, result_array, size, array_index);
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void
vsin_sse_15(const double *input_array, double *result_array, int size,
            int *array_index) {
  if (size == 15) {
    SSE_2_mask2(7, bN2v_sin)
  } else if (size == 14) {
    SSE_2__7(bN2v_sin)
  } else if (size == 13) {
    SSE_2_mask2(6, bN2v_sin)
  } else if (size == 12) {
    SSE_2__6(bN2v_sin)
  } else if (size == 11) {
    SSE_2_mask2(5, bN2v_sin)
  } else if (size == 10) {
    SSE_2__5(bN2v_sin)
  } else if (size == 9) {
    SSE_2_mask2(4, bN2v_sin)
  } else if (size == 8) {
    SSE_2__4(bN2v_sin)
  } else if (size == 7) {
    SSE_2_mask2(3, bN2v_sin)
  } else if (size == 6) {
    SSE_2__3(bN2v_sin)
  } else if (size == 5) {
    SSE_2_mask2(2, bN2v_sin)
  } else if (size == 4) {
    SSE_2__2(bN2v_sin)
  } else if (size == 3) {
    SSE_2_mask2(1, bN2v_sin)
  } else if (size == 2) {
    SSE_2__1(bN2v_sin)
  } else if (size == 1) {
    SSE_2_mask2(0, bN2v_sin)
  }
}

/* kernel with vectorization up to SSE */
void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size) {
  int index = 0;
  int *array_index = &index;
  if (size > 4) {
    unsigned int count = size >> 2;
    unsigned int rest = size & 3;
    for (int i = 0; i < count; i++) {
      SSE_2__2(bN2v_sin)
      *array_index += 4;
    }
    if (rest)
      vsin_sse_3(input_array, result_array, rest, array_index);
  } else if (size == 4) {
    SSE_2__2(bN2v_sin)
  } else {
    vsin_sse_3(input_array, result_array, size, array_index);
  }
}

#else
/************** ckl_vsin *****************/
void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    result_array[i] = sin(input_array[i]);
  }
}
#endif

#ifdef __cplusplus
}
#endif

#endif /*CKL_MATH_H*/