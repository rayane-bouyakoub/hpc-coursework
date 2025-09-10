#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define PI 3.1415926535L

double f (double a) {

    return (double)4.0/(( double )1.0+(a*a));

}

// PI is approximately: 3.1424259850010987 Error is: 0.0008333315010987 for number of intervals = 10.

int main (int argc, char** argv){

    int n, i, rang, start, end;

    double h, sum, x;

    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    for (;;) {

        if (rang == 0){

            printf ("Enter the number of intervals (0 quits ): ");

            scanf ("%d" ,&n);

            MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

            if (n == 0) break;

            start = 1;

            if (n % 2 == 0){

                end = n / 2;

            }else {

                end = (n - 1) / 2;

            }

        }

        else {

            MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

            if (n == 0) break;

            end = n;

            if (n % 2 == 0){

                start =(n / 2) + 1;

            }else {

                start = (n + 1) / 2;

            }

        }

        h = ((double)1.0)/(double)n;

        sum = 0.0;

        for (i = start; i <= end; i++) {

            x = h*((double)i-(double)0.5);

            sum += f(x);

        }

        if (rang == 0){

            double local_sum, pi;

            MPI_Recv(&local_sum, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);

            sum = sum + local_sum;

            pi = h*sum ;

            printf("PI is approximately: %.16f Error is: %.16f\n", pi , fabs(pi-PI));

        }

        else {

            MPI_Send(&sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);

        }

    }

    MPI_Finalize();

    return 0;
}