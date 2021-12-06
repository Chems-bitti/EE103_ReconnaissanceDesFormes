#ifndef _base2donnee_h_
#define _base2donnee_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "listeSC.h"

// déclaration de la structure MatriceBD
typedef struct {
    char* nom;      // Nom du fichier de la matrice
    int type;       // 0: fichier texte, 1: fichier binaire
    int num;        // Numero de la matrice pour l'identifier
    int N;          // Ordre de la Matrice
} MatriceBD;

// déclaration de la structure ImageBD
typedef struct {
    char* nom;              // Nom de l'image dans le dossier de la base de donnee
    char* description;      // Description dans le cas ou le nom n'est pas explicite
    ListeSC listematrice;  // Liste chaine des matrices de l'image dans la base de donnee
} ImageBD;

// déclaration de la structure Base2donnee
typedef struct {
    char* nom;              // Nom de la base de donnee dans le dossier de la base de donnee
    char* description;      // Description dans le cas ou le nom n'est pas explicite

    ListeSC listeimage;  // Liste chaine des image dans la base de donnee
} Base2donnee;



// Pas cree !!
/** Ajoute des matrices d'une image a la base de donnee
  * Chaque matrice ajoute a ajoute a la liste des matrices de l'image
  * Si l'image n'est pas dans listeimage, elle est ajoute
  * @param listeimage :     liste des images de la base de donnee
  * @param nom :            nom du fichier image
  * @param description :    description de l'image pour l'utilisatuer (pris en compte que si l'image n'est pas dans la liste)
  * @param num :            numero de la premier matrice qui sera ajoute
  * @param listeimage :     liste des images de la base de donnee
  * @param nom :            nom du fichier image
  * @param N :              tableau avec les ordres des matrices qu'on souhaite ajoute
  * @param typefichier :    type des fichiers des matrices (0: texte, 1: binaire, 2: les deux)
  * @return nombre de matrice ajoute
  */
int ajoutBD(ListeSC listeimage, char* nom, char* description, int num, int* N, int typefichier);

creerBD
afficheBD
suprimeBD

creerImageBD
afficheImageBD
ajoutImageBD
suprimeImageBD

creerMatriceBD
afficheMatriceBD
ajoutMatriceBD
suprimeMatriceBD








#endif
