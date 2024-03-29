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
  for (j = 0; j < size; ++j) {
    for (i = 0; i < size; ++i)
    {
      a[i][j] = i;
    }
  }
  
  // Taking input using nested for loop
  for (j = 0; j < size; ++j) {
    for (i = 0; i < size; ++i)
    {
      b[i][j] = i;
    }
  }
  
  // multiple corresponding elements of two arrays
  for (j = 0; j < size; ++j) {
    for (i = 0; i < size; ++i)
    {
      result[i][j] = a[i][j] * b[i][j];
    }
  }

  return 0;
}
