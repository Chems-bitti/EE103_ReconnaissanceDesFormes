
#include "image.h"

int main(){

    Matrice mat1 = creerMatrice(2,5);

    mat1.tab[3][2] = 7;

    afficheMatrice(mat1);

    supprMatrice(&mat1);

    /*
    int p;
    for(p = 0 ; p < mat1.N; p++){
        free(mat1.tab[p]);
    }
    free(mat1.tab);
    */

    afficheMatrice(mat1);

    mat1.tab[3][2] = 15;
    mat1.tab[2][2] = 15;

    afficheMatrice(mat1);


    return 0;
}
