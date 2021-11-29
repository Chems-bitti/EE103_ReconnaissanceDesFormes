#include "image.h"

unsigned char reconstruction_pixel(int x, int y, Matrice mat){

    int p,q;
    unsigned char somme1 = 0 ;
    unsigned char somme2 = 0;

    for(p = 0; p < mat.N; p++){
        for (q = 0; q < mat.N - p; q++){
            somme1 += mat.tab[p][q] * base_legendre(x,p) * base_legendre(y,q);
        }
        somme2 += somme1;
        somme1 = 0;
    }
    return somme2;
}

double distance_euclidienne(Matrice mat1, Matrice mat2){

    int p,q;
    double res= 0;

    if (mat1.N != mat2.N){
        printf("ERREUR : Les matrices ne sont pas de meme ordre\n");
        return 0;
    }else{
        for(p = 0 ; p < mat1.N; p++){
            for(q = 0 ; q < mat1.N - p;q++){
                res += pow(mat1.tab[p][q]-mat2.tab[p][q],2);
            }
        }
    }
    return sqrt(res);
}
