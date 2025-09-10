#include <stdio.h>
#include <omp.h>
#define NUMBER 100000

int main () {

    int i, j, val, total = 0 , N = NUMBER;

    double start, end, time;

    start = omp_get_wtime();

    for (i = 2 ; i <= N ; i++)
    {
        val = 1;
        for (j = 2 ; j < i ; j++)
        {
            if (i % j == 0)
            {
                val = 0;
                break;
            }
        }
        total = total + val;
    }

    end = omp_get_wtime();
    time = end-start;
    printf("Done. total = %d\n", total);
    printf("Sequential time %f seconds\n", time);

    total = 0;

    omp_set_num_threads(8);

    start = omp_get_wtime();

    #pragma omp parallel private(j, val)
    {
        #pragma omp for reduction(+:total) schedule(dynamic)
        for (i = 2 ; i <= N ; i++)
        {
            val = 1;
            for (j = 2 ; j < i ; j++)
            {
                if (i % j == 0)
                {
                    val = 0;
                    break;
                }
            }
            total = total + val;
        }
    }
    end = omp_get_wtime();

    time = end-start;
    printf("Done. total = %d\n", total);
    printf("Parallel time %f seconds\n", time);

    return (0);
}