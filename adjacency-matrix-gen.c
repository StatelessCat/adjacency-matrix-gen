#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char **argv) {

    /* compteurs de boucles */
    int i, j;
    
    /* le fichier de sortie */
    FILE * outputFile;

    /* taille de la matrice */
    int size;

    /* contiendra la matrice d'adj */
    int ** arr;

    /* initialisation de la graine de generation pseudo-aléatoire*/
    srand(time(NULL));

    /* vérif de la conformité de la commande */
    if (argc < 3) {
        fprintf(stderr, "please, use:  %s <size> <outputFile.csv>", argv[0]);        
        return 1;
    }
    
    size = atoi(argv[1]);

    /* allocation dynamique de la mémoire */
    arr = malloc(sizeof(int *) * size);
    for(i = 0; i < size; ++i) {
        arr[i] = malloc(sizeof(int) * size);
    }

    /* remplissage de la partie triangulaire inf */
    for(i = 0; i < size; ++i) {
        for(j = 0; j < i; ++j) {
            arr[i][j] = rand() % 2;
        }
    }

    /* remplissage de la diagonale avec 0 car 
     * on ne souhaite pas qu'il existe une arete
     * reliant un sommet à lui même 
     */
    for(i = 0; i < size; ++i) {
        arr[i][i] = 0;
    }

    /* remplissage de la partie triangulaire sup */
    for(i = 0; i < size; ++i) {
        for(j = i; j < size; ++j) {
            arr[i][j] = arr[j][i];
        }
    }

    /* ouverture en écriture du fichier de sortie: */
    outputFile = fopen(argv[2], "w");

    /* écriture dans le fichier */
    for(i = 0; i < size; ++i) {
        for(j = 0; j < size - 1; ++j) {
            fprintf(outputFile, "%d;", arr[i][j]);
        }
        fprintf(outputFile, "%d\n", arr[i][size - 1]);
    }

    fclose(outputFile);
    free(arr);
    return 0;
}