/*For 4 floats*/
#define SSE_4(i, name) SSE_4_TMP(i, name)
#define SSE_4_TMP(i, name)                                                     \
    if(ckl_pre_hook)                                                           \
        ckl_pre_hook(ckl_pre_hook_args);                                       \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                         \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + i * 4])));\
    if(ckl_post_hook)                                                           \
        ckl_post_hook(ckl_post_hook_args);
    

/*Call 1 SSE function for 4 floats*/
#define SSE_4_offset(n, name) SSE_4_offset_TMP(n, name)
#define SSE_4_offset_TMP(n, name)                                              \
    if(ckl_pre_hook)                                                           \
        ckl_pre_hook(ckl_pre_hook_args);                                       \
    _mm_storeu_ps(&result_array[*array_index + n],                             \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + n])));   \
    if(ckl_post_hook)                                                          \
        ckl_post_hook(ckl_post_hook_args);

#define SSE_4__0(name)
/*Call 1 SSE function for 4 floats*/
#define SSE_4__1(name) SSE_4(0, name)
/*Call 2 SSE function for 4 floats*/
#define SSE_4__2(name) SSE_4__1(name) \
SSE_4(1, name)
/*Call 3 SSE function for 4 floats*/
#define SSE_4__3(name) SSE_4__2(name) \
SSE_4(2, name)
/*Call 4 SSE function for 4 floats*/
#define SSE_4__4(name) SSE_4__3(name) \
SSE_4(3, name)
