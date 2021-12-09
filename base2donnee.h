#ifndef _base2donnee_h_
#define _base2donnee_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
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

// Pas cree !!
/** Ajoute des matrices d'une image a la base de donnee
  * Chaque matrice ajoute a ajoute a la liste des matrices de l'image
  * Si l'image n'est pas dans listeimage, elle est ajoute
  * @param bd :             Base de donnee dans laquelle on veut ajouter l'image
  * @param nomfimage :      Nom du fichier image
  * @param nomfmatrice :    Nom du fichier de la matrice
  * @param N :              Ordre de la matrice de l'image
  */
void ajoutBD(BaseDonnee bd, char* nomfimage, char* nomfmatrice, int* N);

BaseDonnee* creerBD(char* nom);
ImageBD* creerImageBD(char* nomfimage, char* nomfmatrice);
void ajoutImageBD(BaseDonnee* bd, ImageBD* imgbd);
void suprimeBD(BaseDonnee* bd);
void suprimeImageBD(ImageBD* imgbd);







#endif
