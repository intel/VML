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
#define PRE_HOOK_OP(pre_hook, pre_args)                \
if(pre_hook)                                           \
        pre_hook(pre_args); 

#define POST_HOOK_OP(post_hook, post_args)             \
if(post_hook)                                          \
        post_hook(post_args);

#undef AVX512_8_TMP
#define AVX512_8(i, name) AVX512_8_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_8_TMP(i, name)                                           \
        _mm512_storeu_pd(                                                   \
            &result_array[*array_index + i * 8],                            \
            _ZGV##name(_mm512_set1_pd(input_value),                         \
                    _mm512_loadu_pd(&input_array[*array_index + i * 8])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_8_TMP(i, name)                                           \
        _mm512_storeu_pd(                                                   \
            &result_array[*array_index + i * 8],                            \
            _ZGV##name(_mm512_loadu_pd(&input_array[*array_index + i * 8]), \
                    _mm512_set1_pd(input_value)));
    #else
    #define AVX512_8_TMP(i, name)                                           \
        _mm512_storeu_pd(                                                   \
            &result_array[*array_index + i * 8],                            \
            _ZGV##name(_mm512_loadu_pd(&input_array[*array_index + i * 8]), \
                    _mm512_loadu_pd(&input_array1[*array_index + i * 8])));
    #endif
#elif defined(SINCOS)
    #define AVX512_8_TMP(i, name)                                                  \
    __m512d input8_value##i = _mm512_loadu_pd(&input_array[*array_index + i * 8]); \
        _mm512_storeu_pd(&result_array[*array_index + i * 8],                      \
                        _ZGVeN8v_sin(input8_value##i));                            \
        _mm512_storeu_pd(&result_array1[*array_index + i * 8],                     \
                        _ZGVeN8v_cos(input8_value##i));
#else
    #define AVX512_8_TMP(i, name)                                                  \
    _mm512_storeu_pd(                                                              \
        &result_array[*array_index + i * 8],                                       \
        _ZGV##name(_mm512_loadu_pd(&input_array[*array_index + i * 8])));
#endif

#define AVX512_8_ops(OP1, OP2, i, name)                              \
OP1                                                                  \
AVX512_8(i, name)                                                    \
OP2

#define AVX512_8__0_ops(OP1, OP2, name)
/*Call 1 AVX512 function for 8 doubles*/
#define AVX512_8__1_ops(OP1, OP2, name) AVX512_8_ops(OP1, OP2, 0, name)
/*Call 2 AVX512 function for 8 doubles*/
#define AVX512_8__2_ops(OP1, OP2, name) \
    AVX512_8__1_ops(OP1, OP2, name)     \
        AVX512_8_ops(OP1, OP2, 1, name)
/*Call 3 AVX512 function for 8 doubles*/
#define AVX512_8__3_ops(OP1, OP2, name) \
    AVX512_8__2_ops(OP1, OP2, name)     \
        AVX512_8_ops(OP1, OP2, 2, name)
/*Call 4 AVX512 function for 8 doubles*/
#define AVX512_8__4_ops(OP1, OP2, name) \
    AVX512_8__3_ops(OP1, OP2, name)     \
        AVX512_8_ops(OP1, OP2, 3, name)

/*For size = 8*i + (8-i)*/
#undef AVX512_8_mask8_TMP
#define AVX512_8_mask8(i, name) AVX512_8_mask8_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_8_mask8_TMP(i, name)                                           \
    unsigned char tail_mask_uint =                                                \
            (((unsigned char)0xff) >> (8 - size + 8 * i));                        \
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                      \
        if(vml_pre_hook)                                                          \
            vml_pre_hook(vml_pre_hook_args);                                      \
        AVX512_8__##i(name) _mm512_mask_storeu_pd(                                \
            &result_array[*array_index + 8 * i], tail_mask,                       \
            _ZGV##name(_mm512_set1_pd(input_value),                               \
                    _mm512_maskz_loadu_pd(tail_mask,                              \
                                        &input_array[*array_index + 8 * i])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_8_mask8_TMP(i, name)                                           \
        unsigned char tail_mask_uint =                                            \
            (((unsigned char)0xff) >> (8 - size + 8 * i));                        \
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                      \
        if(vml_pre_hook)                                                          \
            vml_pre_hook(vml_pre_hook_args);                                      \
        AVX512_8__##i(name) _mm512_mask_storeu_pd(                                \
            &result_array[*array_index + 8 * i], tail_mask,                       \
            _ZGV##name(_mm512_maskz_loadu_pd(tail_mask,                           \
                                        &input_array[*array_index + 8 * i]),      \
                    _mm512_set1_pd(input_value))); 
    #else
    #define AVX512_8_mask8_TMP(i, name)                                           \
        unsigned char tail_mask_uint =                                            \
            (((unsigned char)0xff) >> (8 - size + 8 * i));                        \
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                      \
        _mm512_mask_storeu_pd(                                                    \
            &result_array[*array_index + 8 * i], tail_mask,                       \
            _ZGV##name(_mm512_maskz_loadu_pd(tail_mask,                           \
                                        &input_array[*array_index + 8 * i]),      \
                    _mm512_maskz_loadu_pd(tail_mask,                              \
                                        &input_array1[*array_index + 8 * i])));
    #endif
