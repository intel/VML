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
#ifndef VML_VEXPF_HOOK_H
#define VML_VEXPF_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef void (*vml_vexpf_hook_func_t)(const float *, float *, unsigned int, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vexpf_hook_avx512(const float *input_array, float *result_array,
                                    unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vexpf_hook_avx2(const float *input_array, float *result_array,
                                  unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vexpf_hook_avx(const float *input_array, float *result_array,
                                 unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vexpf_hook_sse(const float *input_array, float *result_array,
                                 unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vexpf_hook_scalar(const float *input_array, float *result_array,
                                    unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#if GCC_IFUN_UNAVAILABLE == 0
    void vml_vexpf_hook(const float *input_array, float *result_array,
                   unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args) __attribute__((ifunc("vexpf_hook_ifunc")));
#else
void vml_vexpf_hook(const float *input_array, float *result_array,
               unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vexpf_hook_func_t, vexpf_hook, vml_vexpf_hook)

    __m128d _ZGVbN2v_exp(__m128d x);
    __m256d _ZGVcN4v_exp(__m256d x);
    __m256d _ZGVdN4v_exp(__m256d x);
    __m512d _ZGVeN8v_exp(__m512d x);
    #define NAME_SCALAR_EXPF expf
    #define vml_expf exp

#include "commonf2d/ops.h"

#define NAME_AVX512_EXPF2D eN8v_exp
#define NAME_AVX2_EXPF2D dN4v_exp
#define NAME_AVX_EXPF2D cN4v_exp
#define NAME_SSE_EXPF2D bN2v_exp
#define OP1 PRE_HOOK_OP(pre_hook, pre_args) 
#define OP2 POST_HOOK_OP(post_hook, post_args)

    /************** vml_vexpf_hook *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX512
    vexpf_hook_avx512_7(const float *input_array,
                   float *result_array,
                   int size,
                   int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_EXPF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
        else if (size == 4)
        {
            AVX_f2d_4_offset_ops(OP1, OP2, 0, NAME_AVX2_EXPF2D);
        }
        else if (size == 5)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 4, NAME_SCALAR_EXPF);
        }
        else if (size == 6)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
        }
        else if (size == 7)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX512
    vexpf_hook_avx512_15(const float *input_array, float *result_array, int size,
                    int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_EXPF);
            // SSE_2_mask2_ops(OP1, OP2, 0, SSE_NAME)
        }
        else if (size == 2)
        {
            // result_array[*array_index] = expf(input_array[*array_index]);
            // result_array[*array_index + 1] = expf(input_array[*array_index + 1]);
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
        else if (size == 13)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 12, NAME_SCALAR_EXPF);
        }
        else if (size == 14)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXPF2D);
            *array_index += 12;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8_ops(OP1, OP2, 1, AVX512_NAME)
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXPF2D);
            *array_index += 12;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
        else if (size == 12)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            AVX_f2d_4_offset_ops(OP1, OP2, 8, NAME_AVX2_EXPF2D);
        }
        else if (size == 11)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            *array_index += 8;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
        else if (size == 10)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            *array_index += 8;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
        }
        else if (size == 9)
        {
            // AVX512_8_mask4_ops(OP1, OP2, 1, AVX2_NAME)
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 8, NAME_SCALAR_EXPF);
        }
        else if (size == 8)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D);
        }
        else if (size == 5)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 4, NAME_SCALAR_EXPF);
        }
        else if (size == 6)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            // result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = expf(input_array[*array_index + 5]);
        }
        else if (size == 7)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            // result_array[*array_index + 4] = expf(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = expf(input_array[*array_index + 5]);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
        else if (size == 4)
        {
            AVX_f2d_4_offset_ops(OP1, OP2, 0, NAME_AVX2_EXPF2D);
        }
    }

    static inline void __VML_FN_ATTR_AVX512 vexpf_hook_avx512_16_group(const float *input_array, float *result_array,
                                                                  unsigned int size, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            unsigned int count = size >> 4;
            unsigned int rest = size & 15;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX512_f2d_8__2_ops(OP1, OP2, NAME_AVX512_EXPF2D);
                *array_index += 16;
            }
            if (rest)
                vexpf_hook_avx512_15(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX512_f2d_8__2_ops(OP1, OP2, NAME_AVX512_EXPF2D)
        }
        else
        {
            vexpf_hook_avx512_15(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __VML_FN_ATTR_AVX512 vexpf_hook_avx512(const float *input_array, float *result_array,
                                                         unsigned int size, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vexpf_hook_avx512_16_group(input_array, result_array, size, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            AVX512_f2d_8__1_ops(OP1, OP2, NAME_AVX512_EXPF2D)
        }
        else
        {
            vexpf_hook_avx512_7(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vexpf_hook *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vexpf_hook_avx2_3(const float *input_array, float *result_array, int size,
                 int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_EXPF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vexpf_hook_avx2(const float *input_array, float *result_array,
               unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D);
                *array_index += 4;
            }
            if (rest)
                vexpf_hook_avx2_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            AVX_f2d_4__1_ops(OP1, OP2, NAME_AVX2_EXPF2D)
        }
        else
        {
            vexpf_hook_avx2_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vexpf_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
    vexpf_hook_avx_3(const float *input_array,
                float *result_array,
                int size,
                int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_EXPF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __VML_FN_ATTR_AVX
    vexpf_hook_avx(const float *input_array, float *result_array,
              unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_EXPF2D);
                *array_index += 4;
            }
            if (rest)
                vexpf_hook_avx_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_EXPF2D)
        }
        else
        {
            vexpf_hook_avx_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vexpf_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
    vexpf_hook_sse_3(const float *input_array,
                float *result_array,
                int size,
                int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_EXPF);
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D)
        }
        else if (size == 3)
        {
            SSE_f2d_2__1_ops(OP1, OP2, NAME_SSE_EXPF2D);
            SCALAR_f2d_1_ops(OP1, OP2, 2, NAME_SCALAR_EXPF);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __VML_FN_ATTR_SSE2
    vexpf_hook_sse(const float *input_array, float *result_array,
              unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_EXPF2D);
                *array_index += 4;
            }
            if (rest)
                vexpf_hook_sse_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_f2d_2__2_ops(OP1, OP2, NAME_SSE_EXPF2D)
        }
        else
        {
            vexpf_hook_sse_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vexpf_hook *****************/
    static inline void vexpf_hook_scalar(const float *input_array, float *result_array,
                                    unsigned int size, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_f2d_1_ops(OP1, OP2, 0, NAME_SCALAR_EXPF);
            *array_index += 1;
        }
    }

#undef OP1
#undef OP2
#ifdef __cplusplus
}
#endif

#endif /*VML_VEXPF_HOOK_H*/
