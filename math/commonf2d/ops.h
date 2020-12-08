#define PRE_HOOK_OP(pre_hook, pre_args)                \
if(pre_hook)                                           \
        pre_hook(pre_args); 

#define POST_HOOK_OP(post_hook, post_args)             \
if(post_hook)                                          \
        post_hook(post_args);

/*For 8 doubles*/
#undef AVX512_f2d_8_TMP
#define AVX512_f2d_8(i, name) AVX512_f2d_8_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_f2d_8_TMP(i, name)                                                     \
    _mm256_storeu_ps(&result_array[*array_index + i * 8],                                 \
                     _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_set1_ps(input_value)),                                \
                     _mm512_cvtps_pd(_mm256_loadu_ps(                                     \
                     &input_array[*array_index + i * 8])))));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_f2d_8_TMP(i, name)                                                     \
    _mm256_storeu_ps(&result_array[*array_index + i * 8],                                 \
                     _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_loadu_ps(          \
                     &input_array[*array_index + i * 8])),                                \
                     _mm512_cvtps_pd(_mm256_set1_ps(input_value)))));
    #else
    #define AVX512_f2d_8_TMP(i, name)                                                     \
    _mm256_storeu_ps(&result_array[*array_index + i * 8],                                 \
                     _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_loadu_ps(          \
                     &input_array[*array_index + i * 8])),                                \
                     _mm512_cvtps_pd(_mm256_loadu_ps(                                     \
                     &input_array1[*array_index + i * 8])))));
    #endif
#else
#define AVX512_f2d_8_TMP(i, name)                                                \
    _mm256_storeu_ps(&result_array[*array_index + i * 8],                        \
                     _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_loadu_ps( \
                         &input_array[*array_index + i * 8])))));
#endif

#define AVX512_f2d_8_ops(OP1, OP2, i, name)                              \
OP1                                                                      \
AVX512_f2d_8(i, name)                                                    \
OP2

#define AVX512_f2d_8__0_ops(OP1, OP2, name)
/*Call 1 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__1_ops(OP1, OP2, name) AVX512_f2d_8_ops(OP1, OP2, 0, name)
/*Call 2 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__2_ops(OP1, OP2, name) \
    AVX512_f2d_8__1_ops(OP1, OP2, name)     \
        AVX512_f2d_8_ops(OP1, OP2, 1, name)
/*Call 3 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__3_ops(OP1, OP2, name) \
    AVX512_f2d_8__2_ops(OP1, OP2, name)     \
        AVX512_f2d_8_ops(OP1, OP2, 2, name)
/*Call 4 AVX512 function for 8 doubles*/
#define AVX512_f2d_8__4_ops(OP1, OP2, name) \
    AVX512_f2d_8__3_ops(OP1, OP2, name)     \
        AVX512_f2d_8_ops(OP1, OP2, 3, name)

/*For size = 8*i + (8-i)*/
#undef AVX512_f2d_8_mask8_TMP
#define AVX512_f2d_8_mask8(i, name) AVX512_f2d_8_mask8_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_f2d_8_mask8_TMP(i, name)                                             \
    unsigned char tail_mask_uint =                                                      \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                \
    _mm256_mask_storeu_ps(                                                              \
        &result_array[*array_index + 8 * i], tail_mask,                                 \
        _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_set1_ps(input_value)), \
                                   _mm512_cvtps_pd(_mm256_maskz_loadu_ps(               \
                                    tail_mask, &input_array[*array_index + 8 * i])))));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_f2d_8_mask8_TMP(i, name)                                             \
    unsigned char tail_mask_uint =                                                      \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                \
    _mm256_mask_storeu_ps(                                                              \
        &result_array[*array_index + 8 * i], tail_mask,                                 \
        _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_maskz_loadu_ps(               \
                                       tail_mask, &input_array[*array_index + 8 * i])), \
                                   _mm512_cvtps_pd(_mm256_set1_ps(input_value)))));
    #else
    #define AVX512_f2d_8_mask8_TMP(i, name)                                             \
    unsigned char tail_mask_uint =                                                      \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                \
    _mm256_mask_storeu_ps(                                                              \
        &result_array[*array_index + 8 * i], tail_mask,                                 \
        _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_maskz_loadu_ps(               \
                                       tail_mask, &input_array[*array_index + 8 * i])), \
                                   _mm512_cvtps_pd(_mm256_maskz_loadu_ps(               \
                                    tail_mask, &input_array1[*array_index + 8 * i])))));
    #endif
