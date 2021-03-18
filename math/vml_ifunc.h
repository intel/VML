/*************************************************************************************/
/*  Copyright (C) 2021 Intel Corporation                                             */
/*                                                                                   */
/*  Redistribution and use in source and binary forms, with or without modification, */
/*  are permitted provided that the following conditions are met:                    */
/*                                                                                   */
/*  1. Redistributions of source code must retain the above copyright notice,        */
/*     this list of conditions and the following disclaimer.                         */
/*  2. Redistributions in binary form must reproduce the above copyright notice,     */
/*     this list of conditions and the following disclaimer in the documentation     */
/*     and/or other materials provided with the distribution.                        */
/*  3. Neither the name of the copyright holder nor the names of its contributors    */
/*     may be used to endorse or promote products derived from this software         */
/*     without specific prior written permission.                                    */
/*                                                                                   */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"      */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,            */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   */
/*  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS          */
/*  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,              */
/*  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT             */
/*  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;                  */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,         */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE             */
/*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,                */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                               */
/*                                                                                   */
/*                                                                                   */
/*  SPDX-License-Identifier: BSD-3-Clause                                            */
/*************************************************************************************/
#ifndef VML_IFUNC_H
#define VML_IFUNC_H

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

#endif /*VML_IFUNC_H*/
