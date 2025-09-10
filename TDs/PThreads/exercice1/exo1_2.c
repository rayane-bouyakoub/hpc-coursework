#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int done = 0;

void* f1(){

    printf("Hello ");

    done = 1;

    pthread_exit(NULL);

}

void* f2(){

    while (done == 0) {}

    printf("World!");

    pthread_exit(NULL);

}


int main(){

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, f1, NULL);

    pthread_create(&thread2, NULL, f2, NULL);

    pthread_join(thread1, NULL);

    pthread_join(thread2, NULL);

    return 0;

}