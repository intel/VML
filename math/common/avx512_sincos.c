/*For 8 doubles*/
#define ADDR(i, n) (uint64_t) & result_array[*array_index + i * 8 + n]
#define ADDR1(i, n) (uint64_t) & result_array1[*array_index + i * 8 + n]

#define AVX512_8(i, name) AVX512_8_TMP(i, name)
#define AVX512_8_TMP(i, name)                                                                                                    \
    _ZGV##name(_mm512_loadu_pd(&input_array[*array_index + i * 8]),                                                              \
               _mm512_set_epi64(ADDR(i, 7), ADDR(i, 6), ADDR(i, 5), ADDR(i, 4), ADDR(i, 3), ADDR(i, 2), ADDR(i, 1), ADDR(i, 0)), \
               _mm512_set_epi64(ADDR1(i, 7), ADDR1(i, 6), ADDR1(i, 5), ADDR1(i, 4), ADDR1(i, 3), ADDR1(i, 2), ADDR1(i, 1), ADDR1(i, 0)));

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
#define AVX512_8_mask8_TMP(i, name)                                                                                                  \
    unsigned char tail_mask_uint =                                                                                                   \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                                                               \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                                                             \
    AVX512_8__##i                                                                                                                    \
        _ZGV##name(_mm512_maskz_loadu_pd(tail_mask,                                                                                  \
                                         &input_array[*array_index + 8 * i]),                                                        \
                   _mm512_set_epi64(ADDR(i, 7), ADDR(i, 6), ADDR(i, 5), ADDR(i, 4), ADDR(i, 3), ADDR(i, 2), ADDR(i, 1), ADDR(i, 0)), \
                   _mm512_set_epi64(ADDR1(i, 7), ADDR1(i, 6), ADDR1(i, 5), ADDR1(i, 4), ADDR1(i, 3), ADDR1(i, 2), ADDR1(i, 1), ADDR1(i, 0)));
/*For size = 8*i + (4-i)*/
#define AVX512_8_mask4(i, name) AVX512_8_mask4_TMP(i, name)
#define AVX512_8_mask4_TMP(i, name)                                                   \
    unsigned char tail_mask_uint =                                                    \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                              \
    &result_array[*array_index + 8 * i], tail_mask,                                   \
        _ZGV##name(_mm256_maskz_loadu_pd(tail_mask,                                   \
                                         &input_array[*array_index + 8 * i]),         \
                   _mm256_set_epi64x(ADDR(i, 3), ADDR(i, 2), ADDR(i, 1), ADDR(i, 0)), \
                   _mm256_set_epi64x(ADDR1(i, 3), ADDR1(i, 2), ADDR1(i, 1), ADDR1(i, 0)));
