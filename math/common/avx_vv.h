#define AVX_vv_4(i, name) AVX_vv_4_TMP(i, name)
#define AVX_vv_4_TMP(i, name)                                         \
  _mm256_storeu_pd(                                                   \
      &result_array[*array_index + i * 4],                            \
      _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + i * 4]), \
                 _mm256_loadu_pd(&input_array1[*array_index + i * 4])));

#define AVX_vv_4__0(name)
/*Call 1 AVX function for 4 doubles*/
#define AVX_vv_4__1(name) AVX_vv_4(0, name)
/*Call 2 AVX function for 4 doubles*/
#define AVX_vv_4__2(name) \
  AVX_vv_4__1(name)       \
      AVX_vv_4(1, name)
/*Call 3 AVX function for 4 doubles*/
#define AVX_vv_4__3(name) \
  AVX_vv_4__2(name)       \
      AVX_vv_4(2, name)
/*Call 4 AVX function for 4 doubles*/
#define AVX_vv_4__4(name) \
  AVX_vv_4__3(name)       \
      AVX_vv_4(3, name)
/*Call 5 AVX function for 4 doubles*/
#define AVX_vv_4__5(name) \
  AVX_vv_4__4(name)       \
      AVX_vv_4(4, name)
/*Call 6 AVX function for 4 doubles*/
#define AVX_vv_4__6(name) \
  AVX_vv_4__5(name)       \
      AVX_vv_4(5, name)
/*Call 7 AVX function for 4 doubles*/
#define AVX_vv_4__7(name) \
  AVX_vv_4__6(name)       \
      AVX_vv_4(6, name)
/*Call 8 AVX function for 4 doubles*/
#define AVX_vv_4__8(name) \
  AVX_vv_4__7(name)       \
      AVX_vv_4(7, name)
/*Call 9 AVX function for 4 doubles*/
#define AVX_vv_4__9(name) \
  AVX_vv_4__8(name)       \
      AVX_vv_4(8, name)
/*Call 10 AVX function for 4 doubles*/
#define AVX_vv_4__10(name) \
  AVX_vv_4__9(name)        \
      AVX_vv_4(9, name)
/*Call 11 AVX function for 4 doubles*/
#define AVX_vv_4__11(name) \
  AVX_vv_4__10(name)       \
      AVX_vv_4(10, name)
/*Call 12 AVX function for 4 doubles*/
#define AVX_vv_4__12(name) \
  AVX_vv_4__11(name)       \
      AVX_vv_4(11, name)
/*Call 13 AVX function for 4 doubles*/
#define AVX_vv_4__13(name) \
  AVX_vv_4__12(name)       \
      AVX_vv_4(12, name)
/*Call 14 AVX function for 4 doubles*/
#define AVX_vv_4__14(name) \
  AVX_vv_4__13(name)       \
      AVX_vv_4(13, name)
/*Call 15 AVX function for 4 doubles*/
#define AVX_vv_4__14(name) \
  AVX_vv_4__13(name)       \
      AVX_vv_4(13, name)
/*Call 16 AVX function for 4 doubles*/
#define AVX_vv_4__15(name) \
  AVX_vv_4__14(name)       \
      AVX_vv_4(14, name)
/*Call 17 AVX function for 4 doubles*/
#define AVX_vv_4__16(name) \
  AVX_vv_4__15(name)       \
      AVX_vv_4(15, name)

#define AVX_vv_MASK_1                                       \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000, \
                    0x0000000000000000, 0xffffffffffffffff)
#define AVX_vv_MASK_2                                       \
  _mm256_set_epi64x(0x0000000000000000, 0x0000000000000000, \
                    0xffffffffffffffff, 0xffffffffffffffff)
#define AVX_vv_MASK_3                                       \
  _mm256_set_epi64x(0x0000000000000000, 0xffffffffffffffff, \
                    0xffffffffffffffff, 0xffffffffffffffff)

/*For size = 4*i + (4-i)*/
#define AVX_vv_4_mask4(i, name) AVX_vv_4_mask4_TMP(i, name)
#define AVX_vv_4_mask4_TMP(i, name)                                        \
  if ((size - 4 * i) == 1)                                                 \
  {                                                                        \
    AVX_vv_4__##i(name) _mm256_maskstore_pd(                               \
        &result_array[*array_index + 4 * i], AVX_vv_MASK_1,                \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                      AVX_vv_MASK_1),                      \
                   _mm256_maskload_pd(&input_array1[*array_index + 4 * i], \
                                      AVX_vv_MASK_1)));                    \
  }                                                                        \
  else if ((size - 4 * i) == 2)                                            \
  {                                                                        \
    AVX_vv_4__##i(name) _mm256_maskstore_pd(                               \
        &result_array[*array_index + 4 * i], AVX_vv_MASK_2,                \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                      AVX_vv_MASK_2),                      \
                   _mm256_maskload_pd(&input_array1[*array_index + 4 * i], \
                                      AVX_vv_MASK_2)));                    \
  }                                                                        \
  else if ((size - 4 * i) == 3)                                            \
  {                                                                        \
    AVX_vv_4__##i(name) _mm256_maskstore_pd(                               \
        &result_array[*array_index + 4 * i], AVX_vv_MASK_3,                \
        _ZGV##name(_mm256_maskload_pd(&input_array[*array_index + 4 * i],  \
                                      AVX_vv_MASK_3),                      \
                   _mm256_maskload_pd(&input_array1[*array_index + 4 * i], \
                                      AVX_vv_MASK_3)));                    \
  }

/*For size = 4*i + (2-i)*/
#define AVX_vv_4_mask2(i, name1, name2) AVX_vv_4_mask2_TMP(i, name1, name2)
#define AVX_vv_4_mask2_TMP(i, name1, name2)                        \
  AVX_vv_4__##i(name1) _mm_store_sd(                               \
      &result_array[*array_index + 4 * i],                         \
      _ZGV##name2(_mm_load_sd(&input_array[*array_index + 2 * i]), \
                  _mm_load_sd(&input_array1[*array_index + 2 * i])));

/*Call 1 AVX2 or AVX function for 4 doubles*/
#define AVX_vv_4_offset(n, name) AVX_vv_4_offset_TMP(n, name)
#define AVX_vv_4_offset_TMP(n, name)                              \
  _mm256_storeu_pd(                                               \
      &result_array[*array_index + n],                            \
      _ZGV##name(_mm256_loadu_pd(&input_array[*array_index + n]), \
                 _mm256_loadu_pd(&input_array1[*array_index + n])));
