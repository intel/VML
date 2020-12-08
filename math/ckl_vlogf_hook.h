#ifndef CKL_VLOGF_HOOK_H
#define CKL_VLOGF_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vlogf_hook_func_t)(const float *, float *, unsigned int, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vlogf_hook_avx512(const float *input_array, float *result_array,
                                    unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vlogf_hook_avx2(const float *input_array, float *result_array,
                                  unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vlogf_hook_avx(const float *input_array, float *result_array,
                                 unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vlogf_hook_sse(const float *input_array, float *result_array,
                                 unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vlogf_hook_scalar(const float *input_array, float *result_array,
                                    unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vlogf_hook(const float *input_array, float *result_array,
                   unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args) __attribute__((ifunc("vlogf_hook_ifunc")));
#else
void ckl_vlogf_hook(const float *input_array, float *result_array,
               unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vlogf_hook_func_t, vlogf_hook, ckl_vlogf_hook)

    __m128 _ZGVbN4v_logf(__m128 x);
    __m256 _ZGVcN8v_logf(__m256 x);
    __m256 _ZGVdN8v_logf(__m256 x);
    __m512 _ZGVeN16v_logf(__m512 x);

#include "commonf/ops.h"

#define NAME_AVX512_LOGF eN16v_logf
#define NAME_AVX2_LOGF dN8v_logf
#define NAME_AVX_LOGF cN8v_logf
#define NAME_SSE_LOGF bN4v_logf
#define NAME_SCALAR_LOGF logf
#define ckl_logf logf
#define OP1 PRE_HOOK_OP(pre_hook, pre_args) 
#define OP2 POST_HOOK_OP(post_hook, post_args)

    /************** ckl_vlogf_hook *****************/
    /*This function deals with size in 1~3 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_hook_avx512_3(const float *input_array, float *result_array, int size,
                   int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
        }
        else if (size == 2)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
        }
        else if (size == 3)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 2, NAME_SCALAR_LOGF);
        }
    }

    /*This function deals with size in 1~7 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_hook_avx512_7(const float *input_array, float *result_array, int size,
                   int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 7)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 6)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 5)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else
        {
            vlogf_hook_avx512_3(input_array, result_array, size,
                           array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /*This function deals with size in 1~15 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_hook_avx512_15(const float *input_array, float *result_array, int size,
                    int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size <= 15 && size >= 12)
        {
            AVX512_16_mask16_ops(OP1, OP2, 0, NAME_AVX512_LOGF)
        }
        else if (size == 11)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 9, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 10, NAME_SCALAR_LOGF);
        }
        else if (size == 10)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 9, NAME_SCALAR_LOGF);
        }
        else if (size == 9)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_hook_avx512_7(input_array, result_array, size,
                           array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }
    /*This function deals with size in 1~31 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_hook_avx512_31(const float *input_array, float *result_array, int size,
                    int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size <= 31 && size >= 26)
        {
            AVX512_16_mask16_ops(OP1, OP2, 1, NAME_AVX512_LOGF)
        }
        else if (size == 25)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            AVX_8_offset_ops(OP1, OP2, 16, NAME_AVX2_LOGF);
            SCALARF_1_ops(OP1, OP2, 24, NAME_SCALAR_LOGF);
        }
        else if (size == 24)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            AVX_8_offset_ops(OP1, OP2, 16, NAME_AVX2_LOGF)
        }
        else if (size == 23)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 22)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 21)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 20)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            *array_index += 16;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else if (size == 19)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            SCALARF_1_ops(OP1, OP2, 16, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 17, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 18, NAME_SCALAR_LOGF);
        }
        else if (size == 18)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            SCALARF_1_ops(OP1, OP2, 16, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 17, NAME_SCALAR_LOGF);
        }
        else if (size == 17)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
            SCALARF_1_ops(OP1, OP2, 16, NAME_SCALAR_LOGF);
        }
        else if (size == 16)
        {
            AVX512_16__1_ops(OP1, OP2, NAME_AVX512_LOGF)
        }
        else
        {
            //AVX512_16_mask4_ops(OP1, OP2, 0, SSE_NAME)
            vlogf_hook_avx512_15(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512
    vlogf_hook_avx512(const float *input_array, float *result_array,
                 unsigned int size, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 31)
        {
            unsigned int count = size >> 5;
            unsigned int rest = size & 31;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX512_16__2_ops(OP1, OP2, NAME_AVX512_LOGF)
                *array_index += 32;
            }
            if (rest)
                vlogf_hook_avx512_31(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else
        {
            vlogf_hook_avx512_31(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vlogf_hook *****************/
    /*This function deals with size in 1~3 */
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_hook_avx2_3(const float *input_array, float *result_array, int size,
                 int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
        }
        else if (size == 2)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
        }
        else if (size == 3)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 2, NAME_SCALAR_LOGF);
        }
    }

    /*This function deals with size in 1~7 */
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_hook_avx2_7(const float *input_array, float *result_array, int size,
                 int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 7)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 6)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 5)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else
        {
            vlogf_hook_avx2_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_hook_avx2_15(const float *input_array, float *result_array, int size,
                  int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 15)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 14)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 13)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 14)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else if (size == 11)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 9, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 10, NAME_SCALAR_LOGF);
        }
        else if (size == 10)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 9, NAME_SCALAR_LOGF);
        }
        else if (size == 9)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_hook_avx2_7(input_array, result_array, size,
                         array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX2 */
    static inline void __CKL_FN_ATTR_AVX2
    vlogf_hook_avx2(const float *input_array, float *result_array,
               unsigned int size, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            unsigned int count = size >> 3;
            unsigned int rest = size & 7;
            for (unsigned int i = 0; i < count; i++)
            {
                AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
                *array_index += 8;
            }
            if (rest)
                vlogf_hook_avx2_7(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_hook_avx2_7(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vlogf_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vlogf_hook_avx_3(const float *input_array,
                float *result_array, int size,
                int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
        }
        else if (size == 2)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
        }
        else if (size == 3)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 2, NAME_SCALAR_LOGF);
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX
    vlogf_hook_avx_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 7)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 6)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 5)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else
        {
            vlogf_hook_avx_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
            //AVX_8_mask4_ops(OP1, OP2, 0, SSE_NAME)
        }
    }

    /*This function deal with size in 1~15*/
    static inline void __CKL_FN_ATTR_AVX
    vlogf_hook_avx_15(const float *input_array, float *result_array, int size,
                 int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 15)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 14)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 13)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 14)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            *array_index += 8;
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else if (size == 11)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 9, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 10, NAME_SCALAR_LOGF);
        }
        else if (size == 10)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 9, NAME_SCALAR_LOGF);
        }
        else if (size == 9)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
            SCALARF_1_ops(OP1, OP2, 8, NAME_SCALAR_LOGF);
        }
        else if (size == 8)
        {
            AVX_8__1_ops(OP1, OP2, NAME_AVX2_LOGF)
        }
        else
        {
            vlogf_hook_avx_7(input_array, result_array, size,
                        array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX */
    static inline void __CKL_FN_ATTR_AVX
    vlogf_hook_avx(const float *input_array, float *result_array,
              unsigned int size, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 4)
        {
            unsigned int count = size >> 2;
            unsigned int rest = size & 3;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
                *array_index += 4;
            }
            if (rest)
                vlogf_hook_avx_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else
        {
            vlogf_hook_avx_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vlogf_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vlogf_hook_sse_3(const float *input_array,
                float *result_array, int size,
                int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 1)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
        }
        else if (size == 2)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
        }
        else if (size == 3)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 1, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 2, NAME_SCALAR_LOGF);
        }
    }

    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_SSE2
    vlogf_hook_sse_7(const float *input_array,
                float *result_array,
                int size,
                int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        if (size == 7)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 6, NAME_SCALAR_LOGF);
        }
        else if (size == 6)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
            SCALARF_1_ops(OP1, OP2, 5, NAME_SCALAR_LOGF);
        }
        else if (size == 5)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
            SCALARF_1_ops(OP1, OP2, 4, NAME_SCALAR_LOGF);
        }
        else if (size == 4)
        {
            SSE_4__1_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else
        {
            vlogf_hook_sse_3(input_array, result_array, size,
                        array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to SSE */
    static inline void __CKL_FN_ATTR_SSE2
    vlogf_hook_sse(const float *input_array, float *result_array,
              unsigned int size, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            unsigned int count = size >> 3;
            unsigned int rest = size & 7;
            for (unsigned int i = 0; i < count; i++)
            {
                SSE_4__2_ops(OP1, OP2, NAME_SSE_LOGF)
                *array_index += 8;
            }
            if (rest)
                vlogf_hook_sse_7(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            SSE_4__2_ops(OP1, OP2, NAME_SSE_LOGF)
        }
        else
        {
            vlogf_hook_sse_7(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vlogf_hook *****************/
    static inline void vlogf_hook_scalar(const float *input_array, float *result_array,
                                    unsigned int size, ckl_hook_func_t pre_hook, 
				   void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALARF_1_ops(OP1, OP2, 0, NAME_SCALAR_LOGF);
            *array_index += 1;
        }
    }

#undef OP1
#undef OP2
#ifdef __cplusplus
}
#endif

#endif /*CKL_VLOGF_HOOK_H*/
