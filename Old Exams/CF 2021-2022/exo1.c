#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5
#define MESSAGE_LENGTH 7

void* verify_word(void *arg){

    int *row = (int *) arg;

    int sum = 0;

    int j;

    bool *correct = malloc(sizeof(bool));

    // printf("The message: ");

    for (j = 1; j < MESSAGE_LENGTH+1; j++){

        if (row[j] == 1){

            sum = sum + 1;

        }

    }

    // printf("\nIs: ");

    if (sum % 2 == row[0]){

        (*correct) = true;

        //printf("Correct.\n");

    }
    else{

        (*correct) = false;

        //printf("False.\n");

    }

    pthread_exit((void *)correct);

}

int main(){

    int m[N][MESSAGE_LENGTH+1] = {{1,0,0,0,0,0,0,0},
        {1,0,0,0,1,0,1,0},
        {0,0,0,1,1,0,0,1},
        {1,0,0,1,1,0,0,1},
        {1,0,0,1,1,1,1,1}
    };

    pthread_t tid[N];

    for (int i = 0; i < N; i++){

        pthread_create(&tid[i], NULL, verify_word, (void*)m[i]);

    }

    void *result;

    for (int i = 0; i < N; i ++){

        printf("The message: ");

        for (int j = 1; j < MESSAGE_LENGTH+1; j++){

            printf("%d  ", m[i][j]);

        }

        pthread_join(tid[i], &result);

        bool correct = *((bool *)result);

        free(result);

        if (correct){

            printf(", is correct.\n");

        }
        else{

            printf(", is false.\n");

        }

    }

    return 0;

}