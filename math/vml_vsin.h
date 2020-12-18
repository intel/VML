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
#ifndef VML_VSIN_H
#define VML_VSIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef int (*vml_vsin_func_t)(const double *, double *, unsigned int);
    static inline int vsin_avx512(const double *input_array, double *result_array,
                                   unsigned int size);
    static inline int vsin_avx2(const double *input_array, double *result_array,
                                 unsigned int size);
    static inline int vsin_avx(const double *input_array, double *result_array,
                                unsigned int size);
    static inline int vsin_sse(const double *input_array, double *result_array,
                                unsigned int size);
    static inline int vsin_scalar(const double *input_array, double *result_array,
                                   unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    int vml_vsin(const double *input_array, double *result_array,
                  unsigned int size) __attribute__((ifunc("vsin_ifunc")));
#else
    int vml_vsin(const double *input_array, double *result_array,
              unsigned int size);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vsin_func_t, vsin, vml_vsin)

    __m128d _ZGVbN2v_sin(__m128d x);
    __m256d _ZGVcN4v_sin(__m256d x);
    __m256d _ZGVdN4v_sin(__m256d x);
    __m512d _ZGVeN8v_sin(__m512d x);

#include "common/ops.h"

#define NAME_AVX512_SIN eN8v_sin
#define NAME_AVX2_SIN dN4v_sin
#define NAME_AVX_SIN cN4v_sin
#define NAME_SSE_SIN bN2v_sin
#define NAME_SCALAR_SIN sin
#define vml_sin sin
#define OP1 
#define OP2 

    /************** vml_vsin *****************/
    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX512
    vsin_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX512_8_mask8_ops(OP1, OP2, 1, NAME_AVX512_SIN)
        }
        else if (size == 12)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_SIN)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_SIN)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX512_8_mask4_ops(OP1, OP2, 1, NAME_AVX512_SIN, NAME_AVX2_SIN)
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_SIN)
        }
        else if (size == 5 || size == 6 || size == 7)
        {
            AVX512_8_mask8_ops(OP1, OP2, 0, NAME_AVX512_SIN)
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_SIN)
        }
        else
        {
            AVX512_8_mask4_ops(OP1, OP2, 0, NAME_AVX512_SIN, NAME_AVX2_SIN)
        }
    }

    /*This function deals with size in 1~31 */
    static inline void __VML_FN_ATTR_AVX512
    vsin_avx512_31(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 31 || size == 30 || size == 29)
        {
            AVX512_8_mask8_ops(OP1, OP2, 3, NAME_AVX512_SIN)
        }
        else if (size == 28)
        {
            AVX512_8__3_ops(OP1, OP2, NAME_AVX512_SIN)
            AVX_4_offset_ops(OP1, OP2, 24, NAME_AVX2_SIN)
        }
        else if (size == 27 || size == 26 || size == 25)
        {
            AVX512_8_mask4_ops(OP1, OP2, 3, NAME_AVX512_SIN, NAME_AVX2_SIN)
        }
        else if (size == 24)
        {
            AVX512_8__3_ops(OP1, OP2, NAME_AVX512_SIN)
        }
        else if (size == 23 || size == 22 || size == 21)
        {
            AVX512_8_mask8_ops(OP1, OP2, 2, NAME_AVX512_SIN)
        }
        else if (size == 20)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_SIN)
            AVX_4_offset_ops(OP1, OP2, 16, NAME_AVX2_SIN)
        }
        else if (size == 19 || size == 18 || size == 17)
        {
            AVX512_8_mask4_ops(OP1, OP2, 2, NAME_AVX512_SIN, NAME_AVX2_SIN)
        }
        else if (size == 16)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_SIN)
        }
        else
            vsin_avx512_15(input_array, result_array, size, array_index);
    }

    static inline void __VML_FN_ATTR_AVX512
    vsin_avx512_sub(const double *input_array, double *result_array,
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
                AVX512_8__2_ops(OP1, OP2, NAME_AVX512_SIN)
                *array_index += 16;
            }
            if (rest)
                vsin_avx512_31(input_array, result_array, rest, array_index);
        }
        else if (size == 32)
        {
            AVX512_8__4_ops(OP1, OP2, NAME_AVX512_SIN)
        }
        else
        {
            vsin_avx512_31(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline int __VML_FN_ATTR_AVX512
    vsin_avx512(const double *input_array, double *result_array,
                unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 16)
        {
            vsin_avx512_sub(input_array, result_array, size);
        }
        else if (size == 16)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_SIN)
        }
        else
        {
            vsin_avx512_15(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vsin *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vsin_avx2_7(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 7 || size == 6 || size == 5)
        {
            AVX_4_mask4_ops(OP1, OP2, 1, NAME_AVX2_SIN)
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_SIN)
        }
        else
        {
            AVX_4_mask4_ops(OP1, OP2, 0, NAME_AVX2_SIN)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX2
    vsin_avx2_15(const double *input_array, double *result_array, int size,
                 int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX_4_mask4_ops(OP1, OP2, 3, NAME_AVX2_SIN)
        }
        else if (size == 12)
        {
            AVX_4__3_ops(OP1, OP2, NAME_AVX2_SIN)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX_4_mask4_ops(OP1, OP2, 2, NAME_AVX2_SIN)
        }
        else if (size == 8)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_SIN)
        }
        else if (size == 5 || size == 6 || size == 7)
        {
            AVX_4_mask4_ops(OP1, OP2, 1, NAME_AVX2_SIN)
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_SIN)
        }
        else
        {
            AVX_4_mask4_ops(OP1, OP2, 0, NAME_AVX2_SIN)
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline int __VML_FN_ATTR_AVX2
    vsin_avx2(const double *input_array, double *result_array,
              unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 8)
        {
            unsigned int count = size >> 3;
            unsigned int rest = size & 7;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_4__2_ops(OP1, OP2, NAME_AVX2_SIN)
                *array_index += 8;
            }
            if (rest)
                vsin_avx2_7(input_array, result_array, rest, array_index);
        }
        else if (size == 8)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_SIN)
        }
        else
        {
            vsin_avx2_7(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vsin *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
    vsin_avx_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 3)
        {
            SSE_2_mask2_ops(OP1, OP2, 1, NAME_SSE_SIN)
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else
        {
            SSE_2_mask2_ops(OP1, OP2, 0, NAME_SSE_SIN)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX
    vsin_avx_7(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 7 || size == 6)
        {
            AVX_4_mask4_ops(OP1, OP2, 1, NAME_AVX_SIN)
        }
        else if (size == 5)
        {
            AVX_4_mask2_ops(OP1, OP2, 1, NAME_AVX_SIN, NAME_SSE_SIN)
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX_SIN)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_SIN)
            *array_index += 2;
            SSE_2_mask2_ops(OP1, OP2, 0, NAME_SSE_SIN)
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else
        {
            AVX_4_mask2_ops(OP1, OP2, 0, NAME_AVX_SIN, NAME_SSE_SIN)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX
    vsin_avx_15(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 13 || size == 14 || size == 15)
        {
            AVX_4_mask4_ops(OP1, OP2, 3, NAME_AVX_SIN)
        }
        else if (size == 12)
        {
            AVX_4__3_ops(OP1, OP2, NAME_AVX_SIN)
        }
        else if (size == 11 || size == 10 || size == 9)
        {
            AVX_4_mask4_ops(OP1, OP2, 2, NAME_AVX_SIN)
        }
        else if (size == 8)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX_SIN)
        }
        else
        {
            vsin_avx_7(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline int __VML_FN_ATTR_AVX
    vsin_avx(const double *input_array, double *result_array,
             unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_2__2_ops(OP1, OP2, NAME_SSE_SIN)
                *array_index += 4;
            }
            if (rest)
                vsin_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else
        {
            vsin_avx_3(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vsin *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
    vsin_sse_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 3)
        {
            SSE_2_mask2_ops(OP1, OP2, 1, NAME_SSE_SIN)
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else
        {
            SSE_2_mask2_ops(OP1, OP2, 0, NAME_SSE_SIN)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_SSE2
    vsin_sse_7(const double *input_array,
               double *result_array,
               int size,
               int *array_index)
    {
        if (size == 7)
        {
            SSE_2_mask2_ops(OP1, OP2, 3, NAME_SSE_SIN)
        }
        else if (size == 6)
        {
            SSE_2__3_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 5)
        {
            SSE_2_mask2_ops(OP1, OP2, 2, NAME_SSE_SIN)
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else
        {
            vsin_sse_3(input_array, result_array, size, array_index);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_SSE2
    vsin_sse_15(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 15)
        {
            SSE_2_mask2_ops(OP1, OP2, 7, NAME_SSE_SIN)
        }
        else if (size == 14)
        {
            SSE_2__7_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 13)
        {
            SSE_2_mask2_ops(OP1, OP2, 6, NAME_SSE_SIN)
        }
        else if (size == 12)
        {
            SSE_2__6_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 11)
        {
            SSE_2_mask2_ops(OP1, OP2, 5, NAME_SSE_SIN)
        }
        else if (size == 10)
        {
            SSE_2__5_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 9)
        {
            SSE_2_mask2_ops(OP1, OP2, 4, NAME_SSE_SIN)
        }
        else if (size == 8)
        {
            SSE_2__4_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 7)
        {
            SSE_2_mask2_ops(OP1, OP2, 3, NAME_SSE_SIN)
        }
        else if (size == 6)
        {
            SSE_2__3_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 5)
        {
            SSE_2_mask2_ops(OP1, OP2, 2, NAME_SSE_SIN)
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 3)
        {
            SSE_2_mask2_ops(OP1, OP2, 1, NAME_SSE_SIN)
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else if (size == 1)
        {
            SSE_2_mask2_ops(OP1, OP2, 0, NAME_SSE_SIN)
        }
    }

    /* kernel with vectorization up to SSE */
    static inline int __VML_FN_ATTR_SSE2
    vsin_sse(const double *input_array, double *result_array,
             unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_2__2_ops(OP1, OP2, NAME_SSE_SIN)
                *array_index += 4;
            }
            if (rest)
                vsin_sse_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_SIN)
        }
        else
        {
            vsin_sse_3(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vsin *****************/
    static inline int vsin_scalar(const double *input_array, double *result_array,
                                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_SIN);
            *array_index += 1;
        }
        return 0;
    }

#undef OP1
#undef OP2
#ifdef __cplusplus
}
#endif

#endif /*VML_VSIN_H*/
