#ifndef _image_h_
#define _image_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calcul.h"
#include "gestionfichier.h"

// Pas teste !!
/** Calcule la distance euclidienne entre deux matrice de moment
  * @param mat1 la premier matrice
  * @param mat2 la deuxieme matrice
  * @return La distance euclidienne des deux matrices
  */
double distance_euclidienne(Matrice mat1, Matrice mat2);

// Pas teste !!
/** Reconstruit un pixel de coordonnee (x,y) à partir du Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @return La valeur du pixel
  */
unsigned char reconstruction_pixel(int x, int y, Matrice mat);

/* Faire une fonction reconstruction_image
   qui reconstruit une image pixel par pixel grace a la fonction reconstruction_pixel */

/* Faire un fonction de comapare_image
   qui compare, grace a la fonction distance_euclidienne, une matrice de momen de l'image avec celles des images de la base donne */



#endif
