#include <stdio.h>
#include <omp.h>
#include <stdio.h>
#define SIZE 10

int main ()
{
    double sum , a[SIZE], b[SIZE];
    sum = 0.;
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
        sum = sum + a[i]*b[i];
    }
    printf("sum = %g\n", sum);

    sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i =0; i < SIZE; i++){
       sum = sum + a[i]*b[i]; 
    }

    printf("sum = %g\n", sum);

    int sum_1 = 0;
    int sum_2 = 0;

    #pragma omp parallel 
    {
        #pragma omp single
        {
            #pragma omp task
            {
                for (int i=0; i < SIZE/2; i++){
                    sum_1 = sum_1 + a[i]*b[i]; 
                }    
            }
            #pragma omp task
            {
                for (int i=SIZE/2; i < SIZE; i++){
                    sum_2 = sum_2+ a[i]*b[i]; 
                }   
            }
            #pragma omp taskwait
            sum = sum_1+sum_2;
        }
    }

    printf("sum = %g\n", sum);

    return 0; 
}