#ifndef CKL_MATH_H
#define CKL_MATH_H

#ifdef __cplusplus
extern "C"
{
#endif
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
    void ckl_vpow(const double *input_array_x, const double *input_array_y,
                  double *result_array, unsigned int size);
    void ckl_vpowf(const float *input_array_x, const float *input_array_y,
                   float *result_array, unsigned int size);
    void ckl_vsincos(const double *input_array, double *sin_result_array,
                     double *cos_result_array, unsigned int size);
    void ckl_vsincosf(const float *input_array, float *sin_result_array,
                      float *cos_result_array, unsigned int size);
    
#include "math/ckl_vsin.h"
#include "math/ckl_vcos.h"
#include "math/ckl_vlog.h"
#include "math/ckl_vexp.h"
#include "math/ckl_vsinf.h"
#include "math/ckl_vcosf.h"
#include "math/ckl_vlogf.h"
#include "math/ckl_vexpf.h"
#include "math/ckl_vpow.h"
#include "math/ckl_vpowf.h"
#include "math/ckl_vsincos.h"
#include "math/ckl_vsincosf.h"
#ifdef __cplusplus
}
#endif

#endif /*CKL_MATH_H*/