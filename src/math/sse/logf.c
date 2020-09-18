#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128 _ZGVbN4v_logf(__m128 x);

#define SSE_NAME bN4v_logf

#include "../commonf/sse.c"

/*This function deals with size in 1~3 */
__attribute__((always_inline)) static inline void
sse_3(const float *input_array, float *result_array, int size,
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
sse_7(const float *input_array, float *result_array, int size,
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
    sse_3(input_array, result_array, size,
          array_index);
  }
}

/* kernel with vectorization up to SSE */
void vlogf_sse(const float *input_array, float *result_array,
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
      SSE_4__2
      *array_index += 8;
    }
    if (rest)
      sse_7(input_array, result_array, rest, array_index);
  }
  else if (size == 8)
  {
    SSE_4__2
  }
  else
  {
    sse_7(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to SSE */
void vlogf_sse_option1(const float *input_array, float *result_array,
                       unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 4)
  {
    unsigned int count = size >> 2;
    unsigned int rest = size & 3;
    for (int i = 0; i < count; i++)
    {
      SSE_4__1
      *array_index += 4;
    }
    if (rest)
      sse_3(input_array, result_array, rest, array_index);
  }
  else if (size == 4)
  {
    SSE_4__1
  }
  else
  {
    sse_3(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to SSE */
void vlogf_sse_option2(const float *input_array, float *result_array,
                       unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 4)
  {
    vlogf_sse_option1(input_array, result_array, size);
  }
  else if (size == 4)
  {
    SSE_4__1
  }
  else
  {
    sse_3(input_array, result_array, size, array_index);
  }
}