#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {
    const int DIM = 1000;
    int i,j,k;
    double **a, **b, **c;
    a= (double**) malloc(DIM*sizeof(double*));
    b= (double**) malloc(DIM*sizeof(double*));
    c= (double**) malloc(DIM*sizeof(double*));
    /* Initialisation */
    for (i=0; i<DIM; i++) {
        a[i]=(double*) malloc(DIM*sizeof(double));
        b[i]=(double*) malloc(DIM*sizeof(double));
        c[i]=(double*) malloc(DIM*sizeof(double));
        for (j = 0; j < DIM; j++) {
            a[i][j] = (double)(i-j);
            b[i][j] = (double)(i+j);
            c[i][j] = 0.0;
        }
    }

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            for (int k = 0; k < DIM; k++)
                c[i][j]+= a[i][k] * b[k][j];
    
    printf("\nSequential result:\n");

    for (int i = 0; i < 5; i++){
        for (int j =0; j < 5; j++){
            printf("c[%d][%d]: %f\n", i, j, c[i][j]);
        }
    }

    for (int i = 0; i < DIM; i++){
        for (int j =0; j < DIM; j++){
            c[i][j] = 0.0;
        }
    }

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        {
            double element = 0;
            #pragma omp parallel for reduction(+:element)
            for (int k = 0; k < DIM; k++){
                element+= a[i][k] * b[k][j];
            }
            c[i][j] = element;
        }

    printf("\nParallel result:\n");

    for (int i = 0; i < 5; i++){
        for (int j =0; j < 5; j++){
            printf("c[%d][%d]: %f\n", i, j, c[i][j]);
        }
    }

    return 0;

}