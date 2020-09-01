#define SSE_2(i, name) SSE_2_TMP(i, name)
#define SSE_2_TMP(i, name)                                                     \
  _mm_storeu_pd(&result_array[*array_index + i * 2],                           \
                _ZGV##name(_mm_loadu_pd(&input_array[*array_index + i * 2])));

#define SSE_2__0
/*Call 1 SSE function for 2 doubles*/
#define SSE_2__1 SSE_2(0, SSE_NAME)
/*Call 2 SSE function for 2 doubles*/
#define SSE_2__2 SSE_2__1 SSE_2(1, SSE_NAME)
/*Call 3 SSE function for 2 doubles*/
#define SSE_2__3 SSE_2__2 SSE_2(2, SSE_NAME)
/*Call 4 SSE function for 2 doubles*/
#define SSE_2__4 SSE_2__3 SSE_2(3, SSE_NAME)
/*Call 5 SSE function for 2 doubles*/
#define SSE_2__5 SSE_2__4 SSE_2(4, SSE_NAME)
/*Call 6 SSE function for 2 doubles*/
#define SSE_2__6 SSE_2__5 SSE_2(5, SSE_NAME)
/*Call 7 SSE function for 2 doubles*/
#define SSE_2__7 SSE_2__6 SSE_2(6, SSE_NAME)
/*Call 8 SSE function for 2 doubles*/
#define SSE_2__8 SSE_2__7 SSE_2(7, SSE_NAME)

/*For size = 2*i + (2-i)*/
#define SSE_2_mask2(i, name) SSE_2_mask2_TMP(i, name)
#define SSE_2_mask2_TMP(i, name)                                               \
  SSE_2__##i _mm_store_sd(                                                     \
      &result_array[*array_index + 2 * i],                                     \
      _ZGV##name(_mm_load_sd(&input_array[*array_index + 2 * i])));
