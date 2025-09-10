#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include<unistd.h>

#define N 3
#define M 5

int mat[M][M];

// Pour récupérer la prochaine ligne à traiter.
int prochaine_ligne = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Nombre de lignes traitées.
int number_lines = 0;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;

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

    int current_ligne;

    int rang = (*((int *) arg));

    free(arg);

    int j;

    while(true){

        pthread_mutex_lock(&mutex);

        current_ligne = prochaine_ligne;

        prochaine_ligne++;

        pthread_mutex_unlock(&mutex);

        if (current_ligne >= M){

            break;

        }

        for (j = 0; j < M; j++){

            mat[current_ligne][j] = mat[current_ligne][j] * rang;

        }

        pthread_mutex_lock(&mutex_2);

        number_lines++;

        pthread_mutex_unlock(&mutex_2);

    }

    return NULL;

}


int create_threads(int nb_threads, pthread_t * tid){

    int success;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for (int i = 0; i < nb_threads; i++){

        int *rang = malloc(sizeof(int));

        (*rang) = i + 1;

        success = pthread_create(&tid[i], &attr, traiter_lignes, (void*) rang);

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

    pthread_t tid[N];

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