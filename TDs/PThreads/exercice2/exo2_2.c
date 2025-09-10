#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

void* func(void* arg){

    int *rang = (int *)arg;

    printf("Hello World! Thread rank: %d\n", *rang);

    pthread_exit(NULL);

}

int main(){

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++){

        pthread_create(&threads[i], NULL, func, (void *)&i);

    }

    for (int i = 0; i < NUM_THREADS; i++){

        pthread_join(threads[i], NULL);

    }

    return 0;

}