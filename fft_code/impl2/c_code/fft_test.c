#include "fft.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    complex * input1 = (complex*) malloc(sizeof(struct complex_t) * 30);
    complex * input2 = (complex*) malloc(sizeof(struct complex_t) * 30);
    complex * result1, * result2;
    
    /* Init inputs */
    for (int i=0; i < 30; i++) {
        input1[i].re = (double) i;
        input1[i].im = 0.0;
        input2[i].re = (double) i;
        input2[i].im = 0.0;
    }
    
    /* Do FFT */
    result1 = FFT_CooleyTukey(input1, 30, 6, 5);
    
    return 0;
}