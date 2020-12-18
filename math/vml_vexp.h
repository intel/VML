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
#ifndef VML_VEXP_H
#define VML_VEXP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef int (*vml_vexp_func_t)(const double *, double *, unsigned int);
    static inline int vexp_avx512(const double *input_array, double *result_array,
                                   unsigned int size);
    static inline int vexp_avx2(const double *input_array, double *result_array,
                                 unsigned int size);
    static inline int vexp_avx(const double *input_array, double *result_array,
                                unsigned int size);
    static inline int vexp_sse(const double *input_array, double *result_array,
                                unsigned int size);
    static inline int vexp_scalar(const double *input_array, double *result_array,
                                   unsigned int size);
#if GCC_IFUN_UNAVAILABLE == 0
    int vml_vexp(const double *input_array, double *result_array,
                  unsigned int size) __attribute__((ifunc("vexp_ifunc")));
#else
    int vml_vexp(const double *input_array, double *result_array,
              unsigned int size);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vexp_func_t, vexp, vml_vexp)

    __m128d _ZGVbN2v_exp(__m128d x);
    __m256d _ZGVcN4v_exp(__m256d x);
    __m256d _ZGVdN4v_exp(__m256d x);
    __m512d _ZGVeN8v_exp(__m512d x);

#include "common/ops.h"

#define NAME_AVX512_EXP eN8v_exp
#define NAME_AVX2_EXP dN4v_exp
#define NAME_AVX_EXP cN4v_exp
#define NAME_SSE_EXP bN2v_exp
#define NAME_SCALAR_EXP exp
#define vml_exp exp
#define OP1 
#define OP2 

    /************** vml_vexp *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX512
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
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_EXP)
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
            result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            // result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = exp(input_array[*array_index + 5]);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX512
    vexp_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
            // SSE_2_mask2_ops(OP1, OP2, 0, SSE_NAME)
        }
        else if (size == 2)
        {
            // result_array[*array_index] = exp(input_array[*array_index]);
            // result_array[*array_index + 1] = exp(input_array[*array_index + 1]);
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 13)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXP);
            result_array[*array_index + 12] = exp(input_array[*array_index + 12]);
        }
        else if (size == 14)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXP);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8_ops(OP1, OP2, 1, AVX512_NAME)
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXP);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 12)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXP)
        }
        else if (size == 11)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 10)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 9)
        {
            // AVX512_8_mask4_ops(OP1, OP2, 1, AVX2_NAME)
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP);
            result_array[*array_index + 8] = exp(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
            result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            // result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = exp(input_array[*array_index + 5]);
        }
        else if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            // result_array[*array_index + 4] = exp(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = exp(input_array[*array_index + 5]);
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_EXP)
        }
    }

    static inline void __VML_FN_ATTR_AVX512 vexp_avx512_16_group(const double *input_array, double *result_array,
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
                AVX512_8__2_ops(OP1, OP2, NAME_AVX512_EXP)
                *array_index += 16;
            }
            if (rest)
                vexp_avx512_15(input_array, result_array, rest, array_index);
        }
        else if (size == 16)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_EXP)
        }
        else
        {
            vexp_avx512_15(input_array, result_array, size, array_index);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline int __VML_FN_ATTR_AVX512 vexp_avx512(const double *input_array, double *result_array,
                                                        unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 8)
        {
            vexp_avx512_16_group(input_array, result_array, size);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
        }
        else
        {
            vexp_avx512_7(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vexp *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vexp_avx2_3(const double *input_array, double *result_array, int size,
                int *array_index)
    {
        if (size == 1)
        {
            result_array[*array_index] = exp(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline int __VML_FN_ATTR_AVX2
    vexp_avx2(const double *input_array, double *result_array,
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
                AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_avx2_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
        }
        else
        {
            vexp_avx2_3(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vexp *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
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
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline int __VML_FN_ATTR_AVX
    vexp_avx(const double *input_array, double *result_array,
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
                SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_avx_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else
        {
            vexp_avx_3(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vexp *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
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
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_EXP)
            result_array[*array_index + 2] = exp(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline int __VML_FN_ATTR_SSE2
    vexp_sse(const double *input_array, double *result_array,
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
                SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_sse_3(input_array, result_array, rest, array_index);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else
        {
            vexp_sse_3(input_array, result_array, size, array_index);
        }
        return 0;
    }

    /************** vml_vexp *****************/
    static inline int vexp_scalar(const double *input_array, double *result_array,
                                   unsigned int size)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_EXP);
            *array_index += 1;
        }
        return 0;
    }

#undef OP1
#undef OP2

#ifdef __cplusplus
}
#endif

#endif /*VML_VEXP_H*/
