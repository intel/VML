#ifndef CKL_VCOSF_H
#define CKL_VCOSF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vcosf_func_t)(const float *, float *, unsigned int);
    static inline void vcosf_avx512(const float *input_array, float *result_array,
                                    unsigned int size);
    static inline void vcosf_avx2(const float *input_array, float *result_array,
                                  unsigned int size);
    static inline void vcosf_avx(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vcosf_sse(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vcosf_scalar(const float *input_array, float *result_array,
                                    unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vcosf(const float *input_array, float *result_array,
                   unsigned int size) __attribute__((ifunc("vcosf_ifunc")));
#else
void ckl_vcosf(const float *input_array, float *result_array,
               unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vcosf_func_t, vcosf, ckl_vcosf)

    __m128 _ZGVbN4v_cosf(__m128 x);
    __m256 _ZGVcN8v_cosf(__m256 x);
    __m256 _ZGVdN8v_cosf(__m256 x);
    __m512 _ZGVeN16v_cosf(__m512 x);
    __m128d _ZGVbN2v_cos(__m128d x);

#include "commonf/avx.h"
#include "commonf/avx512.h"
#include "commonf/sse.h"
#include "commonf2d/sse.h"

#define NAME_AVX512_COSF eN16v_cosf
#define NAME_AVX2_COSF dN8v_cosf
#define NAME_AVX_COSF cN8v_cosf
#define NAME_SSE_COSF bN4v_cosf
#define NAME_SSE_COSF2D bN2v_cos

    /************** ckl_vcosf *****************/
    /*This function deals with size in 1~31 */
    static inline void __CKL_FN_ATTR_AVX512
    vcosf_avx512_31(const float *input_array, float *result_array, int size,
                    int *array_index)
    {
        if (size <= 31 && size >= 25)
        {
            AVX512_16_mask16(1, NAME_AVX512_COSF)
        }
        else if (size == 24)
        {
            AVX512_16__1(NAME_AVX512_COSF)
            AVX_8_offset(16, NAME_AVX2_COSF)
        }
        else if (size <= 23 && size >= 17)
        {
            AVX512_16_mask8(1, NAME_AVX512_COSF, NAME_AVX2_COSF)
        }
        else if (size == 16)
        {
            AVX512_16__1(NAME_AVX512_COSF)
        }
        else if (size <= 15 && size >= 9)
        {
            AVX512_16_mask16(0, NAME_AVX512_COSF)
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_COSF)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            // AVX_8_mask8(0, AVX2_NAME)
            AVX512_16_mask8(0, NAME_AVX512_COSF, NAME_AVX2_COSF)
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_COSF)
        }
        else
        {
            AVX512_16_mask4(0, NAME_AVX512_COSF, NAME_SSE_COSF)
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512
    vcosf_avx512(const float *input_array, float *result_array,
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
                AVX512_16__2(NAME_AVX512_COSF)
                *array_index += 32;
            }
            if (rest)
                vcosf_avx512_31(input_array, result_array, rest, array_index);
        }
        else
        {
            vcosf_avx512_31(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcosf *****************/
    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vcosf_avx2_15(const float *input_array, float *result_array, int size,
                  int *array_index)
    {
        if (size <= 15 && size >= 9)
        {
            AVX_8_mask8(1, NAME_AVX2_COSF)
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_COSF)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX_8_mask8(0, NAME_AVX2_COSF)
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_COSF)
        }
        else
        {
            AVX_8_mask4(0, NAME_AVX2_COSF, NAME_SSE_COSF)
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vcosf_avx2(const float *input_array, float *result_array,
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
                AVX_8__2(NAME_AVX2_COSF)
                *array_index += 16;
            }
            if (rest)
                vcosf_avx2_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX_8__2(NAME_AVX2_COSF)
        }
        else
        {
            vcosf_avx2_15(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcosf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vcosf_avx_3(const float *input_array,
                float *result_array, int size,
                int *array_index)
    {
        if (size == 3)
        {
            SSE_f2d_2_mask2(1, NAME_SSE_COSF2D)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_COSF2D)
        }
        else
        {
            SSE_f2d_2_mask2(0, NAME_SSE_COSF2D)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX
    vcosf_avx_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 7)
        {
            //SSE_f2d_2_mask2(3, NAME_SSE_COSF2D)
            SSE_4__1(NAME_SSE_COSF)
            *array_index += 4;
            SSE_f2d_2_mask2(1, NAME_SSE_COSF2D)
        }
        else if (size == 6)
        {
            //SSE_2__3
            SSE_4__1(NAME_SSE_COSF)
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_COSF2D)
        }
        else if (size == 5)
        {
            //SSE_2_mask2(2, SSE_NAME)
            SSE_4__1(NAME_SSE_COSF)
            *array_index += 4;
            SSE_f2d_2_mask2(0, NAME_SSE_COSF2D)
        }
        else if (size == 4)
        {
            //SSE_2__2
            SSE_4__1(NAME_SSE_COSF)
        }
        else
        {
            vcosf_avx_3(input_array, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX
    vcosf_avx_15(const float *input_array, float *result_array, int size,
                 int *array_index)
    {
        if (size <= 15 && size >= 9)
        {
            AVX_8_mask8(1, NAME_AVX_COSF)
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX_COSF)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX_8_mask8(0, NAME_AVX_COSF)
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_COSF)
        }
        else
        {
            AVX_8_mask4(0, NAME_AVX_COSF, NAME_SSE_COSF)
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vcosf_avx1(const float *input_array, float *result_array,
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
                AVX_8__2(NAME_AVX_COSF)
                *array_index += 16;
            }
            if (rest)
                vcosf_avx_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX_8__2(NAME_AVX_COSF)
        }
        else
        {
            vcosf_avx_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vcosf_avx(const float *input_array, float *result_array,
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
                //SSE_2__2
                SSE_4__2(NAME_SSE_COSF)
                *array_index += 8;
            }
            if (rest)
                vcosf_avx_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            //SSE_2__2
            SSE_4__2(NAME_SSE_COSF)
        }
        else
        {
            vcosf_avx_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcosf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vcosf_sse_3(const float *input_array,
                float *result_array, int size,
                int *array_index)
    {
        if (size == 3)
        {
            SSE_f2d_2_mask2(1, NAME_SSE_COSF2D)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_COSF2D)
        }
        else
        {
            SSE_f2d_2_mask2(0, NAME_SSE_COSF2D)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_SSE2
    vcosf_sse_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 7)
        {
            //SSE_f2d_2_mask2(3, NAME_SSE_COSF2D)
            SSE_4__1(NAME_SSE_COSF)
            *array_index += 4;
            SSE_f2d_2_mask2(1, NAME_SSE_COSF2D)
        }
        else if (size == 6)
        {
            //SSE_2__3
            SSE_4__1(NAME_SSE_COSF)
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_COSF2D)
        }
        else if (size == 5)
        {
            //SSE_2_mask2(2, SSE_NAME)
            SSE_4__1(NAME_SSE_COSF)
            *array_index += 4;
            SSE_f2d_2_mask2(0, NAME_SSE_COSF2D)
        }
        else if (size == 4)
        {
            //SSE_2__2
            SSE_4__1(NAME_SSE_COSF)
        }
        else
        {
            vcosf_sse_3(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vcosf_sse(const float *input_array, float *result_array,
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
                //SSE_2__2
                SSE_4__2(NAME_SSE_COSF)
                *array_index += 8;
            }
            if (rest)
                vcosf_sse_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            //SSE_2__2
            SSE_4__2(NAME_SSE_COSF)
        }
        else
        {
            vcosf_sse_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcosf *****************/
    static inline void vcosf_scalar(const float *input_array, float *result_array,
                                    unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            result_array[i] = cosf(input_array[i]);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VCOSF_H*/
