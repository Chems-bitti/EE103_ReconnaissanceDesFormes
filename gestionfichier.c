#include "gestionfichier.h"


int isDir(char* s){
    if ((strchr(s, '.')) == NULL) // Si le nom du chemin n'a pas de point (une extension)
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
    if ((s[len-3] == 'b') && (s[len-2] == 'm') && (s[len-1] == 'p')){
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
    int len = strlen(s);
    if ((s[len-3] == 't') && (s[len-2] == 'x') && (s[len-1] == 't')){
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


void ecritureMatrice(char * fname, Matrice mat){

	FILE* f = fopen(fname, "w");				// Ouverture du fichier
	if(f == NULL) {						// Verification que le fichier a ete ouvert correctement
		printf("Erreur: Impossible d'ouvrir le fichier");
		exit(1);
	}
	fprintf(f, "%d\n", mat.N);
	for(int i = 0; i <= mat.N; i++) {
		for(int j = 0; j <= mat.N-i; j++) {
				fprintf(f,"%le\t", mat.tab[i][j]);	// Ecriture du terme
		}
		fprintf(f,"\n");				// Retour a la ligne
	}
	fclose(f);

}


Matrice lectureMatrice(char * nomfichier){
	int dim;
	FILE* f = fopen(nomfichier, "r");				// Ouverture du fichier
	if(f == NULL) {						// Verification que le fichier a ete ouvert correctement
		printf("Erreur: Impossible d'ouvrir le fichier");
		exit(1);
	}

	fscanf ( f , "%d\n", & dim );
	Matrice mat= creerMatrice(dim);
	for(int i=0; i<=dim; i++){
        for(int j=0;j<=dim-i; j++){
            fscanf(f,"%lf",&(mat.tab[i][j]));
        }
	}
	fclose(f);
	return mat;
}


int ecritureMatricebin(char *nomfichierbin, Matrice mat){

    FILE *fbin = fopen(nomfichierbin, "wb");

    // Controle si le fichier s'est bien ouvert
    if (fbin == NULL){
        printf("Erreur d'ouverture: %s \n",nomfichierbin);
        return 0;
    }else{

        fwrite ( &mat.N , sizeof (int) , 1 , fbin );         // Ecrit l'ordre de la matrice

	/*
        int q;
        for (q = 0; q <=mat.N; q++){
            fwrite ( &mat.tab[q] , sizeof (double) , mat.N+1 , fbin );      // Ecrit la matrice ligne par ligne
        } //*/

        fwrite ( &mat.tab[0] , sizeof (double) , (mat.N+1)*(mat.N+1) , fbin );

        // Fermeture du fichier
        fclose(fbin);
        return 1;
    }
}


Matrice lectureMatricebin(char *nomfichierbin){

    FILE *fbin = fopen(nomfichierbin, "rb");

    if (fbin == NULL){
        printf("Erreur d'ouverture: %s \n",nomfichierbin);
        return creerMatrice(0);
    }else{

        int N;

        fread ( &N , sizeof (int) , 1 , fbin );                    // Ecrit l'ordre de la matrice

        Matrice mat = creerMatrice(N);

        /*
        int q;
        for (q = 0; q <=mat.N; q++){
            fread ( &mat.tab[q] , sizeof (double) , mat.N+1 , fbin );    // Lit la matrice ligne par ligne
        } //*/

        fread ( &mat.tab[0] , sizeof (double) , (mat.N+1)*(mat.N+1) , fbin );    // Lit la matrice ligne par ligne

        // Fermeture du fichier
        fclose(fbin);
        return mat;
    }
}


void lire(char* chemin){
    char *enter = NULL;
    char temp[100] = ""; /* Chaine de caracteres temporaire contenant la saisie de l'utilisateur. */

    fgets(temp, 99, stdin);

    enter = strchr(temp, '\n');
    if (enter != NULL)
        *enter = '\0';

    strcat(chemin, temp); /* On ajoute a la suite le nom du dossier */
}


void lirebmpDossier(char* chemin, DIR* rep){
    struct dirent* ent = NULL;

    printf(" -- Lecture des images bmp du dossier '%s' -- \n", chemin);

    while ((ent = readdir(rep)) != NULL){ /* Lecture du dossier. */
        if (isbmp(ent->d_name)){
            printf(" -> %s\n", ent->d_name);
        }
    }
}
