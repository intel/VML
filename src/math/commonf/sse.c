/*For 4 floats*/
#define SSE_4(i, name) SSE_4_TMP(i, name)
#define SSE_4_TMP(i, name)                             \
    _mm_storeu_ps(&result_array[*array_index + i * 4], \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + i * 4])));

/*Call 1 SSE function for 4 floats*/
#define SSE_4_offset(n, name) SSE_4_offset_TMP(n, name)
#define SSE_4_offset_TMP(n, name)                  \
    _mm_storeu_ps(&result_array[*array_index + n], \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + n])));

#define SSE_4__0
/*Call 1 SSE function for 4 floats*/
#define SSE_4__1 SSE_4(0, SSE_NAME)
/*Call 2 SSE function for 4 floats*/
#define SSE_4__2 SSE_4__1 SSE_4(1, SSE_NAME)
/*Call 3 SSE function for 4 floats*/
#define SSE_4__3 SSE_4__2 SSE_4(2, SSE_NAME)
/*Call 4 SSE function for 4 floats*/
#define SSE_4__4 SSE_4__3 SSE_4(3, SSE_NAME)
