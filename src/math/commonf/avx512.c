/*For 16 floats*/
#define AVX512_16(i, name) AVX512_16_TMP(i, name)
#define AVX512_16_TMP(i, name)                \
    _mm512_storeu_ps(                         \
        &result_array[*array_index + i * 16], \
        _ZGV##name(_mm512_loadu_ps(&input_array[*array_index + i * 16])));

#define AVX512_16__0
/*Call 1 AVX512 function for 16 floats*/
#define AVX512_16__1 AVX512_16(0, AVX512_NAME)
/*Call 2 AVX512 function for 16 floats*/
#define AVX512_16__2 AVX512_16__1 AVX512_16(1, AVX512_NAME)
/*Call 3 AVX512 function for 16 float*/
#define AVX512_16__3 AVX512_16__2 AVX512_16(2, AVX512_NAME)
/*Call 4 AVX512 function for 16 floats*/
#define AVX512_16__4 AVX512_16__3 AVX512_16(3, AVX512_NAME)

/*For size = 16*i + (16-i)*/
#define AVX512_16_mask16(i, name) AVX512_16_mask16_TMP(i, name)
#define AVX512_16_mask16_TMP(i, name)                      \
    unsigned int tail_mask_uint =                          \
        (((unsigned int)0xffff) >> (16 - size + 16 * i));  \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint); \
    AVX512_16__##i _mm512_mask_storeu_ps(                  \
        &result_array[*array_index + 16 * i], tail_mask,   \
        _ZGV##name(_mm512_maskz_loadu_ps(tail_mask,        \
                                         &input_array[*array_index + 16 * i])));
/*For size = 16*i + (8-i)*/
#define AVX512_16_mask8(i, name) AVX512_16_mask8_TMP(i, name)
#define AVX512_16_mask8_TMP(i, name)                     \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 16 * i));  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    AVX512_16__##i _mm256_mask_storeu_ps(                \
        &result_array[*array_index + 16 * i], tail_mask, \
        _ZGV##name(_mm256_maskz_loadu_ps(tail_mask,      \
                                         &input_array[*array_index + 16 * i])));

/*For size = 16*i + (4-i)*/
#define AVX512_16_mask4(i, name) AVX512_16_mask4_TMP(i, name)
#define AVX512_16_mask4_TMP(i, name)                     \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 16 * i));  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    AVX512_16__##i _mm_mask_storeu_ps(                   \
        &result_array[*array_index + 16 * i], tail_mask, \
        _ZGV##name(_mm_maskz_loadu_ps(tail_mask,         \
                                      &input_array[*array_index + 16 * i])));
