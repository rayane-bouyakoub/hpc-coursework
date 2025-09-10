#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

bool estPremier(int N){

    if (N <2){

        return false;

    }

    for (int i = 2; i < N; i++){

        if (N%i == 0){

            return false;

        }

    }

    return true;

}


int main(void){

    int num = 500;

    int sum = 0;

    #pragma omp parallel for schedule(dynamic) reduction(+:sum)
    for (int j = 2; j <= num; j++){
        if (estPremier(j)){
            sum = sum + 1;
        }
    }

    printf("Sum: %d.\n", sum);

}