#elif defined(SINCOS)
    #define AVX512_8_mask8_TMP(i, name)                                                   \
    unsigned char tail_mask_uint =                                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                  \
    __m512d input8_mask_v##i = _mm512_maskz_loadu_pd(tail_mask,                           \
                                                     &input_array[*array_index + 8 * i]); \
    _mm512_mask_storeu_pd(                                                                \
        &result_array[*array_index + 8 * i], tail_mask,                                   \
        _ZGVeN8v_sin(input8_mask_v##i));                                                  \
    _mm512_mask_storeu_pd(                                                                \
        &result_array1[*array_index + 8 * i], tail_mask,                                  \
        _ZGVeN8v_cos(input8_mask_v##i));
#else
    #define AVX512_8_mask8_TMP(i, name)                                                   \
    unsigned char tail_mask_uint =                                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                  \
    _mm512_mask_storeu_pd(                                                                \
        &result_array[*array_index + 8 * i], tail_mask,                                   \
        _ZGV##name(_mm512_maskz_loadu_pd(tail_mask,                                       \
                   &input_array[*array_index + 8 * i])));
#endif
                        
#define AVX512_8_mask8_ops(OP1, OP2, i, name)                               \
    AVX512_8__##i##_ops(OP1, OP2, name)                                     \
    OP1                                                                     \
    AVX512_8_mask8(i, name)                                                 \
    OP2

/*For size = 8*i + (4-i)*/
#undef AVX512_8_mask4_TMP
#define AVX512_8_mask4(i, name1, name2) AVX512_8_mask4_TMP(i, name1, name2)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_8_mask4_TMP(i, name1, name2)                                    \
        unsigned char tail_mask_uint =                                             \
            (((unsigned char)0xff) >> (8 - size + 8 * i));                         \
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                       \
        _mm256_mask_storeu_pd(                                                     \
            &result_array[*array_index + 8 * i], tail_mask,                        \
            _ZGV##name2(_mm256_set1_pd(input_value),                               \
                        _mm256_maskz_loadu_pd(tail_mask,                           \
                                            &input_array[*array_index + 8 * i])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_8_mask4_TMP(i, name1, name2)                                    \
        unsigned char tail_mask_uint =                                             \
            (((unsigned char)0xff) >> (8 - size + 8 * i));                         \
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                       \
        _mm256_mask_storeu_pd(                                                     \
            &result_array[*array_index + 8 * i], tail_mask,                        \
            _ZGV##name2(_mm256_maskz_loadu_pd(tail_mask,                           \
                                            &input_array[*array_index + 8 * i]),   \
                        _mm256_set1_pd(input_value)));
    #else
    #define AVX512_8_mask4_TMP(i, name1, name2)                                    \
        unsigned char tail_mask_uint =                                             \
            (((unsigned char)0xff) >> (8 - size + 8 * i));                         \
        __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                       \
        _mm256_mask_storeu_pd(                                                     \
            &result_array[*array_index + 8 * i], tail_mask,                        \
            _ZGV##name2(_mm256_maskz_loadu_pd(tail_mask,                           \
                                            &input_array[*array_index + 8 * i]),   \
                        _mm256_maskz_loadu_pd(tail_mask,                           \
                                            &input_array1[*array_index + 8 * i])));
    #endif
