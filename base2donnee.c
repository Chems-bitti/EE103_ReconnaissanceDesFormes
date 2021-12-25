#include "base2donnee.h"


// Fonction de base pour la manipulation des elements de la gestion de donnee
BaseDonnee* creerBD(char* nom){

    BaseDonnee* bd = malloc(sizeof(bd));
    int len = strlen(nom);
    bd->nom = calloc(len+1, sizeof(char));
    strcpy(bd->nom, nom);
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
    free(bd->nom);
    free(bd);
    bd = NULL;
}


void suprimeImageBD(ImageBD* imgbd){

    free(imgbd->nomfimage);
    free(imgbd->nomfmatrice);
}


BaseDonnee* creerBDmoment(DIR* rep, char* chemin, char* nomBD){
    struct dirent* ent = NULL;

    char fichiertxt[taillechemin];              // Itinieraire vers le fichier
    char fichierbmp[taillechemin];              // Itinieraire vers le fichier
    char nomtxt[25];                   // Nom du fichier txt de la matrice de moment
    BaseDonnee* bd = creerBD(nomBD);    // Creer une base de donnee pour lister les images et leur matrice de moment

    while ((ent = readdir(rep)) != NULL){ // Lecture du dossier
        if (isbmp(ent->d_name)){
            /* Partie base de donnee et memoir */
            // prend l'itineraire vers le fichier image
            strcpy(fichierbmp, chemin);       // prend l'itineraire vers le repertoir ou se trouve l'image
            strcat(fichierbmp, ent->d_name); // ajoute le nom de l'image

            // prend l'itineraire vers le fichier text
            strcpy(nomtxt, ent->d_name);     // prend le nom du fichier bmp
            bmptotxt(nomtxt);                // change l'extension de bmp a txt
            strcpy(fichiertxt, chemin);       // prend l'itineraire vers le repertoir ou se trouvera le fichier text
            strcat(fichiertxt, nomtxt); // ajoute le nom du fichier text

            ImageBD* img = creerImageBD(fichierbmp, fichiertxt);
            ajoutImageBD(bd, img); // creer et ajoute l'imageBD avec les noms des fichiers bmp et txt dans la base de donnee

            /* Partie calcul de moment */
            // Calcul la matrice de moment de Legendre et l'ecrit dans un fichier text

            BmpImg pic = readBmpImage(fichierbmp);  // Recupre l'image
            Matrice mat = mom_legendre(&pic, Ordre);    // Calcul les moment de Legendre
            ecritureMatrice(fichiertxt, mat);       // Ecrit la matrice de moment dans un fichier txt

            freeBmpImg(&pic);                       // Supprime l'image
            supprMatrice(&mat);                     // Supprime la matrice de moment
	    free(img);
        }
    }
    return bd;
}


int parcourirDossier(DIR* rep, char* chemin, char* nombd){

    if (!isDir(chemin))
    {
        printf("%s n'est pas un dossier", chemin);
        exit(-1);
    }
    rep = opendir(chemin);

    if (rep == NULL)
    {
        printf("Le dossier '%s' n'a pas pu etre ouvert", chemin);
        exit(-1);
    }

    lirebmpDossier(chemin, rep); // Lecture..
    closedir(rep); // Fermeture du repertoire, pour que la prochaine lecture se fasse du debut

    printf(" -- Voici les images qui seront incluses dans la base de donnee (calcul en cours) -- \n");


    rep = opendir(chemin);
    BaseDonnee* bd = creerBDmoment(rep, chemin, nombd);
    ecritureBD(bd, chemin);  // Ecrit la base de donnee dans un fichier txt
    int nbimg = bd->nbimage; // Prend le nombre d'image de la base de donnee

    suprimeBD(bd);  // Supprime la base de donnee
    closedir(rep); // Fermeture du repertoire

    return nbimg;

    /* A utiliser si on veut faire un parcour de dossier dynamique pour l'itilisateur
       Quelques modifications a apporter pour cela */
    //lire(chemin); (Lecture du nouveau chemin)
    //parcourirDossier(rep, chemin, char* nombd); On rappelle la fonction parcourirDossier (recursivite).
}


void ecritureBD(BaseDonnee* bd, char* chemin){

    char fichiertemp[taillechemin];              // Itinieraire vers le fichier
    strcpy(fichiertemp, chemin);       // prend l'itineraire vers le repertoir ou se trouvera le fichier text
    strcat(fichiertemp, bd->nom);     // ajoute le nom du fichier de la base de donnee
    FILE* ftxt = fopen(fichiertemp, "w");
    if (ftxt == NULL){
        printf(" -- Le fichier '%s' n'a pas pu etre ouvert --\n", fichiertemp);
        printf(" -- La base de donnee n'a pas pu etre ecrite --\n");
    }else{

        fprintf(ftxt,"Nombre d'image : %d\n", bd->nbimage);
        /* Pour chaque image de la base de donnee met le nom du fichier txt et bmp */
        for(bd->listeimage->current = bd->listeimage->root; hasNext(bd->listeimage); getNext(bd->listeimage)){

            ImageBD* imgbd= (ImageBD* )bd->listeimage->current->data;
            fprintf(ftxt, "%s\t%s\n", imgbd->nomfimage, imgbd->nomfmatrice);
        }
    	fclose(ftxt);
    }
}


