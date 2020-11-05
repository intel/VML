#define SSE_f2d_2(i, name) SSE_f2d_2_TMP(i, name)
#define SSE_f2d_2_TMP(i, name)                                  \
  _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]), \
                _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(           \
                    _mm_loadu_ps(&input_array[*array_index + i * 2])))));

#define SSE_f2d_2__0(name)
/*Call 1 SSE function for 2 doubles*/
#define SSE_f2d_2__1(name) SSE_f2d_2(0, name)
/*Call 2 SSE function for 2 doubles*/
#define SSE_f2d_2__2(name) SSE_f2d_2__1(name) \
    SSE_f2d_2(1, name)
/*Call 3 SSE function for 2 doubles*/
#define SSE_f2d_2__3(name) SSE_f2d_2__2(name) \
    SSE_f2d_2(2, name)
/*Call 4 SSE function for 2 doubles*/
#define SSE_f2d_2__4(name) SSE_f2d_2__3(name) \
    SSE_f2d_2(3, name)
/*Call 5 SSE function for 2 doubles*/
#define SSE_f2d_2__5(name) SSE_f2d_2__4(name) \
    SSE_f2d_2(4, name)
/*Call 6 SSE function for 2 doubles*/
#define SSE_f2d_2__6(name) SSE_f2d_2__5(name) \
    SSE_f2d_2(5, name)
/*Call 7 SSE function for 2 doubles*/
#define SSE_f2d_2__7(name) SSE_f2d_2__6(name) \
    SSE_f2d_2(6, name)
/*Call 8 SSE function for 2 doubles*/
#define SSE_f2d_2__8(name) SSE_f2d_2__7(name) \
    SSE_f2d_2(7, name)

/*For size = 2*i + (2-i)*/
#define SSE_f2d_2_mask2(i, name) SSE_f2d_2_mask2_TMP(i, name)
#define SSE_f2d_2_mask2_TMP(i, name)                                                  \
  SSE_f2d_2__##i(name) _mm_store_ss(&result_array[*array_index + 2 * i],              \
                                    _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(_mm_load_ss( \
                                        &input_array[*array_index + 2 * i])))));