#elif defined(SINCOS)
    #define AVX512_8_mask4_TMP(i, name1, name2)                                           \
    unsigned char tail_mask_uint =                                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                  \
    __m256d input4_mask_v##i = _mm256_maskz_loadu_pd(tail_mask,                           \
                                                     &input_array[*array_index + 8 * i]); \
    _mm256_mask_storeu_pd(                                                                \
        &result_array[*array_index + 8 * i], tail_mask,                                   \
        _ZGVdN4v_sin(input4_mask_v##i));                                                  \
    _mm256_mask_storeu_pd(                                                                \
        &result_array1[*array_index + 8 * i], tail_mask,                                  \
        _ZGVdN4v_cos(input4_mask_v##i));

#else
    #define AVX512_8_mask4_TMP(i, name1, name2)          \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 8 * i));   \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    _mm256_mask_storeu_pd(                               \
        &result_array[*array_index + 8 * i], tail_mask,  \
        _ZGV##name2(_mm256_maskz_loadu_pd(tail_mask,     \
                    &input_array[*array_index + 8 * i])));
#endif

#define AVX512_8_mask4_ops(OP1, OP2, i, name1, name2)                        \
    AVX512_8__##i##_ops(OP1, OP2, name1)                                     \
    OP1                                                                      \
    AVX512_8_mask4(i, name1, name2)                                          \
    OP2

#undef AVX_4_TMP
#define AVX_4(i, name) AVX_4_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_4_TMP(i, name)                                          \
    _mm256_storeu_pd(                                                   \
        &result_array[*array_index + i * 4],                            \
        _ZGV##name(_mm256_set1_pd(input_value),                         \
                    _mm256_loadu_pd(&input_array[*array_index + i * 4])));
    #elif defined(ARRAY_SCALAR)
    #define AVX_4_TMP(i, name)                                          \
    _mm256_storeu_pd(                                                   \
        &result_array[*array_index + i * 4],                            \
        _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + i * 4]), \
                    _mm256_set1_pd(input_value)));
    #else
    #define AVX_4_TMP(i, name)                                          \
    _mm256_storeu_pd(                                                   \
        &result_array[*array_index + i * 4],                            \
        _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + i * 4]), \
                    _mm256_loadu_pd(&input_array1[*array_index + i * 4])));
    #endif
#elif defined(SINCOS)
    #define AVX_4_TMP(i, name)                                                      \
    __m256d input4_value_##i = _mm256_loadu_pd(&input_array[*array_index + i * 4]); \
  _mm256_storeu_pd(                                                                 \
      &result_array[*array_index + i * 4],                                          \
      _ZGVdN4v_sin(input4_value_##i));                                              \
  _mm256_storeu_pd(                                                                 \
      &result_array1[*array_index + i * 4],                                         \
      _ZGVdN4v_cos(input4_value_##i));
#else
    #define AVX_4_TMP(i, name)                                          \
    _mm256_storeu_pd(                                                   \
      &result_array[*array_index + i * 4],                              \
      _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + i * 4])));
#endif

#define AVX_4_ops(OP1, OP2, i, name)                               \
OP1                                                                \
AVX_4(i, name)                                                     \
OP2

#define AVX_4__0_ops(OP1, OP2, name)
/*Call 1 AVX function for 4 doubles*/
#define AVX_4__1_ops(OP1, OP2, name) AVX_4_ops(OP1, OP2, 0, name)
/*Call 2 AVX function for 4 doubles*/
#define AVX_4__2_ops(OP1, OP2, name) \
  AVX_4__1_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 1, name)
