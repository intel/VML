#define PRE_HOOK_OP(pre_hook, pre_args)                \
if(pre_hook)                                           \
        pre_hook(pre_args); 

#define POST_HOOK_OP(post_hook, post_args)             \
if(post_hook)                                          \
        post_hook(post_args);

#undef AVX512_16_TMP
/*For 16 floats*/
#define AVX512_16(i, name) AVX512_16_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_16_TMP(i, name)                                            \
    _mm512_storeu_ps(                                                         \
        &result_array[*array_index + i * 16],                                 \
        _ZGV##name(_mm512_set1_ps(input_value),                                \
                   _mm512_loadu_ps(&input_array[*array_index + i * 16])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_16_TMP(i, name)                                            \
    _mm512_storeu_ps(                                                         \
        &result_array[*array_index + i * 16],                                 \
        _ZGV##name(_mm512_loadu_ps(&input_array[*array_index + i * 16]),      \
                   _mm512_set1_ps(input_value)));
    #else
    #define AVX512_16_TMP(i, name)                                            \
    _mm512_storeu_ps(                                                         \
        &result_array[*array_index + i * 16],                                 \
        _ZGV##name(_mm512_loadu_ps(&input_array[*array_index + i * 16]),      \
                   _mm512_loadu_ps(&input_array1[*array_index + i * 16])));
    #endif
#elif defined(SINCOS)
#define AVX512_16_TMP(i, name)                                                      \
    __m512 input16_value##i = _mm512_loadu_ps(&input_array[*array_index + i * 16]); \
    _mm512_storeu_ps(                                                               \
        &result_array[*array_index + i * 16],                                       \
        _ZGVeN16v_sinf(input16_value##i));                                          \
    _mm512_storeu_ps(                                                               \
        &result_array1[*array_index + i * 16],                                      \
        _ZGVeN16v_cosf(input16_value##i));
#else
#define AVX512_16_TMP(i, name)                                            \
    _mm512_storeu_ps(                                                     \
        &result_array[*array_index + i * 16],                             \
        _ZGV##name(_mm512_loadu_ps(&input_array[*array_index + i * 16])));
#endif
    
#define AVX512_16_ops(OP1, OP2, i, name)                              \
OP1                                                                  \
AVX512_16(i, name)                                                    \
OP2

#define AVX512_16__0_ops(OP1, OP2, name)
/*Call 1 AVX512 function for 16 floats*/
#define AVX512_16__1_ops(OP1, OP2, name) AVX512_16_ops(OP1, OP2, 0, name)
/*Call 2 AVX512 function for 16 floats*/
#define AVX512_16__2_ops(OP1, OP2, name) \
    AVX512_16__1_ops(OP1, OP2, name)     \
    AVX512_16_ops(OP1, OP2, 1, name)
/*Call 3 AVX512 function for 16 float*/
#define AVX512_16__3_ops(OP1, OP2, name) \
    AVX512_16__2_ops(OP1, OP2, name)     \
    AVX512_16_ops(OP1, OP2, 2, name)
/*Call 4 AVX512 function for 16 floats*/
#define AVX512_16__4_ops(OP1, OP2, name) \
    AVX512_16__3_ops(OP1, OP2, name)     \
    AVX512_16_ops(OP1, OP2, 3, name)

/*For size = 16*i + (16-i)*/
#undef AVX512_16_mask16_TMP
#define AVX512_16_mask16(i, name) AVX512_16_mask16_TMP(i, name)
#if defined(VV)
#if defined(SCALAR_ARRAY)
    #define AVX512_16_mask16_TMP(i, name)                                      \
    unsigned short tail_mask_uint =                                            \
        (((unsigned short)0xffff) >> (16 - size + 16 * i));                    \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint);                     \
    _mm512_mask_storeu_ps(                                                     \
        &result_array[*array_index + 16 * i], tail_mask,                       \
        _ZGV##name(_mm512_set1_ps(input_value),                                \
                   _mm512_maskz_loadu_ps(tail_mask,                            \
                                         &input_array[*array_index + 16 * i])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_16_mask16_TMP(i, name)                                      \
    unsigned short tail_mask_uint =                                            \
        (((unsigned short)0xffff) >> (16 - size + 16 * i));                    \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint);                     \
    _mm512_mask_storeu_ps(                                                     \
        &result_array[*array_index + 16 * i], tail_mask,                       \
        _ZGV##name(_mm512_maskz_loadu_ps(tail_mask,                            \
                                         &input_array[*array_index + 16 * i]), \
                   _mm512_set1_ps(input_value)));
    #else
    #define AVX512_16_mask16_TMP(i, name)                                      \
    unsigned short tail_mask_uint =                                            \
        (((unsigned short)0xffff) >> (16 - size + 16 * i));                    \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint);                     \
    _mm512_mask_storeu_ps(                                                     \
        &result_array[*array_index + 16 * i], tail_mask,                       \
        _ZGV##name(_mm512_maskz_loadu_ps(tail_mask,                            \
                                         &input_array[*array_index + 16 * i]), \
                   _mm512_maskz_loadu_ps(tail_mask,                            \
                                         &input_array1[*array_index + 16 * i])));
    #endif
