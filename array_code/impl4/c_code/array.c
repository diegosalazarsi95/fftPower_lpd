// C program to find the sum of two matrices of order 2*2
#include <stdio.h>
int main()
{
  // size of the array
  int size =16;

  //make arrays
  float a[size][size], b[size][size], result[size][size];
  
  // Taking input using nested for loop
  int i1,j1,i2,j2;
  int t = 4;
  printf("Enter elements of 1st matrix\n");
  for (i1 = 0; i1 < size; i1+=t) {
    for (j1 = 0; j1 < size; j1+=t){
	 for (i2 = i1; i2 < i1+t-1; i2++) {
	    for (j2 = j1; j1 < j1+t-1; j2++){
      a[i2][j2] = i1;
      b[i2][j2] = i1;
    }
  }
  }
}
   
  // multiple corresponding elements of two arrays
  for (i1 = 0; i1 < size; i1+=t) {
    for (j1 = 0; j1 < size; j1+=t){
	 for (i2 = i1; i2 < i1+t-1; i2++) {
	    for (j2 = j1; j1 < j1+t-1; j2++){
      		result[i2][j2] = a[i2][j2] * b[i2][j2];
    }
  }
  }
}
     
 

  return 0;
}
