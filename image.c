#include "image.h"

unsigned char reconstruction_pixel(int x, int y, Matrice mat, Matrice coef, int dimX, int dimY){

    int p,q;
    unsigned char somme1 = 0 ;
    /* il faut que nos variable x et y varient entre -1 et 1
     * Alors on utilise xn et yn ci-dessous
     */
    double xn = 2*x/(double) dimX -1;
    double yn = 2*y/(double) dimY -1;

    for(p = 0; p < mat.N; p++){
        for (q = 0; q < mat.N - p; q++){
            somme1 += mat.tab[p][q] * base_legendre(xn,p, coef) * base_legendre(yn,q, coef);
        }

    }
    if(somme2>1) somme2 = 1; // pour ne pas overflow?
    if(somme2 < 0) somme2 = 0; // pour ne pas underflow?
    // de toute façon on veut pas dépasser 255 et on ne veut pas être négatif
    return (unsigned char) (somme2*255);

}


void reconstruction_image(Matrice mat, BmpImg* pic, Matrice coef){

    for (int x = 0; x < pic->dimX ; x++){
        for (int y = 0 ; y < pic->dimY ; y++){
            setPixel(*pic,reconstruction_pixel(x,y,mat, coef, pic->dimX, pic->dimY),x,y);
        }
    }
}

