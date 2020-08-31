#define AVX_4(i, name) AVX_4_TMP(i, name)
#define AVX_4_TMP(i, name)                                                     \
  _mm256_storeu_pd(                                                            \
      &result_array[*array_index + i * 4],                                     \
      _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + i * 4])));

#define AVX_4__0
/*Call 1 AVX function for 4 doubles*/
#define AVX_4__1 AVX_4(0, AVX_NAME)
/*Call 2 AVX function for 4 doubles*/
#define AVX_4__2 AVX_4__1 AVX_4(1, AVX_NAME)
/*Call 3 AVX function for 4 doubles*/
#define AVX_4__3 AVX_4__2 AVX_4(2, AVX_NAME)
/*Call 4 AVX function for 4 doubles*/
#define AVX_4__4 AVX_4__3 AVX_4(3, AVX_NAME)

#define AVX_MASK_1                                                             \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000,                    \
                    0x0000000000000000, 0xffffffffffffffff)
#define AVX_MASK_2                                                             \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000,                    \
                    0xffffffffffffffff, 0xffffffffffffffff)
#define AVX_MASK_3                                                             \
  _mm256_set_epi64x(0x0000000000000000, 0xffffffffffffffff,                    \
                    0xffffffffffffffff, 0xffffffffffffffff)

/*For size = 4*i + (4-i)*/
#define AVX_4_mask4(i, name) AVX_4_mask4_TMP(i, name)
#define AVX_4_mask4_TMP(i, name)                                               \
  if ((size - 4 * i) == 1) {                                                   \
    AVX_4__##i _mm256_maskstore_pd(                                            \
        &result_array[*array_index + 4 * i], AVX_MASK_1,                       \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],      \
                                      AVX_MASK_1)));                           \
  } else if ((size - 4 * i) == 2) {                                            \
    AVX_4__##i _mm256_maskstore_pd(                                            \
        &result_array[*array_index + 4 * i], AVX_MASK_2,                       \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],      \
                                      AVX_MASK_2)));                           \
  } else if ((size - 4 * i) == 3) {                                            \
    AVX_4__##i _mm256_maskstore_pd(                                            \
        &result_array[*array_index + 4 * i], AVX_MASK_3,                       \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],      \
                                      AVX_MASK_3)));                           \
  }

/*For size = 4*i + (2-i)*/
#define AVX_4_mask2(i, name) AVX_4_mask2_TMP(i, name)
#define AVX_4_mask2_TMP(i, name)                                               \
  AVX_4__##i _mm_store_sd(                                                     \
      &result_array[*array_index + 4 * i],                                     \
      _ZGV##name(_mm_load_sd(&input_array[*array_index + 4 * i])));
