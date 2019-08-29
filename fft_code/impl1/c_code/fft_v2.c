#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535897932384626434

typedef struct complex_t {
    double re;
    double im;
} complex;


complex conv_from_polar(double r, double radians) {
    complex result;
    result.re = r * cos(radians);
    result.im = r * sin(radians);
    return result;
}

complex add(complex left, complex right) {
    complex result;
    result.re = left.re + right.re;
    result.im = left.im + right.im;
    return result;
}

complex multiply(complex left, complex right) {
    complex result;
    result.re = left.re*right.re - left.im*right.im;
    result.im = left.re*right.im + left.im*right.re;
    return result;
}

complex* DFT_naive(complex* x, int N) {
    complex* X = (complex*) malloc(sizeof(struct complex_t) * N);
    int k, n;
    for(k = 0; k < N; k++) {
        X[k].re = 0.0;
        X[k].im = 0.0;
        for(n = 0; n < N; n++) {
            X[k] = add(X[k], multiply(x[n], conv_from_polar(1, -2*PI*n*k/N)));
        }
    }
    
    return X;
}

/** Implements the Good-Thomas FFT algorithm. 
  *
  * @expects: N1 and N2 must be relatively prime
  * @expects: N1*N2 = N
  */
complex* FFT_GoodThomas(complex* input, int N, int N1, int N2) {
    int k1, k2, z;

    /* Allocate columnwise matrix */
    complex **columns = (complex**) malloc(sizeof(struct complex_t*) * N1);
    complex **rows = (complex**) malloc(sizeof(struct complex_t*) * N2);
    complex *output = (complex*) malloc(sizeof(struct complex_t) * N);

    for(k1 = 0; k1 < N1; k1++) {
        columns[k1] = (complex*) malloc(sizeof(struct complex_t) * N2);
    }
    
    /* Allocate rowwise matrix */
    for(k2 = 0; k2 < N2; k2++) {
        rows[k2] = (complex*) malloc(sizeof(struct complex_t) * N1);
    }
    
    /* Reshape input into N1 columns (Using Good-Thomas Indexing) */
    for(z = 0; z < 30; z++) {
        k1 = z % N1;
        k2 = z % N2;
        columns[k1][k2] = input[z];
    }
    
    /* Compute N1 DFTs of length N2 using naive method */
    for (k1 = 0; k1 < N1; k1++) {
        columns[k1] = DFT_naive(columns[k1], N2);
    }
    
    /* Transpose */
    for(k1 = 0; k1 < N1; k1++) {
        for (k2 = 0; k2 < N2; k2++) {
            rows[k2][k1] = columns[k1][k2];
        }
    }
   
    /* Compute N2 DFTs of length N1 using naive method */
    for (k2 = 0; k2 < N2; k2++) {
        rows[k2] = DFT_naive(rows[k2], N1);
    }
    
    /* Flatten into single output (Using chinese remainder theorem) */
    
    for(k1 = 0; k1 < N1; k1++) {
        for (k2 = 0; k2 < N2; k2++) {
            z = N1*k2 + N2*k1;
            output[z%N] = rows[k2][k1];
        }
    }

    /* Free all alocated memory except output and input arrays */
    for(k1 = 0; k1 < N1; k1++) {
        free(columns[k1]);
    }
    for(k2 = 0; k2 < N2; k2++) {
        free(rows[k2]);
    }
    free(columns);
    free(rows);
    return output;
}

int main(void) {
    complex * input1 = (complex*) malloc(sizeof(struct complex_t) * 30);
    complex * input2 = (complex*) malloc(sizeof(struct complex_t) * 30);
    complex * result1;
    
    /* Init inputs */
    int i;
    for (i=0; i < 30; i++) {
        input1[i].re = (double) i;
        input1[i].im = 0.0;
    }
    
    /* Do FFT */
    result1 = FFT_GoodThomas(input1, 30, 6, 5);
    
    return 0;
}