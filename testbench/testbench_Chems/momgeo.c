#include "momgeo.h"

#define N 10

int main() {
	// Lecture Image Binaire
	
	BmpImg test = readBmpImage("ImageBinaire.bmp");
	
	// Calcul des moments
	// Stockage des résultats dans une variable mat
	
	long double** mat = mom(&test, N); 
	
	// Ecriture des moments dans un fichier text
	
	Ecriture_Moments("Moment_Geometriques_en_C.txt",mat, N, N);	
	
	// Ecriture de l'image lue dans un fichier BMP
	
	writeBmpImage("ImageBinaireEcrit.bmp", &test);	
	
	// Désallocation de l'image lue
	
	freeBmpImg(&test); 	
	
	// Désallocation de la matrice des moments
	
	freemat(&mat, N);	

	return 0;
}

// Fonction désallocation d'une matrice

void freemat( long double*** pmat, int dimY) {
	
	/* On a besoin de déréférencer le pointeur pmat pour désallouer la matrice elle même
	 * et non pas une copie locale de la matrice
	 */
	for(int i = 0; i < dimY; i++) {				// Boucle sur les lignes
		free((*pmat)[i]);				// Désallocation de la ligne
		(*pmat)[i] = NULL;				// Mise à NULL
	}
	free(*pmat);						// Désallocation de la matrice
	*pmat = NULL;						// Mise à NULL;
}

// Fonction de l'allocation de la matrice

long double** alloc(int x, int y) {
	long double** mat = calloc(x, sizeof(long double)); 	// Allocation des lignes
	for(int i = 0; i < x; i++){ 				// Boucle sur le nombre de lignes
		mat[i] = calloc(y, sizeof(long double));	// Allocation des colonnes
	}
	return mat; 						// Return la matrice
}



// Fonction calcul des moments géométriques

long double** mom(BmpImg* pic, int n) {
	long double** mat = alloc(n,n);				// Allocation de la matrice
	/* On calcule les moments pour tout p,q tel que p+q < N
	 * Alors on aura N lignes
	 * à chaque ligne i, le nombre de colonnes sera N - i
	 * On obtiendra alors une matrice triangulaire inversé
	 */
	for(int p = 0; p < n; p++) {			
		for(int q = 0; q < n-p; q++) {			
			mat[p][q] = 0;				// Initialisation à 0, je fais pas confiance au calloc;
			// Boucle sur les pixels de l'image
			for(int x = 0; x < pic->dimX; x++){
				for(int y = 0; y < pic->dimY; y++) {
					if(getPixel(*pic, x,y) != 0)	// Vérification que le pixel est non nul
						mat[p][q] += pow(x,p)*pow(y,q);	// somme
				}
				

			}
				printf("M[%d][%d] = %.0LF\n", p, q, mat[p][q]); // Affichage du terme (juste pour vérifier avec le fichier écrit) 
		}	
		
	}
	return mat;
}


// Fonction écriture des moments géométriques dans un fichier text
void Ecriture_Moments(char* fname,  long double** mat, int dimX, int dimY){
	FILE* f = fopen(fname, "w");				// Ouverture du fichier
	if(f == NULL) {						// Vérification que le fichier à été ouvert correctement
		printf("Erreur: Impossible d'ouvrir le fichier");
		exit(1);
	}

	for(int i = 0; i < dimX; i++) {
		for(int j = 0; j < dimY-i; j++) {			
				fprintf(f,"\t%.0LF\t", mat[i][j]);	// Ecriture du terme
		}
		fprintf(f,"\n");				// Retour à la ligne
	}
	fclose(f);
}

