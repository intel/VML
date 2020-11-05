#define SSE_SINCOS_2(i) SSE_SINCOS_2_TMP(i)
#define SSE_SINCOS_2_TMP(i)                                                   \
  __m128d input2_value##i = _mm_loadu_pd(&input_array[*array_index + i * 2]); \
  _mm_storeu_pd(&result_array[*array_index + i * 2],                          \
                _ZGVbN2v_sin(input2_value##i));                               \
  _mm_storeu_pd(&result_array1[*array_index + i * 2],                         \
                _ZGVbN2v_cos(input2_value##i));

#define SSE_SINCOS_2__0
/*Call 1 SSE function for 2 doubles*/
#define SSE_SINCOS_2__1 SSE_SINCOS_2(0)
/*Call 2 SSE function for 2 doubles*/
#define SSE_SINCOS_2__2 \
  SSE_SINCOS_2__1       \
  SSE_SINCOS_2(1)
/*Call 3 SSE function for 2 doubles*/
#define SSE_SINCOS_2__3 \
  SSE_SINCOS_2__2       \
  SSE_SINCOS_2(2)
/*Call 4 SSE function for 2 doubles*/
#define SSE_SINCOS_2__4 \
  SSE_SINCOS_2__3       \
  SSE_SINCOS_2(3)
/*Call 5 SSE function for 2 doubles*/
#define SSE_SINCOS_2__5 \
  SSE_SINCOS_2__4       \
  SSE_SINCOS_2(4)
/*Call 6 SSE function for 2 doubles*/
#define SSE_SINCOS_2__6 \
  SSE_SINCOS_2__5       \
  SSE_SINCOS_2(5)
/*Call 7 SSE function for 2 doubles*/
#define SSE_SINCOS_2__7 \
  SSE_SINCOS_2__6       \
  SSE_SINCOS_2(6)
/*Call 8 SSE function for 2 doubles*/
#define SSE_SINCOS_2__8 \
  SSE_SINCOS_2__7       \
  SSE_SINCOS_2(7)

/*For size = 2*i + (2-i)*/
#define SSE_SINCOS_2_mask2(i) SSE_SINCOS_2_mask2_TMP(i)
#define SSE_SINCOS_2_mask2_TMP(i)                                                 \
  SSE_SINCOS_2__##i;                                                              \
  __m128d input2_mask_value##i = _mm_load_sd(&input_array[*array_index + 2 * i]); \
  _mm_store_sd(                                                                   \
      &result_array[*array_index + 2 * i],                                        \
      _ZGVbN2v_sin(input2_mask_value##i));                                        \
  _mm_store_sd(                                                                   \
      &result_array1[*array_index + 2 * i],                                       \
      _ZGVbN2v_cos(input2_mask_value##i));
