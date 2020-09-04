#include "cpu.h"
#include "vmath.h"
#include <stdio.h>

int func_index = INDEX_NON_VECTOR;

int __attribute__((constructor)) init(void) {
  if (support_avx512())
    func_index = INDEX_AVX512;
  else if (support_avx2())
    func_index = INDEX_AVX2;
  else if (support_avx())
    func_index = INDEX_AVX;
  else if (support_sse2())
    func_index = INDEX_SSE2;
  // printf("==== func_index=%d\n", func_index);
  // func_index = INDEX_AVX;
  return func_index;
}