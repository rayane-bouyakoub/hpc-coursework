#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define PI 3.1415926535L

double f (double a) {

    return (double)4.0/(( double )1.0+(a*a));

}

/*

Enter the number of intervals (0 quits ): 1
PI is approximately: 3.2000000000000002 Error is: 0.0584073465000001
Enter the number of intervals (0 quits ): 2
PI is approximately: 3.1623529411764704 Error is: 0.0207602876764703
Enter the number of intervals (0 quits ): 3
PI is approximately: 3.1508492098656036 Error is: 0.0092565563656035
Enter the number of intervals (0 quits ): 4
PI is approximately: 3.1468005183939427 Error is: 0.0052078648939426
Enter the number of intervals (0 quits ): 5
PI is approximately: 3.1449258640033277 Error is: 0.0033332105033277
Enter the number of intervals (0 quits ): 8
PI is approximately: 3.1428947295916889 Error is: 0.0013020760916889

*/

int minimum(int a, int b){

    if (a <= b){

        return a;

    }else{

        return b;

    }

}

// PI is approximately: 3.1424259850010987 Error is: 0.0008333315010987 for number of intervals = 10.

int main (int argc, char** argv){

    int n, i, rang, start, end, chunk;

    double h, sum, x, global_sum;

    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    for (;;) {

        if (rang == 0){

            printf ("Enter the number of intervals (0 quits ): ");

            scanf ("%d" ,&n);

        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (n == 0) break;

        if (n % 4 == 0){

            chunk = n / 4;

        }else{

            chunk = (n / 4) + 1;

        }

        start = rang * chunk + 1;

        end = minimum(start + chunk - 1, n);

        h = ((double)1.0)/(double)n;

        sum = 0.0;

        for (i = start; i <= end; i++) {

            x = h*((double)i-(double)0.5);

            sum += f(x);

        }

        MPI_Reduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rang == 0){

            double pi;

            pi = h*global_sum;

            printf("PI is approximately: %.16f Error is: %.16f\n", pi , fabs(pi-PI));

        }

    }

    MPI_Finalize();

    return 0;
}