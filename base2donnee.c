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
    imgbd->nomfimage = nomfimage;
    imgbd->nomfmatrice = nomfmatrice;
    return imgbd;
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


void suprimeBD(BaseDonnee* bd){

    bd->nom = '\0';
    bd->nbimage = 0;

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

    imgbd->nomfimage = '\0';
    imgbd->nomfmatrice = '\0';
}






