#ifndef CKL_VLOGF_H
#define CKL_VLOGF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vlogf_func_t)(const float *, float *, unsigned int);
    static inline void vlogf_avx512(const float *input_array, float *result_array,
                                    unsigned int size);
    static inline void vlogf_avx2(const float *input_array, float *result_array,
                                  unsigned int size);
    static inline void vlogf_avx(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vlogf_sse(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vlogf_scalar(const float *input_array, float *result_array,
                                    unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vlogf(const float *input_array, float *result_array,
                   unsigned int size) __attribute__((ifunc("vlogf_ifunc")));
#else
void ckl_vlogf(const float *input_array, float *result_array,
               unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vlogf_func_t, vlogf, ckl_vlogf)

    __m128 _ZGVbN4v_logf(__m128 x);
    __m256 _ZGVcN8v_logf(__m256 x);
    __m256 _ZGVdN8v_logf(__m256 x);
    __m512 _ZGVeN16v_logf(__m512 x);

#include "commonf/avx.h"
#include "commonf/avx512.h"
#include "commonf/sse.h"

#define NAME_AVX512_LOGF eN16v_logf
#define NAME_AVX2_LOGF dN8v_logf
#define NAME_AVX_LOGF cN8v_logf
#define NAME_SSE_LOGF bN4v_logf

    /************** ckl_vlogf *****************/
    /*This function deals with size in 1~3 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_avx512_3(const float *input_array, float *result_array, int size,
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
            //SSE_f2d_2__1(bN2v_log)
        }
        else if (size == 3)
        {
            result_array[*array_index] = logf(input_array[*array_index]);
            result_array[*array_index + 1] = logf(input_array[*array_index + 1]);
            result_array[*array_index + 2] = logf(input_array[*array_index + 2]);
        }
    }

    /*This function deals with size in 1~7 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_avx512_7(const float *input_array, float *result_array, int size,
                   int *array_index)
    {
        if (size == 7)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 6)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 5)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_LOGF)
        }
        else
        {
            vlogf_avx512_3(input_array, result_array, size,
                           array_index);
        }
    }

    /*This function deals with size in 1~15 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_avx512_15(const float *input_array, float *result_array, int size,
                    int *array_index)
    {
        if (size <= 15 && size >= 12)
        {
            AVX512_16_mask16(0, NAME_AVX512_LOGF)
        }
        else if (size == 11)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
            result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
            result_array[*array_index + 10] = logf(input_array[*array_index + 10]);
        }
        else if (size == 10)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
            result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
        }
        else if (size == 9)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_avx512_7(input_array, result_array, size,
                           array_index);
        }
    }
    /*This function deals with size in 1~31 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_avx512_31(const float *input_array, float *result_array, int size,
                    int *array_index)
    {
        if (size <= 31 && size >= 26)
        {
            AVX512_16_mask16(1, NAME_AVX512_LOGF)
        }
        else if (size == 25)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            AVX_8_offset(16, NAME_AVX2_LOGF);
            result_array[*array_index + 24] = logf(input_array[*array_index + 24]);
        }
        else if (size == 24)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            AVX_8_offset(16, NAME_AVX2_LOGF)
        }
        else if (size == 23)
        {
            //AVX512_16_mask8(1, AVX2_NAME)
            AVX512_16__1(NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 22)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 21)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 20)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1(NAME_SSE_LOGF)
        }
        else if (size == 19)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            result_array[*array_index + 16] = logf(input_array[*array_index + 16]);
            result_array[*array_index + 17] = logf(input_array[*array_index + 17]);
            result_array[*array_index + 18] = logf(input_array[*array_index + 18]);
        }
        else if (size == 18)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            result_array[*array_index + 16] = logf(input_array[*array_index + 16]);
            result_array[*array_index + 17] = logf(input_array[*array_index + 17]);
        }
        else if (size == 17)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
            result_array[*array_index + 16] = logf(input_array[*array_index + 16]);
        }
        else if (size == 16)
        {
            AVX512_16__1(NAME_AVX512_LOGF)
        }
        else
        {
            //AVX512_16_mask4(0, SSE_NAME)
            vlogf_avx512_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_avx512(const float *input_array, float *result_array,
                 unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 31)
        {
            unsigned int count = size >> 5;
            unsigned int rest = size & 31;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX512_16__2(NAME_AVX512_LOGF)
                *array_index += 32;
            }
            if (rest)
                vlogf_avx512_31(input_array, result_array, rest, array_index);
        }
        else
        {
            vlogf_avx512_31(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlogf *****************/
    /*This function deals with size in 1~3 */
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_avx2_3(const float *input_array, float *result_array, int size,
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
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_avx2_7(const float *input_array, float *result_array, int size,
                 int *array_index)
    {
        if (size == 7)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 6)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 5)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_LOGF)
        }
        else
        {
            vlogf_avx2_3(input_array, result_array, size, array_index);
            //AVX2_8_mask4(0, SSE_NAME)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_avx2_15(const float *input_array, float *result_array, int size,
                  int *array_index)
    {
        if (size == 15)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 14)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 13)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 14)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
        }
        else if (size == 11)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
            result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
            result_array[*array_index + 10] = logf(input_array[*array_index + 10]);
        }
        else if (size == 10)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
            result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
        }
        else if (size == 9)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_avx2_7(input_array, result_array, size,
                         array_index);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_avx2(const float *input_array, float *result_array,
               unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            unsigned int count = size >> 3;
            unsigned int rest = size & 7;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_8__1(NAME_AVX2_LOGF)
                *array_index += 8;
            }
            if (rest)
                vlogf_avx2_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_avx2_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlogf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vlogf_avx_3(const float *input_array,
                float *result_array, int size,
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

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX
    vlogf_avx_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 7)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 6)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 5)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_LOGF)
        }
        else
        {
            vlogf_avx_3(input_array, result_array, size, array_index);
            //AVX_8_mask4(0, SSE_NAME)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX
    vlogf_avx_15(const float *input_array, float *result_array, int size,
                 int *array_index)
    {
        if (size == 15)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 14)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 13)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 14)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1(NAME_SSE_LOGF)
        }
        else if (size == 11)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
            result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
            result_array[*array_index + 10] = logf(input_array[*array_index + 10]);
        }
        else if (size == 10)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
            result_array[*array_index + 9] = logf(input_array[*array_index + 9]);
        }
        else if (size == 9)
        {
            AVX_8__1(NAME_AVX2_LOGF)
            result_array[*array_index + 8] = logf(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_avx_7(input_array, result_array, size,
                        array_index);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vlogf_avx(const float *input_array, float *result_array,
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
                SSE_4__1(NAME_SSE_LOGF)
                *array_index += 4;
            }
            if (rest)
                vlogf_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_LOGF)
        }
        else
        {
            vlogf_avx_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlogf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vlogf_sse_3(const float *input_array,
                float *result_array, int size,
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

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_SSE2
    vlogf_sse_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 7)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
            result_array[*array_index + 6] = logf(input_array[*array_index + 6]);
        }
        else if (size == 6)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
            result_array[*array_index + 5] = logf(input_array[*array_index + 5]);
        }
        else if (size == 5)
        {
            SSE_4__1(NAME_SSE_LOGF)
            result_array[*array_index + 4] = logf(input_array[*array_index + 4]);
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_LOGF)
        }
        else
        {
            vlogf_sse_3(input_array, result_array, size,
                        array_index);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vlogf_sse(const float *input_array, float *result_array,
              unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            unsigned int count = size >> 3;
            unsigned int rest = size & 7;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_4__2(NAME_SSE_LOGF)
                *array_index += 8;
            }
            if (rest)
                vlogf_sse_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            SSE_4__2(NAME_SSE_LOGF)
        }
        else
        {
            vlogf_sse_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlogf *****************/
    static inline void vlogf_scalar(const float *input_array, float *result_array,
                                    unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            result_array[i] = logf(input_array[i]);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VLOGF_H*/
