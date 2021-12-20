#ifndef _gestionfichier_h_
#define _gestionfichier_h_

// Bibliotheques
#include <dirent.h>
#include "matrice.h"


#define taillechemin 100    // Nombre de caractere pour les chaines de caractere qui indique un chemin de dossier

/** Verifie si une chaine de caractere correspond au nom d'un dossier
  * @param nom du dossier
  * @return 1 si vrai, sinon 0
  */
int isDir(char* s);

/** Verifie si une chaine de caractere correspond au nom d'une image bmp
  * @param nom du fichier bmp
  * @return 1 si vrai, sinon 0
  */
int isbmp(char* s);

/** Verifie si une chaine de caractere correspond au nom d'un fichier text
  * @param nom du fichier text
  * @return 1 si vrai, sinon 0
  */
int istxt(char* s);

/** Convertie un nom de fichier bmp en un nom de fichier text
  * @param nom du fichier bmp
  * @return 1 si conversion reussi, 0 si le fichier donne n'est pas un bmp
  */
int bmptotxt(char* s);

/** Ecrit une matrice dans un fichier texte
  * 1ere ligne : numero de matrice - tab - ordre de la matrice
  * ligne suivant : valeur de la matrice place en triangulaire inferieure pour ne pas avoir a marquer les 0
                    chaque valeur est separe par une tabulation
  * @param nomfichier Le nom du fichier dans lequel ecrire la matrice
  * @param mat La matrice qui sera ecrite
  */
void ecritureMatrice(char * fname, Matrice mat);


/** Recupere une matrice dans un fichier texte
  * @param nomfichier Le nom du fichier dans lequel lire la matrice
  * @return la matrice
  */
Matrice lectureMatrice(char * nomfichier);


/** Ecrit une matrice dans un fichier binaire
  * Les deux premiers entier sont pour le numero et l'ordre de la matrice, le tableau en deux dimension pour les valeurs
  * @param nomfichierbin Le nom du fichier dans lequel ecrire la matrice
  * @param mat La matrice qui sera ecrite
  * @return 1 si le fichier s'est bien ouvert, sinon 0
  */
int ecritureMatricebin(char * nomfichierbin, Matrice mat);


/** Recupere une matrice dans un fichier binaire
  * @param nomfichier Le nom du fichier dans lequel lire la matrice
  * @param num numero de la matrice
  * @return la matrice
  */
Matrice lectureMatricebin(char * nomfichierbin);

void lire(char* s);

void lirebmpDossier(char* s, DIR* rep);

#endif