#elif defined(SINCOS)
#define AVX512_16_mask16_TMP(i, name)                                                          \
    unsigned short tail_mask_uint =                                                            \
        (((unsigned short)0xffff) >> (16 - size + 16 * i));                                    \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint);                                     \
    __m512 input16_mask_value##i = _mm512_maskz_loadu_ps(tail_mask,                            \
                                                         &input_array[*array_index + 16 * i]); \
    _mm512_mask_storeu_ps(&result_array[*array_index + 16 * i], tail_mask,                     \
                          _ZGVeN16v_sinf(input16_mask_value##i));                              \
    _mm512_mask_storeu_ps(&result_array1[*array_index + 16 * i], tail_mask,                    \
                          _ZGVeN16v_cosf(input16_mask_value##i));
#else
#define AVX512_16_mask16_TMP(i, name)                       \
    unsigned short tail_mask_uint =                         \
        (((unsigned short)0xffff) >> (16 - size + 16 * i)); \
    __mmask16 tail_mask = *((__mmask16 *)&tail_mask_uint);  \
    _mm512_mask_storeu_ps(                                  \
        &result_array[*array_index + 16 * i], tail_mask,    \
        _ZGV##name(_mm512_maskz_loadu_ps(tail_mask,         \
                   &input_array[*array_index + 16 * i])));
#endif

#define AVX512_16_mask16_ops(OP1, OP2, i, name)                               \
    AVX512_16__##i##_ops(OP1, OP2, name)                                      \
    OP1                                                                       \
    AVX512_16_mask16(i, name)                                                 \
    OP2

/*For size = 16*i + (8-i)*/
#undef AVX512_16_mask8_TMP
#define AVX512_16_mask8(i, name1, name2) AVX512_16_mask8_TMP(i, name1, name2)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_16_mask8_TMP(i, name1, name2)                                \
    unsigned char tail_mask_uint =                                              \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                         \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                        \
    _mm256_mask_storeu_ps(                                                      \
        &result_array[*array_index + 16 * i], tail_mask,                        \
        _ZGV##name2(_mm256_set1_ps(input_value),                                \
                    _mm256_maskz_loadu_ps(tail_mask,                            \
                                          &input_array[*array_index + 16 * i])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_16_mask8_TMP(i, name1, name2)                                \
    unsigned char tail_mask_uint =                                              \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                         \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                        \
    _mm256_mask_storeu_ps(                                                      \
        &result_array[*array_index + 16 * i], tail_mask,                        \
        _ZGV##name2(_mm256_maskz_loadu_ps(tail_mask,                            \
                                          &input_array[*array_index + 16 * i]), \
                    _mm256_set1_ps(input_value)));
    #else
    #define AVX512_16_mask8_TMP(i, name1, name2)                                \
    unsigned char tail_mask_uint =                                              \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                         \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                        \
    _mm256_mask_storeu_ps(                                                      \
        &result_array[*array_index + 16 * i], tail_mask,                        \
        _ZGV##name2(_mm256_maskz_loadu_ps(tail_mask,                            \
                                          &input_array[*array_index + 16 * i]), \
                    _mm256_maskz_loadu_ps(tail_mask,                            \
                                          &input_array1[*array_index + 16 * i])));
    #endif
