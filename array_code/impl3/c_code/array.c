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
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; j+=2)
    {
      a[i][j] = i;
      a[i][j+1] = i;
      
    }
  }
  
  // Taking input using nested for loop
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; j+=2)
    {
      b[i][j] = i;
      b[i][j+1] = i;
    }
  }
  
  // multiple corresponding elements of two arrays
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; j+=2)
    {
    
      result[i][j] = a[i][j] * b[i][j];
      result[i][j+1] = a[i][j+1] * b[i][j+1];
    }
  }

  return 0;
}
