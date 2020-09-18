/*For 8 floats*/
#define AVX2_8(i, name) AVX2_8_TMP(i, name)
#define AVX2_8_TMP(i, name)                  \
    _mm256_storeu_ps(                        \
        &result_array[*array_index + i * 8], \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8])));

#define AVX2_8__0
/*Call 1 AVX2 function for 8 floats*/
#define AVX2_8__1 AVX2_8(0, AVX2_NAME)
/*Call 2 AVX2 function for 8 floats*/
#define AVX2_8__2 AVX2_8__1 AVX2_8(1, AVX2_NAME)
/*Call 3 AVX2 function for 8 floats*/
#define AVX2_8__3 AVX2_8__2 AVX2_8(2, AVX2_NAME)
/*Call 4 AVX2 function for 8 floats*/
#define AVX2_8__4 AVX2_8__3 AVX2_8(3, AVX2_NAME)

#define AVX2_MASK_1                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0x00000000, 0xffffffff)
#define AVX2_MASK_2                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0xffffffff, 0xffffffff)
#define AVX2_MASK_3                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX2_MASK_4                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX2_MASK_5                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX2_MASK_6                                                              \
    _mm256_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX2_MASK_7                                                              \
    _mm256_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (8-i)*/
#define AVX2_8_mask8(i, name) AVX2_8_mask8_TMP(i, name)
#define AVX2_8_mask8_TMP(i, name)                                             \
    if ((size - 8 * i) == 1)                                                  \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_1,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_1)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 2)                                             \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_2,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_2)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 3)                                             \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_3,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_3)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 4)                                             \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_4,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_4)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 5)                                             \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_5,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_5)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 6)                                             \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_6,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_6)));                     \
    }                                                                         \
    else if ((size - 8 * i) == 7)                                             \
    {                                                                         \
        AVX2_8__##i _mm256_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK_7,                 \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i], \
                                          AVX2_MASK_7)));                     \
    }

#define AVX2_MASK4_1 \
    _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX2_MASK4_2 \
    _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX2_MASK4_3 \
    _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (4-i)*/
#define AVX2_8_mask4(i, name) AVX2_8_mask4_TMP(i, name)
#define AVX2_8_mask4_TMP(i, name)                                          \
    if ((size - 8 * i) == 1)                                               \
    {                                                                      \
        AVX2_8__##i _mm_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK4_1,             \
            _ZGV##name(_mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                       AVX2_MASK4_1)));                    \
    }                                                                      \
    else if ((size - 8 * i) == 2)                                          \
    {                                                                      \
        AVX2_8__##i _mm_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK4_2,             \
            _ZGV##name(_mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                       AVX2_MASK4_2)));                    \
    }                                                                      \
    else if ((size - 8 * i) == 3)                                          \
    {                                                                      \
        AVX2_8__##i _mm_maskstore_ps(                                      \
            &result_array[*array_index + 8 * i], AVX2_MASK4_3,             \
            _ZGV##name(_mm_maskload_ps(&input_array[*array_index + 8 * i], \
                                       AVX2_MASK4_3)));                    \
    }