#elif defined(SINCOS)
#define AVX512_16_mask8_TMP(i, name1, name2)                                                  \
    unsigned char tail_mask_uint =                                                            \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                                       \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                      \
    __m256 input8_mask_value##i = _mm256_maskz_loadu_ps(tail_mask,                            \
                                                        &input_array[*array_index + 16 * i]); \
    _mm256_mask_storeu_ps(&result_array[*array_index + 16 * i], tail_mask,                    \
                          _ZGVdN8v_sinf(input8_mask_value##i));                               \
    _mm256_mask_storeu_ps(&result_array1[*array_index + 16 * i], tail_mask,                   \
                          _ZGVdN8v_cosf(input8_mask_value##i)); 
#else
#define AVX512_16_mask8_TMP(i, name1, name2)             \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 16 * i));  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    _mm256_mask_storeu_ps(                               \
        &result_array[*array_index + 16 * i], tail_mask, \
        _ZGV##name2(_mm256_maskz_loadu_ps(tail_mask,     \
                    &input_array[*array_index + 16 * i])));
#endif

#define AVX512_16_mask8_ops(OP1, OP2, i, name1, name2)                        \
    AVX512_16__##i##_ops(OP1, OP2, name1)                                     \
    OP1                                                                       \
    AVX512_16_mask8(i, name1, name2)                                          \
    OP2

/*For size = 16*i + (4-i)*/
#undef AVX512_16_mask4_TMP
#define AVX512_16_mask4(i, name1, name2) AVX512_16_mask4_TMP(i, name1, name2)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_16_mask4_TMP(i, name1, name2)                             \
    unsigned char tail_mask_uint =                                           \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                      \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                     \
    _mm_mask_storeu_ps(                                                      \
        &result_array[*array_index + 16 * i], tail_mask,                     \
        _ZGV##name2(_mm_set1_ps(input_value),                                \
                    _mm_maskz_loadu_ps(tail_mask,                            \
                                       &input_array[*array_index + 16 * i])));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_16_mask4_TMP(i, name1, name2)                             \
    unsigned char tail_mask_uint =                                           \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                      \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                     \
    _mm_mask_storeu_ps(                                                      \
        &result_array[*array_index + 16 * i], tail_mask,                     \
        _ZGV##name2(_mm_maskz_loadu_ps(tail_mask,                            \
                                       &input_array[*array_index + 16 * i]), \
                    _mm_set1_ps(input_value)));
    #else
    #define AVX512_16_mask4_TMP(i, name1, name2)                             \
    unsigned char tail_mask_uint =                                           \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                      \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                     \
    _mm_mask_storeu_ps(                                                      \
        &result_array[*array_index + 16 * i], tail_mask,                     \
        _ZGV##name2(_mm_maskz_loadu_ps(tail_mask,                            \
                                       &input_array[*array_index + 16 * i]), \
                    _mm_maskz_loadu_ps(tail_mask,                            \
                                       &input_array1[*array_index + 16 * i])));
    #endif
