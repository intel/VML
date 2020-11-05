#ifndef CKL_VEXPF_H
#define CKL_VEXPF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vexpf_func_t)(const float *, float *, unsigned int);
    static inline void vexpf_avx512(const float *input_array, float *result_array,
                                    unsigned int size);
    static inline void vexpf_avx2(const float *input_array, float *result_array,
                                  unsigned int size);
    static inline void vexpf_avx(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vexpf_sse(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vexpf_scalar(const float *input_array, float *result_array,
                                    unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vexpf(const float *input_array, float *result_array,
                   unsigned int size) __attribute__((ifunc("vexpf_ifunc")));
#else
void ckl_vexpf(const float *input_array, float *result_array,
               unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vexpf_func_t, vexpf, ckl_vexpf)

    __m128d _ZGVbN2v_exp(__m128d x);
    __m256d _ZGVcN4v_exp(__m256d x);
    __m256d _ZGVdN4v_exp(__m256d x);
    __m512d _ZGVeN8v_exp(__m512d x);

#include "commonf2d/avx.h"
#include "commonf2d/avx512.h"
#include "commonf2d/sse.h"

#define NAME_AVX512_EXPF2D eN8v_exp
#define NAME_AVX2_EXPF2D dN4v_exp
#define NAME_AVX_EXPF2D cN4v_exp
#define NAME_SSE_EXPF2D bN2v_exp

    /************** ckl_vexpf *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX512
    vexpf_avx512_7(const float *input_array,
                   float *result_array,
                   int size,
                   int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = expf(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
        }
        else if (size == 3)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_f2d_4_offset(0, NAME_AVX2_EXPF2D);
        }
        else if (size == 5)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D);
            result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
        }
        else if (size == 7)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            // result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = expf(input_array[*array_index + 5]);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vexpf_avx512_15(const float *input_array, float *result_array, int size,
                    int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = expf(input_array[*array_index]);
            // SSE_2_mask2(0, SSE_NAME)
        }
        else if (size == 2)
        {
            // result_array[*array_index] = expf(input_array[*array_index]);
            // result_array[*array_index + 1] = expf(input_array[*array_index + 1]);
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
        }
        else if (size == 3)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
        else if (size == 13)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset(8, NAME_AVX2_EXPF2D);
            result_array[*array_index + 12] = expf(input_array[*array_index + 12]);
        }
        else if (size == 14)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset(8, NAME_AVX2_EXPF2D);
            *array_index += 12;
            SSE_f2d_2__1(NAME_SSE_EXPF2D)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8(1, AVX512_NAME)
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset(8, NAME_AVX2_EXPF2D);
            *array_index += 12;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
        else if (size == 12)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset(8, NAME_AVX2_EXPF2D);
        }
        else if (size == 11)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            *array_index += 8;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
        else if (size == 10)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            *array_index += 8;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
        }
        else if (size == 9)
        {
            // AVX512_8_mask4(1, AVX2_NAME)
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
            result_array[*array_index + 8] = expf(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D);
        }
        else if (size == 5)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D);
            result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            // result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = expf(input_array[*array_index + 5]);
        }
        else if (size == 7)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            // result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = expf(input_array[*array_index + 5]);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_f2d_4_offset(0, NAME_AVX2_EXPF2D);
        }
    }

    static inline void __CKL_FN_ATTR_AVX512 vexpf_avx512_16_group(const float *input_array, float *result_array,
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
                AVX512_f2d_8__2(NAME_AVX512_EXPF2D);
                *array_index += 16;
            }
            if (rest)
                vexpf_avx512_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_f2d_8__2(NAME_AVX512_EXPF2D)
        }
        else
        {
            vexpf_avx512_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512 vexpf_avx512(const float *input_array, float *result_array,
                                                         unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vexpf_avx512_16_group(input_array, result_array, size);
        }
        else if (size == 8)
        {
            AVX512_f2d_8__1(NAME_AVX512_EXPF2D)
        }
        else
        {
            vexpf_avx512_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexpf *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vexpf_avx2_3(const float *input_array, float *result_array, int size,
                 int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = expf(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vexpf_avx2(const float *input_array, float *result_array,
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
                AVX_f2d_4__1(NAME_AVX2_EXPF2D);
                *array_index += 4;
            }
            if (rest)
                vexpf_avx2_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_f2d_4__1(NAME_AVX2_EXPF2D)
        }
        else
        {
            vexpf_avx2_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexpf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vexpf_avx_3(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = expf(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vexpf_avx(const float *input_array, float *result_array,
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
                SSE_f2d_2__2(NAME_SSE_EXPF2D);
                *array_index += 4;
            }
            if (rest)
                vexpf_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_f2d_2__2(NAME_SSE_EXPF2D)
        }
        else
        {
            vexpf_avx_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexpf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vexpf_sse_3(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = expf(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1(NAME_SSE_EXPF2D);
            result_array[*array_index + 2] = expf(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vexpf_sse(const float *input_array, float *result_array,
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
                SSE_f2d_2__2(NAME_SSE_EXPF2D);
                *array_index += 4;
            }
            if (rest)
                vexpf_sse_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_f2d_2__2(NAME_SSE_EXPF2D)
        }
        else
        {
            vexpf_sse_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexpf *****************/
    static inline void vexpf_scalar(const float *input_array, float *result_array,
                                    unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            result_array[i] = expf(input_array[i]);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VEXPF_H*/
