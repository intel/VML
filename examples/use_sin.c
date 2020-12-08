/*
If your compiler doesn't support ifunc, you can uncomment the following define macro
*/
// #define GCC_IFUN_UNAVAILABLE 1

#define WITH_HOOK 1
#include "ckl_math.h"
#include "sys/time.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

#define PI \
    3.1415926535897932384626433832795028841971693993751058209749445923078164062
#define FLOAT double
#define RANGE1 rand_in_range(-2.0 * PI, 2.0 * PI)

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
    struct timeval start, finish;
    FLOAT duration;
    struct hook_args hook_test;
    hook_test.input_arg[0] = PI/2.0;
    hook_test.input_arg[1] = PI/4.0;
    hook_test.output_values[0] = 0.0;
    hook_test.output_values[1] = 0.0;

    unsigned int array_size = dim * loopCount;
    FLOAT *input_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
    FLOAT *result_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);

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
        ckl_vsin_hook(input_array + i * dim, result_array + i * dim, dim, hook_function, &hook_test, NULL, NULL);
    #else
        ckl_vsin(input_array + i * dim, result_array + i * dim, dim);
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
}