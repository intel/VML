#ifndef CKL_CPU_H
#define CKL_CPU_H

#ifdef __cplusplus
extern "C"
{
#endif

    inline int cpu_supports_avx512()
    {
        if (__builtin_cpu_supports("avx512f") && __builtin_cpu_supports("avx512vl"))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    inline int cpu_supports_avx2() { return __builtin_cpu_supports("avx2"); }

    inline int cpu_supports_avx() { return __builtin_cpu_supports("avx"); }

    inline int cpu_supports_sse2() { return __builtin_cpu_supports("sse2"); }

#ifdef __cplusplus
}
#endif

#endif /*CKL_CPU_H*/