#elif defined(SINCOS)
#define AVX512_16_mask4_TMP(i, name1, name2)                                               \
    unsigned char tail_mask_uint =                                                         \
        (((unsigned char)0xff) >> (8 - size + 16 * i));                                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                   \
    __m128 input4_mask_value##i = _mm_maskz_loadu_ps(tail_mask,                            \
                                                     &input_array[*array_index + 16 * i]); \
    _mm_mask_storeu_ps(                                                                    \
        &result_array[*array_index + 16 * i], tail_mask,                                   \
        _ZGVbN4v_sinf(input4_mask_value##i));                                              \
    _mm_mask_storeu_ps(                                                                    \
        &result_array1[*array_index + 16 * i], tail_mask,                                  \
        _ZGVbN4v_cosf(input4_mask_value##i));
#else
#define AVX512_16_mask4_TMP(i, name1, name2)             \
    unsigned char tail_mask_uint =                       \
        (((unsigned char)0xff) >> (8 - size + 16 * i));  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint); \
    _mm_mask_storeu_ps(                                  \
        &result_array[*array_index + 16 * i], tail_mask, \
        _ZGV##name2(_mm_maskz_loadu_ps(tail_mask,        \
                   &input_array[*array_index + 16 * i])));
#endif

#define AVX512_16_mask4_ops(OP1, OP2, i, name1, name2)                        \
    AVX512_16__##i##_ops(OP1, OP2, name1)                                     \
    OP1                                                                       \
    AVX512_16_mask4(i, name1, name2)                                          \
    OP2

/*For 8 floats*/
#undef AVX_8_TMP
#define AVX_8(i, name) AVX_8_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_8_TMP(i, name)                                          \
    _mm256_storeu_ps(                                                   \
        &result_array[*array_index + i * 8],                            \
        _ZGV##name(_mm256_set1_ps(input_value),                         \
                   _mm256_loadu_ps(&input_array[*array_index + i * 8])));
    #elif defined(ARRAY_SCALAR)
    #define AVX_8_TMP(i, name)                                          \
    _mm256_storeu_ps(                                                   \
        &result_array[*array_index + i * 8],                            \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8]), \
                   _mm256_set1_ps(input_value)));
    #else
    #define AVX_8_TMP(i, name)                                          \
    _mm256_storeu_ps(                                                   \
        &result_array[*array_index + i * 8],                            \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8]), \
                   _mm256_loadu_ps(&input_array1[*array_index + i * 8])));
    #endif
