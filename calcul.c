#include "calcul.h"

double distance_euclidienne(Matrice mat1, Matrice mat2){

    int i,j;
    double res= 0;
    
    if (mat1.DIMx != mat2.DIMx || mat1.DIMy != mat2.DIMy){
        printf("ERREUR : Les matrices ne sont pas de meme dimension\n");
        return 0;
    }else{
        for(i = 0 ; i < mat1.DIMx; i++){
            for(j = 0 ; j < mat1.DIMy; j++){
                res = res + (mat1.tab[i][j]-a2[i][j])*(a1[i][j]-a2[i][j]);
            }
        }
    }
    res = sqrt(res);

    return res;

}


unsigned char reconstruction_pixel(int x, int y, Matrice mat){

    int p,q;
    unsigned char somme1 = 0 ;
    unsigned char somme2 = 0;

    for(p = 0; p < N; p++){
        for (q = 0; q < N-p; q++){
            somme1 = somme1 + (mat[p][q] * base_legendre(x,p) * base_legendre(y,q));
        }
        somme2 = somme2 + somme1;
        somme1 = 0;
    }

    return somme2;
}



/*double distance_euclidienne(double **a1, double **a2, int dimx, int dimy){

    int i,j;
    double res= 0;

    for(i = 0 ; i < dimx; i++){
        for(j = 0 ; j < dimy ; j++){
            res = res + (a1[i][j]-a2[i][j])*(a1[i][j]-a2[i][j]);
        }
    }
    res = sqrt(res);

    return res;

}*/