#else
#define AVX512_f2d_8_mask8_TMP(i, name)                                   \
    unsigned char tail_mask_uint =                                        \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                    \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                  \
    _mm256_mask_storeu_ps(                                                \
        &result_array[*array_index + 8 * i], tail_mask,                   \
        _mm512_cvtpd_ps(_ZGV##name(_mm512_cvtps_pd(_mm256_maskz_loadu_ps( \
            tail_mask, &input_array[*array_index + 8 * i])))));
#endif

#define AVX512_f2d_8_mask8_ops(OP1, OP2, i, name)                               \
    AVX512_f2d_8__##i##_ops(OP1, OP2, name)                                     \
    OP1                                                                         \
    AVX512_f2d_8_mask8(i, name)                                                 \
    OP2

/*For size = 8*i + (4-i)*/
#undef AVX512_f2d_8_mask4_TMP
#define AVX512_f2d_8_mask4(i, name1, name2) AVX512_f2d_8_mask4_TMP(i, name1, name2)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX512_f2d_8_mask4_TMP(i, name1, name2)                                      \
    unsigned char tail_mask_uint =                                                       \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                   \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                 \
    _mm_mask_storeu_ps(                                                                  \
        &result_array[*array_index + 8 * i], tail_mask,                                  \
        _mm256_cvtpd_ps(_ZGV##name2(_mm256_cvtps_pd(_mm256_set1_ps(input_value)),        \
                                    _mm256_cvtps_pd(_mm_maskz_loadu_ps(                  \
                                    tail_mask, &input_array[*array_index + 8 * i])))));
    #elif defined(ARRAY_SCALAR)
    #define AVX512_f2d_8_mask4_TMP(i, name1, name2)                                      \
    unsigned char tail_mask_uint =                                                       \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                   \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                 \
    _mm_mask_storeu_ps(                                                                  \
        &result_array[*array_index + 8 * i], tail_mask,                                  \
        _mm256_cvtpd_ps(_ZGV##name2(_mm256_cvtps_pd(_mm_maskz_loadu_ps(                  \
                                        tail_mask, &input_array[*array_index + 8 * i])), \
                                    _mm256_cvtps_pd(_mm256_set1_ps(input_value)))));
    #else
    #define AVX512_f2d_8_mask4_TMP(i, name1, name2)                                      \
    unsigned char tail_mask_uint =                                                       \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                                   \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                                 \
    _mm_mask_storeu_ps(                                                                  \
        &result_array[*array_index + 8 * i], tail_mask,                                  \
        _mm256_cvtpd_ps(_ZGV##name2(_mm256_cvtps_pd(_mm_maskz_loadu_ps(                  \
                                        tail_mask, &input_array[*array_index + 8 * i])), \
                                    _mm256_cvtps_pd(_mm_maskz_loadu_ps(                  \
                                    tail_mask, &input_array1[*array_index + 8 * i])))));
    #endif
#else
#define AVX512_f2d_8_mask4_TMP(i, name1, name2)                         \
    unsigned char tail_mask_uint =                                      \
        (((unsigned char)0xff) >> (8 - size + 8 * i));                  \
    __mmask8 tail_mask = *((__mmask8 *)&tail_mask_uint);                \
    _mm_mask_storeu_ps(                                                 \
        &result_array[*array_index + 8 * i], tail_mask,                 \
        _mm256_cvtpd_ps(_ZGV##name2(_mm256_cvtps_pd(_mm_maskz_loadu_ps( \
            tail_mask, &input_array[*array_index + 8 * i])))));
#endif

#define AVX512_f2d_8_mask4_ops(OP1, OP2, i, name)                               \
    AVX512_f2d_8__##i##_ops(OP1, OP2, name)                                     \
    OP1                                                                         \
    AVX512_f2d_8_mask4(i, name)                                                 \
    OP2

#undef AVX_f2d_4_TMP
#define AVX_f2d_4(i, name) AVX_f2d_4_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_f2d_4_TMP(i, name)                                            \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                        \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                   \
                _mm_set1_ps(input_value)),                                    \
                _mm256_cvtps_pd(                                              \
                _mm_loadu_ps(&input_array[*array_index + i * 4])))));
    #elif defined(ARRAY_SCALAR)
    #define AVX_f2d_4_TMP(i, name)                                            \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                        \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                   \
                _mm_loadu_ps(&input_array[*array_index + i * 4])),            \
                _mm256_cvtps_pd(                                              \
                _mm_set1_ps(input_value)))));
    #else
    #define AVX_f2d_4_TMP(i, name)                                            \
    _mm_storeu_ps(&result_array[*array_index + i * 4],                        \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                   \
                _mm_loadu_ps(&input_array[*array_index + i * 4])),            \
                _mm256_cvtps_pd(                                              \
                _mm_loadu_ps(&input_array1[*array_index + i * 4])))));
    #endif
