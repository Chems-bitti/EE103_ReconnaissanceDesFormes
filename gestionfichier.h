#ifndef _gestionfichier_h_
#define _gestionfichier_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

// Pas creer !!
/** Ecrit une matrice dans un fichier texte
  * 1ere ligne : numero de matrice - tab - ordre de la matrice
  * ligne suivant : valeur de la matrice place en triangulaire inf�rieure pour ne pas avoir a marquer les 0
                    chaque valeur est separe par une tabulation
  * @param nomfichier Le nom du fichier dans lequel ecrire la matrice
  * @param mat La matrice qui sera ecrite
  */
void ecritureMatrice(char * fname, Matrice mat);

// Pas creer !!
/** Recupere une matrice dans un fichier texte
  * @param nomfichier Le nom du fichier dans lequel lire la matrice
  * @return la matrice
  */
Matrice lectureMatrice(char * nomfichier);

// marche pas completement
/** Ecrit une matrice dans un fichier binaire
  * Les deux premiers entier sont pour le numero et l'ordre de la matrice, le tableau en deux dimension pour les valeurs
  * @param nomfichierbin Le nom du fichier dans lequel ecrire la matrice
  * @param mat La matrice qui sera ecrite
  * @return 1 si le fichier s'est bien ouvert, sinon 0
  */
int ecritureMatricebin(char * nomfichierbin, Matrice mat);

// marche pas completement
/** Recupere une matrice dans un fichier binaire
  * @param nomfichier Le nom du fichier dans lequel lire la matrice
  * @param num numero de la matrice
  * @return la matrice
  */
Matrice lectureMatricebin(char * nomfichierbin);




#endif
