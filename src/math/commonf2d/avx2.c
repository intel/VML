#define AVX2_4(i, name) AVX2_4_TMP(i, name)
#define AVX2_4_TMP(i, name)                                                    \
  _mm_storeu_ps(&result_array[*array_index + i * 4],                           \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                    \
                    _mm_loadu_ps(&input_array[*array_index + i * 4])))));

#define AVX2_4__0
/*Call 1 AVX2 function for 4 doubles*/
#define AVX2_4__1 AVX2_4(0, AVX2_NAME)
/*Call 2 AVX2 function for 4 doubles*/
#define AVX2_4__2 AVX2_4__1 AVX2_4(1, AVX2_NAME)
/*Call 3 AVX2 function for 4 doubles*/
#define AVX2_4__3 AVX2_4__2 AVX2_4(2, AVX2_NAME)
/*Call 4 AVX2 function for 4 doubles*/
#define AVX2_4__4 AVX2_4__3 AVX2_4(3, AVX2_NAME)

#define AVX_MASK_1 _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_MASK_2 _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_MASK_3 _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 4*i + (4-i)*/
#define AVX2_4_mask4(i, name) AVX2_4_mask4_TMP(i, name)
#define AVX2_4_mask4_TMP(i, name)                                              \
  if ((size - 4 * i) == 1) {                                                   \
    AVX2_4__##i _mm_maskstore_ps(                                              \
        &result_array[*array_index + 4 * i], AVX_MASK_1,                       \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(            \
            &input_array[*array_index + 4 * i], AVX_MASK_1)))));               \
  } else if ((size - 4 * i) == 2) {                                            \
    AVX2_4__##i _mm_maskstore_ps(                                              \
        &result_array[*array_index + 4 * i], AVX_MASK_2,                       \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(            \
            &input_array[*array_index + 4 * i], AVX_MASK_2)))));               \
  } else if ((size - 4 * i) == 3) {                                            \
    AVX2_4__##i _mm_maskstore_ps(                                              \
        &result_array[*array_index + 4 * i], AVX_MASK_3,                       \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(            \
            &input_array[*array_index + 4 * i], AVX_MASK_3)))));               \
  }

/*For size = 4*i + (2-i)*/
/*#define AVX2_4_mask2(i, name) AVX2_4_mask2_TMP(i, name)
#define AVX2_4_mask2_TMP(i, name)                                              \
  unsigned char tail_mask_uint =                                               \
      (((unsigned char)0xff) >> (8 - size + 4 * i));                           \
  __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                         \
  AVX2_4__##i _mm_mask_storeu_pd(                                              \
      &result_array[*array_index + 4 * i], tail_mask,                          \
      _ZGV##name(                                                              \
          _mm_maskz_loadu_pd(tail_mask, &input_array[*array_index + 4 * i])));*/
