#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* print_message(void* arg){

    char *msg = (char*) arg;

    printf("%s", msg);

    pthread_exit(NULL);

}

int main(){

    pthread_t thread1, thread2;

    char* msg1 = "Hello ";

    char* msg2 = "World!";

    pthread_create(&thread1, NULL, print_message, (void*) msg1);

    pthread_create(&thread2, NULL, print_message, (void*) msg2);

    pthread_join(thread1, NULL);

    pthread_join(thread2, NULL);

    return 0;

}