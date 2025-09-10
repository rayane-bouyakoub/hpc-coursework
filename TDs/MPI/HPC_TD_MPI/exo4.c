#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

/*
Matrice C: 
0  140  280  420  560  700  840  980  
0  168  336  504  672  840  1008  1176  
0  196  392  588  784  980  1176  1372  
0  224  448  672  896  1120  1344  1568  
0  252  504  756  1008  1260  1512  1764  
0  280  560  840  1120  1400  1680  1960  
0  308  616  924  1232  1540  1848  2156  
0  336  672  1008  1344  1680  2016  2352 
*/

int main (int argc, char** argv){

    int ligne_data[8];

    int ligne_result[8];

    int A[8][8];

    int B[8][8];

    int C[8][8];

    int rang;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    if (rang == 0){

        for (int i = 0; i < 8; i++){

            for (int j = 0; j < 8; j++){

                A[i][j] = i+j;

                B[i][j] = i*j;

            }

        }

        printf("\nMatrice A: \n");

        for (int i = 0; i < 8; i++){

            for (int j = 0; j < 8; j++){

                printf("%d  ",A[i][j]);

            }

            printf("\n");

        }

        printf("\nMatrice B: \n");

        for (int i = 0; i < 8; i++){

            for (int j = 0; j < 8; j++){

                printf("%d  ",B[i][j]);

            }

            printf("\n");

        }

    }

    for (int i = 0; i < 8; i ++){

        ligne_result[i] = 0;

    }

    MPI_Bcast(B, 64, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, 8, MPI_INT, ligne_data, 8, MPI_INT, 0, MPI_COMM_WORLD);

    for (int j = 0; j < 8; j ++){

        for (int i = 0; i < 8; i++){

            ligne_result[j] = ligne_result[j] + ligne_data[i] * B[i][j];

        }

    }

    MPI_Gather(ligne_result, 8, MPI_INT, C, 8, MPI_INT, 0, MPI_COMM_WORLD);

    if (rang == 0){

        printf("\nMatrice C: \n");

        for (int i = 0; i < 8; i++){

            for (int j = 0; j < 8; j++){

                printf("%d  ",C[i][j]);

            }

            printf("\n");

        }    

    }

    MPI_Finalize();

    return 0;
}