/*For 8 floats*/
#define AVX_vv_8(i, name) AVX_vv_8_TMP(i, name)
#define AVX_vv_8_TMP(i, name)                                           \
    _mm256_storeu_ps(                                                   \
        &result_array[*array_index + i * 8],                            \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + i * 8]), \
                   _mm256_loadu_ps(&input_array1[*array_index + i * 8])));

#define AVX_vv_8__0(name)
/*Call 1 AVX function for 8 floats*/
#define AVX_vv_8__1(name) AVX_vv_8(0, name)
/*Call 2 AVX function for 8 floats*/
#define AVX_vv_8__2(name) \
    AVX_vv_8__1(name)     \
        AVX_vv_8(1, name)
/*Call 3 AVX function for 8 floats*/
#define AVX_vv_8__3(name) \
    AVX_vv_8__2(name)     \
        AVX_vv_8(2, name)
/*Call 4 AVX function for 8 floats*/
#define AVX_vv_8__4(name) \
    AVX_vv_8__3(name)     \
        AVX_vv_8(3, name)
/*Call 5 AVX function for 8 floats*/
#define AVX_vv_8__5(name) \
    AVX_vv_8__4(name)     \
        AVX_vv_8(4, name)
/*Call 6 AVX function for 8 floats*/
#define AVX_vv_8__6(name) \
    AVX_vv_8__5(name)     \
        AVX_vv_8(5, name)
/*Call 7 AVX function for 8 floats*/
#define AVX_vv_8__7(name) \
    AVX_vv_8__6(name)     \
        AVX_vv_8(6, name)
/*Call 8 AVX function for 8 floats*/
#define AVX_vv_8__8(name) \
    AVX_vv_8__7(name)     \
        AVX_vv_8(7, name)

#define AVX_vv_MASKF_1                                                           \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0x00000000, 0xffffffff)
#define AVX_vv_MASKF_2                                                           \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0x00000000, 0xffffffff, 0xffffffff)
#define AVX_vv_MASKF_3                                                           \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_vv_MASKF_4                                                           \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_vv_MASKF_5                                                           \
    _mm256_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_vv_MASKF_6                                                           \
    _mm256_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)
#define AVX_vv_MASKF_7                                                           \
    _mm256_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, \
                     0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (8-i)*/
#define AVX_vv_8_mask8(i, name) AVX_vv_8_mask8_TMP(i, name)
#define AVX_vv_8_mask8_TMP(i, name)                                            \
    if ((size - 8 * i) == 1)                                                   \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_1,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_1),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_1)));                   \
    }                                                                          \
    else if ((size - 8 * i) == 2)                                              \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_2,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_2),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_2)));                   \
    }                                                                          \
    else if ((size - 8 * i) == 3)                                              \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_3,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_3),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_3)));                   \
    }                                                                          \
    else if ((size - 8 * i) == 4)                                              \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_4,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_4),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_4)));                   \
    }                                                                          \
    else if ((size - 8 * i) == 5)                                              \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_5,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_5),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_5)));                   \
    }                                                                          \
    else if ((size - 8 * i) == 6)                                              \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_6,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_6),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_6)));                   \
    }                                                                          \
    else if ((size - 8 * i) == 7)                                              \
    {                                                                          \
        AVX_vv_8__##i(name) _mm256_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF_7,               \
            _ZGV##name(_mm256_maskload_ps(&input_array[*array_index + 8 * i],  \
                                          AVX_vv_MASKF_7),                     \
                       _mm256_maskload_ps(&input_array1[*array_index + 8 * i], \
                                          AVX_vv_MASKF_7)));                   \
    }

#define AVX_vv_MASKF4_1 \
    _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_vv_MASKF4_2 \
    _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_vv_MASKF4_3 \
    _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 8*i + (4-i)*/
#define AVX_vv_8_mask4(i, name1, name2) AVX_vv_8_mask4_TMP(i, name1, name2)
#define AVX_vv_8_mask4_TMP(i, name1, name2)                                  \
    if ((size - 8 * i) == 1)                                                 \
    {                                                                        \
        AVX_vv_8__##i(name1) _mm_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF4_1,            \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_vv_MASKF4_1),                    \
                        _mm_maskload_ps(&input_array1[*array_index + 8 * i], \
                                        AVX_vv_MASKF4_1)));                  \
    }                                                                        \
    else if ((size - 8 * i) == 2)                                            \
    {                                                                        \
        AVX_vv_8__##i(name1) _mm_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF4_2,            \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_vv_MASKF4_2),                    \
                        _mm_maskload_ps(&input_array1[*array_index + 8 * i], \
                                        AVX_vv_MASKF4_2)));                  \
    }                                                                        \
    else if ((size - 8 * i) == 3)                                            \
    {                                                                        \
        AVX_vv_8__##i(name1) _mm_maskstore_ps(                               \
            &result_array[*array_index + 8 * i], AVX_vv_MASKF4_3,            \
            _ZGV##name2(_mm_maskload_ps(&input_array[*array_index + 8 * i],  \
                                        AVX_vv_MASKF4_3),                    \
                        _mm_maskload_ps(&input_array1[*array_index + 8 * i], \
                                        AVX_vv_MASKF4_3)));                  \
    }

/*Call 1 AVX function for 8 floats*/
#define AVX_vv_8_offset(n, name) AVX_vv_8_offset_TMP(n, name)
#define AVX_vv_8_offset_TMP(n, name)                                \
    _mm256_storeu_ps(                                               \
        &result_array[*array_index + n],                            \
        _ZGV##name(_mm256_loadu_ps(&input_array[*array_index + n]), \
                   _mm256_loadu_ps(&input_array1[*array_index + n])));
