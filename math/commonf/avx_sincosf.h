/*For 8 floats*/
#define AVX_SINCOSF_8(i) AVX_SINCOSF_8_TMP(i)
#define AVX_SINCOSF_8_TMP(i)                                                      \
    if(ckl_pre_hook)                                                              \
        ckl_pre_hook(ckl_pre_hook_args);                                          \
    __m256 input8_value##i = _mm256_loadu_ps(&input_array[*array_index + i * 8]); \
    _mm256_storeu_ps(                                                             \
        &result_array[*array_index + i * 8],                                      \
        _ZGVdN8v_sinf(input8_value##i));                                          \
    _mm256_storeu_ps(                                                             \
        &result_array1[*array_index + i * 8],                                     \
        _ZGVdN8v_cosf(input8_value##i));                                          \
    if(ckl_post_hook)                                                             \
        ckl_post_hook(ckl_post_hook_args);

#define AVX_SINCOSF_8__0
/*Call 1 AVX function for 8 floats*/
#define AVX_SINCOSF_8__1 AVX_SINCOSF_8(0)
/*Call 2 AVX function for 8 floats*/
#define AVX_SINCOSF_8__2 \
    AVX_SINCOSF_8__1     \
    AVX_SINCOSF_8(1)
/*Call 3 AVX function for 8 floats*/
#define AVX_SINCOSF_8__3 \
    AVX_SINCOSF_8__2     \
    AVX_SINCOSF_8(2)
/*Call 4 AVX function for 8 floats*/
#define AVX_SINCOSF_8__4 \
    AVX_SINCOSF_8__3     \
    AVX_SINCOSF_8(3)

#define AVX_SINCOSF_MASKF_1                                                      \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0x00000000, 0xffffffff)
#define AVX_SINCOSF_MASKF_2                                                      \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0xffffffff, 0xffffffff)
#define AVX_SINCOSF_MASKF_3                                                      \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_SINCOSF_MASKF_4                                                      \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_SINCOSF_MASKF_5                                                      \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_SINCOSF_MASKF_6                                                      \
    _mm256_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_SINCOSF_MASKF_7                                                      \
    _mm256_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (8-i)*/
#define AVX_SINCOSF_8_mask8(i) AVX_SINCOSF_8_mask8_TMP(i)
#define AVX_SINCOSF_8_mask8_TMP(i)                                                           \
    AVX_SINCOSF_8__##i;                                                                      \
    if(ckl_pre_hook)                                                                         \
        ckl_pre_hook(ckl_pre_hook_args);                                                     \
    if ((size - 8 * i) == 1)                                                                 \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_1);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_1,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_1,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 2)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_2);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_2,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_2,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 3)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_3);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_3,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_3,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 4)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_4);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_4,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_4,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 5)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_5);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_5,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_5,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 6)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_6);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_6,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_6,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    else if ((size - 8 * i) == 7)                                                            \
    {                                                                                        \
        __m256 input8_mask_value##i = _mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                                         AVX_SINCOSF_MASKF_7);               \
        _mm256_maskstore_ps(                                                                 \
            &result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF_7,                        \
            _ZGVdN8v_sinf(input8_mask_value##i));                                            \
        _mm256_maskstore_ps(                                                                 \
            &result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF_7,                       \
            _ZGVdN8v_cosf(input8_mask_value##i));                                            \
    }                                                                                        \
    if(ckl_post_hook)                                                                        \
        ckl_post_hook(ckl_post_hook_args);

#define AVX_SINCOSF_MASKF4_1 \
    _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_SINCOSF_MASKF4_2 \
    _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_SINCOSF_MASKF4_3 \
    _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (4-i)*/
#define AVX_SINCOSF_8_mask4(i) AVX_SINCOSF_8_mask4_TMP(i)
#define AVX_SINCOSF_8_mask4_TMP(i)                                                        \
    AVX_SINCOSF_8__##i;                                                                   \
    if(ckl_pre_hook)                                                                      \
        ckl_pre_hook(ckl_pre_hook_args);                                                  \
    if ((size - 8 * i) == 1)                                                              \
    {                                                                                     \
        __m128 input4_mask_value##i = _mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                                      AVX_SINCOSF_MASKF4_1);              \
        _mm_maskstore_ps(&result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF4_1,       \
                         _ZGVbN4v_sinf(input4_mask_value##i));                            \
        _mm_maskstore_ps(&result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF4_1,      \
                         _ZGVbN4v_cosf(input4_mask_value##i));                            \
    }                                                                                     \
    else if ((size - 8 * i) == 2)                                                         \
    {                                                                                     \
        __m128 input4_mask_value##i = _mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                                      AVX_SINCOSF_MASKF4_2);              \
        _mm_maskstore_ps(&result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF4_2,       \
                         _ZGVbN4v_sinf(input4_mask_value##i));                            \
        _mm_maskstore_ps(&result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF4_2,      \
                         _ZGVbN4v_cosf(input4_mask_value##i));                            \
    }                                                                                     \
    else if ((size - 8 * i) == 3)                                                         \
    {                                                                                     \
        __m128 input4_mask_value##i = _mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                                      AVX_SINCOSF_MASKF4_3);              \
        _mm_maskstore_ps(&result_array[*array_index + 8 * i], AVX_SINCOSF_MASKF4_3,       \
                         _ZGVbN4v_sinf(input4_mask_value##i));                            \
        _mm_maskstore_ps(&result_array1[*array_index + 8 * i], AVX_SINCOSF_MASKF4_3,      \
                         _ZGVbN4v_cosf(input4_mask_value##i));                            \
    }                                                                                     \
    if(ckl_post_hook)                                                                     \
        ckl_post_hook(ckl_post_hook_args);

/*Call 1 AVX function for 8 floats*/
#define AVX_SINCOSF_8_offset(n) AVX_SINCOSF_8_offset_TMP(n)
#define AVX_SINCOSF_8_offset_TMP(n)                                           \
    if(ckl_pre_hook)                                                          \
        ckl_pre_hook(ckl_pre_hook_args);                                      \
    __m256 input8_value##n = _mm256_loadu_ps(&input_array[*array_index + n]); \
    _mm256_storeu_ps(                                                         \
        &result_array[*array_index + n],                                      \
        _ZGVdN8v_sinf(input8_value##n));                                      \
    _mm256_storeu_ps(                                                         \
        &result_array1[*array_index + n],                                     \
        _ZGVdN8v_cosf(input8_value##n));                                      \
    if(ckl_post_hook)                                                         \
        ckl_post_hook(ckl_post_hook_args);
