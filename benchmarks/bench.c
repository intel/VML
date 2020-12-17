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
FLOAT rand_in_range(FLOAT min, FLOAT max)
{
  FLOAT range = (max - min);
  FLOAT div = RAND_MAX / range;
  return min + (rand() / div);
}

int main(int argc, char *argv[])
{

  int dim = atoi(argv[1]);
  int loopCount = atoi(argv[2]);
  struct timeval start, finish;
  FLOAT duration;

  unsigned int array_size = dim * loopCount;
  FLOAT *input_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
  FLOAT *result_array = (FLOAT *)malloc(sizeof(FLOAT) * array_size);

#ifdef POW
  FLOAT *input_array1 = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
#endif

#ifdef SINCOS
  FLOAT *result_array1 = (FLOAT *)malloc(sizeof(FLOAT) * array_size);
#endif

  for (unsigned int i = 0; i < array_size; i++)
  {
    input_array[i] = RANGE1; //rand_in_range(-360.0, 360.0); //(FLOAT)(rand() / 1000.0);
#ifdef POW
    input_array1[i] = RANGE2; //(FLOAT)(rand() / 100.0);
#endif
    result_array[i] = 0.0;
#ifdef SINCOS
    result_array1[i] = 0.0;
#endif
  }

  //sleep(2);
  //printf("===start \n");
  gettimeofday(&start, NULL);
  FUNCTION_LOOP
  gettimeofday(&finish, NULL);
  //printf("===end \n");
  for (unsigned int i = 0; i < array_size; i++)
  {
    result_array[0] += result_array[i];
  }
  printf("Scalar result:\n");
  printf("%12.8lf\n", result_array[0]);
  duration = ((FLOAT)(finish.tv_sec - start.tv_sec) * 1000000 +
              (FLOAT)(finish.tv_usec - start.tv_usec)) /
             1000000;
  duration /= loopCount;
  FLOAT gflops = 2.0 * dim;
  gflops = gflops / duration * 1.0e-6;
  printf("[%d]:\t%lf s\t%lf MFLOPS\n", dim, duration * loopCount, gflops);

  free(input_array);
  free(result_array);

#ifdef POW
  free(input_array1);
#endif

#ifdef SINCOS
  free(result_array1);
#endif

  return 0;
}
