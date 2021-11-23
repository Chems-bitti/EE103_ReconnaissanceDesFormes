#include "gestionfichier.h"


int ecritureMatrice(char * nomfichier, Matrice mat, int TypeEcriture){


    FILE *ftxt = fopen( nomfichier, "a" );
    return 0;

}


int ecritureMatricebin(char * nomfichierbin, Matrice mat, int TypeEcriture){

    // Choisi le bon type d'ouverture du fichier
    if TypeEcriture{
        FILE *fbin = fopen(nomfichierbin, "wb");
    }else{
        FILE *fbin = fopen(nomfichierbin, "ab");
    }

    // Controle si le fichier s'est bien ouvert
    if fbin == NULL{
        printf("Erreur d'ouverture: %s \n",nomfichierbin);
        return 0;
    }else{

        fwrite ( &mat.num , sizeof (int) , 1 , fBin );                  // Ecrit le numero de la matrice
        fwrite ( &mat.N , sizeof (int) , 1 , fBin );                    // Ecrit l'ordre de la matrice
        fwrite ( &mat.tab , sizeof (double) , pow(mat.N,2) , fBin );    // Ecrit la matrice

        // Fermeture du fichier
        fclose(fbin);
        return 1;
    }
}






