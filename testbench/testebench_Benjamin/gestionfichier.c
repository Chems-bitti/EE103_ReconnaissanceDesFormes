#include "gestionfichier.h"

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
        for (q = 0; q <=mat.N; q++){
            fwrite ( &mat.tab[q] , sizeof (double) , mat.N+1 , fbin );      // Ecrit la matrice ligne par ligne
        }

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
        for (q = 0; q <=mat.N; q++){
            fread ( &mat.tab[q] , sizeof (double) , mat.N+1 , fbin );    // Lit la matrice ligne par ligne
        }

        // Fermeture du fichier
        fclose(fbin);
        return mat;
    }
}



