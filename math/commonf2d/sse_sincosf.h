#define SSE_SINCOSF_f2d_2(i) SSE_SINCOSF_f2d_2_TMP(i)
#define SSE_SINCOSF_f2d_2_TMP(i)                                    \
    if(ckl_pre_hook)                                                \
        ckl_pre_hook(ckl_pre_hook_args);                            \
    __m128d input2_f2d_value##i = _mm_cvtps_pd(                     \
        _mm_loadu_ps(&input_array[*array_index + i * 2]));          \
    _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]),   \
                  _mm_cvtpd_ps(_ZGVbN2v_sin(input2_f2d_value##i))); \
    _mm_storel_pi((__m64 *)(&result_array1[*array_index + i * 2]),  \
                  _mm_cvtpd_ps(_ZGVbN2v_cos(input2_f2d_value##i))); \
    if(ckl_post_hook)                                               \
        ckl_post_hook(ckl_post_hook_args);

#define SSE_SINCOSF_f2d_2__0
/*Call 1 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__1 SSE_SINCOSF_f2d_2(0)
/*Call 2 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__2 SSE_SINCOSF_f2d_2__1 \
    SSE_SINCOSF_f2d_2(1)
/*Call 3 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__3 SSE_SINCOSF_f2d_2__2 \
    SSE_SINCOSF_f2d_2(2)
/*Call 4 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__4 SSE_SINCOSF_f2d_2__3 \
    SSE_SINCOSF_f2d_2(3)
/*Call 5 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__5 SSE_SINCOSF_f2d_2__4 \
    SSE_SINCOSF_f2d_2(4)
/*Call 6 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__6 SSE_SINCOSF_f2d_2__5 \
    SSE_SINCOSF_f2d_2(5)
/*Call 7 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__7 SSE_SINCOSF_f2d_2__6 \
    SSE_SINCOSF_f2d_2(6)
/*Call 8 SSE function for 2 doubles*/
#define SSE_SINCOSF_f2d_2__8 SSE_SINCOSF_f2d_2__7 \
    SSE_SINCOSF_f2d_2(7)

/*For size = 2*i + (2-i)*/
#define SSE_SINCOSF_f2d_2_mask2(i) SSE_SINCOSF_f2d_2_mask2_TMP(i)
#define SSE_SINCOSF_f2d_2_mask2_TMP(i)                                  \
    SSE_SINCOSF_f2d_2__##i;                                             \
    if(ckl_pre_hook)                                                    \
        ckl_pre_hook(ckl_pre_hook_args);                                \
    __m128d input2_f2d_mask_value##i = _mm_cvtps_pd(_mm_load_ss(        \
        &input_array[*array_index + 2 * i]));                           \
    _mm_store_ss(&result_array[*array_index + 2 * i],                   \
                 _mm_cvtpd_ps(_ZGVbN2v_sin(input2_f2d_mask_value##i))); \
    _mm_store_ss(&result_array1[*array_index + 2 * i],                  \
                 _mm_cvtpd_ps(_ZGVbN2v_cos(input2_f2d_mask_value##i))); \
    if(ckl_post_hook)                                                   \
        ckl_post_hook(ckl_post_hook_args);
