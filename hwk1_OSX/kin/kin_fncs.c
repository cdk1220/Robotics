#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415927
#endif

#ifndef MATRIX_HEIGHT
#define MATRIX_DIMENSION 4
#endif


fwd_kin(theta, x)
double *theta;
double x[3];
{
}


inv_kin(x, theta)
double *x;
double theta[6];
{
}


/* This function copy the values of a 4 * 4 matrix to another (A -> B) */
void MatrixCopying(double **matrixA, double **matrixB)
{
    // Check if the pointers are valid
    if((matrixA == NULL) || (matrixB == NULL) || (matrixA[0] == NULL) || (matrixB[0] == NULL))
    {
        return;
    }
    
    
    // If the matrices are not 4 * 4, simply return
    int numRowA = sizeof(matrixA) / sizeof(matrixA[0]);
    int numRowB = sizeof(matrixB) / sizeof(matrixB[0]);
    
    int numColA = sizeof(matrixA[0]) / numRowA;
    int numColB = sizeof(matrixB[0]) / numRowB;
    
    if((numRowA != MATRIX_DIMENSION) || (numRowB != MATRIX_DIMENSION) ||
       (numColA != MATRIX_DIMENSION) || (numColB != MATRIX_DIMENSION))
    {
        return;
    }
    
    
    // Do the copying
    int i, j;
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        for(j = 0; j < MATRIX_DIMENSION; j++)
        {
            matrixB[i][j] = matrixA[i][j];
        }
    }
}




