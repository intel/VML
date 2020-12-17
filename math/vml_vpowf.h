/*************************************************************************************/
/*  Copyright (C) 2021 Intel Corporation                                             */
/*                                                                                   */
/*  Redistribution and use in source and binary forms, with or without modification, */
/*  are permitted provided that the following conditions are met:                    */
/*                                                                                   */
/*  1. Redistributions of source code must retain the above copyright notice,        */
/*     this list of conditions and the following disclaimer.                         */
/*  2. Redistributions in binary form must reproduce the above copyright notice,     */
/*     this list of conditions and the following disclaimer in the documentation     */
/*     and/or other materials provided with the distribution.                        */
/*  3. Neither the name of the copyright holder nor the names of its contributors    */
/*     may be used to endorse or promote products derived from this software         */
/*     without specific prior written permission.                                    */
/*                                                                                   */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"      */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,            */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   */
/*  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS          */
/*  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,              */
/*  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT             */
/*  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;                  */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,         */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE             */
/*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,                */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                               */
/*                                                                                   */
/*                                                                                   */
/*  SPDX-License-Identifier: BSD-3-Clause                                            */
/*************************************************************************************/
#ifndef VML_VPOWF_H
#define VML_VPOWF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef void (*vml_vpowf_func_t)(const float *, const float *, float *, unsigned int);
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
    void vml_vpowf(const float *input_array, const float *input_array1, float *result_array,
                   unsigned int size) __attribute__((ifunc("vpowf_ifunc")));
#else
void vml_vpowf(const float *input_array, const float *input_array1, float *result_array,
               unsigned int size);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vpowf_func_t, vpowf, vml_vpowf)

    __m128d _ZGVbN2vv_pow(__m128d x, __m128d y);
    __m256d _ZGVcN4vv_pow(__m256d x, __m256d y);
    __m256d _ZGVdN4vv_pow(__m256d x, __m256d y);
    __m512d _ZGVeN8vv_pow(__m512d x, __m512d y);

#define VV 1
#include "commonf2d/ops.h"

#define NAME_AVX512_POWF2D eN8vv_pow
#define NAME_AVX2_POWF2D dN4vv_pow
#define NAME_AVX_POWF2D cN4vv_pow
#define NAME_SSE_POWF2D bN2vv_pow
#define NAME_SCALAR_POWF powf
#define vml_powf pow
#define OP1 
#define OP2 

    /************** vml_vpowf *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX512
    vpowf_avx512_7(const float *input_array,
                   const float *input_array1,
                   float *result_array,
                   int size,
                   int *array_index)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_POWF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
        else if (size == 4)
        {
            AVX_f2d_4_offset_ops(OP1, OP2, 0, NAME_AVX2_POWF2D);
        }
        else if (size == 5)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 4, NAME_SCALAR_POWF);
        }
        else if (size == 6)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
        }
        else if (size == 7)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX512
    vpowf_avx512_15(const float *input_array, const float *input_array1, float *result_array, int size,
                    int *array_index)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_POWF);
            // SSE_2_mask2_ops(OP1, OP2, 0, SSE_NAME)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
        else if (size == 13)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 12, NAME_SCALAR_POWF);
        }
        else if (size == 14)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POWF2D);
            *array_index += 12;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8_ops(OP1, OP2, 1, AVX512_NAME)
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POWF2D);
            *array_index += 12;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
        else if (size == 12)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POWF2D);
        }
        else if (size == 11)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            *array_index += 8;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
        else if (size == 10)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            *array_index += 8;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
        }
        else if (size == 9)
        {
            // AVX512_8_mask4_ops(OP1, OP2, 1, AVX2_NAME)
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 8, NAME_SCALAR_POWF);
        }
        else if (size == 8)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D);
        }
        else if (size == 5)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 4, NAME_SCALAR_POWF);
        }
        else if (size == 6)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
        }
        else if (size == 7)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
        else if (size == 4)
        {
            AVX_f2d_4_offset_ops(OP1, OP2, 0, NAME_AVX2_POWF2D);
        }
    }

    static inline void __VML_FN_ATTR_AVX512 vpowf_avx512_16_group(const float *input_array,
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
                AVX512_f2d_8__2_ops(OP1, OP2, NAME_AVX512_POWF2D);
                *array_index += 16;
            }
            if (rest)
                vpowf_avx512_15(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_f2d_8__2_ops(OP1, OP2, NAME_AVX512_POWF2D)
        }
        else
        {
            vpowf_avx512_15(input_array, input_array1, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __VML_FN_ATTR_AVX512 vpowf_avx512(const float *input_array,
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
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_POWF2D)
        }
        else
        {
            vpowf_avx512_7(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** vml_vpowf *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vpowf_avx2_3(const float *input_array, const float *input_array1,
                 float *result_array, int size,
                 int *array_index)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_POWF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
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
                AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D);
                *array_index += 4;
            }
            if (rest)
                vpowf_avx2_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_POWF2D)
        }
        else
        {
            vpowf_avx2_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** vml_vpowf *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
    vpowf_avx_3(const float *input_array,
                const float *input_array1,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_POWF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __VML_FN_ATTR_AVX
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
                SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_POWF2D);
                *array_index += 4;
            }
            if (rest)
                vpowf_avx_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_POWF2D)
        }
        else
        {
            vpowf_avx_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** vml_vpowf *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
    vpowf_sse_3(const float *input_array,
                const float *input_array1,
                float *result_array,
                int size,
                int *array_index)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_POWF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_POWF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_POWF);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __VML_FN_ATTR_SSE2
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
                SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_POWF2D);
                *array_index += 4;
            }
            if (rest)
                vpowf_sse_3(input_array, input_array1, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_POWF2D)
        }
        else
        {
            vpowf_sse_3(input_array, input_array1, result_array, size, array_index);
        }
    }

    /************** vml_vpowf *****************/
    static inline void vpowf_scalar(const float *input_array, const float *input_array1,
                                    float *result_array, unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_POWF);
            *array_index += 1;
        }
    }

#undef VV
#undef OP1
#undef OP2
#ifdef __cplusplus
}
#endif

#endif /*VML_VPOWF_H*/
