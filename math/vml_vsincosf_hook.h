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
#ifndef VML_VSINCOSF_HOOK_H
#define VML_VSINCOSF_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef int (*vml_vsincosf_hook_func_t)(const float *, float *, float *, unsigned int, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline int vsincosf_hook_avx512(const float *input_array, float *result_array,
                                       float *result_array1, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline int vsincosf_hook_avx2(const float *input_array, float *result_array,
                                     float *result_array1, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline int vsincosf_hook_avx(const float *input_array, float *result_array,
                                    float *result_array1, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline int vsincosf_hook_sse(const float *input_array, float *result_array,
                                    float *result_array1, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline int vsincosf_hook_scalar(const float *input_array, float *result_array,
                                       float *result_array1, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#if GCC_IFUN_UNAVAILABLE == 0
    int vml_vsincosf_hook(const float *input_array, float *result_array, float *result_array1,
                      unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args) __attribute__((ifunc("vsincosf_hook_ifunc")));
#else
    int vml_vsincosf_hook(const float *input_array, float *result_array, float *result_array1,
                  unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vsincosf_hook_func_t, vsincosf_hook, vml_vsincosf_hook)

    __m128 _ZGVbN4v_sinf(__m128 x);
    __m256 _ZGVcN8v_sinf(__m256 x);
    __m256 _ZGVdN8v_sinf(__m256 x);
    __m512 _ZGVeN16v_sinf(__m512 x);
    __m128d _ZGVbN2v_sin(__m128d x);
    __m128 _ZGVbN4v_cosf(__m128 x);
    __m256 _ZGVcN8v_cosf(__m256 x);
    __m256 _ZGVdN8v_cosf(__m256 x);
    __m512 _ZGVeN16v_cosf(__m512 x);
    __m128d _ZGVbN2v_cos(__m128d x);

#define SINCOS 1
#include "commonf/ops.h"
#include "commonf2d/ops.h"
#define OP1 PRE_HOOK_OP(pre_hook, pre_args) 
#define OP2 POST_HOOK_OP(post_hook, post_args)

    /************** vml_vsincosf_hook *****************/
    /*This function deals with size in 1~31 */
    static inline void __VML_FN_ATTR_AVX512
    vsincosf_hook_avx512_31(const float *input_array, float *result_array, float *result_array1, int size,
                       int *array_index, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size <= 31 && size >= 25)
        {
            AVX512_16_mask16_ops(OP1, OP2, 1,)
        }
        else if (size == 24)
        {
            AVX512_16__1_ops(OP1, OP2,);
            AVX_8_offset_ops(OP1, OP2, 16,)
        }
        else if (size <= 23 && size >= 17)
        {
            AVX512_16_mask8_ops(OP1, OP2, 1,,)
        }
        else if (size == 16)
        {
            AVX512_16__1_ops(OP1, OP2,)
        }
        else if (size <= 15 && size >= 9)
        {
            AVX512_16_mask16_ops(OP1, OP2, 0,)
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2,)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX512_16_mask8_ops(OP1, OP2, 0,,)
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2,)
        }
        else
        {
            AVX512_16_mask4_ops(OP1, OP2, 0,,)
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline int __VML_FN_ATTR_AVX512
    vsincosf_hook_avx512(const float *input_array, float *result_array, float *result_array1,
                    unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 31)
        {
            unsigned int count = size >> 5;
            unsigned int rest = size & 31;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX512_16__2_ops(OP1, OP2,);
                *array_index += 32;
            }
            if (rest)
                vsincosf_hook_avx512_31(input_array, result_array, result_array1, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else
        {
            vsincosf_hook_avx512_31(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        return 0;
    }

    /************** vml_vsincosf_hook *****************/
    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX2
    vsincosf_hook_AVX_15(const float *input_array, float *result_array, float *result_array1, int size,
                    int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size <= 15 && size >= 9)
        {
            AVX_8_mask8_ops(OP1, OP2, 1,)
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2,)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX_8_mask8_ops(OP1, OP2, 0,)
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2,)
        }
        else
        {
            AVX_8_mask4_ops(OP1, OP2, 0,,)
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline int __VML_FN_ATTR_AVX2
    vsincosf_hook_avx2(const float *input_array, float *result_array, float *result_array1,
                  unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        if (size > 16)
        {
            unsigned int count = size >> 4;
            unsigned int rest = size & 15;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_8__2_ops(OP1, OP2,);
                *array_index += 16;
            }
            if (rest)
                vsincosf_hook_AVX_15(input_array, result_array, result_array1, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX_8__2_ops(OP1, OP2,)
        }
        else
        {
            vsincosf_hook_AVX_15(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        return 0;
    }

    /************** vml_vsincosf_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
    vsincosf_hook_avx_3(const float *input_array,
                   float *result_array, float *result_array1, int size,
                   int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 3)
        {
            SSE_f2d_2_mask2_ops(OP1, OP2, 1,)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2,)
        }
        else
        {
            SSE_f2d_2_mask2_ops(OP1, OP2, 0,)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX
    vsincosf_hook_avx_7(const float *input_array,
                   float *result_array,
                   float *result_array1,
                   int size,
                   int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 7)
        {
            //SSE_f2d_2_mask2_ops(OP1, OP2, 3, bN2v_sincos)
            SSE_4__1_ops(OP1, OP2,);
            *array_index += 4;
            SSE_f2d_2_mask2_ops(OP1, OP2, 1,);
        }
        else if (size == 6)
        {
            //SSE_2__3
            SSE_4__1_ops(OP1, OP2,);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2,)
        }
        else if (size == 5)
        {
            //SSE_2_mask2_ops(OP1, OP2, 2, SSE_NAME)
            SSE_4__1_ops(OP1, OP2,);
            *array_index += 4;
            SSE_f2d_2_mask2_ops(OP1, OP2, 0,)
        }
        else if (size == 4)
        {
            //SSE_2__2
            SSE_4__1_ops(OP1, OP2,);
        }
        else
        {
            vsincosf_hook_avx_3(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX
    vsincosf_hook_avx_15(const float *input_array, float *result_array, float *result_array1, int size,
                    int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size <= 15 && size >= 9)
        {
            AVX_8_mask8_ops(OP1, OP2, 1,)
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2,)
        }
        else if (size == 7 || size == 6 || size == 5)
        {
            AVX_8_mask8_ops(OP1, OP2, 0,)
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2,)
        }
        else
        {
            AVX_8_mask4_ops(OP1, OP2, 0,,)
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __VML_FN_ATTR_AVX
    vsincosf_hook_avx1(const float *input_array, float *result_array, float *result_array1,
                  unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            unsigned int count = size >> 4;
            unsigned int rest = size & 15;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_8__2_ops(OP1, OP2,);
                *array_index += 16;
            }
            if (rest)
                vsincosf_hook_avx_15(input_array, result_array, result_array1, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX_8__2_ops(OP1, OP2,);
        }
        else
        {
            vsincosf_hook_avx_15(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline int __VML_FN_ATTR_AVX
    vsincosf_hook_avx(const float *input_array, float *result_array, float *result_array1,
                 unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
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
                //SSE_2__2
                SSE_4__2_ops(OP1, OP2,);
                *array_index += 8;
            }
            if (rest)
                vsincosf_hook_avx_7(input_array, result_array, result_array1, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            //SSE_2__2
            SSE_4__2_ops(OP1, OP2,)
        }
        else
        {
            vsincosf_hook_avx_7(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        return 0;
    }

    /************** vml_vsincosf_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
    vsincosf_hook_sse_3(const float *input_array,
                   float *result_array, float *result_array1, int size,
                   int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 3)
        {
            SSE_f2d_2_mask2_ops(OP1, OP2, 1,)
        }
        else if (size == 2)
        {
            SSE_f2d_2__1_ops(OP1, OP2,)
        }
        else
        {
            SSE_f2d_2_mask2_ops(OP1, OP2, 0,)
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_SSE2
    vsincosf_hook_sse_7(const float *input_array,
                   float *result_array,
                   float *result_array1,
                   int size,
                   int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 7)
        {
            //SSE_f2d_2_mask2_ops(OP1, OP2, 3, bN2v_sincos)
            SSE_4__1_ops(OP1, OP2,);
            *array_index += 4;
            SSE_f2d_2_mask2_ops(OP1, OP2, 1,)
        }
        else if (size == 6)
        {
            //SSE_2__3
            SSE_4__1_ops(OP1, OP2,);
            *array_index += 4;
            SSE_f2d_2__1_ops(OP1, OP2,)
        }
        else if (size == 5)
        {
            //SSE_2_mask2_ops(OP1, OP2, 2, SSE_NAME)
            SSE_4__1_ops(OP1, OP2,);
            *array_index += 4;
            SSE_f2d_2_mask2_ops(OP1, OP2, 0,)
        }
        else if (size == 4)
        {
            //SSE_2__2
           SSE_4__1_ops(OP1, OP2,);
        }
        else
        {
            vsincosf_hook_sse_3(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline int __VML_FN_ATTR_SSE2
    vsincosf_hook_sse(const float *input_array, float *result_array, float *result_array1,
                 unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, void * post_args)
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
                //SSE_2__2
                SSE_4__2_ops(OP1, OP2,);
                *array_index += 8;
            }
            if (rest)
                vsincosf_hook_sse_7(input_array, result_array, result_array1, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            //SSE_2__2
            SSE_4__2_ops(OP1, OP2,)
        }
        else
        {
            vsincosf_hook_sse_7(input_array, result_array, result_array1, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        return 0;
    }

    /************** vml_vsincosf_hook *****************/
    static inline int vsincosf_hook_scalar(const float *input_array, float *result_array, float *result_array1,
                                       unsigned int size, vml_hook_func_t pre_hook, 
				   void * pre_args, vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if(input_array == NULL || result_array == NULL)
            return -1;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALARF_1_ops(OP1, OP2, 0,);
            *array_index += 1;
        }
        return 0;
    }

#undef OP1
#undef OP2
#undef SINCOS
#ifdef __cplusplus
}
#endif

#endif /*VML_VSINCOSF_HOOK_H*/
