// C program to find the sum of two matrices of order 2*2
#include <stdio.h>
int main()
{
  // size of the array
  int size =128;

  //make arrays
  float a[size][size], b[size][size], result[size][size];
  
  // Taking input using nested for loop
  int i,j;
  printf("Enter elements of 1st matrix\n");

  
  // multiple corresponding elements of two arrays
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j)
    {
      a[i][j] = i;
      b[i][j] = i;
      result[i][j] = a[i][j] * b[i][j];
    }
  }

  return 0;
}
