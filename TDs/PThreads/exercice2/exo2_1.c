#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void* func(void* arg){

    printf("Hello World! from process %d with pthread_t struct: %lu\n", getpid(), (unsigned long)pthread_self());

    pthread_exit(NULL);

}

int main(){

    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, NULL, func, NULL);
    pthread_create(&thread2, NULL, func, NULL);
    pthread_create(&thread3, NULL, func, NULL);
    pthread_create(&thread4, NULL, func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    return 0;

}