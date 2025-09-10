#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 8
#define NUM_THREADS 4

double a[SIZE];
double b[SIZE];

struct thread_data {

    int start;

    int end;

};

void* thread_func(void *arg){

    struct thread_data* data = (struct thread_data*) arg;

    int start = data->start;

    int end = data->end;

    free(arg);

    int *sum = malloc(sizeof(int));

    for (int i = start; i < end; i++){

        (*sum) = (*sum) + a[i]*b[i];

    }

    return (void *) sum;

}

int main(){

    pthread_t tid[NUM_THREADS];

    for (int i = 0; i < SIZE; i++){

        //a[i] = i * 0.5;

        a[i] = i + 1;

        //b[i] = i * 0.25;

        b[i] = i;

    }

    struct thread_data *data_1 = malloc(sizeof(struct thread_data));

    data_1->start = 0;

    data_1->end = 2;

    pthread_create(&tid[0], NULL, thread_func, (void*) data_1);


    struct thread_data *data_2 = malloc(sizeof(struct thread_data));

    data_2->start = 2;

    data_2->end = 4;

    pthread_create(&tid[1], NULL, thread_func, (void*) data_2);


    struct thread_data *data_3 = malloc(sizeof(struct thread_data));

    data_3->start = 4;

    data_3->end = 6;

    pthread_create(&tid[2], NULL, thread_func, (void*) data_3);


    struct thread_data *data_4 = malloc(sizeof(struct thread_data));

    data_4->start = 6;

    data_4->end = 8;

    pthread_create(&tid[3], NULL, thread_func, (void*) data_4);



    void *temp_result;

    int sum = 0;

    int partial_sum;

    for (int i = 0; i < NUM_THREADS; i++){

        pthread_join(tid[i], &temp_result);

        partial_sum = *((int *) temp_result);

        sum = sum + partial_sum;

    }

    printf("Result: %d",sum);
    
}

