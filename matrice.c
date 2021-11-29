#include "matrice.h"

Matrice creerMatrice(num, N){

    Matrice mat = {num, N};

    double **tab = malloc(N*sizeof(double*));
    int p;
    for(p = 0 ; p < N; p++){
        tab[p] = calloc(N, sizeof(double));
    }
    mat.tab = tab;
    return mat;
}

void supprMatrice(Matrice *mat){

    int p;
    for(p = 0 ; p < mat->N; p++){
        free(mat->tab[p]);
    }
    free(mat->tab);
    mat->num = 0;
    mat->N = 0;
}

void afficheMatrice(Matrice mat){

    printf("Matrice numero : %d\n\t\ordre : %d\n\n", mat.num, mat.N);

    int p,q;
    for(p = 0 ; p < mat.N; p++){
        for(q = 0 ; q < mat.N; q++){
            printf("%f\t",mat.tab[p][q]);
        }
        printf("\n");
    }
}
