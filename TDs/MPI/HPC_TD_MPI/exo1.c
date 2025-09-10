#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


int main(int argc, char** argv)
{   
    int n, rang, size;

    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rang == 0){

        printf("Veuillez saisir la valeur de n: ");

        scanf("%d", &n);

        printf("Process %d, I will be sending the value %d to process %d\n", rang, n, rang+1);

        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

    }else{

       MPI_Recv(&n, 1, MPI_INT, rang-1, 0, MPI_COMM_WORLD, &status);

       printf("Process %d, I received the value %d from process %d\n", rang, n, rang-1);

       if (rang != size - 1){

            MPI_Send(&n, 1, MPI_INT, rang+1, 0, MPI_COMM_WORLD);

            printf("Process %d, I am sending the value %d to process %d\n", rang, n, rang+1);

       } 

    }

    MPI_Finalize();

    return 0;
}