BaseDonnee* lectureBD(char *chemin, char *nomfbd){

    char fichiertemp[taillechemin];              // Itinieraire vers le fichier
    strcpy(fichiertemp, chemin);       // prend l'itineraire vers le repertoir ou se trouvera le fichier text
    strcat(fichiertemp, nomfbd);     // ajoute le nom du fichier de la base de donnee
    FILE* ftxt = fopen(fichiertemp, "r");
    if (ftxt == NULL){
        printf(" -- Le fichier '%s' n'a pas pu etre ouvert --\n", fichiertemp);
        fclose(ftxt);
        return NULL;
    }else{

        char fichierbmp[taillechemin];
        char fichiertxt[taillechemin];

        BaseDonnee* bd = creerBD(nomfbd);
        fscanf(ftxt, "Nombre d'image : %d\n", &bd->nbimage);
        // Boucle tant qu'on atteint pas la fin du fichier
        while(fscanf(ftxt, "%s\t%s\n", fichierbmp, fichiertxt) != EOF){ // Prend les information de la base de donnee avec le fichier txt
	    ImageBD* im = creerImageBD(fichierbmp, fichiertxt);
        ajoutImageBD(bd, im); // creer et ajoute l'imageBD avec les noms des fichiers bmp et txt dans la base de donnee
	free(im);

        }
        fclose(ftxt);
        return bd;
    }
}


char *compare_img_BD(BaseDonnee *bd, char* fimg){

    if (isbmp(fimg) == 0){
        printf(" -- Erreur l'image donnee n'est pas un fichier bmp -- \n");
        return "\0";
    }
    if (bd->listeimage->root->data ==  NULL){
        printf(" -- Attention la base de donnee '%s' est vide !! -- \n",bd->nom);
        return "Base de donnee vide !!";
    }
    // Vérification si le fichier existe
    FILE* f = fopen(fimg, "r");
    if( f == NULL ) return "Le fichier n'existe pas";
    fclose(f);
    BmpImg pic = readBmpImage(fimg);                            // Recupre l'image
    Matrice matcomp = mom_legendre(&pic, Ordre);                    // Calcul les moment de Legendre de l'image a comparer
    freeBmpImg(&pic);

    ImageBD* imgbd= (ImageBD* )bd->listeimage->root->data;      // Prend la premier une image de la base de donnee
    Matrice mat = lectureMatrice(imgbd->nomfmatrice);           // Lit la matrice de l'image depuis le fichier txt

    double tmp = distance_euclidienne(matcomp, mat, Ordre);             // Fait une premier comparaison a l'odre N
    double test;

    char* res = malloc((taillechemin+1) * sizeof(char));
    strcpy(res,imgbd->nomfimage);                                   // Prend le nom de la premier image associer
    supprMatrice(&mat);

    for(bd->listeimage->current = bd->listeimage->root; hasNext(bd->listeimage); getNext(bd->listeimage)){

        ImageBD* imgbd= (ImageBD* )bd->listeimage->current->data;
        Matrice mat = lectureMatrice(imgbd->nomfmatrice);
        test = distance_euclidienne(matcomp, mat, Ordre);
        if (test < tmp){
            test = tmp;
            strcpy(res,imgbd->nomfimage);
        }
    	supprMatrice(&mat);
    }
    supprMatrice(&matcomp);
    return res;
}


void afficheimgBD(BaseDonnee *bd){
    /* Parcours la base de donnee */
    for(bd->listeimage->current = bd->listeimage->root; hasNext(bd->listeimage); getNext(bd->listeimage)){

        ImageBD* imgbd= (ImageBD* )bd->listeimage->current->data;   // recuepre chaque image de la base de donne

        char *tmp; // Initialisation d'une chaine de caractere temporaire pour ne donner que le nom de l'image et non le chemin complet
        tmp = strrchr (imgbd->nomfimage, '/') + 1;

        printf(" -> %s\n", tmp);
    }
}


void reconstruction_BD(BaseDonnee *bd, char* dossier, int tailleX, int tailleY){

    printf(" -- Debut de la reconstruction des images de la base de donnee -- \n");

    /* Parcours la base de donnee */
    for(bd->listeimage->current = bd->listeimage->root; hasNext(bd->listeimage); getNext(bd->listeimage)){

        ImageBD* imgbd= (ImageBD* )bd->listeimage->current->data;   // recuepre chaque image de la base de donne
        Matrice mat = lectureMatrice(imgbd->nomfmatrice); 	   // Recupere la matrice des moments de Legendre

        char tmp[taillechemin] = "reconstruction_" ;           // Initialisation d'une chaine de caractere temporaire pour le nom de l'image a reconstruire
        strcat(tmp,strrchr (imgbd->nomfimage, '/') + 1);

        creation_image(mat, dossier, tmp, tailleX, tailleY);
        supprMatrice (&mat);			   // Desallocation Matrice Moment
    }
    printf(" -- Toutes les images de la base de donnee on ete reconstruite -- \n");
}

