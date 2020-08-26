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
  else if (support_sse())
    func_index = INDEX_SSE;
  // printf("==== func_index=%d\n", func_index);
  return func_index;
}