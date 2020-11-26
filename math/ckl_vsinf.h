#ifndef CKL_VSINF_H
#define CKL_VSINF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vsinf_func_t)(const float *, float *, unsigned int);
    static inline void vsinf_avx512(const float *input_array, float *result_array,
                                    unsigned int size);
    static inline void vsinf_avx2(const float *input_array, float *result_array,
                                  unsigned int size);
    static inline void vsinf_avx(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vsinf_sse(const float *input_array, float *result_array,
                                 unsigned int size);
    static inline void vsinf_scalar(const float *input_array, float *result_array,
                                    unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vsinf(const float *input_array, float *result_array,
                   unsigned int size) __attribute__((ifunc("vsinf_ifunc")));
#else
void ckl_vsinf(const float *input_array, float *result_array,
               unsigned int size);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vsinf_func_t, vsinf, ckl_vsinf)

    __m128 _ZGVbN4v_sinf(__m128 x);
    __m256 _ZGVcN8v_sinf(__m256 x);
    __m256 _ZGVdN8v_sinf(__m256 x);
    __m512 _ZGVeN16v_sinf(__m512 x);
    __m128d _ZGVbN2v_sin(__m128d x);
    #define NAME_SCALAR_SINF sinf
    #define ckl_sinf sinf

#include "commonf/avx.h"
#include "commonf/avx512.h"
#include "commonf/sse.h"
#include "commonf2d/sse.h"

#define NAME_AVX512_SINF eN16v_sinf
#define NAME_AVX2_SINF dN8v_sinf
#define NAME_AVX_SINF cN8v_sinf
#define NAME_SSE_SINF bN4v_sinf
#define NAME_SSE_SINF2D bN2v_sin

    /************** ckl_vsinf *****************/
    /*This function deals with size in 1~31 */
    static inline void __CKL_FN_ATTR_AVX512
    vsinf_avx512_31(const float *input_array, float *result_array, int size,
                    int *array_index)
    {
        if (size <= 31 && size >= 25)
        {
            AVX512_16_mask16(1, NAME_AVX512_SINF)
        }
        else if (size == 24)
        {
            AVX512_16__1(NAME_AVX512_SINF)
            AVX_8_offset(16, NAME_AVX2_SINF)
        }
        else if (size <= 23 && size >= 17)
        {
            AVX512_16_mask8(1, NAME_AVX512_SINF, NAME_AVX2_SINF)
        }
        else if (size == 16)
        {
            AVX512_16__1(NAME_AVX512_SINF)
        }
        else if (size <= 15 && size >= 9)
        {
            AVX512_16_mask16(0, NAME_AVX512_SINF)
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_SINF)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            // AVX_8_mask8(0, AVX2_NAME)
            AVX512_16_mask8(0, NAME_AVX512_SINF, NAME_AVX2_SINF)
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_SINF)
        }
        else
        {
            AVX512_16_mask4(0, NAME_AVX512_SINF, NAME_SSE_SINF)
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512
    vsinf_avx512(const float *input_array, float *result_array,
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
                AVX512_16__2(NAME_AVX512_SINF)
                *array_index += 32;
            }
            if (rest)
                vsinf_avx512_31(input_array, result_array, rest, array_index);
        }
        else
        {
            vsinf_avx512_31(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vsinf *****************/
    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vsinf_avx2_15(const float *input_array, float *result_array, int size,
                  int *array_index)
    {
        if (size <= 15 && size >= 9)
        {
            AVX_8_mask8(1, NAME_AVX2_SINF)
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX2_SINF)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX_8_mask8(0, NAME_AVX2_SINF)
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_SINF)
        }
        else
        {
            AVX_8_mask4(0, NAME_AVX2_SINF, NAME_SSE_SINF)
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vsinf_avx2(const float *input_array, float *result_array,
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
                AVX_8__2(NAME_AVX2_SINF)
                *array_index += 16;
            }
            if (rest)
                vsinf_avx2_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX_8__2(NAME_AVX2_SINF)
        }
        else
        {
            vsinf_avx2_15(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vsinf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vsinf_avx_3(const float *input_array,
                float *result_array, int size,
                int *array_index)
    {
        if (size == 3)
        {
            SSE_f2d_2_mask2(1, NAME_SSE_SINF2D)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_SINF2D)
        }
        else
        {
            SSE_f2d_2_mask2(0, NAME_SSE_SINF2D)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX
    vsinf_avx_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 7)
        {
            //SSE_f2d_2_mask2(3, NAME_SSE_SINF2D)
            SSE_4__1(NAME_SSE_SINF)
            *array_index += 4;
            SSE_f2d_2_mask2(1, NAME_SSE_SINF2D)
        }
        else if (size == 6)
        {
            //SSE_2__3
            SSE_4__1(NAME_SSE_SINF)
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_SINF2D)
        }
        else if (size == 5)
        {
            //SSE_2_mask2(2, SSE_NAME)
            SSE_4__1(NAME_SSE_SINF)
            *array_index += 4;
            SSE_f2d_2_mask2(0, NAME_SSE_SINF2D)
        }
        else if (size == 4)
        {
            //SSE_2__2
            SSE_4__1(NAME_SSE_SINF)
        }
        else
        {
            vsinf_avx_3(input_array, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX
    vsinf_avx_15(const float *input_array, float *result_array, int size,
                 int *array_index)
    {
        if (size <= 15 && size >= 9)
        {
            AVX_8_mask8(1, NAME_AVX_SINF)
        }
        else if (size == 8)
        {
            AVX_8__1(NAME_AVX_SINF)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX_8_mask8(0, NAME_AVX_SINF)
        }
        else if (size == 4)
        {
            SSE_4__1(NAME_SSE_SINF)
        }
        else
        {
            AVX_8_mask4(0, NAME_AVX_SINF, NAME_SSE_SINF)
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vsinf_avx1(const float *input_array, float *result_array,
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
                AVX_8__2(NAME_AVX_SINF)
                *array_index += 16;
            }
            if (rest)
                vsinf_avx_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX_8__2(NAME_AVX_SINF)
        }
        else
        {
            vsinf_avx_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vsinf_avx(const float *input_array, float *result_array,
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
                //SSE_2__2
                SSE_4__2(NAME_SSE_SINF)
                *array_index += 8;
            }
            if (rest)
                vsinf_avx_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            //SSE_2__2
            SSE_4__2(NAME_SSE_SINF)
        }
        else
        {
            vsinf_avx_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vsinf *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vsinf_sse_3(const float *input_array,
                float *result_array, int size,
                int *array_index)
    {
        if (size == 3)
        {
            SSE_f2d_2_mask2(1, NAME_SSE_SINF2D)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1(NAME_SSE_SINF2D)
        }
        else
        {
            SSE_f2d_2_mask2(0, NAME_SSE_SINF2D)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_SSE2
    vsinf_sse_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 7)
        {
            //SSE_f2d_2_mask2(3, NAME_SSE_SINF2D)
            SSE_4__1(NAME_SSE_SINF)
            *array_index += 4;
            SSE_f2d_2_mask2(1, NAME_SSE_SINF2D)
        }
        else if (size == 6)
        {
            //SSE_2__3
            SSE_4__1(NAME_SSE_SINF)
            *array_index += 4;
            SSE_f2d_2__1(NAME_SSE_SINF2D)
        }
        else if (size == 5)
        {
            //SSE_2_mask2(2, SSE_NAME)
            SSE_4__1(NAME_SSE_SINF)
            *array_index += 4;
            SSE_f2d_2_mask2(0, NAME_SSE_SINF2D)
        }
        else if (size == 4)
        {
            //SSE_2__2
            SSE_4__1(NAME_SSE_SINF)
        }
        else
        {
            vsinf_sse_3(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vsinf_sse(const float *input_array, float *result_array,
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
                //SSE_2__2
                SSE_4__2(NAME_SSE_SINF)
                *array_index += 8;
            }
            if (rest)
                vsinf_sse_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            //SSE_2__2
            SSE_4__2(NAME_SSE_SINF)
        }
        else
        {
            vsinf_sse_7(input_array, result_array, size, array_index);
        }
    }

    /************** ckl_vsinf *****************/
    static inline void vsinf_scalar(const float *input_array, float *result_array,
                                    unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALARF_1(0, NAME_SCALAR_SINF);
            *array_index += 1;
        }
    }

#ifdef __cplusplus
}
#endif

#endif /*CKL_VSINF_H*/
