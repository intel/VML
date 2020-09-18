#include "vmath.h"
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

__m128d _ZGVbN2v_log(__m128d x);

#define SSE_NAME bN2v_log

#include "../common/sse.c"

/*This function deal with size in 1~3*/
__attribute__((always_inline)) inline void sse_3(const double *input_array,
                                                 double *result_array, int size,
                                                 int *array_index)
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

/*This function deal with size in 1~7*/
__attribute__((always_inline)) inline void sse_7(const double *input_array,
                                                 double *result_array, int size,
                                                 int *array_index)
{
  if (size == 7)
  {
    //SSE_2_mask2(3, SSE_NAME)
    SSE_2__3
    result_array[*array_index + 6] = log(input_array[*array_index + 6]);
  }
  else if (size == 6)
  {
    SSE_2__3
  }
  else if (size == 5)
  {
    //SSE_2_mask2(2, SSE_NAME)
    SSE_2__2
    result_array[*array_index + 4] = log(input_array[*array_index + 4]);
  }
  else if (size == 4)
  {
    SSE_2__2
  }
  else
  {
    sse_3(input_array, result_array, size, array_index);
  }
}

/*This function deal with size in 1~15*/
__attribute__((always_inline)) inline void sse_15(const double *input_array,
                                                  double *result_array,
                                                  int size, int *array_index)
{
  if (size == 15)
  {
    //SSE_2_mask2(7, SSE_NAME)
    SSE_2__7
    result_array[*array_index + 14] = log(input_array[*array_index + 14]);
  }
  else if (size == 14)
  {
    SSE_2__7
  }
  else if (size == 13)
  {
    //SSE_2_mask2(6, SSE_NAME)
    SSE_2__6
    result_array[*array_index + 12] = log(input_array[*array_index + 12]);
  }
  else if (size == 12)
  {
    SSE_2__6
  }
  else if (size == 11)
  {
    //SSE_2_mask2(5, SSE_NAME)
    SSE_2__5
    result_array[*array_index + 10] = log(input_array[*array_index + 10]);
  }
  else if (size == 10)
  {
    SSE_2__5
  }
  else if (size == 9)
  {
    //SSE_2_mask2(4, SSE_NAME)
    SSE_2__4
    result_array[*array_index + 8] = log(input_array[*array_index + 8]);
  }
  else if (size == 8)
  {
    SSE_2__4
  }
  else
  {
    sse_7(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to SSE */
void vlog_sse(const double *input_array, double *result_array,
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
      SSE_2__2
      *array_index += 4;
    }
    if (rest)
      sse_3(input_array, result_array, rest, array_index);
  }
  else if (size == 4)
  {
    SSE_2__2
  }
  else
  {
    sse_3(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to SSE */
void vlog_sse_option2(const double *input_array, double *result_array,
                      unsigned int size)
{
  int index = 0;
  int *array_index = &index;
  if (size > 2)
  {
    unsigned int count = size >> 1;
    unsigned int rest = size & 1;
    for (int i = 0; i < count; i++)
    {
      SSE_2__1
      *array_index += 2;
    }
    for (int i = 0; i < rest; i++)
      result_array[*array_index + i] = log(input_array[*array_index + i]);
  }
  else if (size == 2)
  {
    SSE_2__1
  }
  else
  {
    for (int i = 0; i < size; i++)
      result_array[*array_index + i] = log(input_array[*array_index + i]);
  }
}

/* kernel with vectorization up to SSE */
void vlog_sse_option3(const double *input_array, double *result_array,
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
      SSE_2__4
      *array_index += 8;
    }
    if (rest)
      sse_7(input_array, result_array, rest, array_index);
  }
  else if (size == 8)
  {
    SSE_2__4
  }
  else
  {
    sse_7(input_array, result_array, size, array_index);
  }
}

/* kernel with vectorization up to SSE */
void vlog_sse_option4(const double *input_array, double *result_array,
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
      SSE_2__8
      *array_index += 16;
    }
    if (rest)
      sse_15(input_array, result_array, rest, array_index);
  }
  else if (size == 16)
  {
    SSE_2__8
  }
  else
  {
    sse_15(input_array, result_array, size, array_index);
  }
}