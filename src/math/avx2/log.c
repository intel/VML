#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_log(__m128d x);
//__m256d _ZGVcN4v_log(__m256d x);
__m256d _ZGVdN4v_log(__m256d x);

#define AVX2_NAME dN4v_log
#define SSE_NAME bN2v_log

#include "../common/avx2.c"
#include "../common/sse.c"
#include "../common/avx.c"

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void avx2_7(const double *input_array,
                                                  double *result_array,
                                                  int size, int *array_index)
{
  if (size == 1)
  {
    result_array[*array_index] = log(input_array[*array_index]);
  }
  else if (size == 2)
  {
    SSE_2__1
  }
  else if (size == 3)
  {
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  }
  else if (size == 4)
  {
    AVX_4_offset(0, AVX2_NAME)
  }
  else if (size == 5)
  {
    AVX2_4__1
    result_array[*array_index + 4] = log(input_array[*array_index + 4]);
  }
  else if (size == 6)
  {
    AVX2_4__1
    *array_index += 4;
    SSE_2__1
  }
  else if (size == 7)
  {
    AVX2_4__1
    *array_index += 4;
    SSE_2__1
    // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
    // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  }
}

/*This function deal with size in 1~3*/
__attribute__((always_inline)) inline void avx2_3(const double *input_array,
                                                  double *result_array,
                                                  int size, int *array_index)
{
  if (size == 1)
  {
    result_array[*array_index] = log(input_array[*array_index]);
  }
  else if (size == 2)
  {
    SSE_2__1
  }
  else if (size == 3)
  {
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void avx2_15(const double *input_array,
                                                   double *result_array,
                                                   int size, int *array_index)
{
  if (size == 15)
  {
    AVX2_4__3
    *array_index += 12;
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  }
  else if (size == 14)
  {
    AVX2_4__3
    *array_index += 12;
    SSE_2__1
  }
  else if (size == 13)
  {
    AVX2_4__3
    result_array[*array_index + 12] = log(input_array[*array_index + 12]);
  }
  else if (size == 12)
  {
    AVX2_4__3
  }
  else if (size == 11)
  {
    AVX2_4__2
    *array_index += 8;
    SSE_2__1
    result_array[*array_index + 2] = log(input_array[*array_index + 2]);
  }
  else if (size == 10)
  {
    AVX2_4__2
    *array_index += 8;
    SSE_2__1
  }
  else if (size == 9)
  {
    AVX2_4__2
    result_array[*array_index + 8] = log(input_array[*array_index + 8]);
  }
  else if (size == 8)
  {
    AVX2_4__2
  }
  else
  {
    avx2_7(input_array, result_array, size, array_index);
  }
}

#if 0
/* kernel with vectorization up to AVX2 */
void vlog_avx2(const double *input_array, double *result_array,
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
      AVX2_4__2
      *array_index += 8;
    }
    if (rest)
      avx2_7(input_array, result_array, rest, array_index);
  }
  else if (size == 8)
  {
    AVX2_4__2
  }
  else
  {
    avx2_7(input_array, result_array, size, array_index);
  }
}
#endif

/* kernel with vectorization up to AVX2 */
void vlog_avx2(const double *input_array, double *result_array,
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
      AVX2_4__1
      *array_index += 4;
    }
    if (rest)
      avx2_3(input_array, result_array, rest, array_index);
  }
  else if (size == 4)
  {
    AVX2_4__1
  }
  else
  {
    avx2_3(input_array, result_array, size, array_index);
  }
}

#if 0
/* kernel with vectorization up to AVX2 */
void vlog_avx2(const double *input_array, double *result_array,
               unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 16)
  {
    unsigned int count = size >> 4;
    unsigned int rest = size & 15;
    for (int i = 0; i < count; i++)
    {
      AVX2_4__4
      *array_index += 16;
    }
    if (rest)
      avx2_15(input_array, result_array, rest, array_index);
  }
  else if (size == 16)
  {
    AVX2_4__4
  }
  else
  {
    avx2_15(input_array, result_array, size, array_index);
  }
}
#endif