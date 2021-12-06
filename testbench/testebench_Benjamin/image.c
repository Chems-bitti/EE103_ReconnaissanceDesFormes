#include "image.h"

unsigned char reconstruction_pixel(int x, int y, Matrice mat){

    int p,q;
    unsigned char somme1 = 0;
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

void reconstruction_image(Matrice mat, BmpImg* pic){

    for (int x = 0; x < pic->dimX ; x++){
        for (int y = 0 ; y < pic->dimY ; y++){
            pic->img[x][y]=reconstruction_pixel(x,y,mat);
        }
    }
}
