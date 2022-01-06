#ifndef _base2donnee_h_
#define _base2donnee_h_

// Bibliotheques
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


/** Cree les moments de toutes les images bmp d'un dossier
  * @param rep repertoire ou sont les images
  * @param chemin ou se trouve le repertoire/dossier de la base de donnee (la ou les images sont)
  * @param nomBD nom de la base de donnee
  * @return la base de donnee contenant la liste chaine des images
  */
BaseDonnee* creerBDmoment(DIR* rep, char* chemin, char* nomBD);


/** Liste les images .bmp du dossier de la base de donnee, cree les moments de legendre des images
    et ecrit la base de donnee dans un fichier txt
  * @param rep repertoire ou se fait la lecture (Le repertoir est en parametre car utile pour la recursivite)
  * @param chemin ou se trouve le repertoire/dossier de la base de donnee (la ou les images sont)
  * @param nomBD nom de la base de donnee
  * @return le nombre d'image utilise pour la base de donnee
  */
int parcourirDossier(DIR* rep, char* chemin, char* nombd);


/** Ecrit une base de donnee dans un fichier text dans le dossier de la base de donnee
    ce fichier text sera utiliser pour la comparaison et la reconstruction d'image
  * @param bd la base de donnee a ecrire
  * @param chemin ou sera ecrit la base de donnee
  */
void ecritureBD(BaseDonnee* bd, char* chemin);


/** Lit la base de donnee
  * @param chemin de la base de donnee
  * @param nomfbd fichier .txt est ecrit la base de donnee
  */
BaseDonnee* lectureBD(char *chemin, char *nomfbd);


/** Comapare une image a une base de donnee
  * @param bd la base de donnee
  * @param fimg nom du ficher .bmp de l'image
  * @return Le nom de l'image la plus proche
  */
char *compare_img_BD(BaseDonnee *bd, char* fimg);


/** Affiche dans la console toutes les images d'une base de donnee
  * @param bd la base de donnee
  */
void afficheimgBD(BaseDonnee *bd);


/** Reconstruit toutes le images d'une base de donnee
  * @param bd la base de donnee
  * @param dossier ou seront les images reconstruites
  * @param tailleX Taille horizontal des images reconstruite
  * @param tailleY Taille vertical des images reconstruite
  */
void reconstruction_BD(BaseDonnee *bd, char* dossier, int tailleX, int tailleY);

#endif
