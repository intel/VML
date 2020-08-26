#include "cpu.h"
#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_sin(__m128d x);
__m256d _ZGVcN4v_sin(__m256d x);
__m256d _ZGVdN4v_sin(__m256d x);
__m512d _ZGVeN8v_sin(__m512d x);

void vsin_avx512(const double *input_array, double *result_array,
                 unsigned int size);
void vsin_scalar(const double *input_array, double *result_array,
                 unsigned int size);
static int (*funcs[])(const double *, double *, unsigned int) = {
    vsin_avx512, vsin_scalar, vsin_scalar, vsin_scalar, vsin_scalar};

/* kernel with vectorization up to AVX512 */
void vsin_avx512(const double *input_array, double *result_array,
                 unsigned int size) {
  if (size > 32) {
    unsigned int tail_index_4 = size & (~3);
    unsigned int tail_index_8 = size & (~7);
    unsigned int tail_index_15 = size & (~15);

    for (unsigned int i = 0; i < tail_index_15; i += 16) {
      _mm512_storeu_pd(&result_array[i],
                       _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[i])));
      _mm512_storeu_pd(&result_array[i + 8],
                       _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[i + 8])));
    }

    for (unsigned int i = tail_index_15; i < tail_index_8; i += 8) {
      _mm512_storeu_pd(&result_array[i],
                       _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[i])));
    }

    if (tail_index_4 > tail_index_8) {
      _mm256_storeu_pd(
          &result_array[tail_index_8],
          _ZGVdN4v_sin(_mm256_loadu_pd(&input_array[tail_index_8])));
    }

    if (size > tail_index_4) {
      unsigned char tail_mask_uint =
          (((unsigned char)0xff) >> (8 - (size & 3)));
      __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);
      _mm256_mask_storeu_pd(&result_array[tail_index_4], tail_mask,
                            _ZGVdN4v_sin(_mm256_maskz_loadu_pd(
                                tail_mask, &input_array[tail_index_4])));
    }
  } else if (size == 32) {
    _mm512_storeu_pd(&result_array[0],
                     _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[0])));
    _mm512_storeu_pd(&result_array[8],
                     _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[8])));
    _mm512_storeu_pd(&result_array[16],
                     _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[16])));
    _mm512_storeu_pd(&result_array[24],
                     _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[24])));
  } else {
    if (size > 8) {
      unsigned int tail_index_4 = size & (~3);
      unsigned int tail_index_8 = size & (~7);

      for (unsigned int i = 0; i < tail_index_8; i += 8) {
        _mm512_storeu_pd(&result_array[i],
                         _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[i])));
      }

      if (tail_index_4 > tail_index_8) {
        _mm256_storeu_pd(
            &result_array[tail_index_8],
            _ZGVdN4v_sin(_mm256_loadu_pd(&input_array[tail_index_8])));
      }

      if (size > tail_index_4) {
        unsigned char tail_mask_uint =
            (((unsigned char)0xff) >> (8 - (size & 3)));
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);
        _mm256_mask_storeu_pd(&result_array[tail_index_4], tail_mask,
                              _ZGVdN4v_sin(_mm256_maskz_loadu_pd(
                                  tail_mask, &input_array[tail_index_4])));
      }
    } else if (size == 8) {
      _mm512_storeu_pd(&result_array[0],
                       _ZGVeN8v_sin(_mm512_loadu_pd(&input_array[0])));
    } else {
      if (size > 4) {
        if (size == 7) {
          unsigned char tail_mask_uint = (((unsigned char)0xff) >> (8 - size));
          __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);
          _mm512_mask_storeu_pd(
              &result_array[0], tail_mask,
              _ZGVeN8v_sin(_mm512_maskz_loadu_pd(tail_mask, &input_array[0])));
        } else if (size == 6) {
          _mm256_storeu_pd(&result_array[0],
                           _ZGVdN4v_sin(_mm256_loadu_pd(&input_array[0])));
          _mm_storeu_pd(&result_array[4],
                        _ZGVbN2v_sin(_mm_loadu_pd(&input_array[4])));
        } else {
          _mm256_storeu_pd(&result_array[0],
                           _ZGVdN4v_sin(_mm256_loadu_pd(&input_array[0])));
          result_array[4] = sin(input_array[4]);
        }
      } else if (size == 4) {
        _mm256_storeu_pd(&result_array[0],
                         _ZGVdN4v_sin(_mm256_loadu_pd(&input_array[0])));
      } else if (size == 3) {
        unsigned char tail_mask_uint = (((unsigned char)0xff) >> 5);
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);
        _mm256_mask_storeu_pd(
            &result_array[0], tail_mask,
            _ZGVdN4v_sin(_mm256_maskz_loadu_pd(tail_mask, &input_array[0])));
      } else if (size == 2) {
        _mm_storeu_pd(&result_array[0],
                      _ZGVbN2v_sin(_mm_loadu_pd(&input_array[0])));
      } else {
        result_array[0] = sin(input_array[0]);
      }
    }
  }
}

/* kernel with vectorization up to AVX2 */
// void vsin_avx2  (const double * input_array, double * result_array, unsigned
// int size);

/* kernel with vectorization up to AVX */
// void vsin_avx   (const double * input_array, double * result_array, unsigned
// int size);

/* kernel with vectorization up to SSE */
// void vsin_sse   (const double * input_array, double * result_array, unsigned
// int size);

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
