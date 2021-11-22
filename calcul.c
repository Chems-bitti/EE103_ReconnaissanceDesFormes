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