/*Call 3 AVX function for 4 doubles*/
#define AVX_4__3_ops(OP1, OP2, name) \
  AVX_4__2_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 2, name)
/*Call 4 AVX function for 4 doubles*/
#define AVX_4__4_ops(OP1, OP2, name) \
  AVX_4__3_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 3, name)
/*Call 5 AVX function for 4 doubles*/
#define AVX_4__5_ops(OP1, OP2, name) \
  AVX_4__4_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 4, name)
/*Call 6 AVX function for 4 doubles*/
#define AVX_4__6_ops(OP1, OP2, name) \
  AVX_4__5_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 5, name)
/*Call 7 AVX function for 4 doubles*/
#define AVX_4__7_ops(OP1, OP2, name) \
  AVX_4__6_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 6, name)
/*Call 8 AVX function for 4 doubles*/
#define AVX_4__8_ops(OP1, OP2, name) \
  AVX_4__7_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 7, name)
/*Call 9 AVX function for 4 doubles*/
#define AVX_4__9_ops(OP1, OP2, name) \
  AVX_4__8_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 8, name)
/*Call 10 AVX function for 4 doubles*/
#define AVX_4__10_ops(OP1, OP2, name) \
  AVX_4__9_ops(OP1, OP2, name)        \
      AVX_4_ops(OP1, OP2, 9, name)
/*Call 11 AVX function for 4 doubles*/
#define AVX_4__11_ops(OP1, OP2, name) \
  AVX_4__10_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 10, name)
/*Call 12 AVX function for 4 doubles*/
#define AVX_4__12_ops(OP1, OP2, name) \
  AVX_4__11_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 11, name)
/*Call 13 AVX function for 4 doubles*/
#define AVX_4__13_ops(OP1, OP2, name) \
  AVX_4__12_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 12, name)
/*Call 14 AVX function for 4 doubles*/
#define AVX_4__14_ops(OP1, OP2, name) \
  AVX_4__13_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 13, name)
/*Call 15 AVX function for 4 doubles*/
#define AVX_4__15_ops(OP1, OP2, name) \
  AVX_4__14_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 14, name)
/*Call 16 AVX function for 4 doubles*/
#define AVX_4__16_ops(OP1, OP2, name) \
  AVX_4__15_ops(OP1, OP2, name)       \
      AVX_4_ops(OP1, OP2, 15, name)

#define AVX_MASK_1                                       \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000, \
                    0x0000000000000000, 0xffffffffffffffff)
#define AVX_MASK_2                                       \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000, \
                    0xffffffffffffffff, 0xffffffffffffffff)
#define AVX_MASK_3                                       \
  _mm256_set_epi64x(0x0000000000000000, 0xffffffffffffffff, \
                    0xffffffffffffffff, 0xffffffffffffffff)

