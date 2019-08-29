/*
 * fft() - a straightforward implementation of a decimation in time
 *         FFT algorithm.  No fancy micro-twiddling of C code.  Let
 *         the compiler do that for you.
 *
 * input  - Pointer to the input vector.
 * output - Pointer to where you want the output, ie this is not an
 *          in-place algorithm.
 * n      - The number of points in the input vector.  Must be a power
 *          of two.
 * dir    - Direction :  1 = forward
 *                      -1 = reverse
 * 
 * See Cormen, Leiserson, and Rivest's _Introduction_to_Algorithms_,
 * Chapter 32 for more details.
 * 
 * If you need to speed this up, rewrite bit_reverse_copy() and try changing
 * the local variables with complex type into two variables with double type
 * Some uses of const may help, too.  YMMV.
 *
 * Matt Donadio - m.p.donadio@ieee.org
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* It's not there on mingw systems [05/01 - sof] */
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

typedef struct complex_t {
  double r;
  double i;
} complex;

static void bit_reverse_copy(complex *, complex *, int);

void fft(complex * input, complex * output, unsigned int n, int dir)
{
  unsigned int s, j, k;
  unsigned int lgn;
  unsigned int m;
  complex Wm, W;
  complex t, u;

  bit_reverse_copy(input, output, n);

  for (lgn = 0; n >> lgn > 1; lgn++);

  for (s = 1; s <= lgn; s++) {
    m = 1 << s;
    Wm.r = cos(2.0 * M_PI / (double) m);
    Wm.i = sin(-dir * 2.0 * M_PI / (double) m);
    W.r = 1.0;
    W.i = 0.0;
    for (j = 0; j <= m / 2 - 1; j++) {
      for (k = j; k <= n - 1; k += m) {
	t.r = W.r * (output + k + m / 2)->r - W.i * (output + k + m / 2)->i;
	t.i = W.r * (output + k + m / 2)->i + W.i * (output + k + m / 2)->r;
	u.r = (output + k)->r;
	u.i = (output + k)->i;
	(output + k)->r = u.r + t.r;
	(output + k)->i = u.i + t.i;
	(output + k + m / 2)->r = u.r - t.r;
	(output + k + m / 2)->i = u.i - t.i;
      }
      t.r = W.r * Wm.r - W.i * Wm.i;
      t.i = W.r * Wm.i + W.i * Wm.r;
      W.r = t.r;
      W.i = t.i;
    }
  }

  if (dir == -1) {
    for (j = 0; j < n; j++) {
      (output + j)->r /= (double) n;
      (output + j)->i /= (double) n;
    }
  }
}

/*
 * this could probably be a lot better...
 */

static void bit_reverse_copy(complex * input, complex * output, int n)
{
  unsigned int i, j, k;
  int lgn;

  for (lgn = 0; n >> lgn > 1; lgn++);

  for (i = 0; i < n; i++) {
    k = 0;
    for (j = 0; j < lgn; j++) {
      if ((i & (1 << j)) == (1 << j)) {
	k += 1 << (lgn - 1 - j);
      }
    }
    (output + i)->r = (input + k)->r;
    (output + i)->i = (input + k)->i;
  }
}

int main(void) {
    int N = 32;
    complex * input1 = (complex*) malloc(sizeof(struct complex_t) * N);
    complex * result1;
    
    /* Init inputs */
    int i;
    for (i=0; i < N; i++) {
        input1[i].r = (double) i;
        input1[i].i = 0.0;
    }
    
    /* Do FFT */
    fft(input1, result1, N, 1);
    
    return 0;
}