
#include <string.h>
#include <dirent.h>
#include "image.h"
#include "calcul.h"
#include "matrice.h"
#include "gestionfichier.h"
#include "base2donnee.h"

#define taillechemin 100


#define N 45


void ecritureBD(BaseDonnee* bd, char* chemin);


int isDir(char* s)
{
    if ((strchr(s, '.')) == NULL) /* Si le nom du chemin n'a pas de point (une extension). */
        return 1;
    else
        return 0;
}

int isbmp(char* s){

    /* Si le fichier n'a pas d'extension (premier test pour evite les erreurs) */
    if (isDir(s)){
        return 0;
    }
    int len = strlen(s);
    if ((s[len-2] == 'b') && (s[len-1] == 'm') && (s[len] == 'p')){
        return 1;
    }else{
        return 0;
    }
}

int istxt(char* s){

    /* Si le fichier n'a pas d'extension (premier test pour evite les erreurs) */
    if (isDir(s)){
        return 0;
    }
    char *temp = strchr(s, '.');
    if ((temp[1] == 't') && (temp[2] == 'x') && (temp[3] == 't')){
        return 1;
    }else{
        return 0;
    }
}

int bmptotxt(char* s){
    /* si le fichier n'est pas un bmp */
    if (isbmp(s) == 0){
        return 0;
    }else{
        /* Prend le pointeur vers '.' */
        char *temp = strchr(s, '.');

        /* Remplace les 3 carateres suivant */
        temp[1] = 't';
        temp[2] = 'x';
        temp[3] = 't';
        return 1;
    }
}

void lire(char* s)
{
    char *enter = NULL;
    char temp[100] = ""; /* Chaîne de caractères temporaire contenant la saisie de l'utilisateur. */

    fgets(temp, 99, stdin);

    enter = strchr(temp, '\n'); /* Voir le chapitre des saisies sécurisées. */
    if (enter != NULL)
        *enter = '\0';

    strcat(s, temp); /* On ajoute à la suite le nom du dossier
    pour obtenir quelque chose comme C:/nom/nom/ pour Win
    ou /nom/nom/ pour UNIX. */
}


void lirebmpDossier(char* s, DIR* rep)
{
    struct dirent* ent = NULL;

    printf(" -- Lecture des images bmp du dossier '%s' -- \n", s);

    while ((ent = readdir(rep)) != NULL){ /* Lecture du dossier. */
        if (isbmp(ent->d_name)){
            printf(" -> %s\n", ent->d_name);
        }
    }
}


BaseDonnee* creerBDmoment(char* s, DIR* rep, char* nomBD)
{
    struct dirent* ent = NULL;

    char fichiertxt[taillechemin];              // Itinieraire vers le fichier
    char fichierbmp[taillechemin];              // Itinieraire vers le fichier
    char nomtxt[25];                   // Nom du fichier txt de la matrice de moment
    BaseDonnee* bd = creerBD(nomBD);    // Creer une base de donnee pour lister les images et leur matrice de moment

    while ((ent = readdir(rep)) != NULL){ /* Lecture du dossier. */
        if (isbmp(ent->d_name)){
            /* Partie base de donnee et memoir */
            // prend l'itineraire vers le fichier image
            strcpy(fichierbmp, s);       // prend l'itineraire vers le repertoir ou se trouve l'image
            strcat(fichierbmp, "/");
            strcat(fichierbmp, ent->d_name); // ajoute le nom de l'image

            // prend l'itineraire vers le fichier text
            strcpy(nomtxt, ent->d_name);     // prend le nom du fichier bmp
            bmptotxt(nomtxt);                // change l'extension de bmp a txt
            strcpy(fichiertxt, s);       // prend l'itineraire vers le repertoir ou se trouvera le fichier text
            strcat(fichiertxt, "/");
            strcat(fichiertxt, nomtxt); // ajoute le nom du fichier text
	    ImageBD* im = creerImageBD(fichierbmp, fichiertxt);
            ajoutImageBD(bd, im); // creer et ajoute l'imageBD avec les noms des fichiers bmp et txt dans la base de donnee
	    suprimeImageBD(im);

            /* Partie calcul de moment */
            // Calcul la matrice de moment de Legendre et l'ecrit dans un fichier text

            BmpImg pic = readBmpImage(fichierbmp);  // Recupre l'image
            Matrice mat = mom_legendre(&pic, N);    // Calcul les moment de Legendre
            ecritureMatrice(fichiertxt, mat);       // Ecrit la matrice de moment dans un fichier txt

            freeBmpImg(&pic);                       // Supprime l'image
            supprMatrice(&mat);                     // Supprime la matrice de moment
        }
    }
    return bd;
}

void parcourirDossier(DIR* rep, char* chemin, char* nombd)
{

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

    lirebmpDossier(chemin, rep); /* Lecture... */
    closedir(rep); /* Fermeture du répertoire. */

    printf("\n -- Voici les images qui seront incluses dans la base de donnee -- \n");


    rep = opendir(chemin);
    BaseDonnee* bd = creerBDmoment(chemin, rep, nombd);
    ecritureBD(bd, chemin);  // Ecrit la base de donnee dans un fichier txt

    suprimeBD(bd);  // Supprime la base de donnee

    closedir(rep); /* Fermeture du répertoire. */

    //lire(chemin); /* Lecture du nouveau chemin; */
    //parcourirDossier(rep, chemin); /* On rappelle la fonction parcourirDossier (récursivité). */
}

