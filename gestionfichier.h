#ifndef _gestionfichier_h_
#define _gestionfichier_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

// Pas creer !!
/** Ecrit une matrice dans un fichier texte
  * 1ere ligne : numero de matrice - tab - ordre de la matrice
  * ligne suivant : valeur de la matrice place en triangulaire inférieure pour ne pas avoir a marquer les 0
                    chaque valeur est séparé par une tabulation
  * @param nomfichier Le nom du fichier dans lequel ecrire la matrice
  * @param mat La matrice qui sera ecrite
  * @param TypeEcriture Type d'ecriture dans le fichier (0: remplace, 1: ajoute)
  * @return 1 si le fichier s'est bien ouvert, sinon 0
  */
int ecritureMatrice(char * nomfichier, Matrice mat, int TypeEcriture);

// Pas creer !!
/** Recupere une matrice dans un fichier texte
  * @param nomfichier Le nom du fichier dans lequel lire la matrice
  * @param num numero de la matrice
  * @return la matrice
  */
Matrice lectureMatrice(char * nomfichier, int num);

// Pas creer !!
/** Ecrit une matrice dans un fichier binaire
  * Les deux premiers entier sont pour le numéro et l'ordre de la matrice, le tableau en deux dimension pour les valeurs
  * @param nomfichierbin Le nom du fichier dans lequel ecrire la matrice
  * @param mat La matrice qui sera ecrite
  * @param TypeEcriture Type d'ecriture dans le fichier (0: remplace, 1: ajoute)
  * @return 1 si le fichier s'est bien ouvert, sinon 0
  */
int ecritureMatricebin(char * nomfichierbin, Matrice mat, int TypeEcriture);

// Pas creer !!
/** Recupere une matrice dans un fichier binaire
  * @param nomfichier Le nom du fichier dans lequel lire la matrice
  * @param num numero de la matrice
  * @return la matrice
  */
Matrice lectureMatricebin(char * nomfichierbin, int num);




#endif
