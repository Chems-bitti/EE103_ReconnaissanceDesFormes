#include "gestionfichier.h"


int ecritureMatricebin(char *nomfichierbin, Matrice mat){

    FILE *fbin = fopen(nomfichierbin, "wb");

    // Controle si le fichier s'est bien ouvert
    if (fbin == NULL){
        printf("Erreur d'ouverture: %s \n",nomfichierbin);
        return 0;
    }else{

        fwrite ( &mat.num , sizeof (int) , 1 , fbin );                  // Ecrit le numero de la matrice
        fwrite ( &mat.N , sizeof (int) , 1 , fbin );                    // Ecrit l'ordre de la matrice
        fwrite ( &mat.tab[0] , sizeof (double) , (mat.N+1)*(mat.N+1) , fbin );    // Ecrit la matrice

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

        printf("le num %d, le N %d\n", num, N);

        Matrice mat = creerMatrice(num,N);

        fread ( &mat.tab[0] , sizeof (double) , (mat.N+1)*(mat.N+1) , fbin );    // Ecrit la matrice

        // Fermeture du fichier
        fclose(fbin);
        return mat;
    }
}



