#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415927
#endif

#ifndef MATRIX_HEIGHT
#define MATRIX_DIMENSION 4
#endif

/* This function prints a given matrix to console */
void PrintMatrix(double **matrix)
{
    // Check if the pointers are valid
    if((matrix == NULL)|| (matrix[0] == NULL))
    {
        return;
    }
    

    // Do the printing
    int i, j;
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        for(j = 0; j < MATRIX_DIMENSION; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n\n");
    }
    
    return;
}



/* This function copy the values of a 4 * 4 matrix to another (A -> B) */
void MatrixCopying(double **matrixA, double **matrixB)
{
    // Check if the pointers are valid
    if((matrixA == NULL) || (matrixB == NULL) || (matrixA[0] == NULL) || (matrixB[0] == NULL))
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
    
    return;
}


/* This function multiplies two 4 * 4 matrices, (B = A * B) */
void MatrixMultiplication(double **matrixA, double **matrixB)
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
    
    
    // Declare and intialize another 2D array to store matrixB since it will be storing the result of the multiplication
    double matrixC[4][4] = {0.0};
    
    // Copy B into C
    MatrixCopying(matrixB, matrixC);
    
    // Do the multiplication
    int i, j, k;
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        for(j = 0; j < MATRIX_DIMENSION; j++)
        {
            double addResult = 0;
            for(k = 0; k < MATRIX_DIMENSION; k++)
            {
                double mulResult = matrixA[i][k] * matrixC[k][j];
                addResult = addResult + mulResult;
            }
            
            matrixB[i][j] = addResult;
        }
    }
    
    return;
}



fwd_kin(theta, x)
double *theta;
double x[3];
{
    printf("\n\n");
    
    int i;
    
    double **matrixOne = (double **)malloc(MATRIX_DIMENSION * sizeof(double *));
    double **matrixTwo = (double **)malloc(MATRIX_DIMENSION * sizeof(double *));
    
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        matrixOne[i] = (double *)calloc(MATRIX_DIMENSION, sizeof(double));
        matrixTwo[i] = (double *)calloc(MATRIX_DIMENSION, sizeof(double));
    }
    
    matrixOne[0][0] = 1.0;
    MatrixCopying(matrixOne, matrixTwo);
    PrintMatrix(matrixTwo);
    
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        free(matrixOne[i]);
        free(matrixTwo[i]);
        
        matrixOne[i] = NULL;
        matrixTwo[i] = NULL;
    }
    
    free(matrixOne);
    free(matrixTwo);
    
    matrixOne = NULL;
    matrixTwo = NULL;
}


inv_kin(x, theta)
double *x;
double theta[6];
{
}


