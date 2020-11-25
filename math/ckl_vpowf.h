#ifndef CKL_VPOWF_H
#define CKL_VPOWF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vpowf_func_t)(const float *, const float *, float *, unsigned int);
    static inline void vpowf_avx512(const float *input_array, const float *input_array1, float *result_array,
                                    unsigned int size);
    static inline void vpowf_avx2(const float *input_array, const float *input_array1, float *result_array,
                                  unsigned int size);
    static inline void vpowf_avx(const float *input_array, const float *input_array1, float *result_array,
                                 unsigned int size);
    static inline void vpowf_sse(const float *input_array, const float *input_array1, float *result_array,
                                 unsigned int size);
    static inline void vpowf_scalar(const float *input_array, const float *input_array1, float *result_array,
                                    unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vpowf(const float *input_array, const float *input_array1, float *result_array,
                   unsigned int size) __attribute__((ifunc("vpowf_ifunc")));
#else
void ckl_vpowf(const float *input_array, const float *input_array1, float *result_array,
               unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vpowf_func_t, vpowf, ckl_vpowf)

    __m128d _ZGVbN2vv_pow(__m128d x, __m128d y);
    __m256d _ZGVcN4vv_pow(__m256d x, __m256d y);
    __m256d _ZGVdN4vv_pow(__m256d x, __m256d y);
    __m512d _ZGVeN8vv_pow(__m512d x, __m512d y);

#include "commonf2d/avx_vv.h"
#include "commonf2d/avx512_vv.h"
#include "commonf2d/sse_vv.h"

#define NAME_AVX512_POWF2D eN8vv_pow
#define NAME_AVX2_POWF2D dN4vv_pow
#define NAME_AVX_POWF2D cN4vv_pow
#define NAME_SSE_POWF2D bN2vv_pow

    /************** ckl_vpowf *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX512
    vpowf_avx512_7(const float *input_array,
                   const float *input_array1,
                   float *result_array,
                   int size,
                   int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = powf(input_array[*array_index], input_array1[*array_index]);
        }
        else if (size == 2)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
        }
        else if (size == 3)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_vv_f2d_4_offset(0, NAME_AVX2_POWF2D);
        }
        else if (size == 5)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
            result_array[*array_index + 4] = powf(input_array[*array_index + 4], input_array1[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
        }
        else if (size == 7)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vpowf_avx512_15(const float *input_array, const float *input_array1, float *result_array, int size,
                    int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = powf(input_array[*array_index], input_array1[*array_index]);
            // SSE_2_mask2(0, SSE_NAME)
        }
        else if (size == 2)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
        }
        else if (size == 3)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
        else if (size == 13)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            AVX_vv_f2d_4_offset(8, NAME_AVX2_POWF2D);
            result_array[*array_index + 12] = powf(input_array[*array_index + 12], input_array1[*array_index + 12]);
        }
        else if (size == 14)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            AVX_vv_f2d_4_offset(8, NAME_AVX2_POWF2D);
            *array_index += 12;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8(1, AVX512_NAME)
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            AVX_vv_f2d_4_offset(8, NAME_AVX2_POWF2D);
            *array_index += 12;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
        else if (size == 12)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            AVX_vv_f2d_4_offset(8, NAME_AVX2_POWF2D);
        }
        else if (size == 11)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            *array_index += 8;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
        else if (size == 10)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            *array_index += 8;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
        }
        else if (size == 9)
        {
            // AVX512_8_mask4(1, AVX2_NAME)
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
            result_array[*array_index + 8] = powf(input_array[*array_index + 8], input_array1[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D);
        }
        else if (size == 5)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
            result_array[*array_index + 4] = powf(input_array[*array_index + 4], input_array1[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
        }
        else if (size == 7)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_vv_f2d_4_offset(0, NAME_AVX2_POWF2D);
        }
    }

    static inline void __CKL_FN_ATTR_AVX512 vpowf_avx512_16_group(const float *input_array,
                                                                  const float *input_array1,
                                                                  float *result_array,
                                                                  unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            unsigned int count = size >> 4;
            unsigned int rest = size & 15;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX512_vv_f2d_8__2(NAME_AVX512_POWF2D);
                *array_index += 16;
            }
            if (rest)
                vpowf_avx512_15(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_vv_f2d_8__2(NAME_AVX512_POWF2D)
        }
        else
        {
            vpowf_avx512_15(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512 vpowf_avx512(const float *input_array,
                                                         const float *input_array1,
                                                         float *result_array,
                                                         unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vpowf_avx512_16_group(input_array, input_array1, result_array, size);
        }
        else if (size == 8)
        {
            AVX512_vv_f2d_8__1(NAME_AVX512_POWF2D)
        }
        else
        {
            vpowf_avx512_7(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpowf *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vpowf_avx2_3(const float *input_array, const float *input_array1,
                 float *result_array, int size,
                 int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = powf(input_array[*array_index], input_array1[*array_index]);
        }
        else if (size == 2)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D)
        }
        else if (size == 3)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vpowf_avx2(const float *input_array, const float *input_array1, float *result_array,
               unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_vv_f2d_4__1(NAME_AVX2_POWF2D);
                *array_index += 4;
            }
            if (rest)
                vpowf_avx2_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_vv_f2d_4__1(NAME_AVX2_POWF2D)
        }
        else
        {
            vpowf_avx2_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpowf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vpowf_avx_3(const float *input_array,
                const float *input_array1,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = powf(input_array[*array_index], input_array1[*array_index]);
        }
        else if (size == 2)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D)
        }
        else if (size == 3)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vpowf_avx(const float *input_array, const float *input_array1, float *result_array,
              unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_vv_f2d_2__2(NAME_SSE_POWF2D);
                *array_index += 4;
            }
            if (rest)
                vpowf_avx_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_vv_f2d_2__2(NAME_SSE_POWF2D)
        }
        else
        {
            vpowf_avx_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpowf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vpowf_sse_3(const float *input_array,
                const float *input_array1,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = powf(input_array[*array_index], input_array1[*array_index]);
        }
        else if (size == 2)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D)
        }
        else if (size == 3)
        {
            SSE_vv_f2d_2__1(NAME_SSE_POWF2D);
            result_array[*array_index + 2] = powf(input_array[*array_index + 2], input_array1[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vpowf_sse(const float *input_array, const float *input_array1, float *result_array,
              unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_vv_f2d_2__2(NAME_SSE_POWF2D);
                *array_index += 4;
            }
            if (rest)
                vpowf_sse_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_vv_f2d_2__2(NAME_SSE_POWF2D)
        }
        else
        {
            vpowf_sse_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpowf *****************/
    static inline void vpowf_scalar(const float *input_array, const float *input_array1,
                                    float *result_array, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            result_array[i] = powf(input_array[i], input_array1[i]);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VPOWF_H*/
