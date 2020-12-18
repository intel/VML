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
#include "test_common.h"
#define FLOAT double
#define DOUBLE
#define POW
#define TEST_ARRAY_SCALAR 1
typedef int (*test_func_vector)(const FLOAT *, const FLOAT, FLOAT *, unsigned int);
typedef FLOAT (*test_func_scalar)(FLOAT, FLOAT);
test_func_vector fp_vector = vml_vpow_vs;
test_func_scalar fp_scalar = pow;
/**
Test values define:
The input array is SPECIAL_VALUES + 10 vaules from RANGES + dim values from
RANGE2; SPECIAL_VALUES array is for some special input values; SPEC_SIZE is its
size; RANGE1 is for large random values generation; RANGE2 is for little ramdom
values generation;
**/
#define SPEC_SIZE 50
#define SPECIAL_VALUES \
  {1.9348611798824013607855931695667095482349395751953125, NAN, NAN, NAN, NAN, NAN, NAN, NAN, \
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, \
  -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, \
  -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, \
  INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, \
  -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY};
#define SPECIAL_VALUEST \
  {-1.593880658583753273660477134399116039276123046875, NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY, \
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY,\
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY,\
  NAN, 0.0, 1.0, -1.0, -0.0, INFINITY, -INFINITY};
#define RANGE1 rand_in_range(-2.0, 2.0)
#define RANGE2 rand_in_range(RAND_MAX * -1.0, RAND_MAX * 1.0)
#include "test_common.c"
