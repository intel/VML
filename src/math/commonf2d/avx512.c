/*For 8 doubles*/
#define AVX512_8(i, name) AVX512_8_TMP(i, name)
#define AVX512_8_TMP(i, name)                                                  \
  _mm256_storeu_ps(&result_array[*array_index + i * 8],                        \
                   _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_loadu_ps( \
                       &input_array[*array_index + i * 8])))));

#define AVX512_8__0
/*Call 1 AVX512 function for 8 doubles*/
#define AVX512_8__1 AVX512_8(0, AVX512_NAME)
/*Call 2 AVX512 function for 8 doubles*/
#define AVX512_8__2 AVX512_8__1 AVX512_8(1, AVX512_NAME)
/*Call 3 AVX512 function for 8 doubles*/
#define AVX512_8__3 AVX512_8__2 AVX512_8(2, AVX512_NAME)
/*Call 4 AVX512 function for 8 doubles*/
#define AVX512_8__4 AVX512_8__3 AVX512_8(3, AVX512_NAME)

/*For size = 8*i + (8-i)*/
#define AVX512_8_mask8(i, name) AVX512_8_mask8_TMP(i, name)
#define AVX512_8_mask8_TMP(i, name)                                            \
  unsigned char tail_mask_uint =                                               \
      (((unsigned char)0xff) >> (8 - size + 8 * i));                           \
  __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                         \
  AVX512_8__##i _mm256_mask_storeu_ps(                                         \
      &result_array[*array_index + 8 * i], tail_mask,                          \
      _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_maskz_loadu_ps(        \
          tail_mask, &input_array[*array_index + 8 * i])))));
/*For size = 8*i + (4-i)*/
#define AVX512_8_mask4(i, name) AVX512_8_mask4_TMP(i, name)
#define AVX512_8_mask4_TMP(i, name)                                            \
  unsigned char tail_mask_uint =                                               \
      (((unsigned char)0xff) >> (8 - size + 8 * i));                           \
  __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                         \
  AVX512_8__##i _mm_mask_storeu_ps(                                            \
      &result_array[*array_index + 8 * i], tail_mask,                          \
      _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskz_loadu_ps(           \
          tail_mask, &input_array[*array_index + 8 * i])))));
