#ifndef CKL_VLOG_H
#define CKL_VLOG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vlog_func_t)(const double *, double *, unsigned int);
    static inline void vlog_avx512(const double *input_array, double *result_array,
                                   unsigned int size);
    static inline void vlog_avx2(const double *input_array, double *result_array,
                                 unsigned int size);
    static inline void vlog_avx(const double *input_array, double *result_array,
                                unsigned int size);
    static inline void vlog_sse(const double *input_array, double *result_array,
                                unsigned int size);
    static inline void vlog_scalar(const double *input_array, double *result_array,
                                   unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vlog(const double *input_array, double *result_array,
                  unsigned int size) __attribute__((ifunc("vlog_ifunc")));
#else
void ckl_vlog(const double *input_array, double *result_array,
              unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vlog_func_t, vlog, ckl_vlog)

    __m128d _ZGVbN2v_log(__m128d x);
    __m256d _ZGVcN4v_log(__m256d x);
    __m256d _ZGVdN4v_log(__m256d x);
    __m512d _ZGVeN8v_log(__m512d x);

#include "common/avx.h"
#include "common/avx512.h"
#include "common/sse.h"

#define NAME_AVX512_LOG eN8v_log
#define NAME_AVX2_LOG dN4v_log
#define NAME_AVX_LOG cN4v_log
#define NAME_SSE_LOG bN2v_log
#define NAME_SCALAR_LOG log
#define ckl_log log

    /************** ckl_vlog *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX512
    vlog_avx512_7(const double *input_array,
                  double *result_array,
                  int size,
                  int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset(0, NAME_AVX2_LOG)
        }
        else if (size == 5)
        {
            AVX_4__1(NAME_AVX2_LOG)
            result_array[*array_index + 4] = log(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1(NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 7)
        {
            AVX_4__1(NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1(NAME_SSE_LOG)
            // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vlog_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
            // SSE_2_mask2(0, SSE_NAME)
        }
        else if (size == 2)
        {
            // result_array[*array_index] = log(input_array[*array_index]);
            // result_array[*array_index + 1] = log(input_array[*array_index + 1]);
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 13)
        {
            AVX512_8__1(NAME_AVX512_LOG)
            AVX_4_offset(8, NAME_AVX2_LOG);
            result_array[*array_index + 12] = log(input_array[*array_index + 12]);
        }
        else if (size == 14)
        {
            AVX512_8__1(NAME_AVX512_LOG)
            AVX_4_offset(8, NAME_AVX2_LOG);
            *array_index += 12;
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8(1, AVX512_NAME)
            AVX512_8__1(NAME_AVX512_LOG)
            AVX_4_offset(8, NAME_AVX2_LOG);
            *array_index += 12;
            SSE_2__1(NAME_SSE_LOG);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 12)
        {
            AVX512_8__1(NAME_AVX512_LOG)
            AVX_4_offset(8, NAME_AVX2_LOG)
        }
        else if (size == 11)
        {
            AVX512_8__1(NAME_AVX512_LOG);
            *array_index += 8;
            SSE_2__1(NAME_SSE_LOG);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 10)
        {
            AVX512_8__1(NAME_AVX512_LOG);
            *array_index += 8;
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 9)
        {
            // AVX512_8_mask4(1, AVX2_NAME)
            AVX512_8__1(NAME_AVX512_LOG);
            result_array[*array_index + 8] = log(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX512_8__1(NAME_AVX512_LOG)
        }
        else if (size == 5)
        {
            AVX_4__1(NAME_AVX2_LOG)
            result_array[*array_index + 4] = log(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1(NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1(NAME_SSE_LOG)
            // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
        }
        else if (size == 7)
        {
            AVX_4__1(NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1(NAME_SSE_LOG)
            // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset(0, NAME_AVX2_LOG)
        }
    }

    static inline void __CKL_FN_ATTR_AVX512 vlog_avx512_16_group(const double *input_array, double *result_array,
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
                AVX512_8__2(NAME_AVX512_LOG)
                *array_index += 16;
            }
            if (rest)
                vlog_avx512_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_8__2(NAME_AVX512_LOG)
        }
        else
        {
            vlog_avx512_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512 vlog_avx512(const double *input_array, double *result_array,
                                                        unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vlog_avx512_16_group(input_array, result_array, size);
        }
        else if (size == 8)
        {
            AVX512_8__1(NAME_AVX512_LOG)
        }
        else
        {
            vlog_avx512_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlog *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vlog_avx2_3(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vlog_avx2(const double *input_array, double *result_array,
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
                AVX_4__1(NAME_AVX2_LOG)
                *array_index += 4;
            }
            if (rest)
                vlog_avx2_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_4__1(NAME_AVX2_LOG)
        }
        else
        {
            vlog_avx2_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlog *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vlog_avx_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vlog_avx(const double *input_array, double *result_array,
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
                SSE_2__2(NAME_SSE_LOG)
                *array_index += 4;
            }
            if (rest)
                vlog_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_LOG)
        }
        else
        {
            vlog_avx_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlog *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vlog_sse_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vlog_sse(const double *input_array, double *result_array,
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
                SSE_2__2(NAME_SSE_LOG)
                *array_index += 4;
            }
            if (rest)
                vlog_sse_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_LOG)
        }
        else
        {
            vlog_sse_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vlog *****************/
    static inline void vlog_scalar(const double *input_array, double *result_array,
                                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1(0, NAME_SCALAR_LOG);
            *array_index += 1;
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VLOG_H*/
