#include "calcul.h"

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
