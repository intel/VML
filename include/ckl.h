#ifndef _CKL_H
#define _CKL_H

void vsin_avx512(const double * input_array, double * result_array, unsigned int size);
void ckl_vsin(const double * input_array, double * result_array, unsigned int size);

#endif // END OF THIS HEADER FILE 
