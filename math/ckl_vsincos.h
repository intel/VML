#ifndef CKL_VSINCOS_H
#define CKL_VSINCOS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vsincos_func_t)(const double *, double *, double *, unsigned int);
    static inline void vsincos_avx512(const double *input_array, double *result_array,
                                      double *result_array1, unsigned int size);
    static inline void vsincos_avx2(const double *input_array, double *result_array,
                                    double *result_array1, unsigned int size);
    static inline void vsincos_avx(const double *input_array, double *result_array,
                                   double *result_array1, unsigned int size);
    static inline void vsincos_sse(const double *input_array, double *result_array,
                                   double *result_array1, unsigned int size);
    static inline void vsincos_scalar(const double *input_array, double *result_array,
                                      double *result_array1, unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vsincos(const double *input_array, double *result_array, double *result_array1,
                     unsigned int size) __attribute__((ifunc("vsincos_ifunc")));
#else
void ckl_vsincos(const double *input_array, double *result_array, double *result_array1,
                 unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vsincos_func_t, vsincos, ckl_vsincos)

    __m128d _ZGVbN2v_sin(__m128d x);
    __m256d _ZGVcN4v_sin(__m256d x);
    __m256d _ZGVdN4v_sin(__m256d x);
    __m512d _ZGVeN8v_sin(__m512d x);
    __m128d _ZGVbN2v_cos(__m128d x);
    __m256d _ZGVcN4v_cos(__m256d x);
    __m256d _ZGVdN4v_cos(__m256d x);
    __m512d _ZGVeN8v_cos(__m512d x);

#include "common/avx512_sincos.h"
#include "common/avx_sincos.h"
#include "common/sse_sincos.h"

    /************** ckl_vsincos *****************/
    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vsincos_avx512_15(const double *input_array, double *result_array, double *result_array1, int size,
                      int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX512_SINCOS_8_mask8(1)
        }
        else if (size == 12)
        {
            AVX512_SINCOS_8__1;
            AVX_SINCOS_4_offset(8)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX512_SINCOS_8_mask4(1)
        }
        else if (size == 8)
        {
            AVX512_SINCOS_8__1
        }
        else if (size == 5 || size == 6 || size == 7)
        {
            AVX512_SINCOS_8_mask8(0)
        }
        else if (size == 4)
        {
            AVX_SINCOS_4_offset(0)
        }
        else
        {
            AVX512_SINCOS_8_mask4(0)
        }
    }

    /*This function deals with size in 1~31 */
    static inline void __CKL_FN_ATTR_AVX512
    vsincos_avx512_31(const double *input_array, double *result_array, double *result_array1, int size,
                      int *array_index)
    {
        if (size == 31 || size == 30 || size == 29)
        {
            AVX512_SINCOS_8_mask8(3)
        }
        else if (size == 28)
        {
            AVX512_SINCOS_8__3;
            AVX_SINCOS_4_offset(24)
        }
        else if (size == 27 || size == 26 || size == 25)
        {
            AVX512_SINCOS_8_mask4(3)
        }
        else if (size == 24)
        {
            AVX512_SINCOS_8__3
        }
        else if (size == 23 || size == 22 || size == 21)
        {
            AVX512_SINCOS_8_mask8(2)
        }
        else if (size == 20)
        {
            AVX512_SINCOS_8__2;
            AVX_SINCOS_4_offset(16)
        }
        else if (size == 19 || size == 18 || size == 17)
        {
            AVX512_SINCOS_8_mask4(2)
        }
        else if (size == 16)
        {
            AVX512_SINCOS_8__2;
        }
        else
            vsincos_avx512_15(input_array, result_array, result_array1, size, array_index);
    }

    static inline void __CKL_FN_ATTR_AVX512
    vsincos_avx512_sub(const double *input_array, double *result_array, double *result_array1,
                       unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 32)
        {
            unsigned int count = size >> 5;
            unsigned int rest = size & 31;
            for (int i = 0; i < 2 * count; i++)
            {
                AVX512_SINCOS_8__2;
                *array_index += 16;
            }
            if (rest)
                vsincos_avx512_31(input_array, result_array, result_array1, rest, array_index);
        }
        else if (size == 32)
        {
            AVX512_SINCOS_8__4
        }
        else
        {
            vsincos_avx512_31(input_array, result_array, result_array1, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512
    vsincos_avx512(const double *input_array, double *result_array, double *result_array1,
                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;

        if (size > 16)
        {
            vsincos_avx512_sub(input_array, result_array, result_array1, size);
        }
        else if (size == 16)
        {
            AVX512_SINCOS_8__2
        }
        else
        {
            vsincos_avx512_15(input_array, result_array, result_array1, size, array_index);
        }
    }

    /************** ckl_vsincos *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vsincos_AVX_7(const double *input_array, double *result_array, double *result_array1, int size,
                  int *array_index)
    {
        if (size == 7 || size == 6 || size == 5)
        {
            AVX_SINCOS_4_mask4(1)
        }
        else if (size == 4)
        {
            AVX_SINCOS_4__1
        }
        else
        {
            AVX_SINCOS_4_mask4(0)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vsincos_AVX_15(const double *input_array, double *result_array, double *result_array1, int size,
                   int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX_SINCOS_4_mask4(3)
        }
        else if (size == 12)
        {
            AVX_SINCOS_4__3
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX_SINCOS_4_mask4(2)
        }
        else if (size == 8)
        {
            AVX_SINCOS_4__2
        }
        else if (size == 5 || size == 6 || size == 7)
        {
            AVX_SINCOS_4_mask4(1)
        }
        else if (size == 4)
        {
            AVX_SINCOS_4__1
        }
        else
        {
            AVX_SINCOS_4_mask4(0)
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vsincos_avx2(const double *input_array, double *result_array, double *result_array1,
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
                AVX_SINCOS_4__2;
                *array_index += 8;
            }
            if (rest)
                vsincos_AVX_7(input_array, result_array, result_array1, rest, array_index);
        }
        else if (size == 8)
        {
            AVX_SINCOS_4__2
        }
        else
        {
            vsincos_AVX_7(input_array, result_array, result_array1, size, array_index);
        }
    }

    /************** ckl_vsincos *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vsincos_avx_3(const double *input_array,
                  double *result_array,
                  double *result_array1,
                  int size,
                  int *array_index)
    {
        if (size == 3)
        {
            SSE_SINCOS_2_mask2(1)
        }
        else if (size == 2)
        {
            SSE_SINCOS_2__1
        }
        else
        {
            SSE_SINCOS_2_mask2(0)
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vsincos_avx(const double *input_array, double *result_array, double *result_array1,
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
                SSE_SINCOS_2__2;
                *array_index += 4;
            }
            if (rest)
                vsincos_avx_3(input_array, result_array, result_array1, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_SINCOS_2__2
        }
        else
        {
            vsincos_avx_3(input_array, result_array, result_array1, size, array_index);
        }
    }

    /************** ckl_vsincos *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vsincos_sse_3(const double *input_array,
                  double *result_array,
                  double *result_array1,
                  int size,
                  int *array_index)
    {
        if (size == 3)
        {
            SSE_SINCOS_2_mask2(1)
        }
        else if (size == 2)
        {
            SSE_SINCOS_2__1
        }
        else
        {
            SSE_SINCOS_2_mask2(0)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_SSE2
    vsincos_sse_7(const double *input_array,
                  double *result_array,
                  double *result_array1,
                  int size,
                  int *array_index)
    {
        if (size == 7)
        {
            SSE_SINCOS_2_mask2(3)
        }
        else if (size == 6)
        {
            SSE_SINCOS_2__3
        }
        else if (size == 5)
        {
            SSE_SINCOS_2_mask2(2)
        }
        else if (size == 4)
        {
            SSE_SINCOS_2__2
        }
        else
        {
            vsincos_sse_3(input_array, result_array, result_array1, size, array_index);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_SSE2
    vsincos_sse_15(const double *input_array, double *result_array, double *result_array1, int size,
                   int *array_index)
    {
        if (size == 15)
        {
            SSE_SINCOS_2_mask2(7)
        }
        else if (size == 14)
        {
            SSE_SINCOS_2__7
        }
        else if (size == 13)
        {
            SSE_SINCOS_2_mask2(6)
        }
        else if (size == 12)
        {
            SSE_SINCOS_2__6
        }
        else if (size == 11)
        {
            SSE_SINCOS_2_mask2(5)
        }
        else if (size == 10)
        {
            SSE_SINCOS_2__5
        }
        else if (size == 9)
        {
            SSE_SINCOS_2_mask2(4)
        }
        else if (size == 8)
        {
            SSE_SINCOS_2__4
        }
        else if (size == 7)
        {
            SSE_SINCOS_2_mask2(3)
        }
        else if (size == 6)
        {
            SSE_SINCOS_2__3
        }
        else if (size == 5)
        {
            SSE_SINCOS_2_mask2(2)
        }
        else if (size == 4)
        {
            SSE_SINCOS_2__2
        }
        else if (size == 3)
        {
            SSE_SINCOS_2_mask2(1)
        }
        else if (size == 2)
        {
            SSE_SINCOS_2__1
        }
        else if (size == 1)
        {
            SSE_SINCOS_2_mask2(0)
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vsincos_sse(const double *input_array, double *result_array, double *result_array1,
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
                SSE_SINCOS_2__2;
                *array_index += 4;
            }
            if (rest)
                vsincos_sse_3(input_array, result_array, result_array1, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_SINCOS_2__2;
        }
        else
        {
            vsincos_sse_3(input_array, result_array, result_array1, size, array_index);
        }
    }

    /************** ckl_vsincos *****************/
    static inline void vsincos_scalar(const double *input_array, double *result_array,
                                      double *result_array1, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            sincos(input_array[i], &result_array[i], &result_array1[i]);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VSINCOS_H*/
