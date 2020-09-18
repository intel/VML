#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128 _ZGVbN4v_logf(__m128 x);
__m256 _ZGVcN8v_logf(__m256 x);
__m256 _ZGVdN8v_logf(__m256 x);

#define AVX2_NAME dN8v_logf
#define AVX_NAME cN8v_logf
#define SSE_NAME bN4v_logf

#include "../commonf/avx.c"
#include "../commonf/avx2.c"
#include "../commonf/sse.c"

/*This function deals with size in 1~3 */
__attribute__((always_inline)) static inline void
avx2_3(const float *input_array, float *result_array, int size,
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
avx2_7(const float *input_array, float *result_array, int size,
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
    avx2_3(input_array, result_array, size, array_index);
    //AVX2_8_mask4(0, SSE_NAME)
  }
}

/*This function deals with size in 1~15 */
__attribute__((always_inline)) static inline void
avx2_15(const float *input_array, float *result_array, int size,
        int *array_index)
{
  if (size == 15)
  {
    AVX2_8__1
    *array_index += 8;
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
    result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
    result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
  }
  else if (size == 14)
  {
    AVX2_8__1
    *array_index += 8;
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
    result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
  }
  else if (size == 13)
  {
    AVX2_8__1
    *array_index += 8;
    SSE_4__1
    result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
  }
  else if (size == 14)
  {
    AVX2_8__1
    *array_index += 8;
    SSE_4__1
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
    avx2_7(input_array, result_array, size,
           array_index);
  }
}

/* kernel with vectorization up to AVX2 */
void vlogf_avx2_option1(const float *input_array, float *result_array,
                        unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 16)
  {
    unsigned int count = size >> 5;
    unsigned int rest = size & 15;
    for (int i = 0; i < count; i++)
    {
      AVX2_8__2
      *array_index += 16;
    }
    if (rest)
      avx2_15(input_array, result_array, rest, array_index);
  }
  else if (size == 16)
  {
    AVX2_8__2
  }
  else
  {
    avx2_15(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to AVX2 */
void vlogf_avx2_option2(const float *input_array, float *result_array,
                        unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  unsigned int count_8 = size >> 3;
  unsigned int rest_8 = size & 7;
  unsigned int count_4 = rest_8 >> 2;
  unsigned int rest_4 = rest_8 & 3;
  for (int i = 0; i < count_8; i++)
  {
    AVX2_8__1
    *array_index += 8;
  }
  for (int i = 0; i < count_4; i++)
  {
    SSE_4__1
    *array_index += 4;
  }
  for (int i = 0; i < rest_4; i++)
    result_array[*array_index + i] = logf(input_array[*array_index + i]);
}

/* kernel with vectorization up to AVX2 */
void vlogf_avx2(const float *input_array, float *result_array,
                unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 8)
  {
    unsigned int count = size >> 3;
    unsigned int rest = size & 7;
    for (int i = 0; i < count; i++)
    {
      AVX2_8__1
      *array_index += 8;
    }
    if (rest)
      avx2_7(input_array, result_array, rest, array_index);
  }
  else if (size == 8)
  {
    AVX2_8__1
  }
  else
  {
    avx2_7(input_array, result_array, size, array_index);
  }
}