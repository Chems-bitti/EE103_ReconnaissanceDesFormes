#include "gestionfichier.h"

int ecritureMatrice(char * fname, Matrice mat){
	
	FILE* f = fopen(fname, "w");				// Ouverture du fichier
	if(f == NULL) {						// Vérification que le fichier à été ouvert correctement
		printf("Erreur: Impossible d'ouvrir le fichier");
		exit(1);
	}

	for(int i = 0; i < mat.N; i++) {
		for(int j = 0; j < mat.N-i; j++) {			
				fprintf(f,"%le\t", mat.tab[i][j]);	// Ecriture du terme
		}
		fprintf(f,"\n");				// Retour à la ligne
	}
	fclose(f);
	
}

Matrice lectureMatrice(char * nomfichier){
	int dim;
	FILE* f = fopen(nomfichier, "r");				// Ouverture du fichier
	if(f == NULL) {						// Vérification que le fichier à été ouvert correctement
		printf("Erreur: Impossible d'ouvrir le fichier");
		exit(1);
	}

	fscanf ( f , "%d\n", & dim );
	Matrice mat= creerMatrice(dim);
	for(int i=0; i<dim; i++){
        for(int j=0;j<dim-i; j++){
            fscanf(f,"%f",mat.tab[i][j]);
        }
	}
	fclose(f);
}

int ecritureMatricebin(char *nomfichierbin, Matrice mat){

    FILE *fbin = fopen(nomfichierbin, "wb");

    // Controle si le fichier s'est bien ouvert
    if (fbin == NULL){
        printf("Erreur d'ouverture: %s \n",nomfichierbin);
        return 0;
    }else{

        fwrite ( &mat.num , sizeof (int) , 1 , fbin );                              // Ecrit le numero de la matrice
        fwrite ( &mat.N , sizeof (int) , 1 , fbin );                                // Ecrit l'ordre de la matrice

        int q;
        /*/
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
        return creerMatrice(0,0);
    }else{

        int num, N;

        fread ( &num , sizeof (int) , 1 , fbin );                  // Ecrit le numero de la matrice
        fread ( &N , sizeof (int) , 1 , fbin );                    // Ecrit l'ordre de la matrice

        Matrice mat = creerMatrice(num,N);

        int q;
        /*
        for (q = 0; q <=mat.N; q++){
            fread ( &mat.tab[q] , sizeof (double) , mat.N+1 , fbin );    // Lit la matrice ligne par ligne
        } //*/

        fread ( &mat.tab[0] , sizeof (double) , (mat.N+1)*(mat.N+1) , fbin );    // Lit la matrice ligne par ligne

        // Fermeture du fichier
        fclose(fbin);
        return mat;
    }
}

