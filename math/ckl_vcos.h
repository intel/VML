#ifndef CKL_VCOS_H
#define CKL_VCOS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vcos_func_t)(const double *, double *, unsigned int);
    static inline void vcos_avx512(const double *input_array, double *result_array,
                                   unsigned int size);
    static inline void vcos_avx2(const double *input_array, double *result_array,
                                 unsigned int size);
    static inline void vcos_avx(const double *input_array, double *result_array,
                                unsigned int size);
    static inline void vcos_sse(const double *input_array, double *result_array,
                                unsigned int size);
    static inline void vcos_scalar(const double *input_array, double *result_array,
                                   unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vcos(const double *input_array, double *result_array,
                  unsigned int size) __attribute__((ifunc("vcos_ifunc")));
#else
void ckl_vcos(const double *input_array, double *result_array,
              unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vcos_func_t, vcos, ckl_vcos)

    __m128d _ZGVbN2v_cos(__m128d x);
    __m256d _ZGVcN4v_cos(__m256d x);
    __m256d _ZGVdN4v_cos(__m256d x);
    __m512d _ZGVeN8v_cos(__m512d x);

#include "common/avx.h"
#include "common/avx512.h"
#include "common/sse.h"

#define NAME_AVX512_COS eN8v_cos
#define NAME_AVX2_COS dN4v_cos
#define NAME_AVX_COS cN4v_cos
#define NAME_SSE_COS bN2v_cos
#define NAME_SCALAR_COS cos
#define ckl_cos cos

    /************** ckl_vcos *****************/
    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vcos_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX512_8_mask8(1, NAME_AVX512_COS)
        }
        else if (size == 12)
        {
            AVX512_8__1(NAME_AVX512_COS)
            AVX_4_offset(8, NAME_AVX2_COS)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX512_8_mask4(1, NAME_AVX512_COS, NAME_AVX2_COS)
        }
        else if (size == 8)
        {
            AVX512_8__1(NAME_AVX512_COS)
        }
        else if (size == 5 || size == 6 || size == 7)
        {
            AVX512_8_mask8(0, NAME_AVX512_COS)
        }
        else if (size == 4)
        {
            AVX_4_offset(0, NAME_AVX2_COS)
        }
        else
        {
            AVX512_8_mask4(0, NAME_AVX512_COS, NAME_AVX2_COS)
        }
    }

    /*This function deals with size in 1~31 */
    static inline void __CKL_FN_ATTR_AVX512
    vcos_avx512_31(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 31 || size == 30 || size == 29)
        {
            AVX512_8_mask8(3, NAME_AVX512_COS)
        }
        else if (size == 28)
        {
            AVX512_8__3(NAME_AVX512_COS)
            AVX_4_offset(24, NAME_AVX2_COS)
        }
        else if (size == 27 || size == 26 || size == 25)
        {
            AVX512_8_mask4(3, NAME_AVX512_COS, NAME_AVX2_COS)
        }
        else if (size == 24)
        {
            AVX512_8__3(NAME_AVX512_COS)
        }
        else if (size == 23 || size == 22 || size == 21)
        {
            AVX512_8_mask8(2, NAME_AVX512_COS)
        }
        else if (size == 20)
        {
            AVX512_8__2(NAME_AVX512_COS)
            AVX_4_offset(16, NAME_AVX2_COS)
        }
        else if (size == 19 || size == 18 || size == 17)
        {
            AVX512_8_mask4(2, NAME_AVX512_COS, NAME_AVX2_COS)
        }
        else if (size == 16)
        {
            AVX512_8__2(NAME_AVX512_COS)
        }
        else
            vcos_avx512_15(input_array, result_array, size, array_index);
    }

    static inline void __CKL_FN_ATTR_AVX512
    vcos_avx512_sub(const double *input_array, double *result_array,
                    unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 32)
        {
            unsigned int count = size >> 5;
            unsigned int rest = size & 31;
            for (unsigned int i = 0; i < 2 * count; i++)
            {
                AVX512_8__2(NAME_AVX512_COS)
                *array_index += 16;
            }
            if (rest)
                vcos_avx512_31(input_array, result_array, rest, array_index);
        }
        else if (size == 32)
        {
            AVX512_8__4(NAME_AVX512_COS)
        }
        else
        {
            vcos_avx512_31(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512
    vcos_avx512(const double *input_array, double *result_array,
                unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            vcos_avx512_sub(input_array, result_array, size);
        }
        else if (size == 16)
        {
            AVX512_8__2(NAME_AVX512_COS)
        }
        else
        {
            vcos_avx512_15(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcos *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vcos_avx2_7(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 7 || size == 6 || size == 5)
        {
            AVX_4_mask4(1, NAME_AVX2_COS)
        }
        else if (size == 4)
        {
            AVX_4__1(NAME_AVX2_COS)
        }
        else
        {
            AVX_4_mask4(0, NAME_AVX2_COS)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vcos_avx2_15(const double *input_array, double *result_array, int size,
                 int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX_4_mask4(3, NAME_AVX2_COS)
        }
        else if (size == 12)
        {
            AVX_4__3(NAME_AVX2_COS)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX_4_mask4(2, NAME_AVX2_COS)
        }
        else if (size == 8)
        {
            AVX_4__2(NAME_AVX2_COS)
        }
        else if (size == 5 || size == 6 || size == 7)
        {
            AVX_4_mask4(1, NAME_AVX2_COS)
        }
        else if (size == 4)
        {
            AVX_4__1(NAME_AVX2_COS)
        }
        else
        {
            AVX_4_mask4(0, NAME_AVX2_COS)
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vcos_avx2(const double *input_array, double *result_array,
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
                AVX_4__2(NAME_AVX2_COS)
                *array_index += 8;
            }
            if (rest)
                vcos_avx2_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            AVX_4__2(NAME_AVX2_COS)
        }
        else
        {
            vcos_avx2_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcos *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vcos_avx_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 3)
        {
            SSE_2_mask2(1, NAME_SSE_COS)
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_COS)
        }
        else
        {
            SSE_2_mask2(0, NAME_SSE_COS)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX
    vcos_avx_7(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 7 || size == 6)
        {
            AVX_4_mask4(1, NAME_AVX_COS)
        }
        else if (size == 5)
        {
            AVX_4_mask2(1, NAME_AVX_COS, NAME_SSE_COS)
        }
        else if (size == 4)
        {
            AVX_4__1(NAME_AVX_COS)
        }
        else if (size == 3)
        {
            SSE_2__1(NAME_SSE_COS)
            *array_index += 2;
            SSE_2_mask2(0, NAME_SSE_COS)
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_COS)
        }
        else
        {
            AVX_4_mask2(0, NAME_AVX_COS, NAME_SSE_COS)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX
    vcos_avx_15(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX_4_mask4(3, NAME_AVX_COS)
        }
        else if (size == 12)
        {
            AVX_4__3(NAME_AVX_COS)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX_4_mask4(2, NAME_AVX_COS)
        }
        else if (size == 8)
        {
            AVX_4__2(NAME_AVX_COS)
        }
        else
        {
            vcos_avx_7(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vcos_avx(const double *input_array, double *result_array,
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
                SSE_2__2(NAME_SSE_COS)
                *array_index += 4;
            }
            if (rest)
                vcos_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_COS)
        }
        else
        {
            vcos_avx_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcos *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vcos_sse_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 3)
        {
            SSE_2_mask2(1, NAME_SSE_COS)
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_COS)
        }
        else
        {
            SSE_2_mask2(0, NAME_SSE_COS)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_SSE2
    vcos_sse_7(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 7)
        {
            SSE_2_mask2(3, NAME_SSE_COS)
        }
        else if (size == 6)
        {
            SSE_2__3(NAME_SSE_COS)
        }
        else if (size == 5)
        {
            SSE_2_mask2(2, NAME_SSE_COS)
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_COS)
        }
        else
        {
            vcos_sse_3(input_array, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_SSE2
    vcos_sse_15(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 15)
        {
            SSE_2_mask2(7, NAME_SSE_COS)
        }
        else if (size == 14)
        {
            SSE_2__7(NAME_SSE_COS)
        }
        else if (size == 13)
        {
            SSE_2_mask2(6, NAME_SSE_COS)
        }
        else if (size == 12)
        {
            SSE_2__6(NAME_SSE_COS)
        }
        else if (size == 11)
        {
            SSE_2_mask2(5, NAME_SSE_COS)
        }
        else if (size == 10)
        {
            SSE_2__5(NAME_SSE_COS)
        }
        else if (size == 9)
        {
            SSE_2_mask2(4, NAME_SSE_COS)
        }
        else if (size == 8)
        {
            SSE_2__4(NAME_SSE_COS)
        }
        else if (size == 7)
        {
            SSE_2_mask2(3, NAME_SSE_COS)
        }
        else if (size == 6)
        {
            SSE_2__3(NAME_SSE_COS)
        }
        else if (size == 5)
        {
            SSE_2_mask2(2, NAME_SSE_COS)
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_COS)
        }
        else if (size == 3)
        {
            SSE_2_mask2(1, NAME_SSE_COS)
        }
        else if (size == 2)
        {
            SSE_2__1(NAME_SSE_COS)
        }
        else if (size == 1)
        {
            SSE_2_mask2(0, NAME_SSE_COS)
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vcos_sse(const double *input_array, double *result_array,
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
                SSE_2__2(NAME_SSE_COS)
                *array_index += 4;
            }
            if (rest)
                vcos_sse_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2(NAME_SSE_COS)
        }
        else
        {
            vcos_sse_3(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vcos *****************/
    static inline void vcos_scalar(const double *input_array, double *result_array,
                                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1(0, NAME_SCALAR_COS);
            *array_index += 1;
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VCOS_H*/
