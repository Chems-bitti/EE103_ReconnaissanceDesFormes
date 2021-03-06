#include "matrice.h"


Matrice creerMatrice(int N){

    Matrice mat = {N};

    mat.tab = malloc((N+1)*sizeof(double*));
    int p;
    for(p = 0 ; p <= N; p++){
        mat.tab[p] = calloc((N+1), sizeof(double));
    }
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
    mat->N = 0;
}


void afficheMatrice(Matrice mat){

    if (mat.tab == NULL){
        printf("Erreur : le tableau de la matrice ne pointe vers rien !\n");
    }else{
        printf("Matrice numero d'ordre\t: %d\n", mat.N);
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
