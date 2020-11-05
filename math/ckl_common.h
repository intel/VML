#ifndef CKL_COMMON_H
#define CKL_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#define _GNU_SOURCE
#include <math.h>
#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include "../ckl_cpu.h"

#define __CKL_FN_ATTR_AVX512 __attribute__((__always_inline__, __target__("avx512f,avx512vl")))
#define __CKL_FN_ATTR_AVX2 __attribute__((__always_inline__, __target__("avx2")))
#define __CKL_FN_ATTR_AVX __attribute__((__always_inline__, __target__("avx")))
#define __CKL_FN_ATTR_SSE2 __attribute__((__always_inline__, __target__("sse2")))

#ifdef __cplusplus
}
#endif

#endif /*CKL_COMMON_H*/