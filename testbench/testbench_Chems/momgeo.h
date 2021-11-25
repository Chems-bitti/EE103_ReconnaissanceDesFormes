#ifndef _momgeo_h_
#define _momgeo_h_



	// Inclusion des bibliothèques myBmpGris.h et math.h

	#include "myBmpGris.h"
	#include <math.h>

	/* Fonction de création d'une matrice
	 * @param int x: largeur de la matrice
	 * @param int y : ueur de la matrice
	 * @return pointeur vers le début de la matrice
	 */
	 long double** alloc(int x, int y);

	/* Fonction de destruction d'une matrice
	 * @param long double*** mat : pointeur vers le début de la matrice
	 * @param int dimY : ueur de la matrice
	 */
	void freemat( long double*** pmat, int dimY);
	
	/* Fonction des calculs des moments
	 * @param Pix* root : pointeur vers la tête de notre liste chainée
	 * @param BmpImg* pic : pointeur vers l'image
	 * @param N : l'ordre choisit
	 * @return Matrice de long double
	 */
	 long double** mom(BmpImg* pic, int N);
	
	/* Fonction d'écriture des valeurs du moment dans un fichier
	 * @param char* fnam : nom du fichier
	 * @param long double** mat : matrice contenant la valeur des moments
	 * @param int dimX : Largeur de la matrice
	 * @param int dimY : Longueur de la matrice
	 */
	void Ecriture_Moments(char* fname,  long double** mat, int dimX, int dimY);






#endif
