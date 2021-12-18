#ifndef _image_h_
#define _image_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calcul.h"
#include "gestionfichier.h"


// Marche nickel
/** Reconstruit un pixel de coordonnee (x,y) a partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre a passer a la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
unsigned char reconstruction_pixel(int x, int y, Matrice mat, Matrice coef, int dimX, int dimY);


// Marche nickel
/** Reconstruit une image de coordonnee (x,y) a partir d'une Matrice de moment de Legendre et d'une image bmp
  * @param mat Matrice de moment de Legendre
  * @param *pic image que l'on va reconstruire
  * @param Matrice coef : coefficients du polynome de legendre a passer a la fonction reconstruction pixel
  */
void reconstruction_image(Matrice mat, BmpImg* pic, Matrice coef);



#endif