#else
#define AVX_f2d_4_TMP(i, name)                                       \
  _mm_storeu_ps(&result_array[*array_index + i * 4],                 \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(          \
                _mm_loadu_ps(&input_array[*array_index + i * 4])))));
#endif

#define AVX_f2d_4_ops(OP1, OP2, i, name)                               \
OP1                                                                    \
AVX_f2d_4(i, name)                                                     \
OP2

#define AVX_f2d_4__0_ops(OP1, OP2, name)
/*Call 1 AVX function for 4 doubles*/
#define AVX_f2d_4__1_ops(OP1, OP2, name) AVX_f2d_4_ops(OP1, OP2, 0, name)
/*Call 2 AVX function for 4 doubles*/
#define AVX_f2d_4__2_ops(OP1, OP2, name) \
  AVX_f2d_4__1_ops(OP1, OP2, name)       \
      AVX_f2d_4_ops(OP1, OP2, 1, name)
/*Call 3 AVX function for 4 doubles*/
#define AVX_f2d_4__3_ops(OP1, OP2, name) \
  AVX_f2d_4__2_ops(OP1, OP2, name)       \
      AVX_f2d_4_ops(OP1, OP2, 2, name)
/*Call 4 AVX function for 4 doubles*/
#define AVX_f2d_4__4_ops(OP1, OP2, name) \
  AVX_f2d_4__3_ops(OP1, OP2, name)       \
      AVX_f2d_4_ops(OP1, OP2, 3, name)

#define AVX_f2d_MASKF2D_1 _mm_set_epi32(0x00000000, 0x00000000, 0x00000000, 0xffffffff)
#define AVX_f2d_MASKF2D_2 _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff)
#define AVX_f2d_MASKF2D_3 _mm_set_epi32(0x00000000, 0xffffffff, 0xffffffff, 0xffffffff)

/*For size = 4*i + (4-i)*/
#undef AVX_f2d_4_mask4_TMP
#define AVX_f2d_4_mask4(i, name) AVX_f2d_4_mask4_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_f2d_4_mask4_TMP(i, name)                                                                 \
    if ((size - 4 * i) == 1)                                                                             \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_set1_ps(input_value)),                        \
                                    _mm256_cvtps_pd(_mm_maskload_ps(                                     \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1)))));      \
    }                                                                                                    \
    else if ((size - 4 * i) == 2)                                                                        \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_set1_ps(input_value)),                        \
                                    _mm256_cvtps_pd(_mm_maskload_ps(                                     \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2)))));      \
    }                                                                                                    \
    else if ((size - 4 * i) == 3)                                                                        \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_set1_ps(input_value)),                        \
                                    _mm256_cvtps_pd(_mm_maskload_ps(                                     \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3)))));      \
    } 
    #elif defined(ARRAY_SCALAR)
    #define AVX_f2d_4_mask4_TMP(i, name)                                                                 \
    if ((size - 4 * i) == 1)                                                                             \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                  \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1)),         \
                                    _mm256_cvtps_pd(_mm_set1_ps(input_value)))));                        \
    }                                                                                                    \
    else if ((size - 4 * i) == 2)                                                                        \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                  \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2)),         \
                                    _mm256_cvtps_pd(_mm_set1_ps(input_value)))));                        \
    }                                                                                                    \
    else if ((size - 4 * i) == 3)                                                                        \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                  \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3)),         \
                                    _mm256_cvtps_pd(_mm_set1_ps(input_value)))));                        \
    } 
    #else
    #define AVX_f2d_4_mask4_TMP(i, name)                                                                 \
    if ((size - 4 * i) == 1)                                                                             \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                  \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1)),         \
                                    _mm256_cvtps_pd(_mm_maskload_ps(                                     \
                                        &input_array1[*array_index + 4 * i], AVX_f2d_MASKF2D_1)))));     \
    }                                                                                                    \
    else if ((size - 4 * i) == 2)                                                                        \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                  \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2)),         \
                                    _mm256_cvtps_pd(_mm_maskload_ps(                                     \
                                        &input_array1[*array_index + 4 * i], AVX_f2d_MASKF2D_2)))));     \
    }                                                                                                    \
    else if ((size - 4 * i) == 3)                                                                        \
    {                                                                                                    \
        _mm_maskstore_ps(                                                                                \
            &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3,                                      \
            _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(                                  \
                                        &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3)),         \
                                    _mm256_cvtps_pd(_mm_maskload_ps(                                     \
                                        &input_array1[*array_index + 4 * i], AVX_f2d_MASKF2D_3)))));     \
    } 
    #endif
