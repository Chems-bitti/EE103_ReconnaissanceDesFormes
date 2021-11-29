#ifndef _calcul_h_
#define _calcul_h_

	// Bibliotheques "standards"
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include "myBmpGris.h"
	#include "listeSC.h"
	#include "matrice.h"

	// Pas teste !!
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




#endif