/*For size = 4*i + (4-i)*/
#undef AVX_4_mask4_TMP
#define AVX_4_mask4(i, name) AVX_4_mask4_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_4_mask4_TMP(i, name)                                           \
    if ((size - 4 * i) == 1)                                                   \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_1,                   \
            _ZGV##name(_mm256_set1_pd(input_value),                            \
                    _mm256_maskload_pd(&input_array[*array_index + 4 * i],     \
                                        AVX_MASK_1)));                         \
    }                                                                          \
    else if ((size - 4 * i) == 2)                                              \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_2,                   \
            _ZGV##name(_mm256_set1_pd(input_value),                            \
                    _mm256_maskload_pd(&input_array[*array_index + 4 * i],     \
                                        AVX_MASK_2)));                         \
    }                                                                          \
    else if ((size - 4 * i) == 3)                                              \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_3,                   \
            _ZGV##name(_mm256_set1_pd(input_value),                            \
                    _mm256_maskload_pd(&input_array[*array_index + 4 * i],     \
                                        AVX_MASK_3)));                         \
    }  
    #elif defined(ARRAY_SCALAR)
    #define AVX_4_mask4_TMP(i, name)                                           \
    if ((size - 4 * i) == 1)                                                   \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_1,                   \
            _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                        AVX_MASK_1),                           \
                    _mm256_set1_pd(input_value)));                             \
    }                                                                          \
    else if ((size - 4 * i) == 2)                                              \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_2,                   \
            _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                        AVX_MASK_2),                           \
                    _mm256_set1_pd(input_value)));                             \
    }                                                                          \
    else if ((size - 4 * i) == 3)                                              \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_3,                   \
            _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                        AVX_MASK_3),                           \
                    _mm256_set1_pd(input_value)));                             \
    }
    #else
    #define AVX_4_mask4(i, name) AVX_4_mask4_TMP(i, name)
    #define AVX_4_mask4_TMP(i, name)                                           \
    if ((size - 4 * i) == 1)                                                   \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_1,                   \
            _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                        AVX_MASK_1),                           \
                    _mm256_maskload_pd(&input_array1[*array_index + 4 * i],    \
                                        AVX_MASK_1)));                         \
    }                                                                          \
    else if ((size - 4 * i) == 2)                                              \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_2,                   \
            _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                        AVX_MASK_2),                           \
                    _mm256_maskload_pd(&input_array1[*array_index + 4 * i],    \
                                        AVX_MASK_2)));                         \
    }                                                                          \
    else if ((size - 4 * i) == 3)                                              \
    {                                                                          \
        _mm256_maskstore_pd(                                                   \
            &result_array[*array_index + 4 * i], AVX_MASK_3,                   \
            _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                        AVX_MASK_3),                           \
                    _mm256_maskload_pd(&input_array1[*array_index + 4 * i],    \
                                        AVX_MASK_3)));                         \
    }
    #endif
