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

    #pragma omp parallel for reduction(+:sum_para)
    for (int i = 0; i < SIZE; i++){
        sum_para = sum_para + a[i]*b[i];
    }

    double sum_seq = produit_scalaire(a, b);

    if (sum_seq == sum_para){

        printf("gg\n");

    }

}