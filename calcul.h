#ifndef _calcul_h_
#define _calcul_h_

// Bibliotheques "standards"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// déclaration de la structure Matrice
typedef struct {
    int num;         // Numéro de la matrice pour l'identifier
    int N;              // Ordre de la Matrice
    double **tab        // Tableau avec les valeurs de la matrice
} Matrice;


/** Calcule la distance euclidienne entre deux matrice de moment
  * @param mat1 la premier matrice
  * @param mat2 la deuxieme matrice
  * @return La distance euclidienne des deux matrices
  */
double distance_euclidienne(Matrice mat1, Matrice mat2);

/** Reconstruit un pixel de coordonnee (x,y) à partir du Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @return La valeur du pixel
  */
unsigned char reconstruction_pixel(int x, int y, Matrice mat);

double base_legendre(int x, int n);


#endif
