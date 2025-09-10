#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 256

double produit_scalaire(double* a, double* b){

    double sum = 0;

    for (int i = 0; i < SIZE; i++){

        sum = sum + a[i]*b[i];

    }

    return sum;

}

int main(){

    double a[SIZE];

    double b[SIZE];

    for (int i = 0; i < SIZE; i++){

        a[i] = i*0.5;

        b[i] = i*0.25;

    }

    double sum_para = 0;

    double sum1, sum2, sum3, sum4;


    #pragma omp parallel num_threads(4)
    {

        #pragma omp single
        {

            #pragma omp task
            {
                for (int i = 0; i < 64; i++){

                    sum1 = sum1 + a[i]*b[i];

                }

            }

            #pragma omp task
            {

                for (int i = 64; i < 128; i++){

                    sum2 = sum2 + a[i]*b[i];

                }

            }

            #pragma omp task
            {

                for (int i = 128; i < 192; i++){

                    sum3 = sum3 + a[i]*b[i];

                }

            }

            #pragma omp task
            {

                for (int i = 192; i < 256; i++){

                    sum4 = sum4 + a[i]*b[i];

                }

            }

            #pragma omp taskwait

            sum_para = sum1 + sum2 + sum3 + sum4;

        }
    }

    double sum_seq = produit_scalaire(a, b);

    if (sum_seq == sum_para){

        printf("gg\n");

    }

}