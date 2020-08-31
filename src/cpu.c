#include "cpu.h"

static __inline void xgetbv(int op, int *eax, int *edx) {
  // Use binary code for xgetbv
  __asm__ __volatile__(".byte 0x0f, 0x01, 0xd0"
                       : "=a"(*eax), "=d"(*edx)
                       : "c"(op)
                       : "cc");
}

static __inline void cpuid(int op, int *eax, int *ebx, int *ecx, int *edx) {
  __asm__ __volatile__("mov $0, %%ecx;"
                       "cpuid"
                       : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                       : "0"(op));
}

int support_sse() {
  int eax, ebx, ecx, edx;
  int ret = 0;

  cpuid(1, &eax, &ebx, &ecx, &edx);
  if (edx & (1 << 25))
    ret = 1;
  return ret;
}

int support_sse2() {
  int eax, ebx, ecx, edx;
  int ret = 0;

  cpuid(1, &eax, &ebx, &ecx, &edx);
  if (edx & (1 << 26))
    ret = 1;
  return ret;
}

int support_avx() {
  int eax, ebx, ecx, edx;
  int ret = 0;

  cpuid(1, &eax, &ebx, &ecx, &edx);
  if ((ecx & (1 << 28)) != 0 && (ecx & (1 << 27)) != 0 &&
      (ecx & (1 << 26)) != 0) {
    xgetbv(0, &eax, &edx);
    if ((eax & 6) == 6) {
      ret = 1; // OS support AVX
    }
  }
  return ret;
}

int support_avx2() {
  int eax, ebx, ecx = 0, edx;
  int ret = 0;

  if (!support_avx())
    return 0;
  cpuid(7, &eax, &ebx, &ecx, &edx);
  if ((ebx & (1 << 7)) != 0)
    ret = 1; // OS supports AVX2
  return ret;
}

int support_avx512() {
  int eax, ebx, ecx, edx;
  int ret = 0;

  if (!support_avx())
    return 0;
  cpuid(7, &eax, &ebx, &ecx, &edx);
  if ((ebx & (1 << 7)) == 0) {
    ret = 0; // OS does not even support AVX2
  }
  if ((ebx & (1 << 31)) != 0) {
    xgetbv(0, &eax, &edx);
    if ((eax & 0xe0) == 0xe0)
      ret = 1; // OS supports AVX512VL
  }
  return ret;
}