#elif defined(SINCOS)
    #define AVX_4_mask4_TMP(i, name)                                           \
    if ((size - 4 * i) == 1)                                                                 \
  {                                                                                        \
    __m256d input4_value_mask_##i = _mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                                       AVX_MASK_1);                 \
    _mm256_maskstore_pd(                                                                   \
        &result_array[*array_index + 4 * i], AVX_MASK_1,                            \
        _ZGVdN4v_sin(input4_value_mask_##i));                                              \
    _mm256_maskstore_pd(                                                                   \
        &result_array1[*array_index + 4 * i], AVX_MASK_1,                           \
        _ZGVdN4v_cos(input4_value_mask_##i));                                              \
  }                                                                                        \
  else if ((size - 4 * i) == 2)                                                            \
  {                                                                                        \
    __m256d input4_value_mask_##i = _mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                                       AVX_MASK_2);                 \
    _mm256_maskstore_pd(                                                                   \
        &result_array[*array_index + 4 * i], AVX_MASK_2,                            \
        _ZGVdN4v_sin(input4_value_mask_##i));                                              \
    _mm256_maskstore_pd(                                                                   \
        &result_array1[*array_index + 4 * i], AVX_MASK_2,                           \
        _ZGVdN4v_cos(input4_value_mask_##i));                                              \
  }                                                                                        \
  else if ((size - 4 * i) == 3)                                                            \
  {                                                                                        \
    __m256d input4_value_mask_##i = _mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                                       AVX_MASK_3);                 \
    _mm256_maskstore_pd(                                                                   \
        &result_array[*array_index + 4 * i], AVX_MASK_3,                            \
        _ZGVdN4v_sin(input4_value_mask_##i));                                              \
    _mm256_maskstore_pd(                                                                   \
        &result_array1[*array_index + 4 * i], AVX_MASK_3,                           \
        _ZGVdN4v_cos(input4_value_mask_##i));                                              \
  }
#else
    #define AVX_4_mask4_TMP(i, name)                                      \
    if ((size - 4 * i) == 1)                                              \
  {                                                                       \
    _mm256_maskstore_pd(                                                  \
        &result_array[*array_index + 4 * i], AVX_MASK_1,                  \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                      AVX_MASK_1)));                      \
  }                                                                       \
  else if ((size - 4 * i) == 2)                                           \
  {                                                                       \
    _mm256_maskstore_pd(                                                  \
        &result_array[*array_index + 4 * i], AVX_MASK_2,                  \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                      AVX_MASK_2)));                      \
  }                                                                       \
  else if ((size - 4 * i) == 3)                                           \
  {                                                                       \
    _mm256_maskstore_pd(                                                  \
        &result_array[*array_index + 4 * i], AVX_MASK_3,                  \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                      AVX_MASK_3)));                      \
  }
#endif

#define AVX_4_mask4_ops(OP1, OP2, i, name)                                 \
AVX_4__##i##_ops(OP1, OP2, name)                                           \
OP1                                                                        \
AVX_4_mask4(i, name)                                                       \
OP2

/*For size = 4*i + (2-i)*/
#undef AVX_4_mask2_TMP
#define AVX_4_mask2(i, name1, name2) AVX_4_mask2_TMP(i, name1, name2)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_4_mask2_TMP(i, name1, name2)                             \
    _mm_store_sd(                                                        \
        &result_array[*array_index + 4 * i],                             \
        _ZGV##name2(_mm_set1_pd(input_value),                            \
                    _mm_load_sd(&input_array[*array_index + 2 * i])));
    #elif defined(ARRAY_SCALAR)
    #define AVX_4_mask2_TMP(i, name1, name2)                             \
    _mm_store_sd(                                                        \
        &result_array[*array_index + 4 * i],                             \
        _ZGV##name2(_mm_load_sd(&input_array[*array_index + 2 * i]),     \
                    _mm_set1_pd(input_value)));
    #else
    #define AVX_4_mask2_TMP(i, name1, name2)                             \
    _mm_store_sd(                                                        \
        &result_array[*array_index + 4 * i],                             \
        _ZGV##name2(_mm_load_sd(&input_array[*array_index + 2 * i]),     \
                    _mm_load_sd(&input_array1[*array_index + 2 * i])));
    #endif
#elif defined(SINCOS)
    #define AVX_4_mask2_TMP(i, name1, name2)                                   \
    __m128d input2_value##i = _mm_load_sd(&input_array[*array_index + 2 * i]); \
  _mm_store_sd(                                                                \
      &result_array[*array_index + 4 * i],                                     \
      _ZGVbN2v_sin(input2_value##i));                                          \
  _mm_store_sd(                                                                \
      &result_array1[*array_index + 4 * i],                                    \
      _ZGVbN2v_cos(input2_value##i));
#else
    #define AVX_4_mask2_TMP(i, name1, name2)                              \
    _mm_store_sd(                                                         \
      &result_array[*array_index + 4 * i],                                \
      _ZGV##name2(_mm_load_sd(&input_array[*array_index + 2 * i])));
#endif

#define AVX_4_mask2_ops(OP1, OP2, i, name1, name2)                  \
AVX_4__##i##_ops(OP1, OP2, name1)                                    \
OP1                                                                 \
AVX_4_mask2(i, name1, name2)                                        \
OP2

/*Call 1 AVX2 or AVX function for 4 doubles*/
#undef AVX_4_offset_TMP
#define AVX_4_offset(n, name) AVX_4_offset_TMP(n, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_4_offset_TMP(n, name)                                     \
    _mm256_storeu_pd(                                                    \
        &result_array[*array_index + n],                                 \
        _ZGV##name(_mm256_set1_pd(input_value),                          \
                    _mm256_loadu_pd(&input_array[*array_index + n])));
    #elif defined(ARRAY_SCALAR)
    #define AVX_4_offset_TMP(n, name)                                    \
    _mm256_storeu_pd(                                                    \
        &result_array[*array_index + n],                                 \
        _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + n]),      \
                    _mm256_set1_pd(input_value)));
    #else
    #define AVX_4_offset_TMP(n, name)                                    \
    _mm256_storeu_pd(                                                    \
        &result_array[*array_index + n],                                 \
        _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + n]),      \
                    _mm256_loadu_pd(&input_array1[*array_index + n])));
    #endif
#elif defined(SINCOS)
    #define AVX_4_offset_TMP(n, name)                                           \
    __m256d input4_value_##n = _mm256_loadu_pd(&input_array[*array_index + n]); \
  _mm256_storeu_pd(                                                             \
      &result_array[*array_index + n],                                          \
      _ZGVdN4v_sin(input4_value_##n));                                          \
  _mm256_storeu_pd(                                                             \
      &result_array1[*array_index + n],                                         \
      _ZGVdN4v_cos(input4_value_##n));
#else
    #define AVX_4_offset_TMP(n, name)                                       \
    _mm256_storeu_pd(                                                       \
      &result_array[*array_index + n],                                      \
      _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + n])));
#endif

#define AVX_4_offset_ops(OP1, OP2, n, name)                          \
OP1                                                                  \
AVX_4_offset(n, name)                                                \
OP2

#undef SSE_2_TMP
#define SSE_2(i, name) SSE_2_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SSE_2_TMP(i, name)                                                    \
    _mm_storeu_pd(&result_array[*array_index + i * 2],                            \
                    _ZGV##name(_mm_set1_pd(input_value),                          \
                            _mm_loadu_pd(&input_array[*array_index + i * 2])));
    #elif defined(ARRAY_SCALAR)
    #define SSE_2_TMP(i, name)                                                   \
    _mm_storeu_pd(&result_array[*array_index + i * 2],                           \
                    _ZGV##name(_mm_loadu_pd(&input_array[*array_index + i * 2]), \
                            _mm_set1_pd(input_value)));
    #else
    #define SSE_2_TMP(i, name)                                                   \
    _mm_storeu_pd(&result_array[*array_index + i * 2],                           \
                    _ZGV##name(_mm_loadu_pd(&input_array[*array_index + i * 2]), \
                            _mm_loadu_pd(&input_array1[*array_index + i * 2])));
    #endif
