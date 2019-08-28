// C program to find the sum of two matrices of order 2*2
#include <stdio.h>
int main()
{
  // size of the array
  int size =128;

  //make arrays
  float a[size][size], b[size][size], result[size][size];
  
  // Taking input using nested for loop
  int ii,jj,i,j;
  int t = 4;
  printf("Enter elements of 1st matrix\n");
  for (ii = 0; ii < size; ii+=t) {
    for (jj = 0; jj < size; jj+=t){
	 for (i = ii; i < ii+t; i++) {
	    for (j = jj; j < jj+t; j++){
     		 a[i][j] = i;
     		 b[i][j] = i;
    }
  }
  }
}
   
  // multiple corresponding elements of two arrays
  for (ii = 0; ii < size; ii+=t) {
    for (jj = 0; jj < size; jj+=t){
	 for (i = ii; i < ii+t; i++) {
	    for (j = jj; j < jj+t; j++){
              result[i][j] = a[i][j] * b[i][j];
    }
  }
}
}
  return 0;
}
