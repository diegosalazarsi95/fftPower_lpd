// C program to find the sum of two matrices of order 2*2
#include <stdio.h>
int main()
{
  // size of the array
  int size =16;

  //make arrays
  float a[size][size], b[size][size], result[size][size];
  
  // Taking input using nested for loop
  printf("Enter elements of 1st matrix\n");
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j)
    {
      a[i][j] = i;
    }
  }
  
  // Taking input using nested for loop
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j)
    {
      b[i][j] = i;
    }
  }
  
  // multiple corresponding elements of two arrays
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j)
    {
      result[i][j] = a[i][j] * b[i][j];
    }
  }

  return 0;
}