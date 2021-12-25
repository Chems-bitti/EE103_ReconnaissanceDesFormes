
// Bibliotheque
#include "base2donnee.h" // Seul cette bibliotheque est appele car elle appel toutes les autres


#define tailleimg 100  // Taille des images a reconstruire (plus elle sont grande plus ca prend du temps)


int main(){

    // Variable et chaine de caractere
    char cheminBD[taillechemin] = "base_de_donnee/";
    char fichierBD[taillechemin] = "base_de_donnee.txt";   // Nom du fichier text contenant les informations de la base de donnee
    char com; // Commande utilisateur [o]/[n]

    /* Controle du nom de la base de donnee */

    if (istxt(fichierBD) == 0){
        printf(" -- Attention le nom du fichier text de la base de donnee n'a pas l'extension '.txt' !! -- \n");
        exit(2);
    }

    /** Partie creartion base de donnee */

    printf("\n\t----- Partie creation de base de donnee ----- \n\n");
    while(1){               // Boucle tant que l'utilisateur n'a pas mit une commande valide
        printf(" -- Souhaitez vous mettre a jour la base de donnee ? [o]/[n] -> ");
        char com;
        scanf(" %c", &com);  // Prend la commande utilisateur

        if (com == 'o'){      // Si l'utilisateur veut creer une base de donnee
            DIR* rep = NULL;
            if (parcourirDossier(rep, cheminBD, fichierBD)){
                // Si la base de donnee a ete cree correctement
                closedir(rep);
                fflush(stdin);
                printf(" -- La base de donnee a ete correctement cree  -- \n");
            }else{
                closedir(rep);
                fflush(stdin);
                printf(" -- Attention ! Il n'y a pas d'image dans la base de donnee  -- \n");
                printf(" -- La comparaison et la reconstruction d'image sera donc impossible  -- \n");
                // Appel de la fonction main pour que l'utilisateur puisse re mettre a jour la base de donnee
                main();
            }
            break;
        }else if(com == 'n'){
            fflush(stdin);
            break;
        }
        printf(" -- Veulliez donner une reponse valide -- \n");
        fflush(stdin);
    }

    /** Partie comparaison d'image */

    printf("\n\t----- Partie comparaison d'image ----- \n\n");

    BaseDonnee *bd = lectureBD(cheminBD, fichierBD); // Recupere la base de donnee dans le fichier
    /* Test si la base de donnee a pu etre lu */
    if (bd == NULL){
        printf(" -- La base de donnee n'a pas pu etre lu --\n");
        printf(" -- Impossible de comparer ou de reconstruire une image --\n");
        printf(" -- Entrez n'importe quelle caractere pour mettre fin au programmme -> ");
        scanf(" %c", &com);
        return 0;
    }
    /* Test si il y a des images dans la base de donnee */
    if (bd->nbimage == 0){
        printf(" -- La base ne contient aucune image --\n");
        printf(" -- Impossible de comparer ou de reconstruire une image --\n");
        printf(" -- Entrez n'importe quelle caractere pour mettre fin au programmme -> ");
        scanf(" %c", &com);
        suprimeBD(bd);
        return 0;
    }

    char fimg[taillechemin];  // Nom du fichier image a comparer
    while(1){               // Boucle tant que l'utilisateur n'a pas mit une commande valide
        printf(" -- Souhaitez vous comparer une image a la base de donnee ? [o]/[n] -> ");
        scanf(" %c", &com);  // Prend la commande utilisateur
        fflush(stdin);

        if (com == 'o'){      // Si l'utilisateur veut comparer une image

            char chemincomp[taillechemin] = "comparaison/";   // Nom du dossier dans lequel se trouve les images a comparer

            DIR* repcomp = opendir(chemincomp);
            /* Test si le dossier de comparaison existe */
            if (repcomp == NULL){
                printf("Le dossier '%s' n'a pas pu etre ouvert", chemincomp);
                suprimeBD(bd);
                exit(-1);
            }
            lirebmpDossier(chemincomp, repcomp); // Lecture..
            closedir(repcomp);
            printf(" -- Voici les images bmp disponible dans le dossier '%s' -- \n", chemincomp);
            printf(" -- Entrez le nom de l'image a comparer avec l'extension (.bmp) -> ");
            scanf("%s", fimg);
            strcat(chemincomp, fimg);            // Contatanation

            // test si le fichier est bien dans le dossier
            FILE* test = fopen(chemincomp, "rb");

            // Si le fichier n'est pas dans le dossier renvoie un message d'erreur et reboucle
            if(test == NULL) {
                fclose(test);
                printf(" -- Ce fichier n'est pas present dans la dossier -- \n");
            }
            else {
                fclose(test);  // ferme le fichier de verification
                char* res = compare_img_BD(bd, chemincomp);   // Prend l'image la plus proche de la base de donnee
                strcpy(res,strrchr(res,'/')+1);         // Enleve la partie du nom de l'image sur le chemin du dossier
                printf(" -- L'image la plus proche dans la base de donnee est : %s -- \n", res);
                free(res);   // Supprime la chaine de caractere car alloue dynamiquement dans compare_img_BD
            }

        }else if(com == 'n'){
            fflush(stdin);

            break;
        }else{
            printf(" -- Veulliez donner une reponse valide -- \n");
            fflush(stdin);
        }
    }

    /** Partie reconstruction d'image */

    printf("\n\t----- Partie reconstruction d'image ----- \n\n");

    while(1){               // Boucle tant que l'utilisateur n'a pas mit une commande valide
        printf(" -- Souhaitez vous reconstruire une image de la base de donnee ? [o]/[n] -> ");
        scanf(" %c", &com);  // Prend la commande utilisateur
        fflush(stdin);

        if (com == 'o'){      // Si l'utilisateur veut comparer une image

            char cheminrec[taillechemin] = "reconstruction/";  // Nom du dossier dans lequel se trouverons les images reconstruite
            afficheimgBD(bd);
            printf(" -- Voici les images de la base de donnee --\n");
            printf(" -- Entrez le nom de l'image que vous souhaitez reconstruire avec l'extension (.bmp)\n    ou entrez 'TOUT' pour reconstruire toutes les images (prend du temps) -> ");
            scanf("%s", fimg);

            if(strcmp(fimg, "TOUT") == 0){ // Si l'utilisateur veut reconstruire toutes les images
                reconstruction_BD(bd, cheminrec, tailleimg, tailleimg);
            }else{

                char ftxt[taillechemin];  // Initialise le nom du fichier text de la matrice des moment de Legendre
                strcpy(ftxt, fimg);       // Prend copie le nom de l'image dans la variable du nom de fichier text

                // Si le fichier n'est pas un fichier bmp
                if (bmptotxt(ftxt) == 0){  // Converti le nom .bmp en nom .txt
                    printf(" -- L'image donnee n'est pas un fichier bmp --\n");

                }else{

                    char fimgrec[taillechemin] = "reconstruction_";  // Initialisation du nom de l'image reconstruite
                    strcat(fimgrec, fimg);

                    char tmp[taillechemin];           // Chaine de caractere temporaire pour le nom du fichier txt avec chemin
                    strcpy(tmp, cheminBD);
                    strcat(tmp, ftxt);
                    strcpy(ftxt, tmp);

                    FILE* test = fopen(ftxt, "r"); // test si le fichier est bien dans le dossier

                    // Si le fichier n'est pas dans le dossier renvoie un message d'erreur et reboucle
                    if(test == NULL) {
                        fclose(test);
                        printf(" -- Le fichier n'est pas present dans la base de donnee -- \n");
                    }
                    else {
                        fclose(test);  // ferme le fichier de verification

                        Matrice mat = lectureMatrice(ftxt);  // Prend la matrice
                        creation_image(mat, cheminrec, fimgrec, tailleimg, tailleimg);  // Cree l'image demande
                        supprMatrice(&mat);     // Supprime la matrice utilise pour creer l'image
                    }
                }
            }
        }else if(com == 'n'){
            fflush(stdin);
            break;
        }else{
            printf(" -- Veulliez donner une reponse valide -- \n");
            fflush(stdin);
        }
    }

    suprimeBD(bd);

    printf("\n\t- Fin de programme -\n");
    return 0;
}
