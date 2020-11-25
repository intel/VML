/*For 8 floats*/
#define AVX_8(i, name) AVX_8_TMP(i, name)
#define AVX_8_TMP(i, name)                                                     \
    if(ckl_pre_hook)                                                           \
        ckl_pre_hook(ckl_pre_hook_args);                                       \
    _mm256_storeu_ps(                                                          \
        &result_array[*array_index + i * 8],                                   \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8])));      \
    if(ckl_post_hook)                                                          \
        ckl_post_hook(ckl_post_hook_args);

#define AVX_8__0(name)
/*Call 1 AVX function for 8 floats*/
#define AVX_8__1(name) AVX_8(0, name)
/*Call 2 AVX function for 8 floats*/
#define AVX_8__2(name) \
    AVX_8__1(name)     \
    AVX_8(1, name)
/*Call 3 AVX function for 8 floats*/
#define AVX_8__3(name) \
    AVX_8__2(name)     \
    AVX_8(2, name)
/*Call 4 AVX function for 8 floats*/
#define AVX_8__4(name) \
    AVX_8__3(name)     \
    AVX_8(3, name)

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
#define AVX_8_mask8(i, name) AVX_8_mask8_TMP(i, name)
#define AVX_8_mask8_TMP(i, name)                                              \
    AVX_8__##i(name)                                                          \
    if(ckl_pre_hook)                                                          \
        ckl_pre_hook(ckl_pre_hook_args);                                      \
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
    }                                                                         \
    if(ckl_post_hook)                                                         \
        ckl_post_hook(ckl_post_hook_args);

#define AVX_MASKF4_1 \
    _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_MASKF4_2 \
    _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_MASKF4_3 \
    _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (4-i)*/
#define AVX_8_mask4(i, name1, name2) AVX_8_mask4_TMP(i, name1, name2)
#define AVX_8_mask4_TMP(i, name1, name2)                                    \
    AVX_8__##i(name1)                                                       \
    if(ckl_pre_hook)                                                        \
        ckl_pre_hook(ckl_pre_hook_args);                                    \
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
    }                                                                       \
    if(ckl_post_hook)                                                       \
        ckl_post_hook(ckl_post_hook_args);

/*Call 1 AVX function for 8 floats*/
#define AVX_8_offset(n, name) AVX_8_offset_TMP(n, name)
#define AVX_8_offset_TMP(n, name)                                             \
    if(ckl_pre_hook)                                                          \
        ckl_pre_hook(ckl_pre_hook_args);                                      \
    _mm256_storeu_ps(                                                         \
        &result_array[*array_index + n],                                      \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + n])));         \
    if(ckl_post_hook)                                                         \
        ckl_post_hook(ckl_post_hook_args);
    