void ecritureBD(BaseDonnee* bd, char* chemin){

    char fichiertemp[taillechemin];              // Itinieraire vers le fichier
    strcpy(fichiertemp, chemin);       // prend l'itineraire vers le repertoir ou se trouvera le fichier text
    strcat(fichiertemp, "/");
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
    strcat(fichiertemp, "/");
    strcat(fichiertemp, nomfbd);     // ajoute le nom du fichier de la base de donnee
    FILE* ftxt = fopen(fichiertemp, "r");
    if (ftxt == NULL){
        printf(" -- Le fichier '%s' n'a pas pu etre ouvert --\n", fichiertemp);
        printf(" -- La base de donnee n'a pas pu etre lu --\n");
        fclose(ftxt);
        return creerBD(nomfbd);
    }else{

        char fichierbmp[taillechemin];
        char fichiertxt[taillechemin];

        BaseDonnee* bd = creerBD(nomfbd);
        fscanf(ftxt, "Nombre d'image : %d\n", &bd->nbimage);
        // Boucle tant qu'on atteint pas la fin du fichier
        while(fscanf(ftxt, "%s\t%s\n", fichierbmp, fichiertxt) != EOF){ // Prend les information de la base de donnee avec le fichier txt
	    ImageBD* im = creerImageBD(fichierbmp, fichiertxt);
            ajoutImageBD(bd, im); // creer et ajoute l'imageBD avec les noms des fichiers bmp et txt dans la base de donnee
	    suprimeImageBD(im);
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

    BmpImg pic = readBmpImage(fimg);                            // Recupre l'image
    Matrice matcomp = mom_legendre(&pic, N);                    // Calcul les moment de Legendre de l'image a comparer
    freeBmpImg(&pic);

    ImageBD* imgbd= (ImageBD* )bd->listeimage->root->data;      // Prend la premier une image de la base de donnee
    Matrice mat = lectureMatrice(imgbd->nomfmatrice);           // Lit la matrice de l'image depuis le fichier txt

    double tmp = distance_euclidienne(matcomp, mat, N);             // Fait une premier comparaison a l'odre N

/// !!! Faire une allocation dynamique du char et ne pas oublier de le supprimer dans le main

    char* res = malloc((taillechemin+1) * sizeof(char));
    strcpy(res,imgbd->nomfimage);                                   // Prend le nom de la premier image associer

    for(bd->listeimage->current = bd->listeimage->root; hasNext(bd->listeimage); getNext(bd->listeimage)){

        imgbd= (ImageBD* )bd->listeimage->current->data;

        //distance_euclidienne()

/// !!! Faire la meme chose que juste avant la boucle for avec un if qui prend la nouvelle image si distance eucli plus petit...

    }
    return res;
}







int main()
{
    char chemin[taillechemin] = "base_de_donnee";
    char fichierBD[taillechemin] = "base_de_donnee.txt";

    /* Controle du nom de la base de donnee */

    if (istxt(fichierBD) == 0){
        printf(" -- Attention le nom du fichier text de la base de donnee n'a pas l'extension '.txt' !! -- \n");
        exit(2);
    }

    /** Partie creartion base de donnee */
    printf(" -- Souhaitez vous mettre a jour la base de donnee ? [o]/[n] -- \n");
    char com1;
    while(1){               // Boucle tant que l'utilisateur n'a pas mit une commande valide
        scanf(" %c", &com1);  // Prend la commande utilisateur

        if (com1 == 'o'){      // Si l'utilisateur veut creer une base de donnee
            DIR* rep = NULL;
            parcourirDossier(rep, chemin, fichierBD);
            closedir(rep);
            fflush(stdin);
            printf(" -- La base de donnee a ete correctement cree  -- \n\n");
            break;
        }else if(com1 == 'n'){
            fflush(stdin);
            break;
        }
        printf(" -- Veulliez donner une reponse valide : [o]/[n] -- \n");
        fflush(stdin);
    }

    /** Partie recuperation base de donne et comparaison */

    BaseDonnee *bd = lectureBD(chemin, fichierBD);

    char com2;
    char fimg[taillechemin];  // Nom du fichier image a comparer
    char fres[taillechemin];  // Nom de l'image resultat de la comparaison
    while(1){               // Boucle tant que l'utilisateur n'a pas mit une commande valide
        printf(" -- Souhaitez vous comparer une image a la base de donnee ? [o]/[n] -- \n");
        scanf(" %c", &com2);  // Prend la commande utilisateur
        fflush(stdin);

        if (com2 == 'o'){      // Si l'utilisateur veut comparer une image

/// !!! Je sais pas pk mais il veut pas trouver le fichier qu'on met et il dit que c'est pas un bmp dans le test isbmp dans la fonction compare_img_BD juste apres
            printf(" -- Entrez le nom de l'image a comparer avec l'extention (.bmp) -- \n");
            scanf("%s", fimg);
            fflush(stdin);

            // test si le fichier est bien dans le dossier
            FILE* test = fopen(fimg, "r");
            if(test == NULL) {
                printf(" -- Ce fichier n'est pas present dans la dossier -- \n");
                fclose(test);
            }
            else {
                fclose(test);
		char* res = compare_img_BD(bd, fimg);
                printf(" -- L'image la plus proche est %s -- \n", res);
            }

        }else if(com2 == 'n'){
            fflush(stdin);
            break;
        }else{
            printf(" -- Veulliez donner une reponse valide -- \n");
            fflush(stdin);
        }
    }

/// !!! Faire une partie qui permet de reconstruire une image si l'utilisateur le veut

    suprimeBD(bd);


    printf("fin\n");
    return 0;
}




