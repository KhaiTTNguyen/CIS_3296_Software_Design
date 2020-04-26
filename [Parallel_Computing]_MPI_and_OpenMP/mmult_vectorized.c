


/**
 * An unoptimized implementation of matrix multiplication.


Reference: 
https://azuredevopslabs.com/labs/azuredevops/github/#exercise-2-saving-work-with-commits

 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "mat.h"

/**
 * An unoptimized algorithm for matrix multiplication.
 * 
 * @param c : the matrix in which to place the result of the matrix multiplication.
 * @param a : the first matrix.
 * @param aRows : the number of rows in a.
 * @param aCols : the number of columns in a.
 * @param b : the second matrix.
 * @param bRows : the number of rows in b.
 * @param bCols : the number of columns in b.
 * @return 0 if the matrix multiplication is successful.
 */
int mmult_vectorized(double *c, double *a, int aRows, int aCols, 
	      double *b, int bRows, int bCols) {

    if(aCols != bRows) {
        return -1;
    }
    
    for (int i = 0; i < aRows; i++) {  
        for (int j = 0; j < bCols; j++)  {  
            c[i*aCols + j] = 0;  
        }for (int k = 0; k < bRows; k++)  {  
            for (int l = 0; l < bCols; l++) {     
                c[i*aCols + l] += a[i*aCols + k] * b[k*bCols + l];
            }
        }
    }

    return 0;
}