#else
#define AVX_f2d_4_mask4_TMP(i, name)                                    \
  if ((size - 4 * i) == 1)                                              \
  {                                                                     \
    _mm_maskstore_ps(                                                   \
        &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1,         \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(     \
            &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_1))))); \
  }                                                                     \
  else if ((size - 4 * i) == 2)                                         \
  {                                                                     \
    _mm_maskstore_ps(                                                   \
        &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2,         \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(     \
            &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_2))))); \
  }                                                                     \
  else if ((size - 4 * i) == 3)                                         \
  {                                                                     \
     _mm_maskstore_ps(                                                  \
        &result_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3,         \
        _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(_mm_maskload_ps(     \
            &input_array[*array_index + 4 * i], AVX_f2d_MASKF2D_3))))); \
  }
#endif

#define AVX_f2d_4_mask4_ops(OP1, OP2, i, name)                               \
AVX_f2d_4__##i##_ops(OP1, OP2, name1)                                        \
OP1                                                                          \
AVX_f2d_4_mask4(i, name)                                                     \
OP2

/*Call 1 AVX function for 4 floats*/
#undef AVX_f2d_4_offset_TMP
#define AVX_f2d_4_offset(n, name) AVX_f2d_4_offset_TMP(n, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_f2d_4_offset_TMP(n, name)                                                        \
     _mm_storeu_ps(&result_array[*array_index + n],                                              \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                                      \
                                               _mm_set1_ps(input_value)),                        \
                                           _mm256_cvtps_pd(                                      \
                                               _mm_loadu_ps(&input_array[*array_index + n])))));
    #elif defined(ARRAY_SCALAR)
     #define AVX_f2d_4_offset_TMP(n, name)                                                        \
     _mm_storeu_ps(&result_array[*array_index + n],                                              \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                                      \
                                               _mm_loadu_ps(&input_array[*array_index + n])),    \
                                           _mm256_cvtps_pd(                                      \
                                               _mm_set1_ps(input_value)))));
    #else
     #define AVX_f2d_4_offset_TMP(n, name)                                                        \
     _mm_storeu_ps(&result_array[*array_index + n],                                              \
                _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(                                      \
                                               _mm_loadu_ps(&input_array[*array_index + n])),    \
                                           _mm256_cvtps_pd(                                      \
                                               _mm_loadu_ps(&input_array1[*array_index + n])))));
    #endif
#else
#define AVX_f2d_4_offset_TMP(n, name)                       \
  _mm_storeu_ps(&result_array[*array_index + n],            \
               _mm256_cvtpd_ps(_ZGV##name(_mm256_cvtps_pd(  \
               _mm_loadu_ps(&input_array[*array_index + n])))));
#endif

#define AVX_f2d_4_offset_ops(OP1, OP2, n, name) \
OP1                                             \
AVX_f2d_4_offset(n, name)                       \
OP2

#undef AVX_f2d_2_TMP
#define AVX_f2d_2(i, name) AVX_f2d_2_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define AVX_f2d_2_TMP(i, name)                                        \
    _mm_maskstore_ps(                                                     \
      &result_array[*array_index + i * 2],                                \
      _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff),      \
      _mm_cvtpd_ps(_ZGV##name(                                            \
          _mm_cvtps_pd(_mm_set1_ps(input_value)),                         \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])))));
    #elif defined(ARRAY_SCALAR)
    #define AVX_f2d_2_TMP(i, name)                                        \
    _mm_maskstore_ps(                                                     \
      &result_array[*array_index + i * 2],                                \
      _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff),      \
      _mm_cvtpd_ps(_ZGV##name(                                            \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])), \
          _mm_cvtps_pd(_mm_set1_ps(input_value)))));
    #else
    #define AVX_f2d_2_TMP(i, name)                                        \
    _mm_maskstore_ps(                                                     \
      &result_array[*array_index + i * 2],                                \
      _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff),      \
      _mm_cvtpd_ps(_ZGV##name(                                            \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])), \
          _mm_cvtps_pd(_mm_loadu_ps(&input_array1[*array_index + i * 2])))));
    #endif
