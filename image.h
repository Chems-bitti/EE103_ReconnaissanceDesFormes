#ifndef _image_h_
#define _image_h_

// Bibliotheques
#include "calcul.h"
#include "gestionfichier.h"


/** Reconstruit un pixel de coordonnee (x,y) a partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre a passer a la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
unsigned char reconstruction_pixel(int x, int y, Matrice mat, Matrice coef, int dimX, int dimY);


/** Reconstruit une image de coordonnee (x,y) a partir d'une Matrice de moment de Legendre et d'une image bmp
  * @param mat Matrice de moment de Legendre
  * @param *pic image que l'on va reconstruire
  * @param Matrice coef : coefficients du polynome de legendre a passer a la fonction reconstruction pixel
  */
void reconstruction_image(Matrice mat, BmpImg* pic, Matrice coef);


/** Creer et reconstruit une image
  * @param mat Matrice de moment de Legendre
  * @param dossier ou se trouvera l'image reconstruite
  * @param nom de le l'image
  * @param tailleX Taille horizontal de l'images reconstruite
  * @param tailleY Taille vertical de l'images reconstruite
  */
void creation_image(Matrice mat, char* dossier, char *nom, int tailleX, int tailleY);


#endif
