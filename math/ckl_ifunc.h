#ifndef CKL_IFUNC_H
#define CKL_IFUNC_H

#ifdef __cplusplus
extern "C"
{
#endif

#if GCC_IFUN_UNAVAILABLE == 0
#define RESOLVE_FUNC(type_name, name, func_name) \
    static type_name name##_ifunc()              \
    {                                            \
        __builtin_cpu_init();                    \
        if (cpu_supports_avx512())               \
            return name##_avx512;                \
        else if (cpu_supports_avx2())            \
            return name##_avx2;                  \
        else if (cpu_supports_avx())             \
            return name##_avx;                   \
        else if (cpu_supports_sse2())            \
            return name##_sse;                   \
        else                                     \
            return name##_scalar;                \
    }
#else
#define RESOLVE_FUNC(type_name, name, func_name)      \
    type_name name##_ifunc(void) __asm__(#func_name); \
    type_name name##_ifunc()                          \
    {                                                 \
        __builtin_cpu_init();                         \
        if (cpu_supports_avx512())                    \
            return name##_avx512;                     \
        else if (cpu_supports_avx2())                 \
            return name##_avx2;                       \
        else if (cpu_supports_avx())                  \
            return name##_avx;                        \
        else if (cpu_supports_sse2())                 \
            return name##_sse;                        \
        else                                          \
            return name##_scalar;                     \
    }                                                 \
    __asm__(".type " #func_name ", %gnu_indirect_function");
#endif
#ifdef __cplusplus
}
#endif

#endif /*CKL_IFUNC_H*/