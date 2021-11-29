#include "gestionfichier.h"


int ecritureMatrice(char * nomfichier, Matrice mat, int TypeEcriture){

    FILE *ftxt = fopen( nomfichier, "a" );
    return 0;

}


int ecritureMatricebin(char *nomfichierbin, Matrice mat, int TypeEcriture){

    //if (TypeEcriture){
        FILE *fbin = fopen(nomfichierbin, "ab");
    //}else{
        //FILE *fbin = fopen(nomfichierbin, "wb");
    //}

    // Controle si le fichier s'est bien ouvert
    if (fbin == NULL){
        printf("Erreur d'ouverture: %s \n",nomfichierbin);
        return 0;
    }else{

        fwrite ( &mat.num , sizeof (int) , 1 , fbin );                  // Ecrit le numero de la matrice
        fwrite ( &mat.N , sizeof (int) , 1 , fbin );                    // Ecrit l'ordre de la matrice
        fwrite ( &mat.tab , sizeof (double) , pow(mat.N,2) , fbin );    // Ecrit la matrice

        // Fermeture du fichier
        fclose(fbin);
        return 1;
    }
}






