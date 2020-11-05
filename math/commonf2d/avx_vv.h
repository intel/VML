#define AVX_vv_f2d_4(i, name) AVX_vv_f2d_4_TMP(i, name)
#define AVX_vv_f2d_4_TMP(i, name)                                                                 \
  _mm_storeu_ps(&result_array[*array_index + i * 4],                                              \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                                       \
                                               _mm_loadu_ps(&input_array[*array_index + i * 4])), \
                                           _mm256_cvtps_pd(                                       \
                                               _mm_loadu_ps(&input_array1[*array_index + i * 4])))));

#define AVX_vv_f2d_4__0(name)
/*Call 1 AVX function for 4 doubles*/
#define AVX_vv_f2d_4__1(name) AVX_vv_f2d_4(0, name)
/*Call 2 AVX function for 4 doubles*/
#define AVX_vv_f2d_4__2(name) \
  AVX_vv_f2d_4__1(name)       \
      AVX_vv_f2d_4(1, name)
/*Call 3 AVX function for 4 doubles*/
#define AVX_vv_f2d_4__3(name) \
  AVX_vv_f2d_4__2(name)       \
      AVX_vv_f2d_4(2, name)
/*Call 4 AVX function for 4 doubles*/
#define AVX_vv_f2d_4__4(name) \
  AVX_vv_f2d_4__3(name)       \
      AVX_vv_f2d_4(3, name)

#define AVX_vv_f2d_MASKF2D_1 _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_vv_f2d_MASKF2D_2 _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_vv_f2d_MASKF2D_3 _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 4*i + (4-i)*/
#define AVX_vv_f2d_4_mask4(i, name) AVX_vv_f2d_4_mask4_TMP(i, name)
#define AVX_vv_f2d_4_mask4_TMP(i, name)                                                                \
  if ((size - 4 * i) == 1)                                                                             \
  {                                                                                                    \
    AVX_vv_f2d_4__##i(name) _mm_maskstore_ps(                                                          \
        &result_array[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_1,                                     \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                    \
                                       &input_array[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_1)),     \
                                   _mm256_cvtps_pd(_mm_maskload_ps(                                    \
                                       &input_array1[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_1))))); \
  }                                                                                                    \
  else if ((size - 4 * i) == 2)                                                                        \
  {                                                                                                    \
    AVX_vv_f2d_4__##i(name) _mm_maskstore_ps(                                                          \
        &result_array[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_2,                                     \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                    \
                                       &input_array[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_2)),     \
                                   _mm256_cvtps_pd(_mm_maskload_ps(                                    \
                                       &input_array1[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_2))))); \
  }                                                                                                    \
  else if ((size - 4 * i) == 3)                                                                        \
  {                                                                                                    \
    AVX_vv_f2d_4__##i(name) _mm_maskstore_ps(                                                          \
        &result_array[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_3,                                     \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                    \
                                       &input_array[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_3)),     \
                                   _mm256_cvtps_pd(_mm_maskload_ps(                                    \
                                       &input_array1[*array_index + 4 * i], AVX_vv_f2d_MASKF2D_3))))); \
  }

/*Call 1 AVX function for 4 floats*/
#define AVX_vv_f2d_4_offset(n, name) AVX_vv_f2d_4_offset_TMP(n, name)
#define AVX_vv_f2d_4_offset_TMP(n, name)                                                      \
  _mm_storeu_ps(&result_array[*array_index + n],                                              \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                                   \
                                               _mm_loadu_ps(&input_array[*array_index + n])), \
                                           _mm256_cvtps_pd(                                   \
                                               _mm_loadu_ps(&input_array1[*array_index + n])))));

#define AVX_vv_f2d_2(i, name) AVX_vv_f2d_2_TMP(i, name)
#define AVX_vv_f2d_2_TMP(i, name)                                         \
  _mm_maskstore_ps(                                                       \
      &result_array[*array_index + i * 2],                                \
      _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff),      \
      _mm_cvtpd_ps(_ZGV##name(                                            \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])), \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array1[*array_index + i * 2])))));

#define AVX_vv_f2d_2__0(name)
/*Call 1 SSE function for 2 doubles*/
#define AVX_vv_f2d_2__1(name) AVX_vv_f2d_2(0, name)
/*Call 2 SSE function for 2 doubles*/
#define AVX_vv_f2d_2__2(name) \
  AVX_vv_f2d_2__1(name)       \
      AVX_vv_f2d_2(1, name)
/*Call 3 SSE function for 2 doubles*/
#define AVX_vv_f2d_2__3(name) \
  AVX_vv_f2d_2__2(name)       \
      AVX_vv_f2d_2(2, name)
/*Call 4 SSE function for 2 doubles*/
#define AVX_vv_f2d_2__4(name) \
  AVX_vv_f2d_2__3(name)       \
      AVX_vv_f2d_2(3, name)
