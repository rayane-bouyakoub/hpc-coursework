#include <stdio.h>
#include <stdlib.h>

/*

rayane@Rayanes-MacBook-Air HPC_TD_MPI % mpirun -np 8 exo4   

Matrice A: 
0  1  2  3  4  5  6  7  
1  2  3  4  5  6  7  8  
2  3  4  5  6  7  8  9  
3  4  5  6  7  8  9  10  
4  5  6  7  8  9  10  11  
5  6  7  8  9  10  11  12  
6  7  8  9  10  11  12  13  
7  8  9  10  11  12  13  14  

Matrice B: 
0  0  0  0  0  0  0  0  
0  1  2  3  4  5  6  7  
0  2  4  6  8  10  12  14  
0  3  6  9  12  15  18  21  
0  4  8  12  16  20  24  28  
0  5  10  15  20  25  30  35  
0  6  12  18  24  30  36  42  
0  7  14  21  28  35  42  49  

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

    int A[8][8];

    int B[8][8];

    int C[8][8];

    for (int i = 0; i < 8; i++){

        for (int j = 0; j < 8; j++){

            A[i][j] = i+j;

            B[i][j] = i*j;

            C[i][j] = 0;

        }

    }

    for (int i = 0; i < 8; i ++){

        for (int j = 0; j < 8; j++){

            for (int k = 0; k < 8; k++){

                C[i][j] = C[i][j]+A[i][k] * B[k][j];

            }

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

    printf("\nMatrice C: \n");

    for (int i = 0; i < 8; i++){

        for (int j = 0; j < 8; j++){

            printf("%d  ",C[i][j]);

        }

        printf("\n");

    }    

    int ligne_result[8];

    int ligne_data[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    for (int j = 0; j < 8; j ++){

        for (int i = 0; i < 8; i++){

            ligne_result[j] = ligne_result[j] + ligne_data[i] * B[i][j];

        }

    }

    printf("Ligne result of process\n");

    for (int i = 0; i < 8; i++){

        printf("%d  ",ligne_result[i]);

    }

    return 0;
}