#include "image.h"

unsigned char reconstruction_pixel(int x, int y, Matrice mat, Matrice coef, int dimX, int dimY){

    int p,q;
    double somme = 0 ;
    /* il faut que nos variable x et y varient entre -1 et 1
     * Alors on utilise xn et yn ci-dessous
     */
    double xn = 2*x/(double) dimX -1;
    double yn = 2*y/(double) dimY -1;

    for(p = 0; p < mat.N; p++){
        for (q = 0; q < mat.N - p; q++){
            somme += mat.tab[p][q] * base_legendre(xn,p, coef) * base_legendre(yn,q, coef);
        }

    }
    if(somme>1) somme = 1; // pour ne pas overflow
    if(somme < 0) somme = 0; // pour ne pas underflow

    return (unsigned char) (somme*255);
}


void reconstruction_image(Matrice mat, BmpImg* pic, Matrice coef){

    for (int x = 0; x < pic->dimX ; x++){
        for (int y = 0 ; y < pic->dimY ; y++){
            setPixel(*pic,reconstruction_pixel(x,y,mat, coef, pic->dimX, pic->dimY),x,y);    //assigner la valeur de la fonction reconstruction pixel aux pixel x et y;
                                                                                             //de cette mani?re on reforme chaque pixel puis l'image enti?re
        }
    }
}


void creation_image(Matrice mat, char* dossier, char *nom, int tailleX, int tailleY){

    printf(" -- Veuillez patienter pendant la reconstruction de l'image... -- \n");

    BmpImg pic = createBmpImg(nom, tailleX, tailleY); //Creation image
    Matrice coef = coefLegendre(Ordre);		   // Calculs coefficients Legendre
    reconstruction_image(mat, &pic, coef);         // Reconstruction
    supprMatrice (&coef);			   // Desallocation Matrice coef
    char tmp[taillechemin];             // Chaine temporaire pour prendre le nom du fichier et du dossier
    strcpy(tmp, dossier);               // tmp prend le nom du dossier
    writeBmpImage(strcat(tmp, nom), &pic);	   // Ecriture de l'image reconstruite
    freeBmpImg(&pic);				   // Desallocation image reconstruite

    printf(" -- '%s' disponnible dans le repertoire '%s' --\n", nom, dossier);
}
