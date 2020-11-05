/*For 16 floats*/
#define AVX512_SINCOSF_16(i) AVX512_SINCOSF_16_TMP(i)
#define AVX512_SINCOSF_16_TMP(i)                                                    \
    __m512 input16_value##i = _mm512_loadu_ps(&input_array[*array_index + i * 16]); \
    _mm512_storeu_ps(                                                               \
        &result_array[*array_index + i * 16],                                       \
        _ZGVeN16v_sinf(input16_value##i));                                          \
    _mm512_storeu_ps(                                                               \
        &result_array1[*array_index + i * 16],                                      \
        _ZGVeN16v_cosf(input16_value##i));

#define AVX512_SINCOSF_16__0
/*Call 1 AVX512 function for 16 floats*/
#define AVX512_SINCOSF_16__1 AVX512_SINCOSF_16(0)
/*Call 2 AVX512 function for 16 floats*/
#define AVX512_SINCOSF_16__2 \
    AVX512_SINCOSF_16__1     \
    AVX512_SINCOSF_16(1)
/*Call 3 AVX512 function for 16 float*/
#define AVX512_SINCOSF_16__3 \
    AVX512_SINCOSF_16__2     \
    AVX512_SINCOSF_16(2)
/*Call 4 AVX512 function for 16 floats*/
#define AVX512_SINCOSF_16__4 \
    AVX512_SINCOSF_16__3     \
    AVX512_SINCOSF_16(3)

/*For size = 16*i + (16-i)*/
#define AVX512_SINCOSF_16_mask16(i) AVX512_SINCOSF_16_mask16_TMP(i)
#define AVX512_SINCOSF_16_mask16_TMP(i)                                                        \
    unsigned short tail_mask_uint =                                                            \
        (((unsigned short)0xffff) >> (16 - size + 16 * i));                                    \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint);                                     \
    AVX512_SINCOSF_16__##i;                                                                    \
    __m512 input16_mask_value##i = _mm512_maskz_loadu_ps(tail_mask,                            \
                                                         &input_array[*array_index + 16 * i]); \
    _mm512_mask_storeu_ps(&result_array[*array_index + 16 * i], tail_mask,                     \
                          _ZGVeN16v_sinf(input16_mask_value##i));                              \
    _mm512_mask_storeu_ps(&result_array1[*array_index + 16 * i], tail_mask,                    \
                          _ZGVeN16v_cosf(input16_mask_value##i));

/*For size = 16*i + (8-i)*/
#define AVX512_SINCOSF_16_mask8(i) AVX512_SINCOSF_16_mask8_TMP(i)
#define AVX512_SINCOSF_16_mask8_TMP(i)                                                        \
    unsigned char tail_mask_uint =                                                            \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                                       \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                      \
    AVX512_SINCOSF_16__##i;                                                                   \
    __m256 input8_mask_value##i = _mm256_maskz_loadu_ps(tail_mask,                            \
                                                        &input_array[*array_index + 16 * i]); \
    _mm256_mask_storeu_ps(&result_array[*array_index + 16 * i], tail_mask,                    \
                          _ZGVdN8v_sinf(input8_mask_value##i));                               \
    _mm256_mask_storeu_ps(&result_array1[*array_index + 16 * i], tail_mask,                   \
                          _ZGVdN8v_cosf(input8_mask_value##i));

/*For size = 16*i + (4-i)*/
#define AVX512_SINCOSF_16_mask4(i) AVX512_SINCOSF_16_mask4_TMP(i)
#define AVX512_SINCOSF_16_mask4_TMP(i)                                                     \
    unsigned char tail_mask_uint =                                                         \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                   \
    AVX512_SINCOSF_16__##i;                                                                \
    __m128 input4_mask_value##i = _mm_maskz_loadu_ps(tail_mask,                            \
                                                     &input_array[*array_index + 16 * i]); \
    _mm_mask_storeu_ps(                                                                    \
        &result_array[*array_index + 16 * i], tail_mask,                                   \
        _ZGVbN4v_sinf(input4_mask_value##i));                                              \
    _mm_mask_storeu_ps(                                                                    \
        &result_array1[*array_index + 16 * i], tail_mask,                                  \
        _ZGVbN4v_cosf(input4_mask_value##i));
