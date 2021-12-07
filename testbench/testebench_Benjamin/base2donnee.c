#include "base2donnee.h"

// Fonction de base pour la manipulation des elements de la gestion de donnee
BaseDonnee* creerBD(char* nom, char* description){

    BaseDonnee* bd = malloc(sizeof(bd));
    bd->nom = nom;
    bd->description = description;
    bd->nbimage = 0;
    bd->nbmatrice = 0;
    bd->listeimage = creerListe(sizeof(ImageBD));
    return bd;
}

ImageBD* creerImageBD(char* nom, char* description){

    ImageBD* imgbd = malloc(sizeof(ImageBD));
    imgbd->nom = nom;
    imgbd->description = description;
    imgbd->nbmatrice = 0;
    imgbd->listematrice = creerListe(sizeof(MatriceBD));
    return imgbd;
}

MatriceBD* creerMatriceBD(char* nom, int type, int num, int N){

    MatriceBD* matbd = malloc(sizeof(MatriceBD));
    matbd->nom = nom;
    matbd->type = type;
    matbd->num = num;
    matbd->N = N;
    return matbd;
}

void ajoutImageBD(BaseDonnee* bd, ImageBD* imgbd){

    // ajout alphabetique, pas obligatoire a faire si il y a le temps
    /*
    // boucle while pour ajouter l'image au bon endroit alphabetiquement
    bd.listeimage->current = bd.listeimage->root;
    ImageBD imgbdcurrent = (ImageBD)bd.listeimage->current->data  // image tempon pour la comparaison

    ImageBD imgbdnext = (ImageBD)bd.listeimage->root->data  // image tempon pour la comparaison
    while(hasNext(bd.listeimage) && (strcmp(bd.listeimage->current->data->nom, tmpnom) == -1)){
    }

    */

    ajout( bd->listeimage, imgbd, 1);
    bd->nbimage ++;
}

void ajoutMatriceBD(BaseDonnee* bd, ImageBD* imgbd, MatriceBD* matbd){

    // si il y a le temps faire un ajout dans l'orde numerique

    ajout( imgbd->listematrice, matbd, 1);
    bd->nbmatrice ++;
    imgbd->nbmatrice ++;
}

void suprimeBD(BaseDonnee* bd){

    bd->nom = '\0';
    bd->description = '\0';
    bd->nbimage = 0;
    bd->nbmatrice = 0;

    // Tant que la liste n'est pas vide
    while( bd->listeimage->root != NULL ){
        ImageBD* imgbd = (ImageBD *)bd->listeimage->root->data;         // On point vers l'image de la cellule
        suprimeImageBD(imgbd);                                          // On supprime l'image
        suppr( bd->listeimage, 0 );                                 // On supprime le premier element
    }
    // On libere l'espace memoire occupe par la tete de liste
    free(bd);
    bd = NULL;
}

void suprimeImageBD(ImageBD* imgbd){

    imgbd->nom = '\0';
    imgbd->description = '\0';
    imgbd->nbmatrice = 0;

    // Tant que la liste n'est pas vide
    while( imgbd->listematrice->root != NULL ){
        MatriceBD* matbd = (MatriceBD *)imgbd->listematrice->root->data;   // On point vers la matrice de la cellule
        suprimeMatriceBD(matbd);                                          // On supprime la matrice
        suppr( imgbd->listematrice, 0 );                                 // On supprime le premier element
    }
    // On libere l'espace memoire occupe par la tete de liste
    free( imgbd);
    imgbd = NULL;
}

void suprimeMatriceBD(MatriceBD* matbd){

    matbd->nom = '\0';
    matbd->num = 0;
    matbd->type = 0;
    matbd->N = 0;
    free(matbd);
    matbd = NULL;
}









