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
#ifndef VML_VLOG_HOOK_H
#define VML_VLOG_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef void (*vml_vlog_hook_func_t)(const double *, double *, unsigned int, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vlog_hook_avx512(const double *input_array, double *result_array,
                                   unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vlog_hook_avx2(const double *input_array, double *result_array,
                                 unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vlog_hook_avx(const double *input_array, double *result_array,
                                unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vlog_hook_sse(const double *input_array, double *result_array,
                                unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vlog_hook_scalar(const double *input_array, double *result_array,
                                   unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#if GCC_IFUN_UNAVAILABLE == 0
    void vml_vlog_hook(const double *input_array, double *result_array,
                  unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args) __attribute__((ifunc("vlog_hook_ifunc")));
#else
void vml_vlog_hook(const double *input_array, double *result_array,
              unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vlog_hook_func_t, vlog_hook, vml_vlog_hook)

    __m128d _ZGVbN2v_log(__m128d x);
    __m256d _ZGVcN4v_log(__m256d x);
    __m256d _ZGVdN4v_log(__m256d x);
    __m512d _ZGVeN8v_log(__m512d x);

#include "common/ops.h"

#define NAME_AVX512_LOG eN8v_log
#define NAME_AVX2_LOG dN4v_log
#define NAME_AVX_LOG cN4v_log
#define NAME_SSE_LOG bN2v_log
#define NAME_SCALAR_LOG log
#define vml_log log
#define OP1 PRE_HOOK_OP(pre_hook, pre_args) 
#define OP2 POST_HOOK_OP(post_hook, post_args)

    /************** vml_vlog_hook *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX512
    vlog_hook_avx512_7(const double *input_array,
                  double *result_array,
                  int size,
                  int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_LOG)
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
            result_array[*array_index + 4] = log(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX512
    vlog_hook_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
            // SSE_2_mask2_ops(OP1, OP2, 0, SSE_NAME)
        }
        else if (size == 2)
        {
            // result_array[*array_index] = log(input_array[*array_index]);
            // result_array[*array_index + 1] = log(input_array[*array_index + 1]);
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 13)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_LOG);
            result_array[*array_index + 12] = log(input_array[*array_index + 12]);
        }
        else if (size == 14)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_LOG);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8_ops(OP1, OP2, 1, AVX512_NAME)
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_LOG);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 12)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG)
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_LOG)
        }
        else if (size == 11)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 10)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 9)
        {
            // AVX512_8_mask4_ops(OP1, OP2, 1, AVX2_NAME)
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG);
            result_array[*array_index + 8] = log(input_array[*array_index + 8]);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG)
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
            result_array[*array_index + 4] = log(input_array[*array_index + 4]);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
        }
        else if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            // result_array[*array_index + 4] = log(input_array[*array_index + 4]);
            // result_array[*array_index + 5] = log(input_array[*array_index + 5]);
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_LOG)
        }
    }

    static inline void __VML_FN_ATTR_AVX512 vlog_hook_avx512_16_group(const double *input_array, double *result_array,
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
                AVX512_8__2_ops(OP1, OP2, NAME_AVX512_LOG)
                *array_index += 16;
            }
            if (rest)
                vlog_hook_avx512_15(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_LOG)
        }
        else
        {
            vlog_hook_avx512_15(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __VML_FN_ATTR_AVX512 vlog_hook_avx512(const double *input_array, double *result_array,
                                                        unsigned int size, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vlog_hook_avx512_16_group(input_array, result_array, size, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_LOG)
        }
        else
        {
            vlog_hook_avx512_7(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vlog_hook *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vlog_hook_avx2_3(const double *input_array, double *result_array, int size,
                int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vlog_hook_avx2(const double *input_array, double *result_array,
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
                AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
                *array_index += 4;
            }
            if (rest)
                vlog_hook_avx2_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_LOG)
        }
        else
        {
            vlog_hook_avx2_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vlog_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
    vlog_hook_avx_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __VML_FN_ATTR_AVX
    vlog_hook_avx(const double *input_array, double *result_array,
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
                SSE_2__2_ops(OP1, OP2, NAME_SSE_LOG)
                *array_index += 4;
            }
            if (rest)
                vlog_hook_avx_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else
        {
            vlog_hook_avx_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vlog_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
    vlog_hook_sse_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            result_array[*array_index] = log(input_array[*array_index]);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_LOG)
            result_array[*array_index + 2] = log(input_array[*array_index + 2]);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __VML_FN_ATTR_SSE2
    vlog_hook_sse(const double *input_array, double *result_array,
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
                SSE_2__2_ops(OP1, OP2, NAME_SSE_LOG)
                *array_index += 4;
            }
            if (rest)
                vlog_hook_sse_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_LOG)
        }
        else
        {
            vlog_hook_sse_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vlog_hook *****************/
    static inline void vlog_hook_scalar(const double *input_array, double *result_array,
                                   unsigned int size, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_LOG);
            *array_index += 1;
        }
    }

#undef OP1
#undef OP2
#ifdef __cplusplus
}
#endif

#endif /*VML_VLOG_HOOK_H*/
