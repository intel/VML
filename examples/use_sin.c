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
/*
If your compiler doesn't support ifunc, you can uncomment the following define macro
*/
// #define GCC_IFUN_UNAVAILABLE 1

#define WITH_HOOK 1
#include "vml_math.h"
#include "sys/time.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

#define PI \
    3.1415926535897932384626433832795028841971693993751058209749445923078164062
#define FLOAT double
#define RANGE1 rand_in_range(-2.0 * PI, 2.0 * PI)
#define MAX_DIM 2147483647
#define MAX_LOOP 2147483647

FLOAT rand_in_range(FLOAT min, FLOAT max)
{
    FLOAT range = (max - min);
    FLOAT div = RAND_MAX / range;
    return min + (rand() / div);
}

struct hook_args
{
   FLOAT input_arg[2];
   FLOAT output_values[2];
};


void * hook_function(void * input)
{
    printf("=== I'm a hook function\n");
    struct hook_args * args = input;
    args->output_values[0] = sin(args->input_arg[0]);
    args->output_values[1] = tan(args->input_arg[1]);
    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Usage: ./use_sin <vector length> <loop count>\n");
        return 0;
    }
    int dim = atoi(argv[1]);
    int loopCount = atoi(argv[2]);
    if(dim >= 1 && dim <= MAX_DIM && loopCount >= 1 && loopCount <= MAX_DIM)
    {
        struct timeval start, finish;
        FLOAT duration;
        struct hook_args hook_test;
        hook_test.input_arg[0] = PI/2.0;
        hook_test.input_arg[1] = PI/4.0;
        hook_test.output_values[0] = 0.0;
        hook_test.output_values[1] = 0.0;

        unsigned int array_size = dim * loopCount;
        FLOAT *input_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
        if(input_array == NULL)
        {
            printf("Failed to malloc for input_array\n");
            return -1;
        }
        FLOAT *result_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
        if(result_array == NULL)
        {
            printf("Failed to malloc for result_array\n");
            free(input_array);
            return -1;
        }

        for (unsigned int i = 0; i < array_size; i++)
        {
            input_array[i] = RANGE1;
            result_array[i] = 0.0;
        }

        gettimeofday(&start, NULL);
        for (unsigned int i = 0; i < loopCount; i++)
        {
        #if defined(WITH_HOOK)
            //Use vsin with hooks
            vml_vsin_hook(input_array + i * dim, result_array + i * dim, dim, hook_function, &hook_test, NULL, NULL);
        #else
            vml_vsin(input_array + i * dim, result_array + i * dim, dim);
        #endif
        }
        gettimeofday(&finish, NULL);
        printf("hook_function's results: output_values[0]=%f, output_values[1]=%f\n", 
                hook_test.output_values[0], hook_test.output_values[1]);

    #if 0
        for (unsigned int i = 0; i < array_size; i++)
        {
            result_array[0] += result_array[i];
        }
        printf("Result:\n");
        printf("%12.8lf\n", result_array[0]);
    #endif

        duration = ((FLOAT)(finish.tv_sec - start.tv_sec) * 1000000 +
                    (FLOAT)(finish.tv_usec - start.tv_usec)) /
                1000000;
        duration /= loopCount;
        FLOAT gflops = 2.0 * dim;
        gflops = gflops / duration * 1.0e-6;
        printf("[%d]:\t%lf s\t%lf MFLOPS\n", dim, duration * loopCount, gflops);

        free(input_array);
        free(result_array);

        return 0;
    }else
    {
        printf("Error input for dim or loop Count, which should be in the range [1, 2147483647]\n");
        return -1;
    }
}