/*For 4 floats*/
#define SSE_vv_4(i, name) SSE_vv_4_TMP(i, name)
#define SSE_vv_4_TMP(i, name)                                                  \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                         \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + i * 4]), \
                             _mm_loadu_ps(&input_array1[*array_index + i * 4])));

/*Call 1 SSE function for 4 floats*/
#define SSE_vv_4_offset(n, name) SSE_vv_4_offset_TMP(n, name)
#define SSE_vv_4_offset_TMP(n, name)                                       \
    _mm_storeu_ps(&result_array[*array_index + n],                         \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + n]), \
                             _mm_loadu_ps(&input_array1[*array_index + n])));

#define SSE_vv_4__0(name)
/*Call 1 SSE function for 4 floats*/
#define SSE_vv_4__1(name) SSE_vv_4(0, name)
/*Call 2 SSE function for 4 floats*/
#define SSE_vv_4__2(name) \
    SSE_vv_4__1(name)     \
        SSE_vv_4(1, name)
/*Call 3 SSE function for 4 floats*/
#define SSE_vv_4__3(name) \
    SSE_vv_4__2(name)     \
        SSE_vv_4(2, name)
/*Call 4 SSE function for 4 floats*/
#define SSE_vv_4__4(name) \
    SSE_vv_4__3(name)     \
        SSE_vv_4(3, name)
