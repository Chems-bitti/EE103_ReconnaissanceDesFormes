#include "matrice.h"

Matrice creerMatrice(int num, int N){

    Matrice mat = {num, N};

    double **tab = malloc(N*sizeof(double*));
    int p;
    for(p = 0 ; p <= N; p++){
        tab[p] = calloc(N, sizeof(double));
    }
    mat.tab = tab;
    return mat;
}

void supprMatrice(Matrice *mat){

    if (mat->tab != NULL){
        int p;
        for(p = 0 ; p <= mat->N; p++){
            free(mat->tab[p]);
        }
        free(mat->tab);
        mat->tab = NULL;
    }
    mat->num = 0;
    mat->N = 0;
}

void afficheMatrice(Matrice mat){

    if (mat.tab == NULL){
        printf("Erreur : le tableau de la matrice %d ne pointe vers rien !\n", mat.num);
    }else{
        printf("Matrice numero\t: %d\n\t\ordre\t: %d\n", mat.num, mat.N);
        printf("\t----\t-----\t----\n");
        int p,q;
        for(p = 0 ; p <= mat.N; p++){
            for(q = 0 ; q <= mat.N; q++){
                printf("%f\t",mat.tab[p][q]);
            }
            printf("\n");
        }
        printf("\t----\t-----\t----\n");
    }
}
