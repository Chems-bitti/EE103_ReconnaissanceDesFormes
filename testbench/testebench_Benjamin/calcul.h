#ifndef _calcul_h_
#define _calcul_h_

	// Bibliotheques "standards"
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include "myBmpGris.h"
	#include "listeSC.h"
	#include "matrice.h"


	// Pas testé !!
	/** Calcule la distance euclidienne entre deux matrice de moment
  	* @param mat1 la premier matrice
  	* @param mat2 la deuxieme matrice
  	* @return La distance euclidienne des deux matrices
  	*/
	double distance_euclidienne(Matrice mat1, Matrice mat2);

	// Pas testé !!
	/** Calcul la base de Legendre
	  * @param x la valeur souhaité
	  * @param n l'ordre de la base
	  * @return La valeur de x dans la base de Legendre d'ordre n
	  */
	double base_legendre(int x, int n);

	/* Calcul Moments centres normes
	 * @param BmpImg* pic : Pointeur vers l'image BMP
	 * @param int n : Ordre des moments
	 * @return double** eta : Matrice des moments geometriques centres normes
	 */
	Matrice momcentre(BmpImg* pic, int n);

	/* Calcul des moments geometriques
	 * @param BmpImg* pic : Pointeur vers l'image BMP
	 * @param int n : ordre des moments
	 * @return double** mat : matrice des moments geometriques
	 */
	Matrice mom(BmpImg* pic, int n);

	/* Calcul des moments de Legendre
	 * @param BmpImg* pic : Pointeur vers l'image BMP
	 * @param int n : ordre des moments
	 * @return double** mat : matrice des moments de Legendre
	 */
	Matrice mom_legendre(BmpImg* pic, int n);




#endif
