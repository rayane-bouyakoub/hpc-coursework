# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# define PI 3.1415926535L

double f (double a) {

    return (double)4.0/(( double )1.0+(a*a));

}

int main (){

    int n, i;

    double h, pi, sum, x;

    for (;;) {

        printf ("Enter the number of intervals (0 quits ): ");

        scanf ("%d" ,&n);

        if (n ==0) break ;

        h = ((double)1.0)/(double)n;

        sum = 0.0;

        for (i =1; i <=n; i ++) {

            x = h*((double)i-(double)0.5);

            sum += f(x);

        }

        pi = h*sum ;

        printf("PI is approximately: %.16f Error is: %.16f\n", pi , fabs(pi-PI));

    }

    return 0;
}