#elif defined(SINCOS)
#define AVX_8_TMP(i, name)                                                        \
    __m256 input8_value##i = _mm256_loadu_ps(&input_array[*array_index + i * 8]); \
    _mm256_storeu_ps(                                                             \
        &result_array[*array_index + i * 8],                                      \
        _ZGVdN8v_sinf(input8_value##i));                                          \
    _mm256_storeu_ps(                                                             \
        &result_array1[*array_index + i * 8],                                     \
        _ZGVdN8v_cosf(input8_value##i));
#else
#define AVX_8_TMP(i, name)                                                     \
    _mm256_storeu_ps(                                                          \
        &result_array[*array_index + i * 8],                                   \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8])));
#endif

#define AVX_8_ops(OP1, OP2, i, name)                               \
OP1                                                                \
AVX_8(i, name)                                                     \
OP2

#define AVX_8__0_ops(OP1, OP2, name)
/*Call 1 AVX function for 8 floats*/
#define AVX_8__1_ops(OP1, OP2, name) AVX_8_ops(OP1, OP2, 0, name)
/*Call 2 AVX function for 8 floats*/
#define AVX_8__2_ops(OP1, OP2, name) \
    AVX_8__1_ops(OP1, OP2,name)     \
    AVX_8_ops(OP1, OP2, 1, name)
/*Call 3 AVX function for 8 floats*/
#define AVX_8__3_ops(OP1, OP2, name) \
    AVX_8__2_ops(OP1, OP2, name)     \
    AVX_8_ops(OP1, OP2, 2, name)
/*Call 4 AVX function for 8 floats*/
#define AVX_8__4_ops(OP1, OP2, name) \
    AVX_8__3_ops(OP1, OP2, name)     \
    AVX_8_ops(OP1, OP2, 3, name)

#define AVX_MASKF_1                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0x00000000, 0xffffffff)
#define AVX_MASKF_2                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0xffffffff, 0xffffffff)
#define AVX_MASKF_3                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASKF_4                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASKF_5                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASKF_6                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASKF_7                                                              \
    _mm256_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (8-i)*/
#undef AVX_8_mask8_TMP
#define AVX_8_mask8(i, name) AVX_8_mask8_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_8_mask8_TMP(i, name)                                           \
    if ((size - 8 * i) == 1)                                                   \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_1,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_1)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 2)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_2,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_2)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 3)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_3,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_3)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 4)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_4,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_4)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 5)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_5,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_5)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 6)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_6,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_6)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 7)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_7,                  \
            _ZGV##name(_mm256_set1_ps(input_value),                            \
                       _mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_7)));                      \
    }
    #elif defined(ARRAY_SCALAR)
    #define AVX_8_mask8_TMP(i, name)                                           \
    if ((size - 8 * i) == 1)                                                   \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_1,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_1),                        \
                       _mm256_set1_ps(input_value)));                          \
    }                                                                          \
    else if ((size - 8 * i) == 2)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_2,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_2),                        \
                       _mm256_set1_ps(input_value)));                          \
    }                                                                          \
    else if ((size - 8 * i) == 3)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_3,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_3),                        \
                       _mm256_set1_ps(input_value)));                          \
    }                                                                          \
    else if ((size - 8 * i) == 4)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_4,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_4),                        \
                       _mm256_set1_ps(input_value)));                          \
    }                                                                          \
    else if ((size - 8 * i) == 5)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_5,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_5),                        \
                       _mm256_set1_ps(input_value)));                          \
    }                                                                          \
    else if ((size - 8 * i) == 6)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_6,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_6),                        \
                       _mm256_set1_ps(input_value)));                          \
    }                                                                          \
    else if ((size - 8 * i) == 7)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_7,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_7),                        \
                       _mm256_set1_ps(input_value)));                          \
    }
    #else
    #define AVX_8_mask8_TMP(i, name)                                           \
    if ((size - 8 * i) == 1)                                                   \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_1,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_1),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_1)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 2)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_2,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_2),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_2)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 3)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_3,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_3),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_3)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 4)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_4,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_4),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_4)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 5)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_5,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_5),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_5)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 6)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_6,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_6),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_6)));                      \
    }                                                                          \
    else if ((size - 8 * i) == 7)                                              \
    {                                                                          \
        _mm256_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF_7,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_MASKF_7),                        \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_MASKF_7)));                      \
    }
    #endif
#elif defined(SINCOS)
    #define AVX_8_mask8_TMP(i, name)                                                         \
    if ((size - 8 * i) == 1)                                                                 \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_1);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_1,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_1,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 2)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_2);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_2,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_2,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 3)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_3);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_3,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_3,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 4)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_4);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_4,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_4,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 5)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_5);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_5,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_5,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 6)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_6);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_6,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_6,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 7)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_MASKF_7);                       \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_MASKF_7,                                \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_MASKF_7,                               \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }
#else
#define AVX_8_mask8_TMP(i, name)                                              \
    if ((size - 8 * i) == 1)                                                  \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_1,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_1)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 2)                                             \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_2,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_2)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 3)                                             \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_3,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_3)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 4)                                             \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_4,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_4)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 5)                                             \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_5,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_5)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 6)                                             \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_6,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_6)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 7)                                             \
    {                                                                         \
        _mm256_maskstore_ps(                                                  \
            &result_array[*array_index + 8 * i], AVX_MASKF_7,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASKF_7)));                     \
    }
#endif

#define AVX_8_mask8_ops(OP1, OP2, i, name)                                 \
AVX_8__##i##_ops(OP1, OP2, name)                                           \
OP1                                                                        \
AVX_8_mask8(i, name)                                                       \
OP2

#define AVX_MASKF4_1 \
    _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_MASKF4_2 \
    _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_MASKF4_3 \
    _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (4-i)*/
