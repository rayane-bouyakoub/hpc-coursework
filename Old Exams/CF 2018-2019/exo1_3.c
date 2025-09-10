#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include<unistd.h>

#define N 3
#define M 10

// Nombre de lignes traitées.
int number_lines = 0;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;

int mat[M][M];

pthread_t tid[N];

void init_mat(void){

    for (int i = 0; i < M; i++){

        for (int j = 0; j < M; j++){

            mat[i][j] = 1;

        }

    }

}

void afficher_mat(void){

    for (int i = 0; i < M; i++){

        for (int j = 0; j < M; j++){

            printf("%d  ", mat[i][j]);

        }

        printf("\n");

    }

}


void *traiter_lignes(void *arg){

    int rang = (*((int *) arg));

    free(arg);

    int j;

    for (int i = rang; i < M; i += N) { 

        for (int j = 0; j < M; j++) {

            mat[i][j] *= rang; 

        }

        pthread_mutex_lock(&mutex_2);

        number_lines++;

        pthread_mutex_unlock(&mutex_2);

    }

    pthread_exit(NULL);

}


int create_threads(int nb_threads, pthread_t * tid){

    int success;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < nb_threads; i++){

        int *thread_rang = malloc(sizeof(int));

        (*thread_rang) = i;

        success = pthread_create(&tid[i], NULL, traiter_lignes, (void*)thread_rang);

        if (success != 0){

            return -1;

        }

    }

    pthread_attr_destroy(&attr);

    return 0;

}

void attendre_fin_traitement(){

    int num;

    while (true){

        pthread_mutex_lock(&mutex_2);

        num = number_lines;

        pthread_mutex_unlock(&mutex_2);

        if (num == M){

            break;

        }    

    }

    printf("Matrice finale: \n");

    afficher_mat();

}

int main(){

    init_mat();

    printf("Matrice initiale: \n");

    afficher_mat();

    if (create_threads(N, tid) == -1){

        printf("ERREUR: création threads.\n");

        return EXIT_FAILURE;

    }

    attendre_fin_traitement();

    return EXIT_SUCCESS;

}