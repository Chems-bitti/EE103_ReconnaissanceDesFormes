#ifndef _image_h_
#define _image_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calcul.h"
#include "gestionfichier.h"


// Pas testé !!
/** Reconstruit un pixel de coordonnee (x,y) à partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @return La valeur du pixel
  */
unsigned char reconstruction_pixel(int x, int y, Matrice mat);

// Pas testé !!
/** Reconstruit une image de coordonnee (x,y) à partir d'une Matrice de moment de Legendre et d'une image bmp
  * @param mat Matrice de moment de Legendre
  * @param *pic image que l'on va reconstruire
  */
void reconstruction_image(Matrice mat, BmpImg* pic);



/* Faire une fonction compare_image
   qui compare, grace a la fonction distance_euclidienne, une matrice de moment de l'image avec celles des images de la base de donnee */



#endif
