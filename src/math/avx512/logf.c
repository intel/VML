#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128 _ZGVbN4v_logf(__m128 x);
__m256 _ZGVcN8v_logf(__m256 x);
__m256 _ZGVdN8v_logf(__m256 x);
__m512 _ZGVeN16v_logf(__m512 x);

#define AVX512_NAME eN16v_logf
#define AVX2_NAME dN8v_logf
#define AVX_NAME cN8v_logf
#define SSE_NAME bN4v_logf

#include "../commonf/avx.c"
#include "../commonf/avx2.c"
#include "../commonf/avx512.c"
#include "../commonf/sse.c"

/*This function deals with size in 1~3 */
__attribute__((always_inline)) static inline void
avx512_3(const float *input_array, float *result_array, int size,
         int *array_index)
{
  if (size == 1)
  {
    result_array[*array_index] = logf(input_array[*array_index]);
  }
  else if (size == 2)
  {
    result_array[*array_index] = logf(input_array[*array_index]);
    result_array[*array_index + 1] = logf(input_array[*array_index + 1]);
  }
  else if (size == 3)
  {
    result_array[*array_index] = logf(input_array[*array_index]);
    result_array[*array_index + 1] = logf(input_array[*array_index + 1]);
    result_array[*array_index + 2] = logf(input_array[*array_index + 2]);
  }
}

/*This function deals with size in 1~7 */
__attribute__((always_inline)) static inline void
avx512_7(const float *input_array, float *result_array, int size,
         int *array_index)
{
  if (size == 7)
  {
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
    result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
    result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
  }
  else if (size == 6)
  {
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
    result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
  }
  else if (size == 5)
  {
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
  }
  else if (size == 4)
  {
    SSE_4__1
  }
  else
  {
    avx512_3(input_array, result_array, size,
             array_index);
  }
}

/*This function deals with size in 1~15 */
__attribute__((always_inline)) static inline void
avx512_15(const float *input_array, float *result_array, int size,
          int *array_index)
{
  if (size <= 15 && size >= 12)
  {
    AVX512_16_mask16(0, AVX512_NAME)
  }
  else if (size == 11)
  {
    AVX2_8__1
    result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
    result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
    result_array[*array_index + 10] = logf(input_array[*array_index + 10]);
  }
  else if (size == 10)
  {
    AVX2_8__1
    result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
    result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
  }
  else if (size == 9)
  {
    AVX2_8__1
    result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
  }
  else if (size == 8)
  {
    AVX2_8__1
  }
  else
  {
    avx512_7(input_array, result_array, size,
             array_index);
  }
}

/*This function deals with size in 1~31 */
__attribute__((always_inline)) static inline void
avx512_31(const float *input_array, float *result_array, int size,
          int *array_index)
{
  if (size <= 31 && size >= 26)
  {
    AVX512_16_mask16(1, AVX512_NAME)
  }
  else if (size == 25)
  {
    AVX512_16__1
    AVX_8_offset(16, AVX2_NAME);
    result_array[*array_index + 24] = logf(input_array[*array_index + 24]);
  }
  else if (size == 24)
  {
    AVX512_16__1
    AVX_8_offset(16, AVX2_NAME)
  }
  else if (size == 23)
  {
    //AVX512_16_mask8(1, AVX2_NAME)
    AVX512_16__1
    *array_index += 16;
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
    result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
    result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
  }
  else if (size == 22)
  {
    AVX512_16__1
    *array_index += 16;
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
    result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
  }
  else if (size == 21)
  {
    AVX512_16__1
    *array_index += 16;
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
  }
  else if (size == 20)
  {
    AVX512_16__1
    *array_index += 16;
    SSE_4__1
  }
  else if (size == 19)
  {
    AVX512_16__1
    result_array[*array_index + 16] = logf(input_array[*array_index + 16]);
    result_array[*array_index + 17] = logf(input_array[*array_index + 17]);
    result_array[*array_index + 18] = logf(input_array[*array_index + 18]);
  }
  else if (size == 18)
  {
    AVX512_16__1
    result_array[*array_index + 16] = logf(input_array[*array_index + 16]);
    result_array[*array_index + 17] = logf(input_array[*array_index + 17]);
  }
  else if (size == 17)
  {
    AVX512_16__1
    result_array[*array_index + 16] = logf(input_array[*array_index + 16]);
  }
  else if (size == 16)
  {
    AVX512_16__1
  }
  else
  {
    //AVX512_16_mask4(0, SSE_NAME)
    avx512_15(input_array, result_array, size, array_index);
  }
}

/*This function deals with size in 1~63 */
__attribute__((always_inline)) static inline void
avx512_63(const float *input_array, float *result_array, int size,
          int *array_index)
{
  if (size <= 63 && size >= 57)
  {
    AVX512_16_mask16(3, AVX512_NAME)
  }
  else if (size == 56)
  {
    AVX512_16__3
    AVX_8_offset(48, AVX2_NAME)
  }
  else if (size <= 55 && size >= 49)
  {
    AVX512_16_mask8(3, AVX2_NAME)
  }
  else if (size == 48)
  {
    AVX512_16__3
  }
  else if (size <= 47 && size >= 41)
  {
    AVX512_16_mask16(2, AVX512_NAME)
  }
  else if (size == 40)
  {
    AVX512_16__2
    AVX_8_offset(32, AVX2_NAME)
  }
  else if (size <= 39 && size >= 33)
  {
    AVX512_16_mask8(2, AVX2_NAME)
  }
  else if (size == 32)
  {
    AVX512_16__2
  }
  else
  {
    avx512_31(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX512 */
void vlogf_avx512(const float *input_array, float *result_array,
                  unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 31)
  {
    unsigned int count = size >> 5;
    unsigned int rest = size & 31;
    for (int i = 0; i < count; i++)
    {
      AVX512_16__2
      *array_index += 32;
    }
    if (rest)
      avx512_31(input_array, result_array, rest, array_index);
  }
  else
  {
    avx512_31(input_array, result_array, size, array_index);
  }
}