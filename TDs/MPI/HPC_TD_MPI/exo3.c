#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main (int argc, char** argv){

    int element, rang;

    int A[4][4];

    int X[4];

    int Y[4];

    int ligne[4];

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    if (rang == 0){

        for (int i = 0; i < 4; i++){

            X[i] = 2*i;

            for (int j = 0; j < 4; j++){

                A[i][j] = i+j;

            }

        }

        printf("\nMatrice A: \n");

        for (int i = 0; i < 4; i++){

            for (int j = 0; j < 4; j++){

                printf("%d  ",A[i][j]);

            }

            printf("\n");

        }

        printf("\nVecteur X: \n");

        for (int i = 0; i < 4; i++){

            printf("%d  ",X[i]);

        }

        printf("\n");

    }

    MPI_Bcast(X, 4, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, 4, MPI_INT, ligne, 4, MPI_INT, 0, MPI_COMM_WORLD);

    printf("\nVecteur Ligne %d: \n", rang);

    for (int i = 0; i < 4; i++){

        printf("Ligne du processus %d, L[%d] = %d\n", rang, i, ligne[i]);

    }   

    element = 0;

    for (int i = 0; i < 4; i++){

        element = element + ligne[i] * X[i];

    }

    printf("Element du processus %d = %d\n", rang, element);

    MPI_Gather(&element, 1, MPI_INT, Y, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rang == 0){

        printf("\nVecteur Y: \n");

        for (int i = 0; i < 4; i++){

            printf("%d  ",Y[i]);

        }   

    }
    
    MPI_Finalize();

    return 0;

}