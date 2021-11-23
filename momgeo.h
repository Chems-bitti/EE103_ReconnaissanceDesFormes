#ifndef _momgeo_h_
#define _momgeo_h_



	// Inclusion des bibliothèques myBmpGris.h et math.h

	#include "myBmpGris.h"
	#include <math.h>

	/***************** déclaration de la structure Pix(el) **************

	 * - Champ x : coordonnée x du pixel
	 * - Champ y : coordonnée y du pixel
	 * - Champ next : pointeur vers le pixel suivant
	 *   Cette structure va nous permettre de stocker les coordonnées de chaque pixel qui vaut 1
	*/	
	typedef struct pix {
		int x, y;
		struct pix* next;
	}Pix; 

	/* Fonction de création d'une maille et chainage arrière
	 * @param Pix* root: la tête de la liste chainée
	 * @return pointeur vers la maille
	 */
	Pix* creermaille(Pix* root);

	/* Fonction de suppression de la liste chainée
	 * @param Pix* root: pointeur vers la tête de la liste chainée
	 */
	void freeListe(Pix* root);
	
	/* Fonction d'affichage des mailles de la liste
	 * @param Pix* root : pointeur vers la tête de la liste chainée
	 */
	void afficherliste(Pix* root);

	/* Fonction de création d'une matrice
	 * @param int x: largeur de la matrice
	 * @param int y : longueur de la matrice
	 * @return pointeur vers le début de la matrice
	 */
	long double** alloc(int x, int y);

	/* Fonction de destruction d'une matrice
	 * @param double*** mat : pointeur vers le pointeur du début de la matrice
	 * @param int dimY : longueur de la matrice
	 */
	void freemat(long double*** mat, int dimY);
	
	/* Fonction de repérage des pixels non nuls de l'image binaire
	 * @param BmpImg* pic : pointeur vers l'image
	 * @param Pix* root : pointeur vers la tête de notre liste chainée
	 */
	void calint(BmpImg* pic, Pix* root);

	/* Fonction des calculs des moments
	 * @param Pix* root : pointeur vers la tête de notre liste chainée
	 * @param BmpImg* pic : pointeur vers l'image
	 * @param N : l'ordre choisit
	 * @return Matrice de double
	 */
	long double** mom(Pix* root, BmpImg* pic, int N);
	
	/* Fonction d'écriture des valeurs du moment dans un fichier
	 * @param char* fnam : nom du fichier
	 * @param double** mat : matrice contenant la valeur des moments
	 * @param int dimX : Largeur de la matrice
	 * @param int dimY : Longueur de la matrice
	 */
	void truc(char* fname, long double** mat, int dimX, int dimY);






#endif
