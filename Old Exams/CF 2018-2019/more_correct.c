#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include<unistd.h>

#define N 3
#define M 10

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

    int *nombre_lignes_treated = malloc(sizeof(int));

    (*nombre_lignes_treated) = 0;

    int rang = (*((int *) arg));

    free(arg);

    int j;

    for (int i = rang; i < M; i += N) { 

        (*nombre_lignes_treated)++;

        for (int j = 0; j < M; j++) {

            mat[i][j] *= rang; 

        }
    }

    return (void *)nombre_lignes_treated;

}


int create_threads(int nb_threads, pthread_t * tid){

    int success;

    for (int i = 0; i < nb_threads; i++){

        int *thread_rang = malloc(sizeof(int));

        (*thread_rang) = i + 1;

        success = pthread_create(&tid[i], NULL, traiter_lignes, (void*)thread_rang);

        if (success != 0){

            return -1;

        }

    }

    return 0;

}

int attendre_fin_traitement(int nb_threads, pthread_t *tid){

    void *temp_result;

    int treated_lines;

    int success;

    for (int i = 0; i < nb_threads; i++){

        success = pthread_join(tid[i], &temp_result);

        if (success != 0){

            return -1;

        }

        treated_lines = (*((int *) temp_result));

        free(temp_result);

        printf("Thread %d a traité %d lignes.\n", i+1, treated_lines);

    }

    return 0;

}

int main(){

    init_mat();

    printf("Matrice initiale: \n");

    afficher_mat();

    if (create_threads(N, tid) == -1){

        printf("ERREUR: création threads.\n");

        return EXIT_FAILURE;

    }

    if (attendre_fin_traitement(N, tid) == -1){

        printf("ERREUR: fin traitement.\n");

        return EXIT_FAILURE;

    }

    afficher_mat();

    return EXIT_SUCCESS;

}