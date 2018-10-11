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
    
    // Declare and intialize another 2D array to store matrixB since it will be storing the result of the multiplication
    double **matrixC = (double **)malloc(MATRIX_DIMENSION * sizeof(double *));
    int i;
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        matrixC[i] = (double *)calloc(MATRIX_DIMENSION, sizeof(double));
    }
    
    // Copy B into C
    MatrixCopying(matrixB, matrixC);
    

    // Do the multiplication
    int j, k;
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
    
    
    // Free up C
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        free(matrixC[i]);
        matrixC[i] = NULL;
    }
    free(matrixC);
    matrixC = NULL;
    
    return;
}



fwd_kin(theta, x)
double *theta;
double x[3];
{
    int i;
    
    // Initializing the two matrices
    double **matrixOne = (double **)malloc(MATRIX_DIMENSION * sizeof(double *));
    double **matrixTwo = (double **)malloc(MATRIX_DIMENSION * sizeof(double *));
    
    for(i = 0; i < MATRIX_DIMENSION; i++)
    {
        matrixOne[i] = (double *)calloc(MATRIX_DIMENSION, sizeof(double));
        matrixTwo[i] = (double *)calloc(MATRIX_DIMENSION, sizeof(double));
    }
    

    // Multiplying Dz(0.04x)Dx(0.15) * Ry(theta[3])
    matrixOne[0][0] = 1.0;
    matrixOne[0][1] = 0.0;
    matrixOne[0][2] = 0.0;
    matrixOne[0][3] = 0.15;
    matrixOne[1][0] = 0.0;
    matrixOne[1][1] = 1.0;
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.0;
    matrixOne[2][0] = 0.0;
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = 1.0;
    matrixOne[2][3] = 0.04;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;

    matrixTwo[0][0] = cos(theta[3]);
    matrixTwo[0][1] = 0.0;
    matrixTwo[0][2] = sin(theta[3]);
    matrixTwo[0][3] = 0.0;
    matrixTwo[1][0] = 0.0;
    matrixTwo[1][1] = 1.0;
    matrixTwo[1][2] = 0.0;
    matrixTwo[1][3] = 0.0;
    matrixTwo[2][0] = -1.0 * sin(theta[3]);
    matrixTwo[2][1] = 0.0;
    matrixTwo[2][2] = cos(theta[3]);
    matrixTwo[2][3] = 0.0;
    matrixTwo[3][0] = 0.0;
    matrixTwo[3][1] = 0.0;
    matrixTwo[3][2] = 0.0;
    matrixTwo[3][3] = 1.0;

    MatrixMultiplication(matrixOne, matrixTwo);
    
    
    // Multiplying Ry(theta[2]) * result_above
    matrixOne[0][0] = cos(theta[2]);;
    matrixOne[0][1] = 0.0;
    matrixOne[0][2] = sin(theta[2]);
    matrixOne[0][3] = 0.0;
    matrixOne[1][0] = 0.0;
    matrixOne[1][1] = 1.0;
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.0;
    matrixOne[2][0] = -1.0 * sin(theta[2]);
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = cos(theta[2]);
    matrixOne[2][3] = 0.0;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;
    
    MatrixMultiplication(matrixOne, matrixTwo);
    
    
    // Multiplying Dy(0.04)Dx(0.2) * result_above
    matrixOne[0][0] = 1.0;
    matrixOne[0][1] = 0.0;
    matrixOne[0][2] = 0.0;
    matrixOne[0][3] = 0.2;
    matrixOne[1][0] = 0.0;
    matrixOne[1][1] = 1.0;
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.04;
    matrixOne[2][0] = 0.0;
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = 1.0;
    matrixOne[2][3] = 0.0;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;
    
    MatrixMultiplication(matrixOne, matrixTwo);
    
    
    // Multiplying Ry(theta[1]) * result_above
    matrixOne[0][0] = cos(theta[1]);
    matrixOne[0][1] = 0.0;
    matrixOne[0][2] = sin(theta[1]);
    matrixOne[0][3] = 0.0;
    matrixOne[1][0] = 0.0;
    matrixOne[1][1] = 1.0;
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.0;
    matrixOne[2][0] = -1.0 * sin(theta[1]);
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = cos(theta[1]);
    matrixOne[2][3] = 0.0;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;
    
    MatrixMultiplication(matrixOne, matrixTwo);

    
    // Multiplying Dx(0.2) * result_above
    matrixOne[0][0] = 1.0;
    matrixOne[0][1] = 0.0;
    matrixOne[0][2] = 0.0;
    matrixOne[0][3] = 0.2;
    matrixOne[1][0] = 0.0;
    matrixOne[1][1] = 1.0;
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.0;
    matrixOne[2][0] = 0.0;
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = 1.0;
    matrixOne[2][3] = 0.0;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;
    
    MatrixMultiplication(matrixOne, matrixTwo);
    
    
    // Multiplying Rz(theta[0]) * result_above
    matrixOne[0][0] = cos(theta[0]);
    matrixOne[0][1] = -1.0 * sin(theta[0]);
    matrixOne[0][2] = 0.0;
    matrixOne[0][3] = 0.0;
    matrixOne[1][0] = sin(theta[0]);
    matrixOne[1][1] = cos(theta[0]);
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.0;
    matrixOne[2][0] = 0.0;
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = 1.0;
    matrixOne[2][3] = 0.0;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;
    
    MatrixMultiplication(matrixOne, matrixTwo);
    
    
    // Multiplying Dz(0.25) * result_above
    matrixOne[0][0] = 1.0;
    matrixOne[0][1] = 0.0;
    matrixOne[0][2] = 0.0;
    matrixOne[0][3] = 0.0;
    matrixOne[1][0] = 0.0;
    matrixOne[1][1] = 1.0;
    matrixOne[1][2] = 0.0;
    matrixOne[1][3] = 0.0;
    matrixOne[2][0] = 0.0;
    matrixOne[2][1] = 0.0;
    matrixOne[2][2] = 1.0;
    matrixOne[2][3] = 0.25;
    matrixOne[3][0] = 0.0;
    matrixOne[3][1] = 0.0;
    matrixOne[3][2] = 0.0;
    matrixOne[3][3] = 1.0;
    
    MatrixMultiplication(matrixOne, matrixTwo);
    
    
    // Extracting postion values
    x[0] = matrixTwo[0][3];
    x[1] = matrixTwo[1][3];
    x[2] = matrixTwo[2][3];
    
    
    // Freeing up the two matrices
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


