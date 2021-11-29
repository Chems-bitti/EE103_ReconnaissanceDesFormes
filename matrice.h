#ifndef _matrice_h_
#define _matrice_h_

// Bibliotheques
#include <stdio.h>
#include <stdlib.h>

// d�claration de la structure Matrice
typedef struct {
    int num;            // Num�ro de la matrice pour l'identifier
    int N;              // Ordre de la Matrice
    double **tab        // Tableau avec les valeurs de la matrice
} Matrice;

/** Creation d'une matrice
  * @param num numero de la matrice
  * @param N ordre de la matrice
  * @return matrice
  */
Matrice creerMatrice(int num, int N);

/** Suppression d'une matrice
  * @param *mat adresse de la matrice a supprimer
  */
void supprMatrice(Matrice *mat);

/** Affiche le contenu d'une Matrice
  * Les deux premiers entier sont pour le num�ro et l'ordre de la matrice, le tableau en deux dimension pour les valeurs
  * @param mat La matrice a afficher
  */
void afficheMatrice(Matrice mat);

#endif
