

#include "test.h"
#include "image.h"
#include "matrice.h"
#include "gestionfichier.h"
#include "base2donnee.h"

#define fichierbin "base_de_donnee/matrice/fichierbin.bin"
#define basedonne "donnees/"

#define N 4

int main(){


    Matrice mat1 = creerMatrice(4,N);

    // remplissage de matrice
    //*
    int p,q;
    for(p = 0 ; p <= N; p++){
        for(q = 0 ; q <= N; q++){
            mat1.tab[p][q] = (p + q + 1);
        }
    }//*/

    //*
    mat1.tab[0][2] = 10;
    mat1.tab[2][2] = 7;
    mat1.tab[2][0] = 1563;
    mat1.tab[N][N] = -1000.000001;//*/

    //*
    printf("--Partie 1.1\n");
    afficheMatrice(mat1);
    printf("--Partie 1.2\n");
    ecritureMatricebin(fichierbin, mat1);
    printf("--Partie 1.3\n");
    supprMatrice(&mat1);

    printf("--Partie 2.1\n");
    Matrice mat2 = lectureMatricebin(fichierbin);
    printf("--Partie 2.2\n");
    afficheMatrice(mat2);
    printf("--Partie 2.3\n");
    supprMatrice(&mat2);
    //*/


    printf("fin\n");
    return 0;
}
