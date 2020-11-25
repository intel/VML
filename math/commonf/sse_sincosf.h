/*For 4 floats*/
#define SSE_SINCOSF_4(i) SSE_SINCOSF_4_TMP(i)
#define SSE_SINCOSF_4_TMP(i)                                                   \
    if(ckl_pre_hook)                                                           \
        ckl_pre_hook(ckl_pre_hook_args);                                       \
    __m128 input4_value##i = _mm_loadu_ps(&input_array[*array_index + i * 4]); \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                         \
                  _ZGVbN4v_sinf(input4_value##i));                             \
    _mm_storeu_ps(&result_array1[*array_index + i * 4],                        \
                  _ZGVbN4v_cosf(input4_value##i));                             \
    if(ckl_post_hook)                                                          \
        ckl_post_hook(ckl_post_hook_args);

/*Call 1 SSE function for 4 floats*/
#define SSE_SINCOSF_4_offset(n) SSE_SINCOSF_4_offset_TMP(n)
#define SSE_SINCOSF_4_offset_TMP(n)                                        \
    if(ckl_pre_hook)                                                       \
        ckl_pre_hook(ckl_pre_hook_args);                                   \
    __m128 input4_value##i = _mm_loadu_ps(&input_array[*array_index + n]); \
    _mm_storeu_ps(&result_array[*array_index + n],                         \
                  _ZGVbN4v_sinf(input4_value##i));                         \
    _mm_storeu_ps(&result_array1[*array_index + n],                        \
                  _ZGVbN4v_cosf(input4_value##i));                         \
    if(ckl_post_hook)                                                      \
        ckl_post_hook(ckl_post_hook_args);

#define SSE_SINCOSF_4__0
/*Call 1 SSE function for 4 floats*/
#define SSE_SINCOSF_4__1 SSE_SINCOSF_4(0)
/*Call 2 SSE function for 4 floats*/
#define SSE_SINCOSF_4__2 \
    SSE_SINCOSF_4__1     \
    SSE_SINCOSF_4(1)
/*Call 3 SSE function for 4 floats*/
#define SSE_SINCOSF_4__3 \
    SSE_SINCOSF_4__2     \
    SSE_SINCOSF_4(2)
/*Call 4 SSE function for 4 floats*/
#define SSE_SINCOSF_4__4 \
    SSE_SINCOSF_4__3     \
    SSE_SINCOSF_4(3)
