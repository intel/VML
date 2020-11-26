#ifndef CKL_VPOW_H
#define CKL_VPOW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vpow_func_t)(const double *, const double *, double *, unsigned int);
    static inline void vpow_avx512(const double *input_array, const double *input_array1,
                                   double *result_array, unsigned int size);
    static inline void vpow_avx2(const double *input_array, const double *input_array1,
                                 double *result_array, unsigned int size);
    static inline void vpow_avx(const double *input_array, const double *input_array1,
                                double *result_array, unsigned int size);
    static inline void vpow_sse(const double *input_array, const double *input_array1,
                                double *result_array, unsigned int size);
    static inline void vpow_scalar(const double *input_array, const double *input_array1,
                                   double *result_array, unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vpow(const double *input_array, const double *input_array1, double *result_array,
                  unsigned int size) __attribute__((ifunc("vpow_ifunc")));
#else
void ckl_vpow(const double *input_array, const double *input_array1, double *result_array,
              unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vpow_func_t, vpow, ckl_vpow)

    __m128d _ZGVbN2vv_pow(__m128d x, __m128d y);
    __m256d _ZGVcN4vv_pow(__m256d x, __m256d y);
    __m256d _ZGVdN4vv_pow(__m256d x, __m256d y);
    __m512d _ZGVeN8vv_pow(__m512d x, __m512d y);

#include "common/avx_vv.h"
#include "common/avx512_vv.h"
#include "common/sse_vv.h"

#define NAME_AVX512_POW eN8vv_pow
#define NAME_AVX2_POW dN4vv_pow
#define NAME_AVX_POW cN4vv_pow
#define NAME_SSE_POW bN2vv_pow
#define NAME_SCALAR_POW pow
#define ckl_pow pow

    /************** ckl_vpow *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX512
    vpow_avx512_7(const double *input_array,
                  const double *input_array1,
                  double *result_array,
                  int size,
                  int *array_index)
    {
        if (size == 1)
        {
            SCALAR_vv_1(0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 4)
        {
            AVX_vv_4_offset(0, NAME_AVX2_POW)
        }
        else if (size == 5)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            SCALAR_vv_1(4, NAME_SCALAR_POW);
        }
        else if (size == 6)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            *array_index += 4;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 7)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            *array_index += 4;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX512
    vpow_avx512_15(const double *input_array, const double *input_array1,
                   double *result_array, int size,
                   int *array_index)
    {
        if (size == 1)
        {
            SCALAR_vv_1(0, NAME_SCALAR_POW);
            //SSE_vv_2_mask2(0, NAME_SSE_POW)
        }
        else if (size == 2)
        {
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 13)
        {
            AVX512_vv_8__1(NAME_AVX512_POW);
            AVX_vv_4_offset(8, NAME_AVX2_POW);
            SCALAR_vv_1(12, NAME_SCALAR_POW);
        }
        else if (size == 14)
        {
            AVX512_vv_8__1(NAME_AVX512_POW);
            AVX_vv_4_offset(8, NAME_AVX2_POW);
            *array_index += 12;
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8(1, AVX512_NAME)
            AVX512_vv_8__1(NAME_AVX512_POW);
            AVX_vv_4_offset(8, NAME_AVX2_POW);
            *array_index += 12;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 12)
        {
            AVX512_vv_8__1(NAME_AVX512_POW);
            AVX_vv_4_offset(8, NAME_AVX2_POW)
        }
        else if (size == 11)
        {
            AVX512_vv_8__1(NAME_AVX512_POW);
            *array_index += 8;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 10)
        {
            AVX512_vv_8__1(NAME_AVX512_POW);
            *array_index += 8;
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 9)
        {
            // AVX512_8_mask4(1, AVX2_NAME)
            AVX512_vv_8__1(NAME_AVX512_POW);
            SCALAR_vv_1(8, NAME_SCALAR_POW);
        }
        else if (size == 8)
        {
            AVX512_vv_8__1(NAME_AVX512_POW)
        }
        else if (size == 5)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            SCALAR_vv_1(4, NAME_SCALAR_POW);
        }
        else if (size == 6)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            *array_index += 4;
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 7)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            *array_index += 4;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 4)
        {
            AVX_vv_4_offset(0, NAME_AVX2_POW)
        }
    }

    static inline void __CKL_FN_ATTR_AVX512 vpow_avx512_16_group(const double *input_array,
                                                                 const double *input_array1,
                                                                 double *result_array,
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
                AVX512_vv_8__2(NAME_AVX512_POW);
                *array_index += 16;
            }
            if (rest)
                vpow_avx512_15(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_vv_8__2(NAME_AVX512_POW)
        }
        else
        {
            vpow_avx512_15(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512 vpow_avx512(const double *input_array,
                                                        const double *input_array1,
                                                        double *result_array,
                                                        unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vpow_avx512_16_group(input_array, input_array1, result_array, size);
        }
        else if (size == 8)
        {
            AVX512_vv_8__1(NAME_AVX512_POW)
        }
        else
        {
            vpow_avx512_7(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpow *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_3(const double *input_array, const double *input_array1, double *result_array, int size,
                int *array_index)
    {
        if (size == 1)
        {
            SCALAR_vv_1(0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_7(const double *input_array, const double *input_array1, double *result_array, int size,
                int *array_index)
    {
        if (size == 7)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            *array_index += 4;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 6)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            *array_index += 4;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 5)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
            SCALAR_vv_1(4, NAME_SCALAR_POW);
        }
        else if (size == 4)
        {
            AVX_vv_4__1(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_15(const double *input_array, const double *input_array1, double *result_array, int size,
                 int *array_index)
    {
        if (size == 15)
        {
            AVX_vv_4__3(NAME_AVX2_POW);
            *array_index += 12;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 14)
        {
            AVX_vv_4__3(NAME_AVX2_POW);
            *array_index += 12;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 13)
        {
            AVX_vv_4__3(NAME_AVX2_POW);
            SCALAR_vv_1(12, NAME_SCALAR_POW);
        }
        else if (size == 12)
        {
            AVX_vv_4__3(NAME_AVX2_POW);
        }
        else if (size == 11)
        {
            AVX_vv_4__2(NAME_AVX2_POW);
            *array_index += 8;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 10)
        {
            AVX_vv_4__2(NAME_AVX2_POW);
            *array_index += 8;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 9)
        {
            AVX_vv_4__2(NAME_AVX2_POW);
            SCALAR_vv_1(8, NAME_SCALAR_POW);
        }
        else if (size == 8)
        {
            AVX_vv_4__2(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_7(input_array, input_array1, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~31*/
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_31(const double *input_array, const double *input_array1, double *result_array, int size,
                 int *array_index)
    {
        if (size == 31)
        {
            AVX_vv_4__7(NAME_AVX2_POW);
            *array_index += 28;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 30)
        {
            AVX_vv_4__7(NAME_AVX2_POW);
            *array_index += 28;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 29)
        {
            AVX_vv_4__7(NAME_AVX2_POW);
            SCALAR_vv_1(28, NAME_SCALAR_POW);
        }
        else if (size == 28)
        {
            AVX_vv_4__7(NAME_AVX2_POW);
        }
        else if (size == 27)
        {
            AVX_vv_4__6(NAME_AVX2_POW);
            *array_index += 24;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 26)
        {
            AVX_vv_4__6(NAME_AVX2_POW);
            *array_index += 24;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 25)
        {
            AVX_vv_4__6(NAME_AVX2_POW);
            SCALAR_vv_1(24, NAME_SCALAR_POW);
        }
        else if (size == 24)
        {
            AVX_vv_4__6(NAME_AVX2_POW);
        }
        else if (size == 23)
        {
            AVX_vv_4__5(NAME_AVX2_POW);
            *array_index += 20;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 22)
        {
            AVX_vv_4__5(NAME_AVX2_POW);
            *array_index += 20;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 21)
        {
            AVX_vv_4__5(NAME_AVX2_POW);
            SCALAR_vv_1(20, NAME_SCALAR_POW);
        }
        else if (size == 20)
        {
            AVX_vv_4__5(NAME_AVX2_POW);
        }
        else if (size == 19)
        {
            AVX_vv_4__4(NAME_AVX2_POW);
            *array_index += 16;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 18)
        {
            AVX_vv_4__4(NAME_AVX2_POW);
            *array_index += 16;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 17)
        {
            AVX_vv_4__4(NAME_AVX2_POW);
            SCALAR_vv_1(16, NAME_SCALAR_POW);
        }
        else if (size == 16)
        {
            AVX_vv_4__4(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_15(input_array, input_array1, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~63*/
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_63(const double *input_array, const double *input_array1, double *result_array, int size,
                 int *array_index)
    {
        if (size == 63)
        {
            AVX_vv_4__15(NAME_AVX2_POW);
            *array_index += 60;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 62)
        {
            AVX_vv_4__15(NAME_AVX2_POW);
            *array_index += 60;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 61)
        {
            AVX_vv_4__15(NAME_AVX2_POW);
            SCALAR_vv_1(60, NAME_SCALAR_POW);
        }
        else if (size == 60)
        {
            AVX_vv_4__15(NAME_AVX2_POW);
        }
        else if (size == 59)
        {
            AVX_vv_4__14(NAME_AVX2_POW);
            *array_index += 56;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 58)
        {
            AVX_vv_4__14(NAME_AVX2_POW);
            *array_index += 56;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 57)
        {
            AVX_vv_4__14(NAME_AVX2_POW);
            SCALAR_vv_1(56, NAME_SCALAR_POW);
        }
        else if (size == 56)
        {
            AVX_vv_4__14(NAME_AVX2_POW);
        }
        else if (size == 55)
        {
            AVX_vv_4__13(NAME_AVX2_POW);
            *array_index += 52;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 54)
        {
            AVX_vv_4__13(NAME_AVX2_POW);
            *array_index += 52;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 53)
        {
            AVX_vv_4__13(NAME_AVX2_POW);
            SCALAR_vv_1(52, NAME_SCALAR_POW);
        }
        else if (size == 52)
        {
            AVX_vv_4__13(NAME_AVX2_POW);
        }
        else if (size == 51)
        {
            AVX_vv_4__12(NAME_AVX2_POW);
            *array_index += 48;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 50)
        {
            AVX_vv_4__12(NAME_AVX2_POW);
            *array_index += 48;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 49)
        {
            AVX_vv_4__12(NAME_AVX2_POW);
            SCALAR_vv_1(48, NAME_SCALAR_POW);
        }
        else if (size == 48)
        {
            AVX_vv_4__12(NAME_AVX2_POW);
        }
        else if (size == 47)
        {
            AVX_vv_4__11(NAME_AVX2_POW);
            *array_index += 44;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 46)
        {
            AVX_vv_4__11(NAME_AVX2_POW);
            *array_index += 44;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 45)
        {
            AVX_vv_4__11(NAME_AVX2_POW);
            SCALAR_vv_1(44, NAME_SCALAR_POW);
        }
        else if (size == 44)
        {
            AVX_vv_4__11(NAME_AVX2_POW);
        }
        else if (size == 43)
        {
            AVX_vv_4__10(NAME_AVX2_POW);
            *array_index += 40;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 42)
        {
            AVX_vv_4__10(NAME_AVX2_POW);
            *array_index += 40;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 41)
        {
            AVX_vv_4__10(NAME_AVX2_POW);
            SCALAR_vv_1(40, NAME_SCALAR_POW);
        }
        else if (size == 40)
        {
            AVX_vv_4__10(NAME_AVX2_POW);
        }
        else if (size == 39)
        {
            AVX_vv_4__9(NAME_AVX2_POW);
            *array_index += 36;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 38)
        {
            AVX_vv_4__9(NAME_AVX2_POW);
            *array_index += 36;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 37)
        {
            AVX_vv_4__9(NAME_AVX2_POW);
            SCALAR_vv_1(36, NAME_SCALAR_POW);
        }
        else if (size == 36)
        {
            AVX_vv_4__9(NAME_AVX2_POW);
        }
        else if (size == 35)
        {
            AVX_vv_4__8(NAME_AVX2_POW);
            *array_index += 32;
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
        else if (size == 34)
        {
            AVX_vv_4__8(NAME_AVX2_POW);
            *array_index += 32;
            SSE_vv_2__1(NAME_SSE_POW);
        }
        else if (size == 33)
        {
            AVX_vv_4__8(NAME_AVX2_POW);
            SCALAR_vv_1(32, NAME_SCALAR_POW);
        }
        else if (size == 32)
        {
            AVX_vv_4__8(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_31(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_sub4(const double *input_array, const double *input_array1, double *result_array,
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
                AVX_vv_4__1(NAME_AVX2_POW);
                *array_index += 4;
            }
            if (rest)
                vpow_avx2_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_vv_4__1(NAME_AVX2_POW)
        }
        else
        {
            vpow_avx2_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_sub64(const double *input_array, const double *input_array1, double *result_array,
                    unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 64)
        {
            unsigned int count = size >> 6;
            unsigned int rest = size & 63;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_vv_4__16(NAME_AVX2_POW);
                *array_index += 64;
            }
            if (rest)
                vpow_avx2_63(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 64)
        {
            AVX_vv_4__16(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_63(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_sub32(const double *input_array, const double *input_array1, double *result_array,
                    unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 32)
        {
            vpow_avx2_sub64(input_array, input_array1, result_array, size);
        }
        else if (size == 32)
        {
            AVX_vv_4__8(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_31(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2_sub16(const double *input_array, const double *input_array1, double *result_array,
                    unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            vpow_avx2_sub32(input_array, input_array1, result_array, size);
        }
        else if (size == 16)
        {
            AVX_vv_4__4(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_15(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vpow_avx2(const double *input_array, const double *input_array1, double *result_array,
              unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vpow_avx2_sub16(input_array, input_array1, result_array, size);
        }
        else if (size == 8)
        {
            AVX_vv_4__2(NAME_AVX2_POW);
        }
        else
        {
            vpow_avx2_7(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpow *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vpow_avx_3(const double *input_array,
               const double *input_array1,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 1)
        {
            SCALAR_vv_1(0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vpow_avx(const double *input_array, const double *input_array1, double *result_array,
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
                SSE_vv_2__2(NAME_SSE_POW);
                *array_index += 4;
            }
            if (rest)
                vpow_avx_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_vv_2__2(NAME_SSE_POW)
        }
        else
        {
            vpow_avx_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpow *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vpow_sse_3(const double *input_array,
               const double *input_array1,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 1)
        {
            SCALAR_vv_1(0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_vv_2__1(NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_vv_2__1(NAME_SSE_POW);
            SCALAR_vv_1(2, NAME_SCALAR_POW);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vpow_sse(const double *input_array, const double *input_array1, double *result_array,
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
                SSE_vv_2__2(NAME_SSE_POW);
                *array_index += 4;
            }
            if (rest)
                vpow_sse_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_vv_2__2(NAME_SSE_POW)
        }
        else
        {
            vpow_sse_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** ckl_vpow *****************/
    static inline void vpow_scalar(const double *input_array, const double *input_array1, double *result_array,
                                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_vv_1(0, NAME_SCALAR_POW);
            *array_index += 1;
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VPOW_H*/
