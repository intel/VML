/*For 8 doubles*/
#define AVX512_8(i, name) AVX512_8_TMP(i, name)
#define AVX512_8_TMP(i, name)                \
    _mm512_storeu_pd(                        \
        &result_array[*array_index + i * 8], \
        _ZGV##name(_mm512_loadu_pd(&input_array[*array_index + i * 8])));

#define AVX512_8__0(name)
/*Call 1 AVX512 function for 8 doubles*/
#define AVX512_8__1(name) AVX512_8(0, name)
/*Call 2 AVX512 function for 8 doubles*/
#define AVX512_8__2(name) \
    AVX512_8__1(name)     \
    AVX512_8(1, name)
/*Call 3 AVX512 function for 8 doubles*/
#define AVX512_8__3(name) \
    AVX512_8__2(name)     \
    AVX512_8(2, name)
/*Call 4 AVX512 function for 8 doubles*/
#define AVX512_8__4(name) \
    AVX512_8__3(name)     \
    AVX512_8(3, name)

/*For size = 8*i + (8-i)*/
#define AVX512_8_mask8(i, name) AVX512_8_mask8_TMP(i, name)
#define AVX512_8_mask8_TMP(i, name)                      \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 8 * i));   \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    AVX512_8__##i(name) _mm512_mask_storeu_pd(           \
        &result_array[*array_index + 8 * i], tail_mask,  \
        _ZGV##name(_mm512_maskz_loadu_pd(tail_mask,      \
                                         &input_array[*array_index + 8 * i])));
/*For size = 8*i + (4-i)*/
#define AVX512_8_mask4(i, name1, name2) AVX512_8_mask4_TMP(i, name1, name2)
#define AVX512_8_mask4_TMP(i, name1, name2)              \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 8 * i));   \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    AVX512_8__##i(name1) _mm256_mask_storeu_pd(          \
        &result_array[*array_index + 8 * i], tail_mask,  \
        _ZGV##name2(_mm256_maskz_loadu_pd(tail_mask,     \
                                          &input_array[*array_index + 8 * i])));