#elif defined(SINCOS)
    #define SSE_2_TMP(i, name)                                                   \
    __m128d input2_value##i = _mm_loadu_pd(&input_array[*array_index + i * 2]);  \
  _mm_storeu_pd(&result_array[*array_index + i * 2],                             \
                _ZGVbN2v_sin(input2_value##i));                                  \
  _mm_storeu_pd(&result_array1[*array_index + i * 2],                            \
                _ZGVbN2v_cos(input2_value##i));
#else
    #define SSE_2_TMP(i, name)                                                   \
    _mm_storeu_pd(&result_array[*array_index + i * 2],                           \
                _ZGV##name(_mm_loadu_pd(&input_array[*array_index + i * 2])));
#endif

#define SSE_2_ops(OP1, OP2, i, name)                                      \
OP1                                                                       \
SSE_2(i, name)                                                            \
OP2

#define SSE_2__0_ops(OP1, OP2, name)
/*Call 1 SSE function for 2 doubles*/
#define SSE_2__1_ops(OP1, OP2, name) SSE_2_ops(OP1, OP2, 0, name)
/*Call 2 SSE function for 2 doubles*/
#define SSE_2__2_ops(OP1, OP2, name) \
  SSE_2__1_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 1, name)
/*Call 3 SSE function for 2 doubles*/
#define SSE_2__3_ops(OP1, OP2, name) \
  SSE_2__2_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 2, name)
/*Call 4 SSE function for 2 doubles*/
#define SSE_2__4_ops(OP1, OP2, name) \
  SSE_2__3_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 3, name)
/*Call 5 SSE function for 2 doubles*/
#define SSE_2__5_ops(OP1, OP2, name) \
  SSE_2__4_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 4, name)
/*Call 6 SSE function for 2 doubles*/
#define SSE_2__6_ops(OP1, OP2, name) \
  SSE_2__5_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 5, name)
