#include "base2donnee.h"

// Fonction de base pour la manipulation des elements de la gestion de donnee
BaseDonnee* creerBD(char* nom){

    BaseDonnee* bd = malloc(sizeof(bd));
    bd->nom = nom;
    bd->nbimage = 0;
    bd->listeimage = creerListe(sizeof(ImageBD));
    return bd;
}

ImageBD* creerImageBD(char* nomfimage, char* nomfmatrice){

    ImageBD* imgbd = malloc(sizeof(ImageBD));
    int nbimg = strlen(nomfimage);
    int nbmat = strlen(nomfmatrice);

    imgbd->nomfimage = calloc(nbimg + 1,sizeof(char));
    imgbd->nomfmatrice = calloc(nbmat + 1,sizeof(char));

    strcpy(imgbd->nomfimage, nomfimage);
    strcpy(imgbd->nomfmatrice, nomfmatrice);
    return imgbd;
}


void ajoutImageBD(BaseDonnee* bd, ImageBD* imgbd){

    ajout( bd->listeimage, imgbd, 1);
    bd->nbimage ++;
}


void suprimeBD(BaseDonnee* bd){
    bd->nbimage = 0;

    // Tant que la liste n'est pas vide
    while(bd->listeimage->root != NULL) {
	    suprimeImageBD(bd->listeimage->root->data);
	    suppr(bd->listeimage, 0);
    }
    free(bd->listeimage);
    // On libere l'espace memoire occupe par la tete de liste
    free(bd);
    bd = NULL;


}

void suprimeImageBD(ImageBD* imgbd){

    free(imgbd->nomfimage);
    free(imgbd->nomfmatrice);
}



