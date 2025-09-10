/******************HPC TP CUDA 2024/2025******************/
/******************ABOUD IBRAHIM**************************/
/*****************BOUYAKOUB RAYANE************************/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/** LES HYPERPARAMETRES -variables global- **/
#define RESX 1024
#define RESY 1024
const int resolutionX = RESX;
const int resolutionY = RESY;

double rectangleWidth = 0.00000005;
double rectangleCenterX = -1.86216646;
double rectangleCenterY = 0.0;

int iterationsMax = 10000;
int result_matrix[RESY][RESX];
int Nb_threads_per_block = 1024;

/*valeurs constantes qui sont necessaire a utiliser par chaque thread*/
// resolution de l'image [0] pour RESX et [1] pour RESY [2] pour nbIteration max
__constant__ int resXY[3];
// coordonné et taille [0] pour rectangleWidth [1] pour rectangleCenterX et [2] pour rectangleCenterY
__constant__ double coords[3];

/********************************************************/

/* FONCTION DE SAUVGARDE D'IMAGE DANS LA MEMOIRE SECONDAIRE -sequentiel- */
__host__ void savePPM(char *filename, int matrix[resolutionY][resolutionX])
{
      // ouvrir une image
      FILE *image = fopen(filename, "w");
      if (image == NULL)
      {
            perror("Error opening file");
            return;
      }

      // ecrire le type, la resolution, et la valeur max de chaque couleur R G B
      fprintf(image, "P3\n");
      fprintf(image, "%d %d\n", resolutionX, resolutionY);
      fprintf(image, "255\n");

      // pour chaque pixel dans l'image
      for (int y = 0; y < resolutionY; y++)
      {
            for (int x = 0; x < resolutionX; x++)
            {
                  // acceder a la case correspondant au pixel en question et ecrire sa couleur "3 entiers R G B" du pixel sur le fichier
                  // ps : la couleur d'un pixel correspond au nombre d'iteration d'echappement "ou c'est noir si le point appartient a l'ensemble"
                  fprintf(image, "%d %d %d\n", (int)(matrix[y][x]) % 255, (int)(matrix[y][x]) % 255, (int)(matrix[y][x] * 10) % 255);
            }
      }

      fclose(image);
}

/****************FONCTION KERNEL*******************/
__global__ void calculatePixel(int *gpu_matrix)
{
      // calcule des indexes du pixel dans la matrice - le pixel correspondant au identifiants du thread et du block contenant le thread -
      int i = blockIdx.x * blockDim.x + threadIdx.x;
      int j = blockIdx.y * blockDim.y + threadIdx.y;

      // recuperation des valeurs constantes
      int resX = resXY[0];
      int resY = resXY[1];
      int maxIter = resXY[2];
      double rectW = coords[0];
      double rectCX = coords[1];
      double rectCY = coords[2];

      // calcule des coordonnés necessaires
      double step = rectW / ((double)resX);
      double cx = rectCX - (rectW / 2.0) + j * step;
      double cy = rectCY + (rectW * resolutionY / resY / 2.0) - i * step;

      // on etudie la suite : z= z^2 + c | tel que ( c = x + i.y ) et z0 = x0+i.y0 = 0 par defaut
      int counter = 0;
      double currentX;
      double currentY;
      double x0 = 0.0;
      double y0 = 0.0;
      if (i < resY && j < resX)
      {
            do
            {
                  // Zn+1 = Zn ^ 2 + c
                  currentX = x0 * x0 - y0 * y0 + cx;
                  currentY = 2 * x0 * y0 + cy;
                  x0 = currentX;
                  y0 = currentY;

                  // decrementer le nombre d'iteration max
                  maxIter--;
                  // incrementer le compteur d'iteration courante
                  counter++;

                  // la suite diverges vers l'infini si |y| ou |x| depasse 2,
                  // si le compteur depasse le nombre d'iteration max, on suppose alors
                  // que la suite est borné "ne diverge pas vers l'infini"
                  // donc un nombre plus grands des iterations augmente la precision du calcul
            } while (maxIter != 0 && (currentX * currentX + currentY * currentY) < 4);

            // first result, the point C turns out to be indeed from the julia set
            if (maxIter == 0)
            {
                  // si la suite est borné alors le nombre complex C appartient a l'ensemble
                  counter = 0;
            }
            // si la suite diverge vers l'infini, alors C n'appartient pas a l'ensemble,
            // on retourn le nombre d'iterations necessaire pour que la suite echappe le
            // cercle de centre (0,0) et de rayon 2

            gpu_matrix[i * 1024 + j] = counter;
      }
}

int main(void)
{
      // creation des variable que seront copié vers la zone constante du GPU
      int host_resXY[3] = {RESX, RESY, iterationsMax};
      double host_coords[3] = {rectangleWidth, rectangleCenterX, rectangleCenterY};

      // creation du pointeur vers la matrice gpu
      int *gpu_matrix;

      cudaMalloc((void **)&gpu_matrix, RESX * RESY * sizeof(int));

      // Copier les valeur vers l'espace memoire constante du GPU
      cudaMemcpyToSymbol(resXY, host_resXY, 3 * sizeof(int));
      cudaMemcpyToSymbol(coords, host_coords, 3 * sizeof(double));

      // definir l'organisation des threads dans les block, et des blocks dans la grille
      dim3 block(sqrt(Nb_threads_per_block), sqrt(Nb_threads_per_block));
      dim3 grid(RESY / sqrt(Nb_threads_per_block), RESX / sqrt(Nb_threads_per_block));

      // demmarer le timer
      cudaEvent_t start, stop;
      float elapsedTime;
      cudaEventCreate(&start);
      cudaEventCreate(&stop);

      cudaEventRecord(start, 0);

      // appelle du kernel "utilisation du device pour faire les taches"
      calculatePixel<<<grid, block>>>(gpu_matrix);
      // syncrhonisation des threads
      cudaDeviceSynchronize();

      cudaEventRecord(stop, 0);

      // arreter le timer
      cudaEventSynchronize(stop);

      cudaEventElapsedTime(&elapsedTime, start, stop);
      // afficher le temps de calcul
      printf("Elapsed time : %f ms\n", elapsedTime);

      // copier le resultat obtenu en GPU vers la memoire en CPU
      cudaMemcpy(result_matrix, gpu_matrix, RESX * RESY * sizeof(int), cudaMemcpyDeviceToHost);
      // liberer l'espace memoire aloué en GPU
      cudaFree(gpu_matrix);
      // sauvgarder l'image par le CPU
      savePPM("mandelbrot.ppm", result_matrix);
      return 0;
}
