#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* Hyper-paramètres du programme */
#define N 3      /* Nombre total de chunks */
#define CHUNKSIZE 4 /* Taille du chunk */

#define CONTINUE 1 // Signal pour continuer le travail
#define STOP 0 // Signal pour indiquer la fin du travail
#define FIRST_REQUEST 2  // Signal pour la première requête


/* Cette fonction sera utilisée pour élire un processus maître d'une manière aléatoire à chaque exécution du programme. */
int random_num(int min, int max) {
    return ((rand() % (max - min + 1)) + min);
}

int main(int argc, char** argv)
{

    srand(time(NULL)); // Pour élire un maître différent à chaque exécution du programme.

    int world_size; // Nombre de processus total.

    int world_rank; // Rang du processus.

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int master_id = random_num(0, world_size-1); // Élire un processus maître d'une manière aléatoire.

    int* memory; /* Pointeur vers la zone mémoire qui sera utilisée par le processus maître pour initialiser le tableau de données

    Les processus esclaves vont utiliser cette zone pour récupérer le chunk.

    */
    
    if (world_rank == master_id){ // On est dans le code du processus maître.

        // Afficher le rang du processus maître pour confirmer qu'il est différent à chaque exécution du programme.
        printf("\nJe suis le processus maitre avec id: %d \n", master_id);

        // Allouer deux zones mémoires, une pour le tableau de données, et l'autre pour stocker le résultat de traitement des différents processus esclaves.
        memory = (int*)malloc((N) * CHUNKSIZE * sizeof(int));
        int *result = (int*)malloc((N) * CHUNKSIZE * sizeof(int));;

        // Initialiser le tableau de données.
        printf("\nTableau de données initial: \n");
        for (int i = 0; i < (N)*CHUNKSIZE; i++) {
            memory[i] = i + 2;
            printf("Tab[%d]: %d\n", i, memory[i]);
        }

        // Allouer un espace mémoire qui sera utilisée pour transmettre les données aux esclaves et pour récupérer les résultats. 
        int* buf = (int*)malloc(CHUNKSIZE * sizeof(int));

        // Deux indices seront utilisés, un pour parcourir le tableau de données, et l'un pour remplir le tableau contenant les résultats.
        int sending = 0;
        int receiving = 0;

        // Pour éviter de signaler la fin de traitement aux processus esclaves plusieurs fois.
        bool already_signaled = false;

        // Tant qu'il y a des données non traitées ou bien on n'a pas fini de remplir les resultats transmis par les processus esclaves.
        while(sending < N || receiving < N){

            // Recevoir une demande de l'esclave et éventuellement les données après traitement.
            MPI_Recv(buf, CHUNKSIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            // On n'écrit pas dans le tableau contenant les résultats s'il s'agit de la première requête de l'esclave.
            if (status.MPI_TAG != FIRST_REQUEST){

                for (int j = 0; j<CHUNKSIZE; j++){

                    result[receiving*CHUNKSIZE + j] = buf[j];

                }
                receiving++;
            }

            if (sending < N) {

                // Il reste des données à traiter, envoyer le prochain chunk.

                for (int j = 0; j < CHUNKSIZE; j++) {

                    buf[j] = memory[sending * CHUNKSIZE + j];

                }

                sending++;

                MPI_Send(buf, CHUNKSIZE, MPI_INT, status.MPI_SOURCE, CONTINUE, MPI_COMM_WORLD);

            } else {

                // Envoyer le signal d'arrêt à tous les esclaves si ce n'est pas déjà fait.

                if (already_signaled == false){

                    for (int i = 0; i < world_size; i++) {

                        if (i != master_id) {

                            MPI_Send(buf, CHUNKSIZE, MPI_INT, i, STOP, MPI_COMM_WORLD);

                        }
                    }
                }
            }

        }

        printf("\n-----------------------------------------\n");

        printf("\nTableau contenant les résultats: \n");

            for (int i = 0; i< (N) * CHUNKSIZE; i++){

                printf("resultat[%d]: %d\n", i, result[i]);

        }

        free(memory);
        free(result);
        free(buf);
    }
    else{

        /* Allouer un espace memoire de taille CHUNK, pour récupérer les données et eventuellement soumettre le résultat après traitement. */

        memory = (int*) malloc(CHUNKSIZE * sizeof(int));

        /*
        
            On distingue entre les premières requêtes avec les autres,

            Car la première requête n'envoie pas des données, donc on doit pas les écrire dans le tableau résultat.
        
        */

        bool first_ever_request = true;

        while(1){

            if (first_ever_request){

                /* Demande des données */

                MPI_Send(memory, CHUNKSIZE, MPI_INT, master_id, FIRST_REQUEST, MPI_COMM_WORLD);

                first_ever_request = false;  /* Pour dire que les prochaines requêtes envoient des données. */

            }

            /* Récupérer le chunk du processus maître (ou éventuellement le signal indiquent la fin du travail). */

            MPI_Recv(memory, CHUNKSIZE, MPI_INT, master_id, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == STOP){

                break; /* On arrête le travail si indication de fin. */

            }

            else {

                /* Si la fin n'a pas été indiquée, on traite le chunk reçu par le maître en élevant au carrées ses éléments. */

                for (int i = 0; i < CHUNKSIZE; i++){

                    memory[i] = memory[i] * memory[i];

                }

                /* Transmission du résultat, et demande d'un autre chunk (flag CONTINU) */

                MPI_Send(memory, CHUNKSIZE, MPI_INT, master_id, CONTINUE, MPI_COMM_WORLD);

            }

        }

        free(memory);

    }

    MPI_Finalize();

    return 0;

}