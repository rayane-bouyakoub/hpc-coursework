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

    #pragma omp parallel num_threads(4)
    {

        double sum_partial = 0;

        #pragma omp sections nowait
        {

            #pragma omp section
            {

                for (int i = 0; i < 64; i++){

                    sum_partial = sum_partial + a[i]*b[i];

                }

            }

            #pragma omp section
            {

                for (int i = 64; i < 128; i++){

                    sum_partial = sum_partial + a[i]*b[i];

                }

            }


            #pragma omp section
            {

                for (int i = 128; i < 192; i++){

                    sum_partial = sum_partial + a[i]*b[i];

                }

            }


            #pragma omp section
            {

                for (int i = 192; i < 256; i++){

                    sum_partial = sum_partial + a[i]*b[i];

                }

            }

        }

        #pragma omp critical
        {

            sum_para = sum_para + sum_partial;

        }

    }

    double sum_seq = produit_scalaire(a, b);

    if (sum_seq == sum_para){

        printf("gg\n");

    }

}