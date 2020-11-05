#define AVX_SINCOS_4(i) AVX_SINCOS_4_TMP(i)
#define AVX_SINCOS_4_TMP(i)                                                       \
  __m256d input4_value_##i = _mm256_loadu_pd(&input_array[*array_index + i * 4]); \
  _mm256_storeu_pd(                                                               \
      &result_array[*array_index + i * 4],                                        \
      _ZGVdN4v_sin(input4_value_##i));                                            \
  _mm256_storeu_pd(                                                               \
      &result_array1[*array_index + i * 4],                                       \
      _ZGVdN4v_cos(input4_value_##i));

#define AVX_SINCOS_4__0
/*Call 1 AVX function for 4 doubles*/
#define AVX_SINCOS_4__1 AVX_SINCOS_4(0)
/*Call 2 AVX function for 4 doubles*/
#define AVX_SINCOS_4__2 \
  AVX_SINCOS_4__1       \
  AVX_SINCOS_4(1)
/*Call 3 AVX function for 4 doubles*/
#define AVX_SINCOS_4__3 \
  AVX_SINCOS_4__2       \
  AVX_SINCOS_4(2)
/*Call 4 AVX function for 4 doubles*/
#define AVX_SINCOS_4__4 \
  AVX_SINCOS_4__3       \
  AVX_SINCOS_4(3)

#define AVX_SINCOS_MASK_1                                   \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000, \
                    0x0000000000000000, 0xffffffffffffffff)
#define AVX_SINCOS_MASK_2                                   \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000, \
                    0xffffffffffffffff, 0xffffffffffffffff)
#define AVX_SINCOS_MASK_3                                   \
  _mm256_set_epi64x(0x0000000000000000, 0xffffffffffffffff, \
                    0xffffffffffffffff, 0xffffffffffffffff)

/*For size = 4*i + (4-i)*/
#define AVX_SINCOS_4_mask4(i) AVX_SINCOS_4_mask4_TMP(i)
#define AVX_SINCOS_4_mask4_TMP(i)                                                          \
  if ((size - 4 * i) == 1)                                                                 \
  {                                                                                        \
    AVX_SINCOS_4__##i;                                                                     \
    __m256d input4_value_mask_##i = _mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                                       AVX_SINCOS_MASK_1);                 \
    _mm256_maskstore_pd(                                                                   \
        &result_array[*array_index + 4 * i], AVX_SINCOS_MASK_1,                            \
        _ZGVdN4v_sin(input4_value_mask_##i));                                              \
    _mm256_maskstore_pd(                                                                   \
        &result_array1[*array_index + 4 * i], AVX_SINCOS_MASK_1,                           \
        _ZGVdN4v_cos(input4_value_mask_##i));                                              \
  }                                                                                        \
  else if ((size - 4 * i) == 2)                                                            \
  {                                                                                        \
    AVX_SINCOS_4__##i;                                                                     \
    __m256d input4_value_mask_##i = _mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                                       AVX_SINCOS_MASK_2);                 \
    _mm256_maskstore_pd(                                                                   \
        &result_array[*array_index + 4 * i], AVX_SINCOS_MASK_2,                            \
        _ZGVdN4v_sin(input4_value_mask_##i));                                              \
    _mm256_maskstore_pd(                                                                   \
        &result_array1[*array_index + 4 * i], AVX_SINCOS_MASK_2,                           \
        _ZGVdN4v_cos(input4_value_mask_##i));                                              \
  }                                                                                        \
  else if ((size - 4 * i) == 3)                                                            \
  {                                                                                        \
    AVX_SINCOS_4__##i;                                                                     \
    __m256d input4_value_mask_##i = _mm256_maskload_pd(&input_array[*array_index + 4 * i], \
                                                       AVX_SINCOS_MASK_3);                 \
    _mm256_maskstore_pd(                                                                   \
        &result_array[*array_index + 4 * i], AVX_SINCOS_MASK_3,                            \
        _ZGVdN4v_sin(input4_value_mask_##i));                                              \
    _mm256_maskstore_pd(                                                                   \
        &result_array1[*array_index + 4 * i], AVX_SINCOS_MASK_3,                           \
        _ZGVdN4v_cos(input4_value_mask_##i));                                              \
  }

/*For size = 4*i + (2-i)*/
#define AVX_SINCOS_4_mask2(i) AVX_SINCOS_4_mask2_TMP(i)
#define AVX_SINCOS_4_mask2_TMP(i)                                            \
  AVX_SINCOS_4__##i;                                                         \
  __m128d input2_value##i = _mm_load_sd(&input_array[*array_index + 2 * i]); \
  _mm_store_sd(                                                              \
      &result_array[*array_index + 4 * i],                                   \
      _ZGVbN2v_sin(input2_value##i));                                        \
  _mm_store_sd(                                                              \
      &result_array1[*array_index + 4 * i],                                  \
      _ZGVbN2v_cos(input2_value##i));

/*Call 1 AVX or AVX function for 4 doubles*/
#define AVX_SINCOS_4_offset(n) AVX_SINCOS_4_offset_TMP(n)
#define AVX_SINCOS_4_offset_TMP(n)                                            \
  __m256d input4_value_##n = _mm256_loadu_pd(&input_array[*array_index + n]); \
  _mm256_storeu_pd(                                                           \
      &result_array[*array_index + n],                                        \
      _ZGVdN4v_sin(input4_value_##n));                                        \
  _mm256_storeu_pd(                                                           \
      &result_array1[*array_index + n],                                       \
      _ZGVdN4v_cos(input4_value_##n));
