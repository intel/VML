#define AVX_4(i, name) AVX_4_TMP(i, name)
#define AVX_4_TMP(i, name)                                                     \
  _mm_storeu_ps(&result_array[*array_index + i * 4],                           \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                    \
                    _mm_loadu_ps(&input_array[*array_index + i * 4])))));

#define AVX_4__0
/*Call 1 AVX function for 4 doubles*/
#define AVX_4__1 AVX_4(0, AVX_NAME)
/*Call 2 AVX function for 4 doubles*/
#define AVX_4__2 AVX_4__1 AVX_4(1, AVX_NAME)
/*Call 3 AVX function for 4 doubles*/
#define AVX_4__3 AVX_4__2 AVX_4(2, AVX_NAME)
/*Call 4 AVX function for 4 doubles*/
#define AVX_4__4 AVX_4__3 AVX_4(3, AVX_NAME)

#define AVX_MASK_1 _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_MASK_2 _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_MASK_3 _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 4*i + (4-i)*/
#define AVX_4_mask4(i, name) AVX_4_mask4_TMP(i, name)
#define AVX_4_mask4_TMP(i, name)                                               \
  if ((size - 4 * i) == 1) {                                                   \
    AVX_4__##i _mm_maskstore_ps(                                               \
        &result_array[*array_index + 4 * i], AVX_MASK_1,                       \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(            \
            &input_array[*array_index + 4 * i], AVX_MASK_1)))));               \
  } else if ((size - 4 * i) == 2) {                                            \
    AVX_4__##i _mm_maskstore_ps(                                               \
        &result_array[*array_index + 4 * i], AVX_MASK_2,                       \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(            \
            &input_array[*array_index + 4 * i], AVX_MASK_2)))));               \
  } else if ((size - 4 * i) == 3) {                                            \
    AVX_4__##i _mm_maskstore_ps(                                               \
        &result_array[*array_index + 4 * i], AVX_MASK_3,                       \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(            \
            &input_array[*array_index + 4 * i], AVX_MASK_3)))));               \
  }

/*Call 1 AVX2 or AVX function for 4 doubles*/
#define AVX_4_offset(n, name) AVX_4_offset_TMP(n, name)
#define AVX_4_offset_TMP(n, name)                                              \
  _mm_storeu_ps(&result_array[*array_index + n],                               \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                    \
                    _mm_loadu_ps(&input_array[*array_index + n])))));

#define AVX_2(i, name) AVX_2_TMP(i, name)
#define AVX_2_TMP(i, name)                                                     \
  _mm_maskstore_ps(                                                            \
      &result_array[*array_index + i * 2],                                     \
      _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff),           \
      _mm_cvtpd_ps(_ZGV##name(                                                 \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])))));
#define AVX_2__0
/*Call 1 SSE function for 2 doubles*/
#define AVX_2__1 AVX_2(0, SSE_NAME)
/*Call 2 SSE function for 2 doubles*/
#define AVX_2__2 AVX_2__1 AVX_2(1, SSE_NAME)
/*Call 3 SSE function for 2 doubles*/
#define AVX_2__3 AVX_2__2 AVX_2(2, SSE_NAME)
/*Call 4 SSE function for 2 doubles*/
#define AVX_2__4 AVX_2__3 AVX_2(3, SSE_NAME)