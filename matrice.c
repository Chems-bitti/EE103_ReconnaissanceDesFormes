#include "matrice.h"


void afficheMatrice(Matrice mat){

    printf("Matrice numero : %d et d'ordre : %d\n\n", mat.num, mat.N);

    int p,q;
    for(p = 0 ; p < mat.N; p++){
        for(q = 0 ; q < mat.N; q++){
            printf("%f\t",mat.tab[p][q]);
        }
        printf("\n");
    }
}
