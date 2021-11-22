#include "myBmpGris.h"
#include <math.h>

// structure Pixel
// Contient coordonné du pixel non nul

typedef struct pix{
	double x, y;
	struct pix* next;
}Pix;

// Fonction de création d'une maille du pixel
// crée une maille et effectue un chainage arrière
Pix* creermaille(Pix* root) {
	Pix* maille = malloc(sizeof(Pix));
	maille->x = 0; maille->y = 0; maille->next = NULL;
	Pix* current = root;
	while(current -> next != NULL) {
		current = current -> next;
	}
	current -> next = maille;
	return maille;
}

// Fonction de suppression de la liste
void suppListe(Pix* root) {
	Pix* current = root, *temp = root->next;
	while(current -> next != NULL) {
		free(current);
		current = temp;
		temp = temp->next;
	}
	free(current);
}

// Fonction d'allocation d'une matrice de taille x et y
double** alloc(int x, int y) {
	double** mat = calloc(y, sizeof(int*));
	for(int i = 0; i < x; i++) {
		mat[i] = calloc(x, sizeof(int));
	}
	return mat;
}

// Fonction désallocation matrice
void freemat(double*** mat, int y, int x) {
	for(int i = 0; i < y; i++) 
		free(*mat[i]);
	free(*mat);
}

// Fonction de calcul de omega int
void calint(BmpImg* pic, Pix* root) {
	Pix* current  = root;
	for(int i = 0; i < pic->dimX; i++) {
		for(int j = 0; j < pic->dimY; j++) {
			if(getPixel(*pic, i, j) > 0) {
				Pix* new = creermaille(root);
				new->x = (double)i; new->y = (double)j;
			}
		}
	}
}

double** mom(Pix* root, BmpImg* pic, int N) {
	Pix* current = root;
	double** mat = alloc(N, N);
	for(int p = 0; p < N; p++) {
		for(int q = p; q < N; q++) {
			double x = current->x, y = current->y;
			while(current->next != NULL) {
				mat[p][q] += pow(x,p)*pow(y,q)*getPixel(*pic, x, y);
				current = current->next;
			}
			mat[p][q] += pow(x,p)*pow(y,q)*getPixel(*pic, x, y);
		}
	}
	return mat;
}

void truc(char* fname, double** mat, int dimX, int dimY) {
	FILE* f = fopen(fname, "w");
	for(int i = 0; i < dimX; i++) {
		for(int j = 0; j < dimY; j++) {
			if(mat[i][j] != 0) 
				fprintf(f, "%.0f\t", mat[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}


int main() {
	Pix* root = malloc(sizeof(Pix));
	root->x = 0; root->y = 0; root->next = NULL;
	BmpImg test = readBmpImage("test.bmp");
	calint(&test, root);
	double** mat = mom(root, &test, 10);
	truc("truc.txt", mat, test.dimX, test.dimY);
	writeBmpImage("test2.bmp", &test);
	freeBmpImg(&test);
	suppListe(root);
	freemat(&mat, 10, 10);
	return 0;
}