#undef AVX_8_mask4_TMP
#define AVX_8_mask4(i, name1, name2) AVX_8_mask4_TMP(i, name1, name2)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_8_mask4_TMP(i, name1, name2)                                 \
    if ((size - 8 * i) == 1)                                                 \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_1,               \
            _ZGV##name2(_mm_set1_ps(input_value),                            \
                        _mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_1)));                     \
    }                                                                        \
    else if ((size - 8 * i) == 2)                                            \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_2,               \
            _ZGV##name2(_mm_set1_ps(input_value),                            \
                        _mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_2)));                     \
    }                                                                        \
    else if ((size - 8 * i) == 3)                                            \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_3,               \
            _ZGV##name2(_mm_set1_ps(input_value),                            \
                        _mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_3)));                     \
    }
    #elif defined(ARRAY_SCALAR)
    #define AVX_8_mask4_TMP(i, name1, name2)                                 \
    if ((size - 8 * i) == 1)                                                 \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_1,               \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_1),                       \
                        _mm_set1_ps(input_value)));                          \
    }                                                                        \
    else if ((size - 8 * i) == 2)                                            \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_2,               \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_2),                       \
                        _mm_set1_ps(input_value)));                          \
    }                                                                        \
    else if ((size - 8 * i) == 3)                                            \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_3,               \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_3),                       \
                        _mm_set1_ps(input_value)));                          \
    }
    #else
    #define AVX_8_mask4_TMP(i, name1, name2)                                 \
    if ((size - 8 * i) == 1)                                                 \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_1,               \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_1),                       \
                        _mm_maskload_ps(&input_array1[*array_index + 8 * i], \
                                        AVX_MASKF4_1)));                     \
    }                                                                        \
    else if ((size - 8 * i) == 2)                                            \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_2,               \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_2),                       \
                        _mm_maskload_ps(&input_array1[*array_index + 8 * i], \
                                        AVX_MASKF4_2)));                     \
    }                                                                        \
    else if ((size - 8 * i) == 3)                                            \
    {                                                                        \
        _mm_maskstore_ps(                                                    \
            &result_array[*array_index + 8 * i], AVX_MASKF4_3,               \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_MASKF4_3),                       \
                        _mm_maskload_ps(&input_array1[*array_index + 8 * i], \
                                        AVX_MASKF4_3)));                     \
    }
    #endif
#elif defined(SINCOS)
#define AVX_8_mask4_TMP(i, name1, name2)                                                  \
if ((size - 8 * i) == 1)                                                                  \
    {                                                                                     \
        __m128 input4_mask_value##i = _mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                                      AVX_MASKF4_1);                      \
        _mm_maskstore_ps(&result_array[*array_index + 8 * i], AVX_MASKF4_1,               \
                         _ZGVbN4v_sinf(input4_mask_value##i));                            \
        _mm_maskstore_ps(&result_array1[*array_index + 8 * i], AVX_MASKF4_1,              \
                         _ZGVbN4v_cosf(input4_mask_value##i));                            \
    }                                                                                     \
    else if ((size - 8 * i) == 2)                                                         \
    {                                                                                     \
        __m128 input4_mask_value##i = _mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                                      AVX_MASKF4_2);                      \
        _mm_maskstore_ps(&result_array[*array_index + 8 * i], AVX_MASKF4_2,               \
                         _ZGVbN4v_sinf(input4_mask_value##i));                            \
        _mm_maskstore_ps(&result_array1[*array_index + 8 * i], AVX_MASKF4_2,              \
                         _ZGVbN4v_cosf(input4_mask_value##i));                            \
    }                                                                                     \
    else if ((size - 8 * i) == 3)                                                         \
    {                                                                                     \
        __m128 input4_mask_value##i = _mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                                      AVX_MASKF4_3);                      \
        _mm_maskstore_ps(&result_array[*array_index + 8 * i], AVX_MASKF4_3,               \
                         _ZGVbN4v_sinf(input4_mask_value##i));                            \
        _mm_maskstore_ps(&result_array1[*array_index + 8 * i], AVX_MASKF4_3,              \
                         _ZGVbN4v_cosf(input4_mask_value##i));                            \
    }
#else
#define AVX_8_mask4_TMP(i, name1, name2)                                    \
    if ((size - 8 * i) == 1)                                                \
    {                                                                       \
        _mm_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF4_1,              \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                        AVX_MASKF4_1)));                    \
    }                                                                       \
    else if ((size - 8 * i) == 2)                                           \
    {                                                                       \
        _mm_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF4_2,              \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                        AVX_MASKF4_2)));                    \
    }                                                                       \
    else if ((size - 8 * i) == 3)                                           \
    {                                                                       \
        _mm_maskstore_ps(                                                   \
            &result_array[*array_index + 8 * i], AVX_MASKF4_3,              \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                        AVX_MASKF4_3)));                    \
    }
#endif

#define AVX_8_mask4_ops(OP1, OP2, i, name1, name2)                  \
AVX_8__##i##_ops(OP1, OP2, name1)                                   \
OP1                                                                 \
AVX_8_mask4(i, name1, name2)                                        \
OP2

/*Call 1 AVX function for 8 floats*/
#undef AVX_8_offset_TMP
#define AVX_8_offset(n, name) AVX_8_offset_TMP(n, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_8_offset_TMP(n, name)                               \
    _mm256_storeu_ps(                                               \
        &result_array[*array_index + n],                            \
        _ZGV##name(_mm256_set1_ps(input_value),                     \
                   _mm256_loadu_ps(&input_array[*array_index + n])));
    #elif defined(ARRAY_SCALAR)
    #define AVX_8_offset_TMP(n, name)                               \
    _mm256_storeu_ps(                                               \
        &result_array[*array_index + n],                            \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + n]), \
                   _mm256_set1_ps(input_value)));
    #else
    #define AVX_8_offset_TMP(n, name)                               \
    _mm256_storeu_ps(                                               \
        &result_array[*array_index + n],                            \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + n]), \
                   _mm256_loadu_ps(&input_array1[*array_index + n])));
    #endif
