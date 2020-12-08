#ifndef CKL_MATH_H
#define CKL_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void *(*ckl_hook_func_t1)(void *);

    void ckl_vsin(const double *input_array, double *result_array,
                  unsigned int size);
    void ckl_vsinf(const float *input_array, float *result_array,
                   unsigned int size);
    void ckl_vcos(const double *input_array, double *result_array,
                  unsigned int size);
    void ckl_vcosf(const float *input_array, float *result_array,
                   unsigned int size);
    void ckl_vlog(const double *input_array, double *result_array,
                  unsigned int size);
    void ckl_vlogf(const float *input_array, float *result_array,
                   unsigned int size);
    void ckl_vexp(const double *input_array, double *result_array,
                  unsigned int size);
    void ckl_vexpf(const float *input_array, float *result_array,
                   unsigned int size);
    void ckl_vsincos(const double *input_array, double *sin_result_array,
                     double *cos_result_array, unsigned int size);
    void ckl_vsincosf(const float *input_array, float *sin_result_array,
                      float *cos_result_array, unsigned int size);
    void ckl_vpow(const double *input_array_x, const double *input_array_y,
                  double *result_array, unsigned int size);
    void ckl_vpowf(const float *input_array_x, const float *input_array_y,
                   float *result_array, unsigned int size);
    void ckl_vpow_vs(const double *input_array_x, const double input_y,
                  double *result_array, unsigned int size);
    void ckl_vpow_sv(const double input_x, const double *input_array_y,
                  double *result_array, unsigned int size);
    void ckl_vpowf_vs(const float *input_array_x, const float input_y,
                  float *result_array, unsigned int size);
    void ckl_vpowf_sv(const float input_x, const float *input_array_y,
                  float *result_array, unsigned int size);
    void ckl_vsin_hook(const double *input_array, double *result_array,
                  unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vsinf_hook(const float *input_array, float *result_array,
                   unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vcos_hook(const double *input_array, double *result_array,
                  unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vcosf_hook(const float *input_array, float *result_array,
                   unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vlog_hook(const double *input_array, double *result_array,
                  unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vlogf_hook(const float *input_array, float *result_array,
                   unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vexp_hook(const double *input_array, double *result_array,
                  unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vexpf_hook(const float *input_array, float *result_array,
                   unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vsincos_hook(const double *input_array, double *sin_result_array,
                     double *cos_result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vsincosf_hook(const float *input_array, float *sin_result_array,
                      float *cos_result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vpow_hook(const double *input_array_x, const double *input_array_y,
                   double *result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vpow_sv_hook(const double input_x, const double *input_array_y,
                   double *result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vpow_vs_hook(const double *input_array_x, const double input_y,
                   double *result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vpowf_hook(const float *input_array_x, const float *input_array_y,
                   float *result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vpowf_sv_hook(const float input_x, const float *input_array_y,
                   float *result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
    void ckl_vpowf_vs_hook(const float *input_array_x, const float input_y,
                   float *result_array, unsigned int size, ckl_hook_func_t1 pre_hook, 
                   void * pre_args, ckl_hook_func_t1 post_hook, void * post_args);
        
#include "math/ckl_vsin.h"
#include "math/ckl_vcos.h"
#include "math/ckl_vlog.h"
#include "math/ckl_vexp.h"
#include "math/ckl_vsinf.h"
#include "math/ckl_vcosf.h"
#include "math/ckl_vlogf.h"
#include "math/ckl_vexpf.h"
#include "math/ckl_vpow.h"
#include "math/ckl_vpow_sv.h"
#include "math/ckl_vpow_vs.h"
#include "math/ckl_vpowf.h"
#include "math/ckl_vpowf_sv.h"
#include "math/ckl_vpowf_vs.h"
#include "math/ckl_vsincos.h"
#include "math/ckl_vsincosf.h"
#include "math/ckl_vsin_hook.h"
#include "math/ckl_vcos_hook.h"
#include "math/ckl_vlog_hook.h"
#include "math/ckl_vexp_hook.h"
#include "math/ckl_vsinf_hook.h"
#include "math/ckl_vcosf_hook.h"
#include "math/ckl_vlogf_hook.h"
#include "math/ckl_vexpf_hook.h"
#include "math/ckl_vpow_hook.h"
#include "math/ckl_vpow_sv_hook.h"
#include "math/ckl_vpow_vs_hook.h"
#include "math/ckl_vpowf_hook.h"
#include "math/ckl_vpowf_sv_hook.h"
#include "math/ckl_vpowf_vs_hook.h"
#include "math/ckl_vsincos_hook.h"
#include "math/ckl_vsincosf_hook.h"
#ifdef __cplusplus
}
#endif

#endif /*CKL_MATH_H*/