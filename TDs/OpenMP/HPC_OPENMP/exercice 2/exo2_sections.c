#include <omp.h>
#include <stdio.h>

int main() {
    int n = 64;
    int a[64], b[64], c[64];

    omp_set_num_threads(8);

    // Initialisation des tableaux
    for (int i = 0; i < n; i++) {
        a[i] = i;  // Exemple : a[i] = i
        b[i] = 2 * i;  // Exemple : b[i] = 2 * i
    }

    for (int i = 0; i < n; i++){
        c[i] = a[i] + b[i];
    }

    // Affichage du résultat
    for (int i = 0; i < n; i++) {
        printf("c[%d] = %d\n", i, c[i]);
    }

    for (int i = 0; i < n; i++){
        c[i] = 0;
    }


    #pragma omp parallel
    {

        #pragma omp sections
        {

            #pragma omp section
            {
                for (int i = 0; i<=4; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }


            #pragma omp section
            {
                for (int i = 8; i<=12; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }


            #pragma omp section
            {
                for (int i = 16; i<=20; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }

            #pragma omp section
            {
                for (int i = 24; i<=28; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }

            
            #pragma omp section
            {
                for (int i = 32; i<=36; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }


            #pragma omp section
            {
                for (int i = 40; i<=44; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }


            #pragma omp section
            {
                for (int i = 48; i<=52; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }
            }
            

            #pragma omp section
            {
                for (int i = 56; i<=60; i=i+4){
                    c[i] = a[i] + b[i];
                    c[i+1] = a[i+1] + b[i+1];
                    c[i+2] = a[i+2] + b[i+2];
                    c[i+3] = a[i+3] + b[i+3];
                }           
            }


        }
    }
   
    // Affichage du résultat
    for (int i = 0; i < n; i++) {
        printf("c[%d] = %d\n", i, c[i]);
    }

    return 0;
}
