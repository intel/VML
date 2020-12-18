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
#ifndef VML_MATH_H
#define VML_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif
    #include "math/vml_common.h"

    int vml_vsin(const double *input_array, double *result_array,
                  unsigned int size);
    int vml_vsinf(const float *input_array, float *result_array,
                   unsigned int size);
    int vml_vcos(const double *input_array, double *result_array,
                  unsigned int size);
    int vml_vcosf(const float *input_array, float *result_array,
                   unsigned int size);
    int vml_vlog(const double *input_array, double *result_array,
                  unsigned int size);
    int vml_vlogf(const float *input_array, float *result_array,
                   unsigned int size);
    int vml_vexp(const double *input_array, double *result_array,
                  unsigned int size);
    int vml_vexpf(const float *input_array, float *result_array,
                   unsigned int size);
    int vml_vsincos(const double *input_array, double *sin_result_array,
                     double *cos_result_array, unsigned int size);
    int vml_vsincosf(const float *input_array, float *sin_result_array,
                      float *cos_result_array, unsigned int size);
    int vml_vpow(const double *input_array_x, const double *input_array_y,
                  double *result_array, unsigned int size);
    int vml_vpowf(const float *input_array_x, const float *input_array_y,
                   float *result_array, unsigned int size);
    int vml_vpow_vs(const double *input_array_x, const double input_y,
                  double *result_array, unsigned int size);
    int vml_vpow_sv(const double input_x, const double *input_array_y,
                  double *result_array, unsigned int size);
    int vml_vpowf_vs(const float *input_array_x, const float input_y,
                  float *result_array, unsigned int size);
    int vml_vpowf_sv(const float input_x, const float *input_array_y,
                  float *result_array, unsigned int size);
    int vml_vsin_hook(const double *input_array, double *result_array,
                  unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vsinf_hook(const float *input_array, float *result_array,
                   unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vcos_hook(const double *input_array, double *result_array,
                  unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vcosf_hook(const float *input_array, float *result_array,
                   unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vlog_hook(const double *input_array, double *result_array,
                  unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vlogf_hook(const float *input_array, float *result_array,
                   unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vexp_hook(const double *input_array, double *result_array,
                  unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vexpf_hook(const float *input_array, float *result_array,
                   unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vsincos_hook(const double *input_array, double *sin_result_array,
                     double *cos_result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vsincosf_hook(const float *input_array, float *sin_result_array,
                      float *cos_result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vpow_hook(const double *input_array_x, const double *input_array_y,
                   double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vpow_sv_hook(const double input_x, const double *input_array_y,
                   double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vpow_vs_hook(const double *input_array_x, const double input_y,
                   double *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vpowf_hook(const float *input_array_x, const float *input_array_y,
                   float *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vpowf_sv_hook(const float input_x, const float *input_array_y,
                   float *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
    int vml_vpowf_vs_hook(const float *input_array_x, const float input_y,
                   float *result_array, unsigned int size, vml_hook_func_t pre_hook, 
                   void * pre_args, vml_hook_func_t post_hook, void * post_args);
        
#include "math/vml_vsin.h"
#include "math/vml_vcos.h"
#include "math/vml_vlog.h"
#include "math/vml_vexp.h"
#include "math/vml_vsinf.h"
#include "math/vml_vcosf.h"
#include "math/vml_vlogf.h"
#include "math/vml_vexpf.h"
#include "math/vml_vpow.h"
#include "math/vml_vpow_sv.h"
#include "math/vml_vpow_vs.h"
#include "math/vml_vpowf.h"
#include "math/vml_vpowf_sv.h"
#include "math/vml_vpowf_vs.h"
#include "math/vml_vsincos.h"
#include "math/vml_vsincosf.h"
#include "math/vml_vsin_hook.h"
#include "math/vml_vcos_hook.h"
#include "math/vml_vlog_hook.h"
#include "math/vml_vexp_hook.h"
#include "math/vml_vsinf_hook.h"
#include "math/vml_vcosf_hook.h"
#include "math/vml_vlogf_hook.h"
#include "math/vml_vexpf_hook.h"
#include "math/vml_vpow_hook.h"
#include "math/vml_vpow_sv_hook.h"
#include "math/vml_vpow_vs_hook.h"
#include "math/vml_vpowf_hook.h"
#include "math/vml_vpowf_sv_hook.h"
#include "math/vml_vpowf_vs_hook.h"
#include "math/vml_vsincos_hook.h"
#include "math/vml_vsincosf_hook.h"
#ifdef __cplusplus
}
#endif

#endif /*VML_MATH_H*/