#ifndef CKL_VEXP_HOOK_H
#define CKL_VEXP_HOOK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ckl_common.h"
    typedef void (*ckl_vexp_hook_func_t)(const double *, double *, unsigned int, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vexp_hook_avx512(const double *input_array, double *result_array,
                                   unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vexp_hook_avx2(const double *input_array, double *result_array,
                                 unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vexp_hook_avx(const double *input_array, double *result_array,
                                unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vexp_hook_sse(const double *input_array, double *result_array,
                                unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
    static inline void vexp_hook_scalar(const double *input_array, double *result_array,
                                   unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
#if GCC_IFUN_UNAVAILABLE == 0
    void ckl_vexp_hook(const double *input_array, double *result_array,
                  unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args) __attribute__((ifunc("vexp_hook_ifunc")));
#else
void ckl_vexp_hook(const double *input_array, double *result_array,
              unsigned int size, ckl_hook_func_t pre_hook, 
                                   void * pre_args, ckl_hook_func_t post_hook, void * post_args);
#endif

#include "ckl_ifunc.h"
    RESOLVE_FUNC(ckl_vexp_hook_func_t, vexp_hook, ckl_vexp_hook)

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
#define ckl_exp exp
#define OP1 PRE_HOOK_OP(pre_hook, pre_args) 
#define OP2 POST_HOOK_OP(post_hook, post_args)

    /************** ckl_vexp_hook *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX512
    vexp_hook_avx512_7(const double *input_array,
                  double *result_array,
                  int size,
                  int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
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
    static inline void __CKL_FN_ATTR_AVX512
    vexp_hook_avx512_15(const double *input_array, double *result_array, int size,
                   int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
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

    static inline void __CKL_FN_ATTR_AVX512 vexp_hook_avx512_16_group(const double *input_array, double *result_array,
                                                                 unsigned int size, ckl_hook_func_t pre_hook, 
				   void * pre_args, ckl_hook_func_t post_hook, void * post_args)
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
                vexp_hook_avx512_15(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 16)
        {
            AVX512_8__2_ops(OP1, OP2, NAME_AVX512_EXP)
        }
        else
        {
            vexp_hook_avx512_15(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /* kernel with vectorization up to AVX512 */
    static inline void __CKL_FN_ATTR_AVX512 vexp_hook_avx512(const double *input_array, double *result_array,
                                                        unsigned int size, ckl_hook_func_t pre_hook, 
				   void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        if (size > 8)
        {
            vexp_hook_avx512_16_group(input_array, result_array, size, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 8)
        {
            AVX512_8__1_ops(OP1, OP2, NAME_AVX512_EXP)
        }
        else
        {
            vexp_hook_avx512_7(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vexp_hook *****************/
    /*This function deal with size in 1~7*/
    static inline void __CKL_FN_ATTR_AVX2
    vexp_hook_avx2_3(const double *input_array, double *result_array, int size,
                int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
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
    static inline void __CKL_FN_ATTR_AVX2
    vexp_hook_avx2(const double *input_array, double *result_array,
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
                AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_hook_avx2_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            AVX_4__1_ops(OP1, OP2, NAME_AVX2_EXP)
        }
        else
        {
            vexp_hook_avx2_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vexp_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_AVX
    vexp_hook_avx_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
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
    static inline void __CKL_FN_ATTR_AVX
    vexp_hook_avx(const double *input_array, double *result_array,
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
                SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_hook_avx_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else
        {
            vexp_hook_avx_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vexp_hook *****************/
    /*This function deal with size in 1~3*/
    static inline void __CKL_FN_ATTR_SSE2
    vexp_hook_sse_3(const double *input_array,
               double *result_array,
               int size,
               int *array_index, ckl_hook_func_t pre_hook, void * pre_args, ckl_hook_func_t post_hook, void * post_args)
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
    static inline void __CKL_FN_ATTR_SSE2
    vexp_hook_sse(const double *input_array, double *result_array,
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
                SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
                *array_index += 4;
            }
            if (rest)
                vexp_hook_sse_3(input_array, result_array, rest, array_index, pre_hook, pre_args, post_hook, post_args);
        }
        else if (size == 4)
        {
            SSE_2__2_ops(OP1, OP2, NAME_SSE_EXP)
        }
        else
        {
            vexp_hook_sse_3(input_array, result_array, size, array_index, pre_hook, pre_args, post_hook, post_args);
        }
    }

    /************** ckl_vexp_hook *****************/
    static inline void vexp_hook_scalar(const double *input_array, double *result_array,
                                   unsigned int size, ckl_hook_func_t pre_hook, 
				   void * pre_args, ckl_hook_func_t post_hook, void * post_args)
    {
        int index = 0;
        int *array_index = &index;
        for (unsigned int i = 0; i < size; i++)
        {
            SCALAR_1_ops(OP1, OP2, 0, NAME_SCALAR_EXP);
            *array_index += 1;
        }
    }

#undef OP1
#undef OP2

#ifdef __cplusplus
}
#endif

#endif /*CKL_VEXP_HOOK_H*/
