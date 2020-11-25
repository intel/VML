/*For 8 doubles*/
#define AVX512_SINCOS_8(i) AVX512_SINCOS_8_TMP(i)
#define AVX512_SINCOS_8_TMP(i)                                                     \
    if(ckl_pre_hook)                                                               \
        ckl_pre_hook(ckl_pre_hook_args);                                           \
    __m512d input8_value##i = _mm512_loadu_pd(&input_array[*array_index + i * 8]); \
    _mm512_storeu_pd(&result_array[*array_index + i * 8],                          \
                     _ZGVeN8v_sin(input8_value##i));                               \
    _mm512_storeu_pd(&result_array1[*array_index + i * 8],                         \
                     _ZGVeN8v_cos(input8_value##i));                               \
    if(ckl_post_hook)                                                              \
        ckl_post_hook(ckl_post_hook_args);

#define AVX512_SINCOS_8__0
/*Call 1 AVX512 function for 8 doubles*/
#define AVX512_SINCOS_8__1 AVX512_SINCOS_8(0)
/*Call 2 AVX512 function for 8 doubles*/
#define AVX512_SINCOS_8__2 \
    AVX512_SINCOS_8__1     \
    AVX512_SINCOS_8(1)
/*Call 3 AVX512 function for 8 doubles*/
#define AVX512_SINCOS_8__3 \
    AVX512_SINCOS_8__2     \
    AVX512_SINCOS_8(2)
/*Call 4 AVX512 function for 8 doubles*/
#define AVX512_SINCOS_8__4 \
    AVX512_SINCOS_8__3     \
    AVX512_SINCOS_8(3)

/*For size = 8*i + (8-i)*/
#define AVX512_SINCOS_8_mask8(i) AVX512_SINCOS_8_mask8_TMP(i)
#define AVX512_SINCOS_8_mask8_TMP(i)                                                      \
    unsigned char tail_mask_uint =                                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                  \
    AVX512_SINCOS_8__##i;                                                                 \
    if(ckl_pre_hook)                                                                      \
        ckl_pre_hook(ckl_pre_hook_args);                                                  \
    __m512d input8_mask_v##i = _mm512_maskz_loadu_pd(tail_mask,                           \
                                                     &input_array[*array_index + 8 * i]); \
    _mm512_mask_storeu_pd(                                                                \
        &result_array[*array_index + 8 * i], tail_mask,                                   \
        _ZGVeN8v_sin(input8_mask_v##i));                                                  \
    _mm512_mask_storeu_pd(                                                                \
        &result_array1[*array_index + 8 * i], tail_mask,                                  \
        _ZGVeN8v_cos(input8_mask_v##i));                                                  \
    if(ckl_post_hook)                                                                     \
        ckl_post_hook(ckl_post_hook_args);

/*For size = 8*i + (4-i)*/
#define AVX512_SINCOS_8_mask4(i) AVX512_SINCOS_8_mask4_TMP(i)
#define AVX512_SINCOS_8_mask4_TMP(i)                                                      \
    unsigned char tail_mask_uint =                                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                  \
    AVX512_SINCOS_8__##i;                                                                 \
    if(ckl_pre_hook)                                                                      \
        ckl_pre_hook(ckl_pre_hook_args);                                                  \
    __m256d input4_mask_v##i = _mm256_maskz_loadu_pd(tail_mask,                           \
                                                     &input_array[*array_index + 8 * i]); \
    _mm256_mask_storeu_pd(                                                                \
        &result_array[*array_index + 8 * i], tail_mask,                                   \
        _ZGVdN4v_sin(input4_mask_v##i));                                                  \
    _mm256_mask_storeu_pd(                                                                \
        &result_array1[*array_index + 8 * i], tail_mask,                                  \
        _ZGVdN4v_cos(input4_mask_v##i));                                                  \
    if(ckl_post_hook)                                                                     \
        ckl_post_hook(ckl_post_hook_args);
