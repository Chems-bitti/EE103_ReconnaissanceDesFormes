#include "calcul.h"

double distance_euclidienne(double **a1, double **a2, int dimx, int dimy){

    int i,j;
    double res= 0;

    for(i = 0 ; i < dimx; i++){
        for(j = 0 ; j < dimy ; j++){
            res = res + (a1[i][j]-a2[i][j])*(a1[i][j]-a2[i][j]);
        }
    }
    res = sqrt(res);

    return res;

}