#elif defined(SINCOS)
#define AVX_8_offset_TMP(n, name)                                             \
    __m256 input8_value##n = _mm256_loadu_ps(&input_array[*array_index + n]); \
    _mm256_storeu_ps(                                                         \
        &result_array[*array_index + n],                                      \
        _ZGVdN8v_sinf(input8_value##n));                                      \
    _mm256_storeu_ps(                                                         \
        &result_array1[*array_index + n],                                     \
        _ZGVdN8v_cosf(input8_value##n));
#else
#define AVX_8_offset_TMP(n, name)                                             \
    _mm256_storeu_ps(                                                         \
        &result_array[*array_index + n],                                      \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + n])));
#endif

#define AVX_8_offset_ops(OP1, OP2, n, name)                          \
OP1                                                                  \
AVX_8_offset(n, name)                                                \
OP2
    
/*For 4 floats*/
#undef SSE_4_TMP
#define SSE_4(i, name) SSE_4_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SSE_4_TMP(i, name)                                                     \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                             \
                  _ZGV##name(_mm_set1_ps(input_value),                             \
                             _mm_loadu_ps(&input_array[*array_index + i * 4])));
    #elif defined(ARRAY_SCALAR)
    #define SSE_4_TMP(i, name)                                                     \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                             \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + i * 4]),     \
                             _mm_set1_ps(input_value)));
    #else
    #define SSE_4_TMP(i, name)                                                     \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                             \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + i * 4]),     \
                             _mm_loadu_ps(&input_array1[*array_index + i * 4])));
    #endif
