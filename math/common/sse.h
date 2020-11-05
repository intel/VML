#define SSE_2(i, name) SSE_2_TMP(i, name)
#define SSE_2_TMP(i, name)                           \
  _mm_storeu_pd(&result_array[*array_index + i * 2], \
                _ZGV##name(_mm_loadu_pd(&input_array[*array_index + i * 2])));

#define SSE_2__0(name)
/*Call 1 SSE function for 2 doubles*/
#define SSE_2__1(name) SSE_2(0, name)
/*Call 2 SSE function for 2 doubles*/
#define SSE_2__2(name) SSE_2__1(name) \
SSE_2(1, name)
/*Call 3 SSE function for 2 doubles*/
#define SSE_2__3(name) SSE_2__2(name) \
SSE_2(2, name)
/*Call 4 SSE function for 2 doubles*/
#define SSE_2__4(name) SSE_2__3(name) \
SSE_2(3, name)
/*Call 5 SSE function for 2 doubles*/
#define SSE_2__5(name) SSE_2__4(name) \
SSE_2(4, name)
/*Call 6 SSE function for 2 doubles*/
#define SSE_2__6(name) SSE_2__5(name) \
SSE_2(5, name)
/*Call 7 SSE function for 2 doubles*/
#define SSE_2__7(name) SSE_2__6(name) \
SSE_2(6, name)
/*Call 8 SSE function for 2 doubles*/
#define SSE_2__8(name) SSE_2__7(name) \
SSE_2(7, name)

/*For size = 2*i + (2-i)*/
#define SSE_2_mask2(i, name) SSE_2_mask2_TMP(i, name)
#define SSE_2_mask2_TMP(i, name)           \
  SSE_2__##i(name) _mm_store_sd(           \
      &result_array[*array_index + 2 * i], \
      _ZGV##name(_mm_load_sd(&input_array[*array_index + 2 * i])));
