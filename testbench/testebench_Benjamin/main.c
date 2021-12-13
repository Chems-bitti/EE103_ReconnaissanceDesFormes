
#include <string.h>
#include <dirent.h>
#include "test.h"
#include "image.h"
#include "calcul.h"
#include "matrice.h"
#include "gestionfichier.h"
#include "base2donnee.h"

#define fichierbin "base_de_donnee/matrice/fichierbin.bin"
#define basedonne "donnees/"
#define chemindossier "base_de_donnee"

#define N 45


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
    char *temp = strchr(s, '.');
    if ((temp[1] == 'b') && (temp[2] == 'm') && (temp[3] == 'p')){
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

    char fichiertxt[500];              // Itinieraire vers le fichier
    char fichierbmp[500];              // Itinieraire vers le fichier
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

            ajoutImageBD(bd,creerImageBD(fichierbmp, fichiertxt)); // creer et ajoute l'imageBD avec les noms des fichiers bmp et txt dans la base de donnee

            /* Partie calcul de moment */
            // Calcul la matrice de moment de Legendre et l'ecrit dans un fichier text

            printf("%s\n",fichierbmp);
            BmpImg pic = readBmpImage(fichierbmp);
            printf("check1\n");
            Matrice mat = mom_legendre(&pic, N);
            printf("check2\n");
            ecritureMatrice(fichiertxt, mat);
            printf("check3\n");
            // supprimer la matrice
        }
    }printf("checkfin\n");
    return bd;
}

void parcourirDossier(DIR* rep, char* chemin)
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

    rep = opendir(chemin);
    BaseDonnee* bd = creerBDmoment(chemin, rep, "Base_de_donnee");
    suprimeBD(bd);

    closedir(rep); /* Fermeture du répertoire. */

    //lire(chemin); /* Lecture du nouveau chemin; */
    //parcourirDossier(rep, chemin); /* On rappelle la fonction parcourirDossier (récursivité). */
}

int main()
{
    printf("debut\n");



    DIR* rep = NULL;
    char chemin[500] = chemindossier;

    parcourirDossier(rep, chemin);

    closedir(rep);

    printf("fin\n");

    return 0;
}





    /*
    char text1[10];
    char text2[10] = "faux";
    char text3[10] = "fifu";

    strcat(text1,text2);

    printf("%s \n", text1);

    strcpy(text1, "");

    strcat(text1,text3);

    printf("%s \n", text1);
    printf("%s \n", text2); //*/


