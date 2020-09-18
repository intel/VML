/*For 8 floats*/
#define AVX_8(i, name) AVX_8_TMP(i, name)
#define AVX_8_TMP(i, name)                   \
    _mm256_storeu_ps(                        \
        &result_array[*array_index + i * 8], \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8])));

#define AVX_8__0
/*Call 1 AVX function for 8 floats*/
#define AVX_8__1 AVX_8(0, AVX_NAME)
/*Call 2 AVX function for 8 floats*/
#define AVX_8__2 AVX_8__1 AVX_8(1, AVX_NAME)
/*Call 3 AVX function for 8 floats*/
#define AVX_8__3 AVX_8__2 AVX_8(2, AVX_NAME)
/*Call 4 AVX function for 8 floats*/
#define AVX_8__4 AVX_8__3 AVX_8(3, AVX_NAME)

/*Call 1 AVX or AVX function for 8 floats*/
#define AVX_8_offset(n, name) AVX_8_offset_TMP(n, name)
#define AVX_8_offset_TMP(n, name)        \
    _mm256_storeu_ps(                    \
        &result_array[*array_index + n], \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + n])));

#define AVX_MASK_1                                                               \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0x00000000, 0xffffffff)
#define AVX_MASK_2                                                               \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0xffffffff, 0xffffffff)
#define AVX_MASK_3                                                               \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASK_4                                                               \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASK_5                                                               \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASK_6                                                               \
    _mm256_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_MASK_7                                                               \
    _mm256_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (8-i)*/
#define AVX_8_mask8(i, name) AVX_8_mask8_TMP(i, name)
#define AVX_8_mask8_TMP(i, name)                                              \
    if ((size - 8 * i) == 1)                                                  \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_1,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_1)));                      \
    }                                                                         \
    else if ((size - 8 * i) == 2)                                             \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_2,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_2)));                      \
    }                                                                         \
    else if ((size - 8 * i) == 3)                                             \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_3,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_3)));                      \
    }                                                                         \
    else if ((size - 8 * i) == 4)                                             \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_4,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_4)));                      \
    }                                                                         \
    else if ((size - 8 * i) == 5)                                             \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_5,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_5)));                      \
    }                                                                         \
    else if ((size - 8 * i) == 6)                                             \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_6,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_6)));                      \
    }                                                                         \
    else if ((size - 8 * i) == 7)                                             \
    {                                                                         \
        AVX_8__##i _mm256_maskstore_ps(                                       \
            &result_array[*array_index + 8 * i], AVX_MASK_7,                  \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX_MASK_7)));                      \
    }
