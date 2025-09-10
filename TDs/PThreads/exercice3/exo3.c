#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* partial_sum(void* arg){

    long int* tab_thread = (long int *) arg;

    int *sum;

    (*sum) = 0;

    for (int j = 0; j < 4; j++){

        (*sum) = (*sum) + tab_thread[j];

    }

    pthread_exit(sum);    

}

int main(){

    long int tab[15];

    int i;

    pthread_t thread1, thread2, thread3;

    for (i = 0; i < 15; i++){

        tab[i] = tab[i] + 1;

    }

    long int tab1[3];

    long int tab2[4];

    long int tab3[4];

    long int tab4[4];

    for (i = 0; i < 3; i++){

        tab1[i] = tab[i];

    }

    for (i = 0; i < 4; i++){

        tab2[i] = tab[i+3];
        tab3[i] = tab[i+7];
        tab4[i] = tab[i+11];

    }

    pthread_create(&thread1, NULL, (void*) tab1, NULL);

    return 0;

}