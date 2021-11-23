#include "momgeo.h"

#define N 5

int main() {
//	Pix* root = malloc(sizeof(Pix));
//	root->x = 0; root->y = 0; root->next = NULL;
	BmpImg test = readBmpImage("testpaint2.bmp"); // Lecture de l'image
	//calint(&test, root);
	 double** mat = mom(&test, N); // Calcul des moment géométriques
	truc("truc.txt",mat, N, N); // écriture des moments dans un fichier
	//afficherliste(root);
	writeBmpImage("test2.bmp", &test); // écriture de l'image vers un autre ficheir 
	freeBmpImg(&test); // désallocation de l'image
	//freeListe(root);
	//freemat(&mat, 10); //fonction de désallocation de la matrice (marche pas)
	return 0;
}


void freemat( double*** mat, int dimY) {
	for(int i = 0; i < dimY; i++) {
		free((*mat)[i]);
		(*mat)[i] = NULL;
	}
	free(*mat);
	*mat = NULL;
}

// Fonction de l'allocation de la matrice
 	double** alloc(int x, int y) {
	double** mat = calloc(y, sizeof(int*));
	for(int i = 0; i < x; i++) 
		mat[i] = calloc(x, sizeof(int));
	return mat;
}

// Fonction de désallocation de la liste chainée
void freeListe(Pix* root) {
	Pix* current = root, *temp = root->next;
	while(temp->next != NULL) {
		free(current);
		current = temp;
		temp = temp->next;
	}
	free(temp);
}

// Fonction de création d'une maille
Pix* creermaille(Pix* root) {
	Pix* maille = malloc(sizeof(Pix));
	maille->x = 0;
	maille->y = 0;
	maille->next = NULL;
	Pix* current  = root;
	while(current -> next != NULL) 
		current = current -> next;
	current -> next = maille;
	return maille;
}

// Fonction calcul région non nulle de l'image
void calint(BmpImg* pic, Pix* root) {
	Pix* current = root;
	for(int i = 0; i < pic->dimX;i++) {
		for(int j = 0; j < pic->dimY; j++){
			if(getPixel(*pic, i, j) > 0){
				Pix* new = creermaille(root);
				new->x = i;
				new->y = j;
				current = current -> next;
			}
		}
	}	
}


// Fonction calcul des moments géométriques
 double** mom(BmpImg* pic, int n) {
	 double** mat = alloc(n,n);
	for(int p = 0; p < n; p++) {
		for(int q = p; q < n; q++) {
			mat[p][q] = 0;
			for(int x = 0; x < pic->dimX; x++){
				for(int y = 0; y < pic->dimY; y++) {
				mat[p][q] += pow(x,p)*pow(y,q)*getPixel(*pic, x,y);
				}

			}
		}	

	return mat;
	}
}

// Fonction de l'affichage d'une liste chainée
void afficherliste(Pix* root){
	Pix* current = root;
	while(current->next != NULL){
		printf("P: %p\tx:%d\ty:%d\n",current,current->x,current->y);
		current = current -> next;
	}
	
	printf("P: %p\tx:%d\ty:%d\n",current,current->x,current->y);
	
}


// Fonction écriture des moments géométriques dans un fichier text
void truc(char* fname,  double** mat, int dimX, int dimY){
	FILE* f = fopen(fname, "w");
	if(f == NULL) {
		printf("Erreur: Impossible d'ouvrir le fichier");
		exit(1);
	}
	for(int i = 0; i < dimX; i++) {
		for(int j = 0; j < dimY; j++) {
				fprintf(f,"\t%.0f\t", mat[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}