#else
#define AVX_f2d_2_TMP(i, name)                                       \
  _mm_maskstore_ps(                                                  \
      &result_array[*array_index + i * 2],                           \
      _mm_set_epi32(0x00000000, 0x00000000, 0xffffffff, 0xffffffff), \
      _mm_cvtpd_ps(_ZGV##name(                                       \
      _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])))));
#endif

#define AVX_f2d_2_ops(OP1, OP2, i, name)            \
OP1                                                 \
AVX_f2d_2(i, name)                                  \
OP2

#define AVX_f2d_2__0_ops(OP1, OP2, name)
/*Call 1 SSE function for 2 doubles*/
#define AVX_f2d_2__1_ops(OP1, OP2, name) AVX_f2d_2_ops(OP1, OP2, 0, name)
/*Call 2 SSE function for 2 doubles*/
#define AVX_f2d_2__2_ops(OP1, OP2, name) \
  AVX_f2d_2__1_ops(OP1, OP2, name)       \
      AVX_f2d_2_ops(OP1, OP2, 1, name)
/*Call 3 SSE function for 2 doubles*/
#define AVX_f2d_2__3_ops(OP1, OP2, name) \
  AVX_f2d_2__2_ops(OP1, OP2, name)       \
      AVX_f2d_2_ops(OP1, OP2, 2, name)
/*Call 4 SSE function for 2 doubles*/
#define AVX_f2d_2__4_ops(OP1, OP2, name) \
  AVX_f2d_2__3_ops(OP1, OP2, name)       \
      AVX_f2d_2_ops(OP1, OP2, 3, name)

#undef SSE_f2d_2_TMP
#define SSE_f2d_2(i, name) SSE_f2d_2_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SSE_f2d_2_TMP(i, name)                                                               \
    _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]),                                \
                  _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(                                          \
                               _mm_set1_ps(input_value)),                                        \
                               _mm_cvtps_pd(_mm_loadu_ps(&input_array[*array_index + i * 2])))));
    #elif defined(ARRAY_SCALAR)
    #define SSE_f2d_2_TMP(i, name)                                                               \
    _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]),                                \
                  _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(                                          \
                               _mm_loadu_ps(&input_array[*array_index + i * 2])),                \
                               _mm_cvtps_pd(_mm_set1_ps(input_value)))));
    #else
    #define SSE_f2d_2_TMP(i, name)                                                               \
    _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]),                                \
                  _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(                                          \
                               _mm_loadu_ps(&input_array[*array_index + i * 2])),                \
                               _mm_cvtps_pd(_mm_loadu_ps(&input_array1[*array_index + i * 2])))));
    #endif
