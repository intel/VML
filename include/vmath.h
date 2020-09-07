#ifndef _VMATH_H
#define _VMATH_H

#define INDEX_AVX512 0
#define INDEX_AVX2 1
#define INDEX_AVX 2
#define INDEX_SSE2 3
#define INDEX_NON_VECTOR 4

extern int func_index;

void ckl_vsin(const double *input_array, double *result_array,
              unsigned int size);
void ckl_vsinf(const float *input_array, float *result_array,
               unsigned int size);
void ckl_vcos(const double *input_array, double *result_array,
              unsigned int size);

#endif // END OF THIS HEADER FILE