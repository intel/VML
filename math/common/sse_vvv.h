#define SSE_vvv_ADDR(i, n) (uint64_t) & result_array[*array_index + i * 2 + n]
#define SSE_vvv_ADDR1(i, n) (uint64_t) & result_array1[*array_index + i * 2 + n]

#define SSE_vvv_2(i, name) SSE_vvv_2_TMP(i, name)
#define SSE_vvv_2_TMP(i, name)                                       \
  _ZGV##name(_mm_loadu_pd(&input_array[*array_index + 2 * i]),       \
             _mm_set_epi64x(SSE_vvv_ADDR(i, 1), SSE_vvv_ADDR(i, 0)), \
             _mm_set_epi64x(SSE_vvv_ADDR1(i, 1), SSE_vvv_ADDR1(i, 0)));

#define SSE_vvv_2__0(name)
/*Call 1 SSE function for 2 doubles*/
#define SSE_vvv_2__1(name) SSE_vvv_2(0, name)
/*Call 2 SSE function for 2 doubles*/
#define SSE_vvv_2__2(name) \
  SSE_vvv_2__1(name)       \
      SSE_vvv_2(1, name)
/*Call 3 SSE function for 2 doubles*/
#define SSE_vvv_2__3(name) \
  SSE_vvv_2__2(name)       \
      SSE_vvv_2(2, name)
/*Call 4 SSE function for 2 doubles*/
#define SSE_vvv_2__4(name) \
  SSE_vvv_2__3(name)       \
      SSE_vvv_2(3, name)
/*Call 5 SSE function for 2 doubles*/
#define SSE_vvv_2__5(name) \
  SSE_vvv_2__4(name)       \
      SSE_vvv_2(4, name)
/*Call 6 SSE function for 2 doubles*/
#define SSE_vvv_2__6(name) \
  SSE_vvv_2__5(name)       \
      SSE_vvv_2(5, name)
/*Call 7 SSE function for 2 doubles*/
#define SSE_vvv_2__7(name) \
  SSE_vvv_2__6(name)       \
      SSE_vvv_2(6, name)
/*Call 8 SSE function for 2 doubles*/
#define SSE_vvv_2__8(name) \
  SSE_vvv_2__7(name)       \
      SSE_vvv_2(7, name)

/*For size = 2*i + (2-i)*/
#define SSE_vvv_2_mask2(i, name) SSE_vvv_2_mask2_TMP(i, name)
#define SSE_vvv_2_mask2_TMP(i, name)                             \
  SSE_vvv_2__##i(name);                                          \
  double tmp, tmp1;                                              \
  _ZGV##name(_mm_load_sd(&input_array[*array_index + 2 * i]),    \
             _mm_set_epi64x((uint64_t)&tmp, SSE_vvv_ADDR(i, 0)), \
             _mm_set_epi64x((uint64_t)&tmp1, SSE_vvv_ADDR1(i, 0)));
