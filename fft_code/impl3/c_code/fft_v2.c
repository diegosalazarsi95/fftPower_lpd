/* The authors of this work have released all rights to it and placed it
in the public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
Retrieved from: http://en.literateprograms.org/Cooley-Tukey_FFT_algorithm_(C)?oldid=19032
*/


#include <stdlib.h>
#include <math.h>

#define PI  3.1415926535897932

typedef struct complex_t {
    double re;
    double im;
} complex;

complex complex_from_polar(double r, double theta_radians) {
    complex result;
    result.re = r * cos(theta_radians);
    result.im = r * sin(theta_radians);
    return result;
}

complex complex_add(complex left, complex right) {
    complex result;
    result.re = left.re + right.re;
    result.im = left.im + right.im;
    return result;
}

complex complex_sub(complex left, complex right) {
    complex result;
    result.re = left.re - right.re;
    result.im = left.im - right.im;
    return result;
}

complex complex_mult(complex left, complex right) {
    complex result;
    result.re = left.re*right.re - left.im*right.im;
    result.im = left.re*right.im + left.im*right.re;
    return result;
}

complex* FFT_simple(complex* x, int N /* must be a power of 2 */) {
    complex* X = (complex*) malloc(sizeof(struct complex_t) * N);
    complex * d, * e, * D, * E;
    int k;

    if (N == 1) {
        X[0] = x[0];
        return X;
    }

    e = (complex*) malloc(sizeof(struct complex_t) * N/2);
    d = (complex*) malloc(sizeof(struct complex_t) * N/2);
    for(k = 0; k < N/2; k++) {
        e[k] = x[2*k];
        d[k] = x[2*k + 1];
    }

    E = FFT_simple(e, N/2);
    D = FFT_simple(d, N/2);

    for(k = 0; k < N/2; k++) {
        /* Multiply entries of D by the twiddle factors e^(-2*pi*i/N * k) */
        complex c = complex_from_polar(1, -2.0*PI*k/N);
        D[k] = complex_mult(D[k], c);
    }

    for(k = 0; k < N/2; k++) {
        X[k]       = complex_add(E[k], D[k]);
        X[k + N/2] = complex_sub(E[k], D[k]);
    }

    free(e);
    free(d);
    free(D);
    free(E);
    return X;
}

int main(void) {
    int N = 32;
    complex * input1 = (complex*) malloc(sizeof(struct complex_t) * N);
    complex * result1;
    
    /* Init inputs */
    int i;
    for (i=0; i < N; i++) {
        input1[i].re = (double) i;
        input1[i].im = 0.0;
    }
    
    /* Do FFT */
    result1 = FFT_simple(input1, N);
    
    return 0;
}
