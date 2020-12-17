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
#ifndef VML_VPOW_SV_HOOK_H
#define VML_VPOW_SV_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "vml_common.h"
    typedef void (*vml_vpow_sv_hook_func_t)(const double, const double *, double *, unsigned int, 
    vml_hook_func_t, void *, vml_hook_func_t, void *);
    static inline void vpow_sv_hook_avx512(const double input_value, const double *input_array,
                                   double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vpow_sv_hook_avx2(const double input_value, const double *input_array,
                                 double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                                 void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vpow_sv_hook_avx(const double input_value, const double *input_array,
                                double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                                void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vpow_sv_hook_sse(const double input_value, const double *input_array,
                                double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                                void * pre_args, vml_hook_func_t post_hook, void * post_args);
    static inline void vpow_sv_hook_scalar(const double input_value, const double *input_array,
                                   double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
#if GCC_IFUN_UNAVAILABLE == 0
    void vml_vpow_sv_hook(const double input_value, const double *input_array, double *result_array,
                  unsigned int size, vml_hook_func_t pre_hook, void * pre_args, 
                  vml_hook_func_t post_hook, void * post_args) __attribute__((ifunc("vpow_sv_hook_ifunc")));
#else
void vml_vpow_sv_hook(const double input_value, const double *input_array, double *result_array,
              unsigned int size, vml_hook_func_t pre_hook, void * pre_args, 
              vml_hook_func_t post_hook, void * post_args);
#endif

#include "vml_ifunc.h"
    RESOLVE_FUNC(vml_vpow_sv_hook_func_t, vpow_sv_hook, vml_vpow_sv_hook)

    __m128d _ZGVbN2vv_pow(__m128d x, __m128d y);
    __m256d _ZGVcN4vv_pow(__m256d x, __m256d y);
    __m256d _ZGVdN4vv_pow(__m256d x, __m256d y);
    __m512d _ZGVeN8vv_pow(__m512d x, __m512d y);

#define SCALAR_ARRAY 1
#define VV 1
#include "common/ops.h"

#define NAME_AVX512_POW eN8vv_pow
#define NAME_AVX2_POW dN4vv_pow
#define NAME_AVX_POW cN4vv_pow
#define NAME_SSE_POW bN2vv_pow
#define NAME_SCALAR_POW pow
#ifndef vml_pow
#define vml_pow pow
#endif
#define OP1 PRE_HOOK_OP(pre_hook, pre_args) 
#define OP2 POST_HOOK_OP(post_hook, post_args)
#define SCALAR_1(i, name) SCALAR_1_TMP(i, name)

    /************** vml_vpow *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX512
    vpow_sv_hook_avx512_7(const double input_value,
                  const double *input_array,
                  double *result_array,
                  int size,
                  int *array_index,
                  vml_hook_func_t pre_hook, 
                  void * pre_args, 
                  vml_hook_func_t post_hook, 
                  void * post_args)
    {
        if (size == 1)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_POW)
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 4, NAME_SCALAR_POW);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX512
    vpow_sv_hook_avx512_15(const double input_value, const double *input_array,
                   double *result_array, int size,
                   int *array_index,
                   vml_hook_func_t pre_hook, 
                   void * pre_args, 
                   vml_hook_func_t post_hook, 
                   void * post_args)
    {
        if (size == 1)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_POW);
            //SSE_2_mask2(0, NAME_SSE_POW)
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 13)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 12, NAME_SCALAR_POW);
        }
        else if (size == 14)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POW);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 15)
        {
            // AVX512_8_mask8_ops(OP1, OP2, 1, AVX512_NAME)
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POW);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 12)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            AVX_4_offset_ops(OP1, OP2, 8, NAME_AVX2_POW)
        }
        else if (size == 11)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 10)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 9)
        {
            // AVX512_8_mask4_ops(OP1, OP2, 1, AVX2_NAME)
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW);
            SCALAR_1_ops(OP1, OP2, 8, NAME_SCALAR_POW);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW)
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 4, NAME_SCALAR_POW);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 4)
        {
            AVX_4_offset_ops(OP1, OP2, 0, NAME_AVX2_POW)
        }
    }

    static inline void __VML_FN_ATTR_AVX512 
    vpow_sv_hook_avx512_16_group(const double input_value,
                              const double *input_array,
                              double *result_array,
                              unsigned int size, vml_hook_func_t pre_hook, 
                              void * pre_args, vml_hook_func_t post_hook, 
                              void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            unsigned int count = size >> 4;
            unsigned int rest = size & 15;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX512_8__2_ops(OP1, OP2, NAME_AVX512_POW);
                *array_index += 16;
            }
            if (rest)
                vpow_sv_hook_avx512_15(input_value, input_array, result_array, rest, 
                array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_POW)
        }
        else
        {
            vpow_sv_hook_avx512_15(input_value, input_array, result_array, size, 
            array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __VML_FN_ATTR_AVX512 vpow_sv_hook_avx512(const double input_value,
                                                        const double *input_array,
                                                        double *result_array,
                                                        unsigned int size, 
                                                        vml_hook_func_t pre_hook, 
                                                        void * pre_args, 
                                                        vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vpow_sv_hook_avx512_16_group(input_value, input_array, result_array, size, 
            pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_POW)
        }
        else
        {
            vpow_sv_hook_avx512_7(input_value, input_array, result_array, size, 
            array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vpow *****************/
    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_3(const double input_value, const double *input_array, double *result_array, int size,
                int *array_index,vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                void * post_args)
    {
        if (size == 1)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_7(const double input_value, const double *input_array, double *result_array, int size,
                int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                void * post_args)
    {
        if (size == 7)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 6)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 4;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 5)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 4, NAME_SCALAR_POW);
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_3(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_15(const double input_value, const double *input_array, double *result_array, int size,
                 int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                 void * post_args)
    {
        if (size == 15)
        {
            AVX_4__3_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 14)
        {
            AVX_4__3_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 12;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 13)
        {
            AVX_4__3_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 12, NAME_SCALAR_POW);
        }
        else if (size == 12)
        {
            AVX_4__3_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 11)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 10)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 8;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 9)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 8, NAME_SCALAR_POW);
        }
        else if (size == 8)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_7(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /*This function deal with size in 1~31*/
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_31(const double input_value, const double *input_array, double *result_array, int size,
                 int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                 void * post_args)
    {
        if (size == 31)
        {
            AVX_4__7_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 28;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 30)
        {
            AVX_4__7_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 28;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 29)
        {
            AVX_4__7_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 28, NAME_SCALAR_POW);
        }
        else if (size == 28)
        {
            AVX_4__7_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 27)
        {
            AVX_4__6_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 24;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 26)
        {
            AVX_4__6_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 24;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 25)
        {
            AVX_4__6_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 24, NAME_SCALAR_POW);
        }
        else if (size == 24)
        {
            AVX_4__6_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 23)
        {
            AVX_4__5_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 20;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 22)
        {
            AVX_4__5_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 20;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 21)
        {
            AVX_4__5_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 20, NAME_SCALAR_POW);
        }
        else if (size == 20)
        {
            AVX_4__5_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 19)
        {
            AVX_4__4_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 16;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 18)
        {
            AVX_4__4_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 16;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 17)
        {
            AVX_4__4_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 16, NAME_SCALAR_POW);
        }
        else if (size == 16)
        {
            AVX_4__4_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_15(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /*This function deal with size in 1~63*/
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_63(const double input_value, const double *input_array, double *result_array, int size,
                 int *array_index, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                 void * post_args)
    {
        if (size == 63)
        {
            AVX_4__15_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 60;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 62)
        {
            AVX_4__15_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 60;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 61)
        {
            AVX_4__15_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 60, NAME_SCALAR_POW);
        }
        else if (size == 60)
        {
            AVX_4__15_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 59)
        {
            AVX_4__14_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 56;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 58)
        {
            AVX_4__14_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 56;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 57)
        {
            AVX_4__14_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 56, NAME_SCALAR_POW);
        }
        else if (size == 56)
        {
            AVX_4__14_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 55)
        {
            AVX_4__13_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 52;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 54)
        {
            AVX_4__13_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 52;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 53)
        {
            AVX_4__13_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 52, NAME_SCALAR_POW);
        }
        else if (size == 52)
        {
            AVX_4__13_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 51)
        {
            AVX_4__12_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 48;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 50)
        {
            AVX_4__12_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 48;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 49)
        {
            AVX_4__12_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 48, NAME_SCALAR_POW);
        }
        else if (size == 48)
        {
            AVX_4__12_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 47)
        {
            AVX_4__11_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 44;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 46)
        {
            AVX_4__11_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 44;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 45)
        {
            AVX_4__11_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 44, NAME_SCALAR_POW);
        }
        else if (size == 44)
        {
            AVX_4__11_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 43)
        {
            AVX_4__10_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 40;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 42)
        {
            AVX_4__10_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 40;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 41)
        {
            AVX_4__10_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 40, NAME_SCALAR_POW);
        }
        else if (size == 40)
        {
            AVX_4__10_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 39)
        {
            AVX_4__9_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 36;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 38)
        {
            AVX_4__9_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 36;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 37)
        {
            AVX_4__9_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 36, NAME_SCALAR_POW);
        }
        else if (size == 36)
        {
            AVX_4__9_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else if (size == 35)
        {
            AVX_4__8_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 32;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
        else if (size == 34)
        {
            AVX_4__8_ops(OP1, OP2, NAME_AVX2_POW);
            *array_index += 32;
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
        }
        else if (size == 33)
        {
            AVX_4__8_ops(OP1, OP2, NAME_AVX2_POW);
            SCALAR_1_ops(OP1, OP2, 32, NAME_SCALAR_POW);
        }
        else if (size == 32)
        {
            AVX_4__8_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_31(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_sub4(const double input_value, const double *input_array, double *result_array,
                   unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                   void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW);
                *array_index += 4;
            }
            if (rest)
                vpow_sv_hook_avx2_3(input_value, input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_POW)
        }
        else
        {
            vpow_sv_hook_avx2_3(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_sub64(const double input_value, const double *input_array, double *result_array,
                    unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                    void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 64)
        {
            unsigned int count = size >> 6;
            unsigned int rest = size & 63;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_4__16_ops(OP1, OP2, NAME_AVX2_POW);
                *array_index += 64;
            }
            if (rest)
                vpow_sv_hook_avx2_63(input_value, input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 64)
        {
            AVX_4__16_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_63(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_sub32(const double input_value, const double *input_array, double *result_array,
                    unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                    void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 32)
        {
            vpow_sv_hook_avx2_sub64(input_value, input_array, result_array, size,
            pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 32)
        {
            AVX_4__8_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_31(input_value, input_array, result_array, size, 
            array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2_sub16(const double input_value, const double *input_array, double *result_array,
                    unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
                    void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 16)
        {
            vpow_sv_hook_avx2_sub32(input_value, input_array, result_array, size, 
            pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX_4__4_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_15(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __VML_FN_ATTR_AVX2
    vpow_sv_hook_avx2(const double input_value, const double *input_array, double *result_array,
              unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
              void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vpow_sv_hook_avx2_sub16(input_value, input_array, result_array, size, 
            pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            AVX_4__2_ops(OP1, OP2, NAME_AVX2_POW);
        }
        else
        {
            vpow_sv_hook_avx2_7(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vpow *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_AVX
    vpow_sv_hook_avx_3(const double input_value,
               const double *input_array,
               double *result_array,
               int size,
               int *array_index, 
               vml_hook_func_t pre_hook, 
               void * pre_args, 
               vml_hook_func_t post_hook, 
               void * post_args)
    {
        if (size == 1)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __VML_FN_ATTR_AVX
    vpow_sv_hook_avx(const double input_value, const double *input_array, double *result_array,
             unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
             void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_2__2_ops(OP1, OP2, NAME_SSE_POW);
                *array_index += 4;
            }
            if (rest)
                vpow_sv_hook_avx_3(input_value, input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_POW)
        }
        else
        {
            vpow_sv_hook_avx_3(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vpow *****************/
    /*This function deal with size in 1~3*/
    static inline void __VML_FN_ATTR_SSE2
    vpow_sv_hook_sse_3(const double input_value,
               const double *input_array,
               double *result_array,
               int size,
               int *array_index, 
               vml_hook_func_t pre_hook, 
               void * pre_args, 
               vml_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_POW);
        }
        else if (size == 2)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW)
        }
        else if (size == 3)
        {
            SSE_2__1_ops(OP1, OP2, NAME_SSE_POW);
            SCALAR_1_ops(OP1, OP2, 2, NAME_SCALAR_POW);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __VML_FN_ATTR_SSE2
    vpow_sv_hook_sse(const double input_value, const double *input_array, double *result_array,
             unsigned int size, vml_hook_func_t pre_hook, void * pre_args, vml_hook_func_t post_hook, 
             void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_2__2_ops(OP1, OP2, NAME_SSE_POW);
                *array_index += 4;
            }
            if (rest)
                vpow_sv_hook_sse_3(input_value, input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_POW)
        }
        else
        {
            vpow_sv_hook_sse_3(input_value, input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** vml_vpow *****************/
    static inline void vpow_sv_hook_scalar(const double input_value, const double *input_array, double *result_array,
                                   unsigned int size, vml_hook_func_t pre_hook, void * pre_args, 
                                   vml_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_POW);
            *array_index += 1;
        }
    }

#undef OP1
#undef OP2
#undef SCALAR_ARRAY
#undef VV
#ifdef __cplusplus
}
#endif

#endif /*VML_VPOW_SV_HOOK_H*/