#elif defined(SINCOS)
    #define SSE_f2d_2_TMP(i, name)                                  \
    __m128d input2_f2d_value##i = _mm_cvtps_pd(                     \
        _mm_loadu_ps(&input_array[*array_index + i * 2]));          \
    _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]),   \
                  _mm_cvtpd_ps(_ZGVbN2v_sin(input2_f2d_value##i))); \
    _mm_storel_pi((__m64 *)(&result_array1[*array_index + i * 2]),  \
                  _mm_cvtpd_ps(_ZGVbN2v_cos(input2_f2d_value##i)));
#else
#define SSE_f2d_2_TMP(i, name)                                  \
  _mm_storel_pi((__m64 *)(&result_array[*array_index + i * 2]), \
                _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(           \
                _mm_loadu_ps(&input_array[*array_index + i * 2])))));
#endif

#define SSE_f2d_2_ops(OP1, OP2, i, name)     \
OP1                                          \
SSE_f2d_2(i, name)                           \
OP2

#define SSE_f2d_2__0_ops(OP1, OP2, name)
/*Call 1 SSE function for 2 doubles*/
#define SSE_f2d_2__1_ops(OP1, OP2, name) SSE_f2d_2_ops(OP1, OP2, 0, name)
/*Call 2 SSE function for 2 doubles*/
#define SSE_f2d_2__2_ops(OP1, OP2, name) SSE_f2d_2__1_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 1, name)
/*Call 3 SSE function for 2 doubles*/
#define SSE_f2d_2__3_ops(OP1, OP2, name) SSE_f2d_2__2_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 2, name)
/*Call 4 SSE function for 2 doubles*/
#define SSE_f2d_2__4_ops(OP1, OP2, name) SSE_f2d_2__3_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 3, name)
/*Call 5 SSE function for 2 doubles*/
#define SSE_f2d_2__5_ops(OP1, OP2, name) SSE_f2d_2__4_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 4, name)
/*Call 6 SSE function for 2 doubles*/
#define SSE_f2d_2__6_ops(OP1, OP2, name) SSE_f2d_2__5_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 5, name)
/*Call 7 SSE function for 2 doubles*/
#define SSE_f2d_2__7_ops(OP1, OP2, name) SSE_f2d_2__6_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 6, name)
/*Call 8 SSE function for 2 doubles*/
#define SSE_f2d_2__8_ops(OP1, OP2, name) SSE_f2d_2__7_ops(OP1, OP2, name) \
    SSE_f2d_2_ops(OP1, OP2, 7, name)

/*For size = 2*i + (2-i)*/
#undef SSE_f2d_2_mask2_TMP
#define SSE_f2d_2_mask2(i, name) SSE_f2d_2_mask2_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SSE_f2d_2_mask2_TMP(i, name)                                         \
    _mm_store_ss(&result_array[*array_index + 2 * i],                            \
                  _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(_set1_ps(input_value)),   \
                  _mm_cvtps_pd(_mm_load_ss(                                      \
                   &input_array[*array_index + 2 * i])))));
    #elif defined(ARRAY_SCALAR)
    #define SSE_f2d_2_mask2_TMP(i, name)                                         \
    _mm_store_ss(&result_array[*array_index + 2 * i],                            \
                  _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(_mm_load_ss(              \
                  &input_array[*array_index + 2 * i])),                          \
                  _mm_cvtps_pd(_set1_ps(input_value)))));
    #else
    #define SSE_f2d_2_mask2_TMP(i, name)                                         \
    _mm_store_ss(&result_array[*array_index + 2 * i],                            \
                  _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(_mm_load_ss(              \
                  &input_array[*array_index + 2 * i])), _mm_cvtps_pd(_mm_load_ss(\
                   &input_array1[*array_index + 2 * i])))));
    #endif
#elif defined(SINCOS)
    #define SSE_f2d_2_mask2_TMP(i, name)                                \
    __m128d input2_f2d_mask_value##i = _mm_cvtps_pd(_mm_load_ss(        \
        &input_array[*array_index + 2 * i]));                           \
    _mm_store_ss(&result_array[*array_index + 2 * i],                   \
                 _mm_cvtpd_ps(_ZGVbN2v_sin(input2_f2d_mask_value##i))); \
    _mm_store_ss(&result_array1[*array_index + 2 * i],                  \
                 _mm_cvtpd_ps(_ZGVbN2v_cos(input2_f2d_mask_value##i)));
#else
#define SSE_f2d_2_mask2_TMP(i, name)                                                  \
  _mm_store_ss(&result_array[*array_index + 2 * i],                                   \
                                    _mm_cvtpd_ps(_ZGV##name(_mm_cvtps_pd(_mm_load_ss( \
                                        &input_array[*array_index + 2 * i])))));
#endif

#define SSE_f2d_2_mask2_ops(OP1, OP2, i, name)          \
SSE_f2d_2__##i##_ops(OP1, OP2, name)                    \
OP1                                                     \
SSE_f2d_2_mask2(i, name)                                \
OP2


#undef SCALAR_f2d_1_TMP
#define SCALAR_f2d_1(i, name) SCALAR_f2d_1_TMP(i, name)
#if defined(VV)
    #if defined(SCALAR_ARRAY)
    #define SCALAR_f2d_1_TMP(i, name)                                          \
    result_array[*array_index+i] = ckl_##name(input_value,                     \
                                              input_array[*array_index+i]);
    #elif defined(ARRAY_SCALAR)
    #define SCALAR_f2d_1_TMP(i, name)                                          \
    result_array[*array_index+i] = ckl_##name(input_array[*array_index+i],     \
                                              input_value);
    #else
    #define SCALAR_f2d_1_TMP(i, name)                                          \
    result_array[*array_index+i] = ckl_##name(input_array[*array_index+i],     \
                                              input_array1[*array_index+i]);
    #endif
#else
#define SCALAR_f2d_1_TMP(i, name)                                              \
    result_array[*array_index+i] = ckl_##name(input_array[*array_index+i]);
#endif

#define SCALAR_f2d_1_ops(OP1, OP2, i, name)         \
OP1                                                 \
SCALAR_f2d_1(i, name)                               \
OP2