#elif defined(SINCOS)
#define SSE_4_TMP(i, name)                                                     \
    __m128 input4_value##i = _mm_loadu_ps(&input_array[*array_index + i * 4]); \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                         \
                  _ZGVbN4v_sinf(input4_value##i));                             \
    _mm_storeu_ps(&result_array1[*array_index + i * 4],                        \
                  _ZGVbN4v_cosf(input4_value##i));
#else
#define SSE_4_TMP(i, name)                                                     \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                         \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + i * 4])));
#endif

#define SSE_4_ops(OP1, OP2, i, name)                                      \
OP1                                                                       \
SSE_4(i, name)                                                            \
OP2

#define SSE_4__0_ops(OP1, OP2, name)
/*Call 1 SSE function for 4 floats*/
#define SSE_4__1_ops(OP1, OP2, name) SSE_4_ops(OP1, OP2, 0, name)
/*Call 2 SSE function for 4 floats*/
#define SSE_4__2_ops(OP1, OP2,name) SSE_4__1_ops(OP1, OP2,name) \
SSE_4_ops(OP1, OP2,1, name)
/*Call 3 SSE function for 4 floats*/
#define SSE_4__3_ops(OP1, OP2,name) SSE_4__2_ops(OP1, OP2,name) \
SSE_4_ops(OP1, OP2,2, name)
/*Call 4 SSE function for 4 floats*/
#define SSE_4__4_ops(OP1, OP2,name) SSE_4__3_ops(OP1, OP2,name) \
SSE_4_ops(OP1, OP2,3, name)

/*Call 1 SSE function for 4 floats*/
#undef SSE_4_offset_TMP
#define SSE_4_offset(n, name) SSE_4_offset_TMP(n, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SSE_4_offset_TMP(n, name)                                      \
    _mm_storeu_ps(&result_array[*array_index + n],                         \
                  _ZGV##name(_mm_set1_ps(input_value),                     \
                             _mm_loadu_ps(&input_array[*array_index + n])));
    #elif defined(ARRAY_SCALAR)
    #define SSE_4_offset_TMP(n, name)                                      \
    _mm_storeu_ps(&result_array[*array_index + n],                         \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + n]), \
                             _mm_set1_ps(input_value)));
    #else
    #define SSE_4_offset_TMP(n, name)                                      \
    _mm_storeu_ps(&result_array[*array_index + n],                         \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + n]), \
                             _mm_loadu_ps(&input_array1[*array_index + n])));
    #endif
#elif defined(SINCOS)
#define SSE_4_offset_TMP(n, name)                                          \
    __m128 input4_value##n = _mm_loadu_ps(&input_array[*array_index + n]); \
    _mm_storeu_ps(&result_array[*array_index + n],                         \
                  _ZGVbN4v_sinf(input4_value##n));                         \
    _mm_storeu_ps(&result_array1[*array_index + n],                        \
                  _ZGVbN4v_cosf(input4_value##n));
#else
#define SSE_4_offset_TMP(n, name)                                              \
    _mm_storeu_ps(&result_array[*array_index + n],                             \
                  _ZGV##name(_mm_loadu_ps(&input_array[*array_index + n])));
#endif

#define SSE_4_offset_ops(OP1, OP2, n, name)                                      \
OP1                                                                              \
SSE_4_offset(n, name)                                                            \
OP2

#undef SCALARF_1_TMP
#define SCALARF_1(i, name) SCALARF_1_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SCALARF_1_TMP(i, name)                                                 \
    result_array[*array_index+i] = ckl_##name(input_value,                         \
                                                        input_array[*array_index+i]);
    #elif defined(ARRAY_SCALAR)
    #define SCALARF_1_TMP(i, name)                                                 \
    result_array[*array_index+i] = ckl_##name(input_array[*array_index+i],         \
                                                        input_value);
    #else
    #define SCALARF_1_TMP(i, name)                                                 \
    result_array[*array_index+i] = ckl_##name(input_array[*array_index+i],         \
                                                        input_array1[*array_index+i]);
    #endif
#elif defined(SINCOS)
#define SCALARF_1_TMP(i, name)                                                 \
sincosf(input_array[*array_index+i], &result_array[*array_index+i],            \
                                               &result_array1[*array_index+i]);
#else
#define SCALARF_1_TMP(i, name)                                                 \
    result_array[*array_index+i] = ckl_##name(input_array[*array_index+i]);
#endif

#define SCALARF_1_ops(OP1, OP2, i, name)        \
OP1                                             \
SCALARF_1(i, name)                              \
OP2
