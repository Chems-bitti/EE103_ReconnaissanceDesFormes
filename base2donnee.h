#ifndef _base2donnee_h_
#define _base2donnee_h_

// Bibliotheques
#include <string.h>

#include "image.h"
#include "listeSC.h"

#define taillenom 20
#define taillenomfichier 60



// déclaration de la structure ImageBD
typedef struct {
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


/** creer une base de donnee
  * @param nom correspond au nom de la base de donnee
  * @return La base de donnee cree
  */
BaseDonnee* creerBD(char* nom);


/** cree une image que l'on mettra dans la base de donnee à partir du nom de l'image et du nom de la matrice
  * @param nomfimage correspond au nom du fichier de l'image
  * @param nomfmatrice correspond au nom du fichier de la matrice
  * @return l'image cree
  */
ImageBD* creerImageBD(char* nomfimage, char* nomfmatrice);


/** Ajoute l'image crée dans la base de donnee
  * @param bd correspond à la base de donnee dans laquelle on mettra l'image
  * @param imgbd est la l'image que l'on va mettre dans la base de donnee
  */
void ajoutImageBD(BaseDonnee* bd, ImageBD* imgbd);


/** Fonction qui supprime la base de donnee
  * @param bd
  */
void suprimeBD(BaseDonnee* bd);


/** fonction qui supprime l'image que l'on a mis dans la base de donnee
  * @param imgbd
  */
void suprimeImageBD(ImageBD* imgbd);


BaseDonnee* creerBDmoment(char* s, DIR* rep, char* nomBD);


void parcourirDossier(DIR* rep, char* chemin, char* nombd);


void ecritureBD(BaseDonnee* bd, char* chemin);


BaseDonnee* lectureBD(char *chemin, char *nomfbd);


char *compare_img_BD(BaseDonnee *bd, char* fimg);


void afficheimgBD(BaseDonnee *bd);


void reconstruction_BD(BaseDonnee *bd, char* dossier, int tailleX, int tailleY);

#endif
