#ifndef _calcul_h_
#define _calcul_h_

// Bibliotheques "standards"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myBmpGris.h"
#include "listeSC.h"
#include "matrice.h"

/** Calcule la distance euclidienne entre deux matrice de moment
  * @param mat1 la premier matrice
  * @param mat2 la deuxieme matrice
  * @return La distance euclidienne des deux matrices
  */
double distance_euclidienne(Matrice mat1, Matrice mat2);

double base_legendre(int x, int n);


#endif
