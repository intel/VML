#ifndef CKL_VEXP_H
#define CKL_VEXP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vexp_func_t)(const double *, double *, unsigned int);
    static inline void vexp_avx512(const double *input_array, double *result_array,
                                   unsigned int size);
    static inline void vexp_avx2(const double *input_array, double *result_array,
                                 unsigned int size);
    static inline void vexp_avx(const double *input_array, double *result_array,
                                unsigned int size);
    static inline void vexp_sse(const double *input_array, double *result_array,
                                unsigned int size);
    static inline void vexp_scalar(const double *input_array, double *result_array,
                                   unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vexp(const double *input_array, double *result_array,
                  unsigned int size) __attribute__((ifunc("vexp_ifunc")));
#else
void ckl_vexp(const double *input_array, double *result_array,
              unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vexp_func_t, vexp, ckl_vexp)

    __m128d _ZGVbN2v_exp(__m128d x);
    __m256d _ZGVcN4v_exp(__m256d x);
    __m256d _ZGVdN4v_exp(__m256d x);
    __m512d _ZGVeN8v_exp(__m512d x);

#include "common/avx.h"
#include "common/avx512.h"
#include "common/sse.h"

#define NAME_AVX512_EXP eN8v_exp
#define NAME_AVX2_EXP dN4v_exp
#define NAME_AVX_EXP cN4v_exp
#define NAME_SSE_EXP bN2v_exp
#define NAME_SCALAR_EXP exp
#define ckl_exp exp


    /************** ckl_vexp *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX512
    vexp_avx512_7(const double *input_array,
                  double *result_array,
                  int size,
                  int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset(0, NAME_AVX2_EXP)
        }
        else if (size == 5)
        {
            AVX_4__1(NAME_AVX2_EXP)
            result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1(NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 7)
        {
            AVX_4__1(NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1(NAME_SSE_EXP)
            // result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = exp(input_array[*array_index + 5]);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vexp_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
            // SSE_2_mask2(0, SSE_NAME)
        }
        else if (size == 2)
        {
            // result_array[*array_index] = exp(input_array[*array_index]);
            // result_array[*array_index + 1] = exp(input_array[*array_index + 1]);
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 13)
        {
            AVX512_8__1(NAME_AVX512_EXP)
            AVX_4_offset(8, NAME_AVX2_EXP);
            result_array[*array_index + 12] = exp(input_array[*array_index + 12]);
        }
        else if (size == 14)
        {
            AVX512_8__1(NAME_AVX512_EXP)
            AVX_4_offset(8, NAME_AVX2_EXP);
            *array_index += 12;
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8(1, AVX512_NAME)
            AVX512_8__1(NAME_AVX512_EXP)
            AVX_4_offset(8, NAME_AVX2_EXP);
            *array_index += 12;
            SSE_2__1(NAME_SSE_EXP);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 12)
        {
            AVX512_8__1(NAME_AVX512_EXP)
            AVX_4_offset(8, NAME_AVX2_EXP)
        }
        else if (size == 11)
        {
            AVX512_8__1(NAME_AVX512_EXP);
            *array_index += 8;
            SSE_2__1(NAME_SSE_EXP);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 10)
        {
            AVX512_8__1(NAME_AVX512_EXP);
            *array_index += 8;
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 9)
        {
            // AVX512_8_mask4(1, AVX2_NAME)
            AVX512_8__1(NAME_AVX512_EXP);
            result_array[*array_index + 8] = exp(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX512_8__1(NAME_AVX512_EXP)
        }
        else if (size == 5)
        {
            AVX_4__1(NAME_AVX2_EXP)
            result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1(NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1(NAME_SSE_EXP)
            // result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = exp(input_array[*array_index + 5]);
        }
        else if (size == 7)
        {
            AVX_4__1(NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1(NAME_SSE_EXP)
            // result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = exp(input_array[*array_index + 5]);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset(0, NAME_AVX2_EXP)
        }
    }

    static inline void __CKL_FN_ATTR_AVX512 vexp_avx512_16_group(const double *input_array, double *result_array,
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
                AVX512_8__2(NAME_AVX512_EXP)
                *array_index += 16;
            }
            if (rest)
                vexp_avx512_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_8__2(NAME_AVX512_EXP)
        }
        else
        {
            vexp_avx512_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512 vexp_avx512(const double *input_array, double *result_array,
                                                        unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vexp_avx512_16_group(input_array, result_array, size);
        }
        else if (size == 8)
        {
            AVX512_8__1(NAME_AVX512_EXP)
        }
        else
        {
            vexp_avx512_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexp *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vexp_avx2_3(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vexp_avx2(const double *input_array, double *result_array,
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
                AVX_4__1(NAME_AVX2_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_avx2_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_4__1(NAME_AVX2_EXP)
        }
        else
        {
            vexp_avx2_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexp *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vexp_avx_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vexp_avx(const double *input_array, double *result_array,
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
                SSE_2__2(NAME_SSE_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_EXP)
        }
        else
        {
            vexp_avx_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexp *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vexp_sse_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vexp_sse(const double *input_array, double *result_array,
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
                SSE_2__2(NAME_SSE_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_sse_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_EXP)
        }
        else
        {
            vexp_sse_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vexp *****************/
    static inline void vexp_scalar(const double *input_array, double *result_array,
                                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1(0, NAME_SCALAR_EXP);
            *array_index += 1;
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VEXP_H*/
