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



BaseDonnee* creerBD(char* nom);
ImageBD* creerImageBD(char* nomfimage, char* nomfmatrice);
void ajoutImageBD(BaseDonnee* bd, ImageBD* imgbd);
void suprimeBD(BaseDonnee* bd);
void suprimeImageBD(ImageBD* imgbd);







#endif
