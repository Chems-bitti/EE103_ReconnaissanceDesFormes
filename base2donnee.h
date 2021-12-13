#ifndef _base2donnee_h_
#define _base2donnee_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listeSC.h"

#define taillenom 20
#define taillenomfichier 60


// déclaration de la structure ImageBD
typedef struct {
    char* nom;              // Nom de ce qu'il y a a l'image
    char* nomfimage;        // Nom du fichier image
    char* nomfmatrice;      // Nom du fichier de la matrice des moments de Legendre
    int N;                  // Ordre de la matrice de l'image
} ImageBD;

// déclaration de la structure BD
typedef struct {
    char* nom;              // Nom de la base de donnee
    int nbimage;            // Nombre d'image dans la base de donnee
    ListeSC* listeimage;    // Liste chaine des image dans la base de donnee
} BaseDonnee;


// Marche nickel
/** Reconstruit un pixel de coordonnee (x,y) à partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre à passer à la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
BaseDonnee* creerBD(char* nom);



// Marche nickel
/** Reconstruit un pixel de coordonnee (x,y) à partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre à passer à la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
ImageBD* creerImageBD(char* nomfimage, char* nomfmatrice);



// Marche nickel
/** Reconstruit un pixel de coordonnee (x,y) à partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre à passer à la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
void ajoutImageBD(BaseDonnee* bd, ImageBD* imgbd);




// Marche nickel
/** Reconstruit un pixel de coordonnee (x,y) à partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre à passer à la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
void suprimeBD(BaseDonnee* bd);




// Marche nickel
/** Reconstruit un pixel de coordonnee (x,y) à partir d'une Matrice de moment de Legendre
  * @param x coordonnee en abscisse
  * @param y coordonnee en ordonnee
  * @param mat Matrice de moment de Legendre
  * @param Matrice coef : coefficients du polynome de legendre à passer à la fonction baseLegendre
  * @param int dimX, int dimY : dimensions de notre image
  * @return La valeur du pixel
  */
void suprimeImageBD(ImageBD* imgbd);


#endif