/*Call 7 SSE function for 2 doubles*/
#define SSE_2__7_ops(OP1, OP2, name) \
  SSE_2__6_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 6, name)
/*Call 8 SSE function for 2 doubles*/
#define SSE_2__8_ops(OP1, OP2, name) \
  SSE_2__7_ops(OP1, OP2, name)       \
      SSE_2_ops(OP1, OP2, 7, name)

/*For size = 2*i + (2-i)*/
#undef SSE_2_mask2_TMP
#define SSE_2_mask2(i, name) SSE_2_mask2_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SSE_2_mask2_TMP(i, name)                                   \
    _mm_store_sd(                                                      \
        &result_array[*array_index + 2 * i],                           \
        _ZGV##name(_mm_set1_pd(input_value),                           \
                    _mm_load_sd(&input_array[*array_index + 2 * i])));
    #elif defined(ARRAY_SCALAR)
    #define SSE_2_mask2_TMP(i, name)                                   \
    _mm_store_sd(                                                      \
        &result_array[*array_index + 2 * i],                           \
        _ZGV##name(_mm_load_sd(&input_array[*array_index + 2 * i]),    \
                    _mm_set1_pd(input_value)));
    #else
    #define SSE_2_mask2_TMP(i, name)                                   \
    _mm_store_sd(                                                      \
        &result_array[*array_index + 2 * i],                           \
        _ZGV##name(_mm_load_sd(&input_array[*array_index + 2 * i]),    \
                    _mm_load_sd(&input_array1[*array_index + 2 * i])));
    #endif
#elif defined(SINCOS)
    #define SSE_2_mask2_TMP(i, name)                                                \
    __m128d input2_mask_value##i = _mm_load_sd(&input_array[*array_index + 2 * i]); \
  _mm_store_sd(                                                                     \
      &result_array[*array_index + 2 * i],                                          \
      _ZGVbN2v_sin(input2_mask_value##i));                                          \
  _mm_store_sd(                                                                     \
      &result_array1[*array_index + 2 * i],                                         \
      _ZGVbN2v_cos(input2_mask_value##i));
#else
    #define SSE_2_mask2_TMP(i, name)                                   \
    _mm_store_sd(                                                      \
      &result_array[*array_index + 2 * i],                             \
      _ZGV##name(_mm_load_sd(&input_array[*array_index + 2 * i])));
#endif

#define SSE_2_mask2_ops(OP1, OP2, i, name)                        \
SSE_2__##i##_ops(OP1, OP2, name)                                  \
OP1                                                               \
SSE_2_mask2(i, name)                                              \
OP2

#define SSE_2_mask2_offset_ops(OP1, OP2, i, name)                 \
OP1                                                               \
SSE_2_mask2(i, name)                                              \
OP2

#undef SCALAR_1_TMP
#define SCALAR_1(i, name) SCALAR_1_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SCALAR_1_TMP(i, name)                                           \
    result_array[*array_index+i] = vml_##name(input_value,                  \
                                            input_array[*array_index+i]);
    #elif defined(ARRAY_SCALAR)
    #define SCALAR_1_TMP(i, name)                                           \
    result_array[*array_index+i] = vml_##name(input_array[*array_index+i],  \
                                            input_value);
    #else
    #define SCALAR_1_TMP(i, name)                                            \
    result_array[*array_index+i] = vml_##name(input_array[*array_index+i],   \
                                                input_array1[*array_index+i]);
    #endif
#elif defined(SINCOS)
    #define SCALAR_1_TMP(i, name)                                           \
    sincos(input_array[*array_index+i], &result_array[*array_index+i],      \
                                            &result_array1[*array_index+i]);
#else
    #define SCALAR_1_TMP(i, name)                                           \
    result_array[*array_index+i] = vml_##name(input_array[*array_index+i]);
#endif

#define SCALAR_1_ops(OP1, OP2, i, name)                            \
OP1                                                                \
SCALAR_1(i, name)                                                  \
OP2
