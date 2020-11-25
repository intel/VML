/*For 8 doubles*/
#define AVX512_f2d_8(i, name) AVX512_f2d_8_TMP(i, name)
#define AVX512_f2d_8_TMP(i, name)                                                \
    if(ckl_pre_hook)                                                             \
        ckl_pre_hook(ckl_pre_hook_args);                                         \
    _mm256_storeu_ps(&result_array[*array_index + i * 8],                        \
                     _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_loadu_ps( \
                         &input_array[*array_index + i * 8])))));                \
    if(ckl_post_hook)                                                            \
        ckl_post_hook(ckl_post_hook_args);

#define AVX512_f2d_8__0(name)
/*Call 1 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__1(name) AVX512_f2d_8(0, name)
/*Call 2 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__2(name) \
    AVX512_f2d_8__1(name)     \
        AVX512_f2d_8(1, name)
/*Call 3 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__3(name) \
    AVX512_f2d_8__2(name)     \
        AVX512_f2d_8(2, name)
/*Call 4 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__4(name) \
    AVX512_f2d_8__3(name)     \
        AVX512_f2d_8(3, name)

/*For size = 8*i + (8-i)*/
#define AVX512_f2d_8_mask8(i, name) AVX512_f2d_8_mask8_TMP(i, name)
#define AVX512_f2d_8_mask8_TMP(i, name)                                   \
    unsigned char tail_mask_uint =                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                  \
    AVX512_f2d_8__##i(name)                                               \
    if(ckl_pre_hook)                                                      \
        ckl_pre_hook(ckl_pre_hook_args);                                  \
    _mm256_mask_storeu_ps(                                                \
        &result_array[*array_index + 8 * i], tail_mask,                   \
        _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_maskz_loadu_ps( \
            tail_mask, &input_array[*array_index + 8 * i])))));           \
    if(ckl_post_hook)                                                     \
        ckl_post_hook(ckl_post_hook_args);

/*For size = 8*i + (4-i)*/
#define AVX512_f2d_8_mask4(i, name1, name2) AVX512_f2d_8_mask4_TMP(i, name1, name2)
#define AVX512_f2d_8_mask4_TMP(i, name1, name2)                         \
    unsigned char tail_mask_uint =                                      \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                \
    AVX512_f2d_8__##i(name1)                                            \
    if(ckl_pre_hook)                                                    \
        ckl_pre_hook(ckl_pre_hook_args);                                \
    _mm_mask_storeu_ps(                                                 \
        &result_array[*array_index + 8 * i], tail_mask,                 \
        _mm256_cvtpd_ps(_ZGV##name2(_mm256_cvtps_pd(_mm_maskz_loadu_ps( \
            tail_mask, &input_array[*array_index + 8 * i])))));         \
    if(ckl_post_hook)                                                   \
        ckl_post_hook(ckl_post_hook_args);
